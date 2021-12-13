// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GeneralHUD.generated.h"

UENUM()
enum class EWidgetID : uint8
{
	Wid_MainMenu,
	Wid_PauseMenu,
	Wid_Death,
};

UCLASS()
class LONGDAY_API AGeneralHUD : public AHUD
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	AGeneralHUD();
	UFUNCTION(BlueprintCallable)
	UUserWidget * ShowWidget(const EWidgetID WidgetID, const int32 ZOrder = 0);
	UFUNCTION(BlueprintCallable)
	void HideWidget();
	UFUNCTION(BlueprintPure)
	UUserWidget * GetCurrentWidget() const { return CurrentWidget; }
protected:
	UUserWidget * CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder = 0);
	UPROPERTY(EditAnywhere)
	TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY()
	UUserWidget * CurrentWidget;
	UPROPERTY()
	APlayerController * PC;
};
