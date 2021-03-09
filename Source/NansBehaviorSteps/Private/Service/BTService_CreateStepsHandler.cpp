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

#include "Service/BTService_CreateStepsHandler.h"

#include "AIController.h"
#include "BTStepsContainer.h"
#include "BTStepsHandlerContainer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTService_CreateStepsHandler::UBTService_CreateStepsHandler(const FObjectInitializer& ObjectInitializer) : Super(
	ObjectInitializer
)
{
	NodeName = "Create Steps Handler";

	bNotifyTick = false;
	bTickIntervals = false;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;
}

void UBTService_CreateStepsHandler::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* BTSteps = BlackboardComp->GetValueAsObject(StepsKeyName);

	if (IsValid(BTSteps) && BTSteps->IsA<UBTStepsHandlerContainer>())
	{
		return;
	}

	AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn<AActor>();
	if (!OwnerActor->Implements<UBTStepsContainer>())
	{
		EDITOR_ERROR(
			"BehaviorSteps",
			LOCTEXT("OwnerIsNotStepsHandlerAware", "The owner of the behavior tree should implements IBTStepsContainer")
		);
		OwnerComp.GetAIOwner()->GetBrainComponent()->StopLogic("Abort cause error");
		return;
	}
	IBTStepsContainer* OwnerStepsAware = Cast<IBTStepsContainer>(OwnerActor);
	UBTStepsHandlerContainer* NewBTSteps = NewObject<UBTStepsHandlerContainer>(OwnerActor, HandlerClass);
	OwnerStepsAware->SetBTSteps(NewBTSteps);
	BlackboardComp->SetValueAsObject(StepsKeyName, NewBTSteps);
}

#undef LOCTEXT_NAMESPACE
