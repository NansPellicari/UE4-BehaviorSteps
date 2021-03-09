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

#include "Task/BTTask_ConcludeAllSteps.h"

#include "BTStepsHandlerContainer.h"
#include "BTStepsLibrary.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

EBTNodeResult::Type UBTTask_ConcludeAllSteps::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UBTStepsHandlerContainer* BTSteps = Cast<UBTStepsHandlerContainer>(BlackboardComp->GetValueAsObject(StepsKeyName));

	if (BTSteps != nullptr)
	{
		UBTStepsLibrary::ConcludeAll(BTSteps);
		return EBTNodeResult::Succeeded;
	}

	EDITOR_ERROR(
		"BehaviorSteps",
		LOCTEXT("StepsHandlerNotInitiated", "The steps handler can not be retrieved from the blackboard")
	);
	return EBTNodeResult::Aborted;
}

FString UBTTask_ConcludeAllSteps::GetStaticDescription() const
{
	FString ReturnDesc;
	return ReturnDesc;
}

#if WITH_EDITOR
FName UBTTask_ConcludeAllSteps::GetNodeIconName() const
{
	// TODO import my own icon
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}
#endif	  // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
