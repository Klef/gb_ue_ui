// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"
#include "InventoryComponent.h"
#include "InventoryCellWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "StyleSet.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WidgetStyle = FStyleSet::Get().GetWidgetStyle<FGeneralStyle>("DarkStyle");
	if (CloseButton)
	{
		CloseButton->WidgetStyle = WidgetStyle.ButtonStyle;
		CloseButton->OnClicked.AddDynamic(this, &UInventoryWidget::OnCloseButtonClick);
		
	}
	if (CloseText)
	{
		CloseText->SetColorAndOpacity(WidgetStyle.TextStyle.ColorAndOpacity);
		CloseText->SetShadowColorAndOpacity(WidgetStyle.TextStyle.ShadowColorAndOpacity);
		CloseText->SetFont(WidgetStyle.TextStyle.Font);
	}

	for (auto * Cell : CellWidgets)
	{
		InitCell(Cell);
	}
}

void UInventoryWidget::Init(int32 ItemsCount)
{
	if (CellsPanel)
	{
		CellsPanel->ClearChildren();
		for (int32 i = 0; i < ItemsCount; ++i)
		{
			if (auto * Cell = CreateCell())
			{
				Cell->IndexInInventory = i;
				CellsPanel->AddChildToUniformGrid(Cell, i / ItemsInRow, i % ItemsInRow);
			}
		}
	}
}

bool UInventoryWidget::AddItem(const FInventorySlotInfo & InSlot, const FInventoryItemInfo & Info, int32 SlotIndex)
{

	if (Info.Type == EItemType::It_Currency)
	{
		if (MoneyCell)
		{
			return MoneyCell->AddItem(InSlot, Info);
		}
	}
	if (CellsPanel)
	{
		UInventoryCellWidget * Found = nullptr;
		UInventoryCellWidget ** FoundPtr = CellWidgets.FindByPredicate([SlotIndex] (UInventoryCellWidget * Cell)
		{
			return Cell && Cell->IndexInInventory == SlotIndex;
		});
		if (FoundPtr)
		{
			Found = * FoundPtr;
		}
		else
		{
			for (auto * Cell : CellWidgets)
			{
				if (!Cell->HasItem())
				{
					Found = Cell;
					break;
				}
			}
		}
		if (Found)
		{
			return Found->AddItem(InSlot, Info);
		}
	}
	return false;
}

UInventoryComponent* UInventoryWidget::GetParentInventory()
{
	return ParentInventory ? ParentInventory : nullptr;
}

void UInventoryWidget::SetParentInventory(UInventoryComponent* InInventoryComponent)
{
	ParentInventory = InInventoryComponent;
}

UInventoryCellWidget* UInventoryWidget::CreateCell()
{
	if (CellWidgetClass)
	{
		auto * Cell = CreateWidget<UInventoryCellWidget>(this, CellWidgetClass);
		CellWidgets.Add(Cell);
		InitCell(Cell);
		return Cell;
	}
	return nullptr;
}

void UInventoryWidget::OnItemDropFunction(UInventoryCellWidget* From, UInventoryCellWidget* To)
{
	OnItemDrop.Broadcast(From, To);
}

void UInventoryWidget::OnCloseButtonClick()
{
	if (OnCloseButton.IsBound())
	{
		OnCloseButton.Broadcast();
	}
}

void UInventoryWidget::InitCell(UInventoryCellWidget* NewCell)
{
	if (NewCell)
	{
		NewCell->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunction);
		NewCell->SetParentInventoryWidget(this);
	}
}

UInventoryCellWidget* UInventoryWidget::GetMoneyCell() const
{
	return MoneyCell;
}
