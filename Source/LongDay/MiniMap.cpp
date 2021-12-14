// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniMap.h"
#include "SMiniMap.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "DrawDebugHelpers.h"


UMiniMap::UMiniMap()
{

	
}

void UMiniMap::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Radar.Reset();
}


TSharedRef<SWidget> UMiniMap::RebuildWidget()
{
	Player = Cast<ALongDayCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	if (Player)
	{
		Player->NewPositionPlayer.AddDynamic(this, &UMiniMap::NewPosition);
	}
	//Enemy->NewPositionEnemy.AddDynamic(this, &UMiniMap::NewPositionEnemy);
	// Enemy->DeathEnemy.AddDynamic(this, &UMiniMap::DeathEnemy);
	
	//
	//TArray<AActor *> Terra;
	//строим карту
	//на костылях
	
	
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("AI Vision Trace")), true, PlayerPawn);
	TraceParams.bReturnPhysicalMaterial = false;
	//X 1075,260498 -1874,739502
	//y 1475,056641 -1474,943359
	//TArray<FVector2D> Border;
	//Border.Add(LocalSize * FVector2D(0.f, 0.f));
	//GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams
	for (float x = MinX; x <= MaxX; ++x)
	{
		FHitResult HitResult;
		FVector TraceStart = FVector(x, -1400.0f, 150.0f);
		FVector TraceEnd = FVector(x, 1400.0f, 150.0f);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
		{
			if (Cast<AStaticMeshActor>(HitResult.Actor))
			{
				Border1.Add(FVector2D((x - MinX) / CooX, (HitResult.Location.Y - MinY) / CooY));
				GetWorld()->LineTraceSingleByChannel(HitResult, TraceEnd, TraceStart, ECC_Visibility, TraceParams);
				Border2.Add(FVector2D((x - MinX) / CooX, (HitResult.Location.Y - MinY) / CooY));
			}
		}
	
		
	}
	Radar = SNew(SMiniMap)
		.Border1(Border1)
		.Border2(Border2)
		;

	return Radar.ToSharedRef();
	
}

// void UMiniMap::NewPositionEnemy_Implementation(FString NameValue, FVector2D NewPosition)
// {
// 	Radar->SetEnemy(NameValue, FVector2D((NewPosition.X - MinX) / CooX, (NewPosition.Y - MinY) / CooY), true);
// }

// void UMiniMap::DeathEnemy_Implementation(FString NameValue)
// {
// 	Radar->SetEnemy(NameValue, FVector2D(0.0f, 0.0f), true);
// }


void UMiniMap::NewPosition_Implementation(FVector2D NewPositionVector)
{
	Radar->SetPlayerPosition(FVector2D((NewPositionVector.X - MinX) / CooX, (NewPositionVector.Y - MinY) / CooY));
}




