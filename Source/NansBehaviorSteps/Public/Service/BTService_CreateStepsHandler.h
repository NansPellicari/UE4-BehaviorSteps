// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BTSteps.h"
#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"

#include "BTService_CreateStepsHandler.generated.h"

/**
 *
 */
UCLASS()
class NANSBEHAVIORSTEPS_API UBTService_CreateStepsHandler : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = "Blackboard", meta = (MustImplement = "BTStepsHandler"))
	TSubclassOf<UObject> HandlerClass = UBTSteps::StaticClass();

	UPROPERTY(EditInstanceOnly, Category = "Blackboard")
	FName StepsKeyName = FName("Steps");

	UBTService_CreateStepsHandler(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
