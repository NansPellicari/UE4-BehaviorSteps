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

#include "Step.generated.h"

USTRUCT(BlueprintType)
struct NANSBEHAVIORSTEPS_API FNStep
{
	GENERATED_USTRUCT_BODY()
	FNStep() {}
	FNStep(int32 InId) : Id(InId) {}

	FNStep(int32 InId, FName InLabel) : Id(InId),
										Label(InLabel) {}

	FNStep(int32 InId, FName InLabel, int32 InParentId) : Id(InId),
														  ParentId(InParentId),
														  Label(InLabel) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StepDefinition)
	int32 Id = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StepDefinition)
	int32 ParentId = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StepDefinition)
	FName Label = NAME_None;

	void Reset()
	{
		Id = 0;
		ParentId = 0;
		Label = NAME_None;
	}

	bool IsDefined() const
	{
		return Id > 0 || ParentId > 0 || !Label.IsNone();
	}

	FName GetLabel() const
	{
		if (Label == NAME_None && Id > 0)
		{
			FString StrName = FString("Step");
			StrName.AppendInt(Id);
			return FName(*StrName);
		}
		return Label;
	}

	FString ToString() const
	{
		FString Str = FString();
		Str += "[";
		if (Id > 0)
		{
			Str += "id: " + (ParentId > 0 ? FString::FromInt(ParentId) + " > " : "") + FString::FromInt(Id);
		}
		if (!Label.IsNone())
		{
			Str += Str.Len() > 1 ? TEXT(", ") : TEXT("");
			Str += TEXT("label: ") + Label.ToString();
		}
		Str += "]";
		return Str;
	}

	int32 operator+(const int32& RHS) const { return Id + RHS; }
	int32 operator-(const int32& RHS) const { return Id - RHS; }

	FNStep& operator=(const int32& RHS)
	{
		Id = RHS;
		if (RHS == 0)
		{
			Label = NAME_None;
		}
		return *this;
	}

	bool operator==(const int32& RHS) const { return Id == RHS; }
	bool operator!=(const int32& RHS) const { return Id != RHS; }
	bool operator<(const int32& RHS) const { return Id < RHS; }
	bool operator<=(const int32& RHS) const { return Id < RHS || Id == RHS; }
	bool operator>(const int32& RHS) const { return Id > RHS; }
	bool operator>=(const int32& RHS) const { return Id > RHS || Id == RHS; }

	bool operator==(const FNStep& RHS) const
	{
		if ((Id > 0 && Label.IsNone()) || (RHS.Id > 0 && RHS.Label.IsNone()))
		{
			return Id == RHS.Id;
		}
		if ((Id == 0 && !Label.IsNone()) || (RHS.Id == 0 && !RHS.Label.IsNone()))
		{
			return Label == RHS.Label;
		}
		return Id == RHS.Id && Label == RHS.Label;
	}

	bool operator!=(const FNStep& RHS) const { return !(*this == RHS); }
	bool operator<(const FNStep& RHS) const { return Id < RHS.Id; }
	bool operator<=(const FNStep& RHS) const { return Id < RHS.Id || Id == RHS.Id; }
	bool operator>(const FNStep& RHS) const { return Id > RHS.Id; }
	bool operator>=(const FNStep& RHS) const { return Id > RHS.Id || Id == RHS.Id; }
};
