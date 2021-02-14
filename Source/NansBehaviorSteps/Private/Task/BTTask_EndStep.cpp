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

#include "Task/BTTask_EndStep.h"

#include "BTSteps.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

EBTNodeResult::Type UBTTask_EndStep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* BTSteps = BlackboardComp->GetValueAsObject(StepsKeyName);

	if (BTSteps == nullptr)
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepsKey", "Invalid key for Steps in "));
		return EBTNodeResult::Aborted;
	}

	if (!BTSteps->Implements<UBTStepsHandler>())
	{
		EDITOR_ERROR(
			"BehaviorSteps",
			LOCTEXT("InvalidStepsHandlerObject", "Step Handler must implements IBTStepsHandler!")
		);
		return EBTNodeResult::Aborted;
	}

	IBTStepsHandler::Execute_FinishedCurrentStep(BTSteps);

	return EBTNodeResult::Succeeded;
}

FString UBTTask_EndStep::GetStaticDescription() const
{
	FString ReturnDesc;
	return ReturnDesc;
}

#if WITH_EDITOR
FName UBTTask_EndStep::GetNodeIconName() const
{
	// TODO import my own icon
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}
#endif	  // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
