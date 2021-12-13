// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AGeneralHUD::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		PC = GetWorld()->GetFirstPlayerController();
	}
}

AGeneralHUD::AGeneralHUD()
{
}

UUserWidget* AGeneralHUD::ShowWidget(const EWidgetID WidgetID, const int32 ZOrder)
{
	HideWidget();
	TSubclassOf<UUserWidget> * ClassPtr = WidgetClasses.Find(WidgetID);
	///////
	
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Wert"));
	if (ClassPtr && *ClassPtr)
	{
		CreateWidgetByClass(* ClassPtr, ZOrder);
	}
	return CurrentWidget;
}

void AGeneralHUD::HideWidget()
{
	if (PC)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
		// PC, nullptr, EMouseLockMode::DoNotLock, false);
		PC->bShowMouseCursor = false;
		PC->SetPause(false);
	}
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}

UUserWidget* AGeneralHUD::CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder)
{
	if (PC)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
			PC, nullptr, EMouseLockMode::DoNotLock, false);
		PC->bShowMouseCursor = true;
		PC->SetPause(true);
	}
	CurrentWidget = CreateWidget(GetWorld(), WidgetClass);
	CurrentWidget->AddToViewport(ZOrder);
	return CurrentWidget;
}
