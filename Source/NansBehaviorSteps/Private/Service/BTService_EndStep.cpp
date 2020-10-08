// Fill out your copyright notice in the Description page of Project Settings.

#include "Service/BTService_EndStep.h"

#include "BTSteps.h"
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
	UObject* BTSteps = BlackboardComp->GetValueAsObject(StepsKeyName);

	if (BTSteps != nullptr && BTSteps->Implements<UBTStepsHandler>())
	{
		IBTStepsHandler::Execute_FinishedCurrentStep(BTSteps);
		return;
	}

	EDITOR_ERROR(
		"BehaviorSteps", LOCTEXT("StepsHandlerNotInitiated", "The steps handler can not be retrieved from the blackboard"));
}

#undef LOCTEXT_NAMESPACE
