// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class LONGDAY_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHealthBar(float Value);
protected:
	UPROPERTY(meta=(BindWidget))
	class UProgressBar * HealthBar;
	//
};
