// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "GeneralHUD.h"
#include "StyleSet.h"
#include "Kismet/GameplayStatics.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameBtn)
	{
		NewGameBtn->OnClicked.AddDynamic(this,
			&UMainMenuWidget::OnNewGameClicked);
		NewGameBtn->OnHovered.AddDynamic(this,
			&UMainMenuWidget::OnNewGameHovered);
		NewGameBtn->OnUnhovered.AddDynamic(this,
			&UMainMenuWidget::OnNewGameUnHovered);
	}
	if (OptionsBtn)
	{
		OptionsBtn->OnClicked.AddDynamic(this,
			&UMainMenuWidget::OnOptionsClicked);
		OptionsBtn->OnHovered.AddDynamic(this,
			&UMainMenuWidget::OnOptionsHovered);
		OptionsBtn->OnUnhovered.AddDynamic(this,
			&UMainMenuWidget::OnOptionsUnHovered);
	}
	if (QuitBtn)
	{
		QuitBtn->OnClicked.AddDynamic(this,
			&UMainMenuWidget::OnQuitClicked);
		QuitBtn->OnHovered.AddDynamic(this,
			&UMainMenuWidget::OnQuitHovered);
		QuitBtn->OnUnhovered.AddDynamic(this,
			&UMainMenuWidget::OnQuitUnHovered);
	}
	if (ContinioBtn)
	{
		ContinioBtn->OnClicked.AddDynamic(this,
			&UMainMenuWidget::OnContinioClicked);
		ContinioBtn->OnHovered.AddDynamic(this,
			&UMainMenuWidget::OnContinioHovered);
		ContinioBtn->OnUnhovered.AddDynamic(this,
			&UMainMenuWidget::OnContinioUnHovered);
	}
	if (MainBtn)
	{
		MainBtn->OnClicked.AddDynamic(this,
			&UMainMenuWidget::OnMainClicked);
		MainBtn->OnHovered.AddDynamic(this,
			&UMainMenuWidget::OnMainHovered);
		MainBtn->OnUnhovered.AddDynamic(this,
			&UMainMenuWidget::OnMainUnHovered);
	}
	if (OptionHard)
	{
		OptionHard->OnCheckStateChanged.AddDynamic(this,
			&UMainMenuWidget::OnHardChange);
	}
	if (DarkBox)
	{
		DarkBox->OnCheckStateChanged.AddDynamic(this,
			&UMainMenuWidget::OnDarkChange);
	}
	if (OptionSound)
	{
		OptionSound->OnValueChanged.AddDynamic(this,
			&UMainMenuWidget::OnSoundChange);
	}

}

void UMainMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	LoadTheme("DarkStyle");

}

inline void UMainMenuWidget::LoadTheme(FName ThemeName)
{
	MenuWidgetStyle = FStyleSet::Get().GetWidgetStyle<FGeneralStyle>(ThemeName);
	if (NewGameBtn)
	{
		NewGameBtn->WidgetStyle = MenuWidgetStyle.ButtonStyle;
	}
	if (OptionsBtn)
	{
		OptionsBtn->WidgetStyle = MenuWidgetStyle.ButtonStyle;
	}
	if (QuitBtn)
	{
		QuitBtn->WidgetStyle = MenuWidgetStyle.ButtonStyle;
	}
	if (ContinioBtn)
	{
		ContinioBtn->WidgetStyle = MenuWidgetStyle.ButtonStyle;
	}
	if (MainBtn)
	{
		MainBtn->WidgetStyle = MenuWidgetStyle.ButtonStyle;
	}
	if (OptionHard)
	{
		OptionHard->WidgetStyle = MenuWidgetStyle.CheckBoxStyle;
	}
	if (DarkBox)
	{
		DarkBox->WidgetStyle = MenuWidgetStyle.CheckBoxStyle;
	}
	if (OptionSound)
	{
		OptionSound->WidgetStyle = MenuWidgetStyle.SlyderStyle;
	}
	if (StartText)
	{
		StartText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		StartText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		StartText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}
	if (BackText)
	{
		BackText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		BackText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		BackText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}
	if (DarkText)
	{
		DarkText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		DarkText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		DarkText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}
	if (HardText)
	{
		HardText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		HardText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		HardText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}
	if (SoundText)
	{
		SoundText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		SoundText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		SoundText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}
	if (ResumeText)
	{
		ResumeText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		ResumeText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		ResumeText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}
	if (MainText)
	{
		MainText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		MainText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		MainText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}
	if (ExitText)
	{
		ExitText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		ExitText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		ExitText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}
	if (OptionsText)
	{
		OptionsText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		OptionsText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		OptionsText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}
	if (RestartText)
	{
		RestartText->SetColorAndOpacity(MenuWidgetStyle.TextStyle.ColorAndOpacity);
		RestartText->SetShadowColorAndOpacity(MenuWidgetStyle.TextStyle.ShadowColorAndOpacity);
		RestartText->SetFont(MenuWidgetStyle.TextStyle.Font);
	}

}

void UMainMenuWidget::OnNewGameHovered()
{
	if (NewGameBtnColor)
	{
		PlayAnimation(NewGameBtnColor);
	}
}
void UMainMenuWidget::OnNewGameUnHovered()
{
	if (NewGameBtnColor)
	{
			PlayAnimationReverse(NewGameBtnColor);
	}
}
void UMainMenuWidget::OnNewGameClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("New Game"));
	AGeneralHUD * GeneralHud = Cast<AGeneralHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	GeneralHud->HideWidget();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("LevelOne"));
}

void UMainMenuWidget::OnOptionsClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Options Game"));
	OptionSwitcher->SetActiveWidget(OptionMenu);
}

void UMainMenuWidget::OnOptionsHovered()
{
	if (OptionsBtnColor)
	{
		PlayAnimation(OptionsBtnColor);
	}
}

void UMainMenuWidget::OnOptionsUnHovered()
{
	if (OptionsBtnColor)
	{
		PlayAnimationReverse(OptionsBtnColor);
	}
}

void UMainMenuWidget::OnQuitHovered()
{
	if (QuitBtnColor)
	{
		PlayAnimation(QuitBtnColor);
	}
}

void UMainMenuWidget::OnQuitUnHovered()
{
	if (QuitBtnColor)
	{
		PlayAnimationReverse(QuitBtnColor);
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("ALL EXIT"));
	FGenericPlatformMisc::RequestExit(false);
}
void UMainMenuWidget::OnContinioHovered()
{
	if (ContinioBtnColor)
	{
		PlayAnimation(ContinioBtnColor);
	}
}

void UMainMenuWidget::OnContinioUnHovered()
{
	if (ContinioBtnColor)
	{
		PlayAnimationReverse(ContinioBtnColor);
	}
}

void UMainMenuWidget::OnMainClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Main Menu"));
	FString CurentLevel = GetWorld()->GetMapName();
	CurentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	if (CurentLevel == TEXT("MainMenu"))
	{
		OptionSwitcher->SetActiveWidget(MainMenu);
	}
	else
	{
		AGeneralHUD * GeneralHud = Cast<AGeneralHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		GeneralHud->HideWidget();
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
	}
}

void UMainMenuWidget::OnMainHovered()
{
	if (MainBtnColor)
	{
		PlayAnimation(MainBtnColor);
	}
}

void UMainMenuWidget::OnMainUnHovered()
{
	if (MainBtnColor)
	{
		PlayAnimationReverse(MainBtnColor);
	}
}

void UMainMenuWidget::OnHardChange(bool bIsChecked)
{
	if (bIsChecked)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Curent difficult level HARD"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Curent difficult level NORMAL"));
	}
}

void UMainMenuWidget::OnDarkChange(bool bIsChecked)
{
	if (bIsChecked)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Dark"));
		LoadTheme("DarkStyle");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Light"));
		LoadTheme("LightStyle");
	}
}

void UMainMenuWidget::OnSoundChange(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Current Sound Level %f"), Value));
}

void UMainMenuWidget::OnContinioClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("CONTINIO"));
	AGeneralHUD * GeneralHud = Cast<AGeneralHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	GeneralHud->HideWidget();
}
