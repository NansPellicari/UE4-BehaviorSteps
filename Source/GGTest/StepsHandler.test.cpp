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

#include "StepsHandlerBase.h"


class NansBehaviorStepsStepsHandlerTest : public ::testing::Test
{
protected:
	void SetUp() override {}

	void TearDown() override {}

	bool bDebug = false;
};

TEST_F(NansBehaviorStepsStepsHandlerTest, ShouldPlaysStepByStep)
{
	TArray<FNStep> Steps = {FNStep(1), FNStep(2), FNStep(3), FNStep(4)};
	NStepsHandlerBase* StepsHandler = new NStepsHandlerBase();
	ASSERT_TRUE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[3]));
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[1])); // Cause step 1 is playing
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[3]));
	StepsHandler->FinishedCurrent(); // Step 1 end
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_TRUE(StepsHandler->CanPlay(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[3]));
	ASSERT_TRUE(StepsHandler->Play(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[3]));
	StepsHandler->FinishedCurrent(); // Step 2 end
	ASSERT_TRUE(StepsHandler->Play(Steps[2]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[3]));
	StepsHandler->FinishedCurrent(); // Step 3 end
	ASSERT_TRUE(StepsHandler->Play(Steps[3]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
}

TEST_F(NansBehaviorStepsStepsHandlerTest, ShouldPlaysStepByStepWithLabelOnly)
{
	TArray<FNStep> StepsLabelOnly = {
		FNStep(0, FName("label1")), FNStep(0, FName("label2")), FNStep(0, FName("label3")), FNStep(0, FName("label4"))
	};
	TArray<FNStep> Steps = {
		FNStep(1, StepsLabelOnly[0].Label),
		FNStep(2, StepsLabelOnly[1].Label),
		FNStep(3, StepsLabelOnly[2].Label),
		FNStep(4, StepsLabelOnly[3].Label)
	};
	NStepsHandlerBase* StepsHandler = new NStepsHandlerBase();
	// For now we can't use label only with CanPlay()
	ASSERT_TRUE(StepsHandler->CanPlay(StepsLabelOnly[0]));
	ASSERT_TRUE(StepsHandler->CanPlay(StepsLabelOnly[1]));
	ASSERT_TRUE(StepsHandler->CanPlay(StepsLabelOnly[2]));
	ASSERT_TRUE(StepsHandler->CanPlay(StepsLabelOnly[3]));
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
	ASSERT_TRUE(StepsHandler->IsPlaying(StepsLabelOnly[0]));
	StepsHandler->FinishedCurrent(); // Step 1 end
	ASSERT_TRUE(StepsHandler->Play(Steps[1]));
	ASSERT_TRUE(StepsHandler->IsPlaying(StepsLabelOnly[1]));
	StepsHandler->FinishedCurrent(); // Step 2 end
	ASSERT_TRUE(StepsHandler->Play(Steps[2]));
	ASSERT_TRUE(StepsHandler->IsPlaying(StepsLabelOnly[2]));
	StepsHandler->FinishedCurrent(); // Step 3 end
	ASSERT_TRUE(StepsHandler->Play(Steps[3]));
	ASSERT_TRUE(StepsHandler->IsPlaying(StepsLabelOnly[3]));
}

TEST_F(NansBehaviorStepsStepsHandlerTest, CanRedoStep)
{
	TArray<FNStep> Steps = {FNStep(1), FNStep(2), FNStep(3), FNStep(4)};
	NStepsHandlerBase* StepsHandler = new NStepsHandlerBase();
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
	StepsHandler->FinishedCurrent(); // Step 1 end
	ASSERT_TRUE(StepsHandler->Play(Steps[1]));
	StepsHandler->Redo(Steps[0]);
	StepsHandler->FinishedCurrent(); // Step 2 end
	ASSERT_TRUE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[3]));
	ASSERT_FALSE(StepsHandler->Play(Steps[1]));
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
	StepsHandler->FinishedCurrent(); // Step 1 end
	ASSERT_TRUE(StepsHandler->Play(Steps[1]));
	StepsHandler->FinishedCurrent(); // Step 2 end
	ASSERT_TRUE(StepsHandler->Play(Steps[2]));
	StepsHandler->FinishedCurrent(); // Step 3 end
	ASSERT_TRUE(StepsHandler->Play(Steps[3]));
	StepsHandler->FinishedCurrent(); // Step 4 end
}

TEST_F(NansBehaviorStepsStepsHandlerTest, CanRedoStepByLabel)
{
	TArray<FNStep> StepsLabelOnly = {
		FNStep(0, FName("label1")), FNStep(0, FName("label2")), FNStep(0, FName("label3")), FNStep(0, FName("label4"))
	};
	TArray<FNStep> Steps = {
		FNStep(1, StepsLabelOnly[0].Label),
		FNStep(2, StepsLabelOnly[1].Label),
		FNStep(3, StepsLabelOnly[2].Label),
		FNStep(4, StepsLabelOnly[3].Label)
	};
	NStepsHandlerBase* StepsHandler = new NStepsHandlerBase();
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
	StepsHandler->FinishedCurrent(); // Step 1 end
	ASSERT_TRUE(StepsHandler->Play(Steps[1]));
	StepsHandler->Redo(StepsLabelOnly[0]);
	StepsHandler->FinishedCurrent(); // Step 2 end
	ASSERT_TRUE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[3]));
	ASSERT_FALSE(StepsHandler->Play(Steps[1]));
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
	StepsHandler->FinishedCurrent(); // Step 1 end
	ASSERT_TRUE(StepsHandler->Play(Steps[1]));
	StepsHandler->FinishedCurrent(); // Step 2 end
	ASSERT_TRUE(StepsHandler->Play(Steps[2]));
	StepsHandler->FinishedCurrent(); // Step 3 end
	ASSERT_TRUE(StepsHandler->Play(Steps[3]));
	StepsHandler->FinishedCurrent(); // Step 4 end
}

TEST_F(NansBehaviorStepsStepsHandlerTest, CanRedoCurrentStep)
{
	TArray<FNStep> Steps = {FNStep(1), FNStep(2), FNStep(3), FNStep(4)};
	NStepsHandlerBase* StepsHandler = new NStepsHandlerBase();
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
	StepsHandler->Redo(Steps[0]);
	StepsHandler->FinishedCurrent(); // Step 1 end
	ASSERT_TRUE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[3]));
}

TEST_F(NansBehaviorStepsStepsHandlerTest, CanRedoCurrentStepByLabel)
{
	TArray<FNStep> StepsLabelOnly = {
		FNStep(0, FName("label1")), FNStep(0, FName("label2")), FNStep(0, FName("label3")), FNStep(0, FName("label4"))
	};
	TArray<FNStep> Steps = {
		FNStep(1, StepsLabelOnly[0].Label),
		FNStep(2, StepsLabelOnly[1].Label),
		FNStep(3, StepsLabelOnly[2].Label),
		FNStep(4, StepsLabelOnly[3].Label)
	};
	NStepsHandlerBase* StepsHandler = new NStepsHandlerBase();
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
	StepsHandler->Redo(StepsLabelOnly[0]);
	StepsHandler->FinishedCurrent(); // Step 1 end
	ASSERT_TRUE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[3]));
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
}

TEST_F(NansBehaviorStepsStepsHandlerTest, CanJumpTo)
{
	TArray<FNStep> Steps = {FNStep(1), FNStep(2), FNStep(3), FNStep(4)};
	NStepsHandlerBase* StepsHandler = new NStepsHandlerBase();
	ASSERT_TRUE(StepsHandler->Play(Steps[0]));
	StepsHandler->FinishedCurrent(); // Step 1 end
	ASSERT_TRUE(StepsHandler->Play(Steps[1]));
	StepsHandler->JumpTo(Steps[3]);
	StepsHandler->FinishedCurrent(); // Step 2 end
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[0]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[1]));
	ASSERT_FALSE(StepsHandler->CanPlay(Steps[2]));
	ASSERT_TRUE(StepsHandler->CanPlay(Steps[3]));
	ASSERT_FALSE(StepsHandler->Play(Steps[2]));
	ASSERT_TRUE(StepsHandler->Play(Steps[3]));
	StepsHandler->FinishedCurrent(); // Step 4 end
}
