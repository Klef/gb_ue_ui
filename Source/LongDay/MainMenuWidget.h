// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralWidgetStyle.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Animation/WidgetAnimation.h"
#include "Components/CheckBox.h"
#include "Components/ComboBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
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
	class UButton * NewGameBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton * OptionsBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton * QuitBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton * ContinioBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton * MainBtn;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UWidgetSwitcher * OptionSwitcher;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UWidget* MainMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UWidget* OptionMenu;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UCheckBox * OptionHard;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UCheckBox * DarkBox;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class USlider  * OptionSound;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UComboBox  * OptionVideo;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * StartText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * OptionsText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * BackText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * DarkText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * HardText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * SoundText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * ResumeText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * MainText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * ExitText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock * RestartText;
	
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
	void OnDarkChange(bool bIsChecked);
	UFUNCTION()
	void OnSoundChange(float Value);

	UFUNCTION()
	void LoadTheme(FName ThemeName);
	
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
	void NativePreConstruct() override;

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FGeneralStyle MenuWidgetStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FName StyleName;
};


