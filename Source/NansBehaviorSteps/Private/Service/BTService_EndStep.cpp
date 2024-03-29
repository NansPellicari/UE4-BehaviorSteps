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

#include "Service/BTService_EndStep.h"

#include "BTStepsHandlerContainer.h"
#include "BTStepsLibrary.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTService_EndStep::UBTService_EndStep(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "End Step";

	bNotifyTick = false;
	bTickIntervals = false;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;
}

void UBTService_EndStep::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UBTStepsHandlerContainer* BTSteps = Cast<UBTStepsHandlerContainer>(BlackboardComp->GetValueAsObject(StepsKeyName));

	if (BTSteps != nullptr)
	{
		UBTStepsLibrary::FinishedCurrent(BTSteps);
		return;
	}

	EDITOR_ERROR(
		"BehaviorSteps",
		LOCTEXT("StepsHandlerNotInitiated", "The steps handler can not be retrieved from the blackboard")
	);
}

#undef LOCTEXT_NAMESPACE
