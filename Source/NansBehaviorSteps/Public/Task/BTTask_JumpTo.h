// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "BTTask_JumpTo.generated.h"

/**
 *
 */
UCLASS()
class NANSBEHAVIORSTEPS_API UBTTask_JumpTo : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = "Blackboard")
	FName StepsKeyName = FName("Steps");

	UPROPERTY(EditInstanceOnly, Category = "Step")
	int32 StepToGo = 0;

	UPROPERTY(EditInstanceOnly, Category = "Step")
	FName StepToGoLabel = NAME_None;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif	  // WITH_EDITOR
};
