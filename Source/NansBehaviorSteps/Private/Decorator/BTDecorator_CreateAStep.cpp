// Fill out your copyright notice in the Description page of Project Settings.

#include "Decorator/BTDecorator_CreateAStep.h"

#include "BTStepsHandler.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NansBehaviorStepsLog.h"
#include "NansUE4Utilities/public/Misc/ErrorUtils.h"

#define LOCTEXT_NAMESPACE "BehaviorSteps"

UBTDecorator_CreateAStep::UBTDecorator_CreateAStep(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Step";

	bNotifyTick = false;
	bTickIntervals = false;
}

bool UBTDecorator_CreateAStep::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (Step == 0)
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepNumber", "Invalid step number (need to be > 0) in "));
		return false;
	}

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

	return IBTStepsHandler::Execute_PlayStepAndMoveForward(BTSteps, Step);
}

FString UBTDecorator_CreateAStep::GetStaticDescription() const
{
	FString ReturnDesc;

	ReturnDesc += "Step: " + FString::FromInt(Step);
	ReturnDesc += "\nSteps Key Name: " + StepsKeyName.ToString();

	return ReturnDesc;
}

#undef LOCTEXT_NAMESPACE
