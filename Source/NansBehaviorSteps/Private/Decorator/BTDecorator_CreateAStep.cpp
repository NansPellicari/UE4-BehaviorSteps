// Fill out your copyright notice in the Description page of Project Settings.

#include "Decorator/BTDecorator_CreateAStep.h"

#include "BTSteps.h"
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
	UBTSteps* BTSteps = Cast<UBTSteps>(BlackboardComp->GetValueAsObject(StepsKeyName));

	if (BTSteps == nullptr)
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepsKey", "Invalid key for Steps in "));
		return false;
	}
	if (Step == 0)
	{
		EDITOR_ERROR("BehaviorSteps", LOCTEXT("InvalidStepNumber", "Invalid step number (need to be > 0) in "));
		return false;
	}

	return BTSteps->PlayStepAndMoveForward(Step);
}

FString UBTDecorator_CreateAStep::GetStaticDescription() const
{
	// FString ReturnDesc = Super::GetStaticDescription();
	FString ReturnDesc;

	ReturnDesc += "Step: " + FString::FromInt(Step);
	ReturnDesc += "\nSteps Key Name: " + StepsKeyName.ToString();

	return ReturnDesc;
}

#undef LOCTEXT_NAMESPACE
