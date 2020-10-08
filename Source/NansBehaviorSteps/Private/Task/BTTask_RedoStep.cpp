// Fill out your copyright notice in the Description page of Project Settings.

#include "Task/BTTask_RedoStep.h"

#include "BTSteps.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

EBTNodeResult::Type UBTTask_RedoStep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepsHandlerObject", "Step Handler must implements IBTStepsHandler!"));
		return EBTNodeResult::Aborted;
	}

	if (StepToGo == 0)
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepNumber", "Invalid step number (need to be > 0) in "));
		return EBTNodeResult::Aborted;
	}

	IBTStepsHandler::Execute_RedoStep(BTSteps, StepToGo, false);

	return EBTNodeResult::Succeeded;
}

FString UBTTask_RedoStep::GetStaticDescription() const
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
FName UBTTask_RedoStep::GetNodeIconName() const
{
	// TODO import my own icon
	return FName("BTEditor.Graph.BTNode.Task.Wait.Icon");
}
#endif	  // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
