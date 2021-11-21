// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LongDayCharacter.h"
#include "Blueprint/UserWidget.h"
#include "LocalGameControler.generated.h"

/**
 * 
 */
UCLASS()
class LONGDAY_API ALocalGameControler : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY()
	ALongDayCharacter * PlayChar;
	bool bIsVisibleDeathScreen = false;
public:

//  	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
//  	TSubclassOf<class UUserWidget> WidgetDeathScren;
// 
//  	// Variable to hold the widget After Creating it.
//  	UUserWidget * DeathScren;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
