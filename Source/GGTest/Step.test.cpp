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

#include "CoreMinimal.h"
#include "gtest/gtest.h"

#include <iostream>

#include "Step.h"
#include "../../../../../UnrealEngine/Engine/Plugins/Animation/RigLogic/Source/RigLogicLibTest/Private/dnatests/Defs.h"


class NansBehaviorStepsStepTest : public ::testing::Test
{
protected:
	void SetUp() override {}

	void TearDown() override {}

	bool bDebug = false;
};

TEST_F(NansBehaviorStepsStepTest, TestShouldBeEqualEvenIfNameAreDifferents)
{
	FNStep Step1 = FNStep(1);
	FNStep Step2 = FNStep(1);
	Step2.Label = FName("Test");
	ASSERT_EQ(Step1, Step2);
	ASSERT_EQ(Step2, Step1);
}

TEST_F(NansBehaviorStepsStepTest, TestShouldBeEqualIfNameAreEquals)
{
	FNStep Step1 = FNStep(1);
	FNStep Step2 = FNStep();
	Step1.Label = FName("Test");
	Step2.Label = FName("Test");
	ASSERT_EQ(Step1, Step2);
	ASSERT_EQ(Step2, Step1);
}

TEST_F(NansBehaviorStepsStepTest, TestShouldBeInferiorOrGreaterIfIdsAre)
{
	{
		FNStep Step1 = FNStep(1);
		FNStep Step2 = FNStep(2);
		Step1.Label = FName("Test");
		ASSERT_LT(Step1, Step2);
		ASSERT_GT(Step2, Step1);
	}
	{
		FNStep Step1 = FNStep(1);
		FNStep Step2 = FNStep(2);
		FNStep Step3 = FNStep(2);
		Step2.Label = FName("Test");
		ASSERT_LT(Step1, Step2);
		ASSERT_GE(Step2, Step3);
		ASSERT_LE(Step2, Step3);
	}
}
