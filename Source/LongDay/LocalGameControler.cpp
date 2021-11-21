// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalGameControler.h"
#include "Blueprint/UserWidget.h"

void ALocalGameControler::BeginPlay()
{
	Super::BeginPlay();
	PlayChar = Cast<ALongDayCharacter>(GetPawn());
// 	if (WidgetDeathScren)
// 	{
// 		DeathScren = CreateWidget<UUserWidget>(this, WidgetDeathScren);
// 		if (DeathScren)
// 		{
// 			DeathScren->AddToViewport();
// 		}
// 	}

}

void ALocalGameControler::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bIsVisibleDeathScreen && PlayChar->GetDeath())
	{
		bIsVisibleDeathScreen = true;

	}
}
