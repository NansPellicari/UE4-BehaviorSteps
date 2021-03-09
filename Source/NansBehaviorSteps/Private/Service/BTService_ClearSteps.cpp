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

#include "Service/BTService_ClearSteps.h"


#include "AIController.h"
#include "BTStepsContainer.h"
#include "BTStepsLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTService_ClearSteps::UBTService_ClearSteps(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Clear Steps";

	bNotifyTick = false;
	bTickIntervals = false;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;
}

void UBTService_ClearSteps::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UBTStepsHandlerContainer* BTSteps = Cast<UBTStepsHandlerContainer>(BlackboardComp->GetValueAsObject(StepsKeyName));

	if (IsValid(BTSteps) && BTSteps->IsA<UBTStepsHandlerContainer>())
	{
		UBTStepsLibrary::ClearStepsHandler(BTSteps);
		AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn<AActor>();
		if (OwnerActor->Implements<UBTStepsContainer>())
		{
			IBTStepsContainer* OwnerStepsAware = Cast<IBTStepsContainer>(OwnerActor);
			OwnerStepsAware->RemoveBTSteps();
		}
		BlackboardComp->ClearValue(StepsKeyName);
	}
}

FString UBTService_ClearSteps::GetStaticDescription() const
{
	FString Desc;
	Desc += "Steps Key Name: " + StepsKeyName.ToString();

	return Desc;
}

#if WITH_EDITOR
FName UBTService_ClearSteps::GetNodeIconName() const
{
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}
#endif	  // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
