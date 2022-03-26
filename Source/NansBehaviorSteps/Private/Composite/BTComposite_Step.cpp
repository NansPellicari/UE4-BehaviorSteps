// Copyright 2020-present Nans Pellicari (nans.pellicari@gmail.com).
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Composite/BTComposite_Step.h"

#include "BTStepsLibrary.h"
#include "NansBehaviorStepsLog.h"
#include "StepsHandler.h"
#include "BTStepsSubsystem.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Misc/ErrorUtils.h"
#include "Misc/TextLibrary.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTComposite_Step::UBTComposite_Step()
{
	NodeName = "Step";
	bUseNodeActivationNotify = true;
	bUseNodeDeactivationNotify = true;
}

void UBTComposite_Step::FindStepsInChildren(const UBTCompositeNode* NodeToParse, int32& Num, int32 ParentNum,
	int32& FinalParentNum,
	bool& bBreak) const
{
	if (!IsValid(NodeToParse)) return;

	if (NodeToParse->GetExecutionIndex() == GetExecutionIndex() || bBreak)
	{
		FinalParentNum = ParentNum;
		if (bDebug) UE_LOG(LogBehaviorSteps, Warning, TEXT("%s is same execution or break"), *NodeToParse->NodeName);
		bBreak = true;
		return;
	}

	if (NodeToParse->GetClass()->IsChildOf(UBTCompositeNode::StaticClass()))
	{
		if (bDebug) UE_LOG(LogBehaviorSteps, Warning, TEXT("%s: Is composite"), *NodeToParse->NodeName);
		bool bIsStep = false;
		if (NodeToParse->GetClass()->IsChildOf(StaticClass()))
		{
			bIsStep = true;
			if (bDebug) UE_LOG(LogBehaviorSteps, Warning, TEXT("Is Step"));
			Num++;
			if (bDebug) UE_LOG(LogBehaviorSteps, Warning, TEXT("Has StepId: %i"), Num);
			if (bDebug) UE_LOG(LogBehaviorSteps, Warning, TEXT("Parent StepId: %i"), ParentNum);
		}
		if (NodeToParse->GetChildrenNum() > 1)
		{
			TArray<FBTCompositeChild> ChildrenList = NodeToParse->Children;
			if (bIsStep) ParentNum = Num;
			for (auto& Child : ChildrenList)
			{
				FindStepsInChildren(Child.ChildComposite, Num, ParentNum, FinalParentNum, bBreak);
				if (bDebug) UE_LOG(LogBehaviorSteps, Warning, TEXT("Break: %i"), bBreak);
				if (bBreak) break;
			}
		}
	}
}

void UBTComposite_Step::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	if (!IsValid(Asset.RootNode)) return;

	if (IsValid(GetWorld()) && GetWorld()->IsGameWorld())
	{
		if (bDebug) UE_LOG(
			LogBehaviorSteps,
			Log,
			TEXT(" In world %s"),
			*UNTextLibrary::WorldTypeToString(GetWorld()->WorldType)
		);
		return;
	}

	if (bDebug) UE_LOG(LogBehaviorSteps, Warning, TEXT(">>>>>> START: Seek Steps for %s (id: %i)"), *NodeName, Step.Id);
	int32 MyNum = 0;
	int32 ParentNum = 0;
	bool bBreak = false;
	FindStepsInChildren(Asset.RootNode, MyNum, 0, ParentNum, bBreak);
	Step.ParentId = ParentNum;
	Step.Id = MyNum + 1;
	if (bDebug) UE_LOG(LogBehaviorSteps, Warning, TEXT("<<<<<< END: for %s (id: %i)"), *NodeName, Step.Id);
}

void UBTComposite_Step::NotifyNodeActivation(FBehaviorTreeSearchData& SearchData) const {}

void UBTComposite_Step::NotifyNodeDeactivation(FBehaviorTreeSearchData& SearchData,
	EBTNodeResult::Type& NodeResult) const {}

int32 UBTComposite_Step::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild,
	EBTNodeResult::Type LastResult) const
{
	if (Step == 0)
	{
		EDITOR_ERROR(
			"BehaviorSteps",
			FText::Format(LOCTEXT("InvalidStepNumber", "Invalid step number \"{0}\" (need to be > 0) in "), Step.Id)
		);
		return BTSpecialChild::ReturnToParent;
	}

	const AAIController* AIOwner = SearchData.OwnerComp.GetAIOwner();
	const TSharedPtr<NStepsHandler>& BTSteps = UBTStepsLibrary::GetStepsSubsystem()->GetStepsHandler(AIOwner);
	if (!BTSteps.IsValid())
	{
		EDITOR_WARN(
			"BehaviorSteps",
			FText::Format(
				LOCTEXT("", "{0} Can't find the steps handler for current AI owner"),
				FText::FromString(ANSI_TO_TCHAR(__FUNCTION__))
			)
		);
		return BTSpecialChild::ReturnToParent;
	}

	if (!BTSteps->IsPlaying(Step)
		&& !BTSteps->Play(Step))
	{
		if (Step.ParentId > 0 && BTSteps->IsPlaying(FNStep(Step.ParentId)))
		{
			BTSteps->FinishedCurrent();
			BTSteps->Play(Step);
		}
		else
		{
			return BTSpecialChild::ReturnToParent;
		}
	}

	// ++++++++++++++++++++++++++++++++++++++++++
	// This to mimic the sequence or select node
	// bIsSequence: failure = quit
	// !bIsSequence: success = quit
	int32 NextChildIdx = BTSpecialChild::ReturnToParent;

	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		// newly activated: start from first
		NextChildIdx = 0;
	}
	else if (LastResult == (bIsSequence ? EBTNodeResult::Succeeded : EBTNodeResult::Failed) && (PrevChild + 1) <
			 GetChildrenNum())
	{
		// bIsSequence: success = choose next child
		// !bIsSequence: failed = choose next child
		NextChildIdx = PrevChild + 1;
	}
	// ------------------------------------------

	if (NextChildIdx == BTSpecialChild::ReturnToParent && BTSteps->IsPlaying(Step))
	{
		BTSteps->FinishedCurrent();
	}

	return NextChildIdx;
}

#if WITH_EDITOR

bool UBTComposite_Step::CanAbortLowerPriority() const
{
	// bIsSequence: don't allow aborting lower priorities, as it breaks sequence order and doesn't makes sense
	return bIsSequence ? false : true;
}

FName UBTComposite_Step::GetNodeIconName() const
{
	return bIsSequence
			   ? FName("BTEditor.Graph.BTNode.Composite.Sequence.Icon")
			   : FName("BTEditor.Graph.BTNode.Composite.Selector.Icon");
}

void UBTComposite_Step::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

FString UBTComposite_Step::GetStaticDescription() const
{
	FString Str;
	if (Step.ParentId > 0)
	{
		Str += FString::Printf(TEXT("%i > "), Step.ParentId);
	}
	Str += FString::Printf(TEXT("%i"), Step.Id);
	if (!Step.Label.IsNone())
	{
		Str += FString::Printf(TEXT(" [%s]"), *Step.Label.ToString());
	}
	return Str;
}

#endif
#undef LOCTEXT_NAMESPACE
