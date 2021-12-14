// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LongDayCharacter.h"
#include "SpereDeath.h"
#include "Components/Widget.h"
#include "MiniMap.generated.h"

class SMiniMap;

UCLASS()
class LONGDAY_API UMiniMap : public UWidget
{
	GENERATED_BODY()

public:
	UMiniMap();
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	UPROPERTY(EditAnywhere, Category = "Player")
	ALongDayCharacter * Player;
	UPROPERTY(EditAnywhere, Category = "Enemy ")
	ASpereDeath * Enemy;
	
protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;
	UFUNCTION(BlueprintNativeEvent, Category = "Player")
	void NewPosition(FVector2D NewPositionVector);
	// UFUNCTION(BlueprintNativeEvent, Category = "Enemy")
	// void NewPositionEnemy(FString NameValue, FVector2D NewPosition);
	// UFUNCTION(BlueprintNativeEvent, Category = "Enemy")
	// void DeathEnemy(FString NameValue);
	
private:
	
	TSharedPtr<SMiniMap> Radar;
	//в угаре не придумал ничего лучше, чем два массива. хотя можно и нужно обойтись одним с 4 элементами, например сделать структурку
	//оставим решением на моей совести
	TArray<FVector2D> Border1;
	TArray<FVector2D> Border2;
	//набор хардкода, плохо, плохо
	float LocalSize = 400.0f;
	float MinX = - 1800.f;
	float MaxX = 1000.f;
	float MinY = - 1400.f;
	float MaxY = 1400.f;
	float CooX = (MaxX - MinX) / LocalSize;
	float CooY = (MaxY - MinY) / LocalSize;
};
