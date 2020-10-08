// Fill out your copyright notice in the Description page of Project Settings.

#include "Service/BTService_RedoStep.h"

#include "BTSteps.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTService_RedoStep::UBTService_RedoStep(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Redo Step";

	bNotifyTick = false;
	bTickIntervals = false;
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = false;
}

void UBTService_RedoStep::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* BTSteps = BlackboardComp->GetValueAsObject(StepsKeyName);

	if (BTSteps == nullptr)
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepsKey", "Invalid key for Steps in "));
		return;
	}

	if (!BTSteps->Implements<UBTStepsHandler>())
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepsHandlerObject", "Step Handler must implements IBTStepsHandler!"));
		return;
	}

	if (StepToGo == 0)
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepNumber", "Invalid step number (need to be > 0) in "));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("%s - StepToGo: %d"), ANSI_TO_TCHAR(__FUNCTION__), StepToGo);

	IBTStepsHandler::Execute_RedoStep(BTSteps, StepToGo, false);
}

FString UBTService_RedoStep::GetStaticDescription() const
{
	FString ReturnDesc;

	if (!StepsKeyName.IsNone())
	{
		ReturnDesc += TEXT("Steps: ");
		ReturnDesc += StepsKeyName.ToString();
	}

	ReturnDesc += "\nStep To Go: " + FString::FromInt(StepToGo);

	return ReturnDesc;
}

#if WITH_EDITOR
FName UBTService_RedoStep::GetNodeIconName() const
{
	// TODO import my own icon
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}
#endif	  // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
