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

#include "Service/BTService_JumpTo.h"

#include "BTStepsLibrary.h"
#include "StepsHandler.h"
#include "BTStepsSubsystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTService_JumpTo::UBTService_JumpTo(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Jump To";

	bNotifyTick = false;
	bTickIntervals = false;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;
}

void UBTService_JumpTo::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TSharedPtr<NStepsHandler>& StepsHandler = UBTStepsLibrary::GetStepsSubsystem(OwnerComp)
		->GetStepsHandler(OwnerComp.GetAIOwner());

	if (StepToGo == 0 && StepToGoLabel.IsNone())
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepNumber", "Invalid step number (need to be > 0) in "));
		return;
	}
	StepsHandler->JumpTo(FNStep(StepToGo, StepToGoLabel));
}

FString UBTService_JumpTo::GetStaticDescription() const
{
	return "\nStep To Go: " + FNStep(StepToGo, StepToGoLabel).ToString();
}

#if WITH_EDITOR
FName UBTService_JumpTo::GetNodeIconName() const
{
	// TODO import my own icon
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}
#endif	  // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
