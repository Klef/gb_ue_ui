// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "GeneralHUD.h"
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
	if (OptionSound)
	{
		OptionSound->OnValueChanged.AddDynamic(this,
			&UMainMenuWidget::OnSoundChange);
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
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Curent difficult level HARD"));
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Curent difficult level NORMAL"));
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
