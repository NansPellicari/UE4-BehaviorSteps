// Fill out your copyright notice in the Description page of Project Settings.

#include "Service/BTService_CreateStepsHandler.h"

#include "BTStepsHandler.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTService_CreateStepsHandler::UBTService_CreateStepsHandler(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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

	if (BTSteps != nullptr && BTSteps->Implements<UBTStepsHandler>())
	{
		return;
	}

	UObject* NewBTSteps = NewObject<UObject>(&OwnerComp, HandlerClass);
	BlackboardComp->SetValueAsObject(StepsKeyName, NewBTSteps);
}

#undef LOCTEXT_NAMESPACE
