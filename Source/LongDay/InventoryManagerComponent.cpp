// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagerComponent.h"

#include "EquipInventoryComponent.h"
#include "InventaryBox.h"
#include "InventoryCellWidget.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


UInventoryManagerComponent::UInventoryManagerComponent()
{

}
void UInventoryManagerComponent::Init(UInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;
	if (LocalInventoryComponent && ItemsData && InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		InventoryWidget->SetParentInventory(InInventoryComponent);
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

void UInventoryManagerComponent::InitEquip(UInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent && EquipWidgetClass)
	{
		EquipWidget = CreateWidget<UInventoryWidget>(GetWorld(), EquipWidgetClass);
		EquipWidget->SetParentInventory(InInventoryComponent);
		EquipWidget->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunction);
		
		
	}
}

const FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName& InId) const
{
	return ItemsData ? ItemsData->FindRow<FInventoryItemInfo>(InId, "") : nullptr;
}

void UInventoryManagerComponent::ShowWidget()
{
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetWorld()->GetFirstPlayerController(), nullptr, EMouseLockMode::DoNotLock, false);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	if (InventoryWidget && !bIsInventoryVisibility)
	{
		InventoryWidget->AddToViewport();
	}
	if (EquipWidget && !bIsInventoryVisibility)
	{
		EquipWidget->AddToViewport();
	}
	bIsInventoryVisibility = true;
}

void UInventoryManagerComponent::HideWidget()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	if (InventoryWidget && bIsInventoryVisibility)
	{
		InventoryWidget->RemoveFromParent();
	}
	if (EquipWidget && bIsInventoryVisibility)
	{
		EquipWidget->RemoveFromParent();
	}
	bIsInventoryVisibility = false;
}

void UInventoryManagerComponent::FlipFlopWidget()
{
	if (bIsInventoryVisibility)
	{
		HideWidget();
		if (Box)
		{
			Box->InventoryManager->HideWidget();
			Box = nullptr;
		}
	}
	else
	{
		ShowWidget();
		FindBox();
		if (Box)
		{
			Box->InventoryManager->ShowWidget();
		}
	}
}

void UInventoryManagerComponent::OnItemDropFunction(UInventoryCellWidget* From, UInventoryCellWidget* To)
{
	if (!From || !To)
	{
		return;
	}
	UInventoryComponent * FromInventory = From->GetParentInventory();
	UInventoryComponent * ToInventory = To->GetParentInventory();
	if (!FromInventory || !ToInventory)
	{
		return;
	}

	const FInventorySlotInfo FromItem = From->GetItem();
	if (FromItem.Count == 0)
	{
		return;
	}
	const FInventoryItemInfo* FromInfo = GetItemData(FromItem.Id);
	if (FromInfo->Id == "Nuyen")
	{
		To = InventoryWidget->GetMoneyCell();
	}
	const FInventorySlotInfo ToItem = To->GetItem();

	
	//если деньги, то работаем с другим виджетом
	
	const int32 ToItemAmount = ToInventory->GetMaxItemAmount(To->IndexInInventory, *FromInfo);
	//-1 - нельзя
	// 0 - можно неограниченно
	// n - можно n (не реализовано) todo
	if (ToItemAmount == 0)
	{
		return;
	}
	FInventorySlotInfo NewFromItem = ToItem;
	FInventorySlotInfo NewToItem = FromItem;
	
	

	if (ToItemAmount == -1)
	{
		if (NewFromItem.Id == NewToItem.Id)
		{
			NewToItem.Count += NewFromItem.Count;
			NewFromItem.Count = 0;
		}
	}
	if (ToItemAmount == 1)
	{
		//что то не далься каменный цветок, перехожу к хардкоду
		
		if (NewFromItem.Count == 0)
		{
			NewFromItem = NewToItem;
			NewFromItem.Count = NewToItem.Count;
			NewFromItem.Count -= 1;
			NewToItem.Count = 1;
		}
		else
		{
			if (NewFromItem.Count != 1 || NewToItem.Count != 1)
			{
				return;
			}
		}
		
	}

	const FInventoryItemInfo* NewFromInfo = NewFromItem.Count > 0 ? GetItemData(NewFromItem.Id) : nullptr;
	const FInventoryItemInfo* NewToInfo = GetItemData(NewToItem.Id);

	
	
	From->Clear();
	if (NewFromInfo)
	{
		From->AddItem(NewFromItem, *NewFromInfo);
	}

	To->Clear();
	To->AddItem(NewToItem, *NewToInfo);
	if (NewFromInfo)
	{
		FromInventory->SetItem(From->IndexInInventory, NewFromItem);
	}
	else
	{
		FromInventory->ClearItem(From->IndexInInventory);
	}
	ToInventory->SetItem(To->IndexInInventory, NewToItem);
	
}

void UInventoryManagerComponent::FindBox()
{
	if (!Box)
	{
		const ACharacter* Player = GetWorld()->GetFirstPlayerController()->GetCharacter();
		TArray<AActor*> FindBox;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInventaryBox::StaticClass(), FindBox);
		float Min = 150.0f;
		for (AActor* Actor : FindBox)
		{
			AInventaryBox* VariableBox = Cast<AInventaryBox>(Actor);
		
			const float Distance = Player->GetDistanceTo(VariableBox);
			if (Distance < Min)
			{
				Box = VariableBox;
				Min = Distance;
			}
		}
	}
}
