// Copyright 2020-present Nans Pellicari (nans.pellicari@gmail.com).
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

#include "IStepsHandler.h"
#include "StepsHandlerBase.h"


#include "BTStepsHandlerContainer.generated.h"


/**
 * Its goal is to contains the StepsHandler object.
 * This way it can be saved in a BehaviorTree key.
 * To call StepsHandler's functions, use the UBTStepsLibrary.
 */
UCLASS(BlueprintType)
class NANSBEHAVIORSTEPS_API UBTStepsHandlerContainer : public UObject
{
	GENERATED_BODY()
public:
	UBTStepsHandlerContainer()
	{
		Handler = MakeShareable(new NStepsHandlerBase());
	}


	virtual void BeginDestroy() override
	{
		if (Handler.IsValid())
		{
			Handler.Reset();
		}
		Super::BeginDestroy();
	}

	TSharedPtr<IStepsHandler> GetHandler() const
	{
		return Handler;
	}

protected:
	TSharedPtr<IStepsHandler> Handler;
};
