// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"

#include "BTService_JumpTo.generated.h"

/**
 *
 */
UCLASS()
class NANSBEHAVIORSTEPS_API UBTService_JumpTo : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = "Blackboard")
	FName StepsKeyName = FName("Steps");

	UPROPERTY(EditInstanceOnly, Category = "Step")
	int32 StepToGo = 0;

	UBTService_JumpTo(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif	  // WITH_EDITOR
};
