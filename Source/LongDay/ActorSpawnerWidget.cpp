// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UIPlayerController.h"


void UActorSpawnerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (DraggedText)
	{
		DraggedText->SetText(FText::FromString(DraggedName));
	}
}

void UActorSpawnerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AUIPlayerController * PC = 
		Cast<AUIPlayerController>(PlayerController);
	PC->OnMouseButtonUp.AddUObject(this, &UActorSpawnerWidget::OnMouseButtonUp);

}

void UActorSpawnerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (DraggedActor && PlayerController)
	{
		FVector WorldMouseLocation;
		FVector WorldMouseDirection;
		PlayerController->DeprojectMousePositionToWorld(
			WorldMouseLocation, WorldMouseDirection);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(DraggedActor);
		Params.AddIgnoredActor(PlayerController->GetPawn());
		FHitResult HitResult;
		float TraseDistance = 1000000.0f;
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			WorldMouseLocation,
			WorldMouseLocation + WorldMouseDirection * TraseDistance,
			ECollisionChannel::ECC_WorldStatic,
			Params);

		if (HitResult.Actor.Get())
		{
			DraggedActor->SetActorLocation(HitResult.Location);
		}
	}
}

FReply UActorSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		DraggedActor = GetWorld()->SpawnActor<AActor>(DraggedActorClass);
	}
	return FReply::Handled();

}

void UActorSpawnerWidget::OnMouseButtonUp()
{
	if (DraggedActor)
	{
		DraggedActor = nullptr;
	}

}
