// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BTSteps.generated.h"

/**
 */
UCLASS(BlueprintType)
class NANSBEHAVIORSTEPS_API UBTSteps : public UObject
{
	GENERATED_BODY()

public:
	UBTSteps();
	~UBTSteps();

	UFUNCTION(BlueprintCallable, Category = "Step")
	void AddFinishedStep(int32 Step);

	UFUNCTION(BlueprintCallable, Category = "Step")
	void FinishedCurrentStep();

	UFUNCTION(BlueprintCallable, Category = "Step")
	void RedoStep(int32 Step, bool FromLastPlay = false);

	UFUNCTION(BlueprintCallable, Category = "Step")
	void JumpTo(int32 Step);

	UFUNCTION(BlueprintCallable, Category = "Step")
	bool StepIsAlreadyDone(const int32 Step) const;

	UFUNCTION(BlueprintCallable, Category = "Step")
	void Clear();

	UFUNCTION(BlueprintCallable, Category = "Step")
	bool StepCanPlay(const int32& Step);

	// If the step is the same as StepToGo, this method reset StepToGo to 0
	UFUNCTION(BlueprintCallable, Category = "Step")
	bool StepCanPlayAndReset(const int32& Step);

	UFUNCTION(BlueprintCallable, Category = "Step")
	bool PlayStepAndMoveForward(const int32& Step);

	int32 GetStepToGo();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Step")
	int32 StepToGo = 0;
	int32 CurrentStep = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Step")
	bool bDebug = false;

	TArray<int32> FinishedSteps;

private:
	bool IsStepPlayable(const int32& Step, const bool& ResetStepToGoIfPlay = true);
};
