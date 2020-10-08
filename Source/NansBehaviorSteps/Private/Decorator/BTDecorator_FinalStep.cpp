// Fill out your copyright notice in the Description page of Project Settings.

#include "Decorator/BTDecorator_FinalStep.h"

#include "BTStepsHandler.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansBehaviorStepsLog.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTDecorator_FinalStep::UBTDecorator_FinalStep(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Final Step";

	bNotifyTick = false;
	bTickIntervals = false;
}

bool UBTDecorator_FinalStep::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	UObject* BTSteps = BlackboardComp->GetValueAsObject(StepsKeyName);
	if (BTSteps == nullptr)
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepsHandlerKey", "Invalid key for Steps in "));
		return false;
	}
	if (!BTSteps->Implements<UBTStepsHandler>())
	{
		EDITOR_ERROR(
			"BehaviorSteps", LOCTEXT("InvalidStepsHandlerClass", "Invalid class for Steps, should implements IBTStepsHandler"));
		return false;
	}
	int Step = -1;
	return IBTStepsHandler::Execute_StepIsPlayable(BTSteps, Step, false);
}

FString UBTDecorator_FinalStep::GetStaticDescription() const
{
	FString ReturnDesc;

	ReturnDesc += "Steps Key Name: " + StepsKeyName.ToString();

	return ReturnDesc;
}

#undef LOCTEXT_NAMESPACE
