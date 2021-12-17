// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableItem.h"

#include "TurretDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/VerticalBox.h"

void UDraggableItem::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (TurretText)
	{
		TurretText->SetText(FText::FromString(TurretName));
	}

}

FReply UDraggableItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	
	return FReply::Handled();
}

void UDraggableItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
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

bool UDraggableItem::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
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

bool UDraggableItem::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
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

void UDraggableItem::OnDragRestore(UDragDropOperation* Operation)
{
	UDraggableItem * Item = Cast<UDraggableItem>(Operation->DefaultDragVisual);
	if (Item)
	{
		Item->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		Item->SetVisibility(ESlateVisibility::Visible);
	}
}
