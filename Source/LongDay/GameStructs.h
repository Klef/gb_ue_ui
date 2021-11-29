#pragma once
#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "GameStructs.generated.h"

USTRUCT(BlueprintType)
struct FDamageData
{
	GENERATED_BODY()

	UPROPERTY()
	float DamageValue;

	UPROPERTY()
	class AActor* Instigator;

	UPROPERTY()
	class AActor* DamageMaker;
};