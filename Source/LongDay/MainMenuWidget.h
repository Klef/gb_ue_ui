// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Animation/WidgetAnimation.h"
#include "Components/CheckBox.h"
#include "Components/ComboBox.h"
#include "Components/Slider.h"
#include "Components/WidgetSwitcher.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class LONGDAY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UButton * NewGameBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UButton * OptionsBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UButton * QuitBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UButton * ContinioBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UButton * MainBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UWidgetSwitcher * OptionSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UWidget* MainMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UWidget* OptionMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UCheckBox * OptionHard;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	USlider  * OptionSound;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UComboBox  * OptionVideo;
	UFUNCTION()
	void OnNewGameClicked();
	UFUNCTION()
	void OnNewGameHovered();
	UFUNCTION()
	void OnNewGameUnHovered();
	UFUNCTION()
	void OnOptionsClicked();
	UFUNCTION()
	void OnOptionsHovered();
	UFUNCTION()
	void OnOptionsUnHovered();
	UFUNCTION()
	void OnQuitClicked();
	UFUNCTION()
	void OnQuitHovered();
	UFUNCTION()
	void OnQuitUnHovered();
	UFUNCTION()
	void OnContinioClicked();
	UFUNCTION()
	void OnContinioHovered();
	UFUNCTION()
	void OnContinioUnHovered();
	UFUNCTION()
	void OnMainClicked();
	UFUNCTION()
	void OnMainHovered();
	UFUNCTION()
	void OnMainUnHovered();
	UFUNCTION()
	void OnHardChange(bool bIsChecked);
	UFUNCTION()
	void OnSoundChange(float Value);
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation * NewGameBtnColor;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation * OptionsBtnColor;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation * QuitBtnColor;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation * ContinioBtnColor;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation * MainBtnColor;

public:
	void NativeConstruct() override;
};
