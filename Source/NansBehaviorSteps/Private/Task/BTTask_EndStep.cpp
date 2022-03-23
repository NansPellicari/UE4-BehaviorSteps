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

#include "BTStepsLibrary.h"
#include "StepsHandler.h"
#include "BTStepsSubsystem.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

EBTNodeResult::Type UBTTask_EndStep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TSharedPtr<NStepsHandler>& StepsHandler = UBTStepsLibrary::GetStepsSubsystem(OwnerComp)
		->GetStepsHandler(OwnerComp.GetAIOwner());

	StepsHandler->FinishedCurrent();

	return EBTNodeResult::Succeeded;
}

#if WITH_EDITOR
FName UBTTask_EndStep::GetNodeIconName() const
{
	// TODO import my own icon
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}
#endif	  // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
