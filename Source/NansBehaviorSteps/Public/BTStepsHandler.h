#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "BTStepsHandler.generated.h"

UINTERFACE(BlueprintType)
class NANSBEHAVIORSTEPS_API UBTStepsHandler : public UInterface
{
	GENERATED_BODY()
};

class NANSBEHAVIORSTEPS_API IBTStepsHandler
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	int32 GetCurrentStep();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void ConcludeAllSteps();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void FinishedCurrentStep();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void RedoStep(int32 Step, bool FromLastPlay = false);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void JumpTo(int32 Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepIsAlreadyDone(const int32 Step) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepCanPlay(const int32& Step);
	// If the step is the same as StepToGo, this method reset StepToGo to 0

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepCanPlayAndReset(const int32& Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool PlayStepAndMoveForward(const int32& Step);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	int32 GetStepToGo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	bool StepIsPlayable(const int32& Step, bool ResetStepToGoIfPlay = true);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "StepsHandler")
	void Clear();
};
