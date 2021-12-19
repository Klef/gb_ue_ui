// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	if (ItemsData)
	{
		int32 IdSlot = 0;
		for(const auto Data : ItemsData->GetRowMap())
		{
		
			//FInventorySlotInfo * Slot = Cast<FInventorySlotInfo>(Data.Value);
			FString rowName = (Data.Key).ToString();
			FInventorySlotInfo* pSlot = reinterpret_cast<FInventorySlotInfo*>(Data.Value);
			FInventorySlotInfo Slot;
			Slot.Id = pSlot->Id;
			Slot.Count = pSlot->Count;
			if (pSlot->Id == "Nuyen")
			{
				SetItem(-1, Slot);
			}
			else
			{
				SetItem(IdSlot, Slot);
				++IdSlot;
			}
		}
	}
}

void UInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	ClearItem(SlotIndex);
	Items.Add(SlotIndex, Item);
	
}

void UInventoryComponent::ClearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}
