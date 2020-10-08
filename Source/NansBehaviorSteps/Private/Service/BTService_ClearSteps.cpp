// Fill out your copyright notice in the Description page of Project Settings.

#include "Service/BTService_ClearSteps.h"

#include "AIController.h"
#include "BTSteps.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* BTSteps = BlackboardComp->GetValueAsObject(StepsKeyName);

	if (BTSteps != nullptr && BTSteps->Implements<UBTStepsHandler>())
	{
		IBTStepsHandler::Execute_Clear(BTSteps);

		return;
	}

	return;
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
