// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BTStepsHandler.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "BTSteps.generated.h"

/**
 */
UCLASS(BlueprintType)
class NANSBEHAVIORSTEPS_API UBTSteps : public UObject, public IBTStepsHandler
{
	GENERATED_BODY()

public:
	UBTSteps();
	virtual void BeginDestroy() override;

	void AddFinishedStep(int32 Step);

	virtual int32 GetCurrentStep_Implementation() override;
	virtual void ConcludeAllSteps_Implementation() override;
	virtual void FinishedCurrentStep_Implementation() override;
	virtual void RedoStep_Implementation(int32 Step, bool FromLastPlay = false) override;
	virtual void JumpTo_Implementation(int32 Step) override;
	virtual bool StepIsAlreadyDone_Implementation(const int32 Step) const override;
	virtual void Clear_Implementation() override;
	virtual bool StepCanPlay_Implementation(const int32& Step) override;
	// If the step is the same as StepToGo, this method reset StepToGo to 0
	virtual bool StepCanPlayAndReset_Implementation(const int32& Step) override;
	virtual bool PlayStepAndMoveForward_Implementation(const int32& Step) override;
	virtual bool StepIsPlayable_Implementation(const int32& Step, bool ResetStepToGoIfPlay = true) override;
	virtual int32 GetStepToGo_Implementation() override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Step")
	int32 StepToGo = 0;
	int32 CurrentStep = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Step")
	bool bDebug = false;

	TArray<int32> FinishedSteps;
};
