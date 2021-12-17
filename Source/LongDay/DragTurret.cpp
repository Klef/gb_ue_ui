// Fill out your copyright notice in the Description page of Project Settings.


#include "DragTurret.h"
#include "TurretDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "UIPlayerController.h"

void UDragTurret::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (TurretText)
	{
		TurretText->SetText(FText::FromString(TurretName));
	}

}

void UDragTurret::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AUIPlayerController * PC = Cast<AUIPlayerController>(PlayerController);
	PC->OnMouseButtonUp.AddUObject(this, &UDragTurret::OnMouseButtonUp);
}

void UDragTurret::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

void UDragTurret::OnMouseButtonUp()
{
	if (DraggedActor)
	{
		DraggedActor = nullptr;
	}
}

void UDragTurret::WidgetHovered()
{
	bIsInWidget = true;
}

void UDragTurret::WidgetUnHovered()
{
	bIsInWidget = false;
}

FReply UDragTurret::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		//THUS!
		UUserWidget * IsTest = this;
		DraggedActor = GetWorld()->SpawnActor<AActor>(DraggedActorClass);
		return FReply::Handled();
		//disable
		//return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
		
	}
	return FReply::Handled();
	
}

void UDragTurret::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UTurretDragDropOperation::StaticClass());
	UTurretDragDropOperation * TurretOperation = Cast<UTurretDragDropOperation>(OutOperation);
	if (TurretOperation)
	{
		TurretOperation->DefaultDragVisual = this;
		SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 0.7f));
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		TurretOperation->OnDragCancelled.AddDynamic(this, &ThisClass::OnDragRestore); 
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UDragTurret::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UVerticalBox * VerticalBox =  Cast<UVerticalBox>(GetParent());
	UTurretDragDropOperation * TurretOperation = Cast<UTurretDragDropOperation>(InOperation);
	if (VerticalBox && TurretOperation && TurretOperation->DefaultDragVisual && this != TurretOperation->DefaultDragVisual)
	{
		const int32 OverIndex = VerticalBox->GetChildIndex(TurretOperation->DefaultDragVisual);
		if (OverIndex >= 0)
		{
			VerticalBox->RemoveChildAt(OverIndex);
			const TArray<UWidget *> Children = VerticalBox->GetAllChildren();
			VerticalBox->ClearChildren();
			for (int32 i = 0; i < Children.Num(); ++i)
			{
				VerticalBox->AddChildToVerticalBox(Children[i]);
				if (Children[i] == this)
				{
					VerticalBox->AddChildToVerticalBox(TurretOperation->DefaultDragVisual);
					
				}
			}
			return true;
		}
		
	}

	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	
}

bool UDragTurret::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	//
	if (InOperation && InOperation->DefaultDragVisual)
	{
		OnDragRestore(InOperation);
		return true;
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UDragTurret::OnDragRestore(UDragDropOperation* Operation)
{
	UDragTurret * Item = Cast<UDragTurret>(Operation->DefaultDragVisual);
	if (Item)
	{
		Item->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		Item->SetVisibility(ESlateVisibility::Visible);
	}
}
