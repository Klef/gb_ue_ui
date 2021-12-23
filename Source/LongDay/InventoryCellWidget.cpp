// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCellWidget.h"
#include "InventoryDropOperation.h"
#include "InventoryWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

class UTurretDragDropOperation;

FReply UInventoryCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (bCanDrop && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	return FReply::Handled();
}

void UInventoryCellWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UInventoryDropOperation::StaticClass());
	
	UInventoryCellWidget * DragVisual = CreateWidget<UInventoryCellWidget>(GetWorld(), DragWidgetClass);
	
	if (OutOperation)
	{
	UInventoryDropOperation * OutInventoryOperation = Cast<UInventoryDropOperation>(OutOperation);
		if (OutInventoryOperation)
		{
			if (DragVisual && DragVisual->ItemImage)
			{
				// ItemImage->SetBrushFromTexture(Info.Icon.LoadSynchronous());
				// CurrentTexture = Info.Icon.LoadSynchronous();
				DragVisual->ItemImage->SetBrushFromTexture(TextureForDrag);
				DragVisual->ItemImage->SetVisibility(ESlateVisibility::Visible);
			}
			OutInventoryOperation->FromCell = this;
			OutInventoryOperation->Pivot = EDragPivot::MouseDown;
			OutInventoryOperation->DefaultDragVisual = DragVisual;
		}
		else
		{
			Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
		}
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
	
}

bool UInventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	const auto InventoryDropOperation = Cast<UInventoryDropOperation>(InOperation);
	if (InventoryDropOperation && InventoryDropOperation->FromCell != this)
	{
		if (OnItemDrop.IsBound())
		{
			OnItemDrop.Broadcast(InventoryDropOperation->FromCell, this);
			return true;
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

bool UInventoryCellWidget::AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info)
{
	if (bHasItem)
	{
		return false;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemImage->SetBrushFromTexture(Info.Icon.LoadSynchronous());
		TextureForDrag = Info.Icon.LoadSynchronous();
	}
	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CountText->SetText(FText::FromString(FString::FromInt(InSlot.Count)));
	}
	if (NameText)
	{
		NameText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		NameText->SetText(Info.Name);
	}
	bHasItem = true;
	Item = InSlot;
	return  true;
}

void UInventoryCellWidget::Clear()
{
	if (!bHasItem)
	{
		return;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (NameText)
	{
		NameText->SetVisibility(ESlateVisibility::Collapsed);
	}
	bHasItem = false;
	Item = FInventorySlotInfo();
}

UInventoryComponent* UInventoryCellWidget::GetParentInventory() const
{
	return ParentInventoryWidget ? ParentInventoryWidget->GetParentInventory() : nullptr;
}

void UInventoryCellWidget::SetParentInventoryWidget(UInventoryWidget* InParentWidget)
{
	ParentInventoryWidget = InParentWidget;
}


