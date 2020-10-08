// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"

#include "BTDecorator_FinalStep.generated.h"

class UBTSteps;

/**
 *
 */
UCLASS()
class NANSBEHAVIORSTEPS_API UBTDecorator_FinalStep : public UBTDecorator
{
	GENERATED_BODY()

	UBTDecorator_FinalStep(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditInstanceOnly, Category = "Blackboard")
	FName StepsKeyName = FName("Steps");

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;
};
