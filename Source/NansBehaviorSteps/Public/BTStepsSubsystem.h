﻿// Copyright 2020-present Nans Pellicari (nans.pellicari@gmail.com).
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "CoreMinimal.h"

#include "BTStepsSubsystem.generated.h"

class AAIController;
class NStepsHandler;

/**
 * 
 */
UCLASS()
class NANSBEHAVIORSTEPS_API UBTStepsSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	TSharedPtr<NStepsHandler> CreateStepsHandler(const AAIController* Owner);
	TSharedPtr<NStepsHandler> GetStepsHandler(const AAIController* Owner) const;
	void RemoveStepsHandler(const AAIController* Owner);
private:
	TMap<const FString, TSharedPtr<NStepsHandler>> StepsHandlers;
};
