// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"

#include "InventoryCellWidget.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


UInventoryManagerComponent::UInventoryManagerComponent()
{

}
void UInventoryManagerComponent::Init(UInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;
	if (LocalInventoryComponent && ItemsData && InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		
		InventoryWidget->Init(FMath::Max(MinInventorySize, LocalInventoryComponent->GetItemsNum()));
		InventoryWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunction);
		InventoryWidget->OnCloseButton.AddUObject(this, &ThisClass::HideWidget);
		
		for (const auto & Item : LocalInventoryComponent->GetItems())
		{
			auto * ItemData = GetItemData(Item.Value.Id);
			if (ItemData)
			{
				GLog->Log(ELogVerbosity::Warning, * FString::Printf(TEXT("Item %s, count %d"), * ItemData->Name.ToString(), Item.Value.Count));
				InventoryWidget->AddItem(Item.Value, * ItemData, Item.Key);
			}
		}
	}
}

const FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName& InId) const
{
	return ItemsData ? ItemsData->FindRow<FInventoryItemInfo>(InId, "") : nullptr;
}

void UInventoryManagerComponent::ShowWidget()
{
	if (InventoryWidget && !bIsInventoryVisibility)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
		GetWorld()->GetFirstPlayerController(), nullptr, EMouseLockMode::DoNotLock, false);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		InventoryWidget->AddToViewport();
		bIsInventoryVisibility = true;
	}
}

void UInventoryManagerComponent::HideWidget()
{
	if (InventoryWidget && bIsInventoryVisibility)
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		InventoryWidget->RemoveFromParent();
		bIsInventoryVisibility = false;
	}
}

void UInventoryManagerComponent::FlipFlopWidget()
{
	if (bIsInventoryVisibility)
	{
		HideWidget();
	}
	else
	{
		ShowWidget();
	}
}

void UInventoryManagerComponent::OnItemDropFunction(UInventoryCellWidget* From, UInventoryCellWidget* To)
{
	
	FInventorySlotInfo FromItem = From->GetItem();
	FInventorySlotInfo ToItem = To->GetItem();
	From->Clear();
	To->Clear();
	
	To->AddItem(FromItem, * GetItemData(FromItem.Id));
	
	if (!ToItem.Id.IsNone())
	{
		From->AddItem(ToItem, * GetItemData(ToItem.Id));
	}
}

