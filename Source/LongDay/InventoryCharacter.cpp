// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCharacter.h"

#include "EquipInventoryComponent.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "InventoryManagerComponent.h"



// Sets default values
AInventoryCharacter::AInventoryCharacter()
{
	LocalInventory  = CreateDefaultSubobject<UInventoryComponent>("LocalInventory");
	EquipInventory  = CreateDefaultSubobject<UEquipInventoryComponent>("EquipInventory");
	InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
	
}

void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InventoryManager->Init(LocalInventory);
	InventoryManager->InitEquip(EquipInventory);
	
	
}

void AInventoryCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ThisClass::InventoryWork);
}

void AInventoryCharacter::InventoryWork()
{
	InventoryManager->FlipFlopWidget();
}

void AInventoryCharacter::ChoiceEnd(FInventorySlotInfo *)
{
	
}

void AInventoryCharacter::EquipItem(EEquipSlot Slot, FName ItemId)
{
	UStaticMeshComponent * Comp = GetEquipComponent(Slot);
	if (Comp)
	{
		auto * Info = InventoryManager->GetItemData(ItemId);
		Comp->SetStaticMesh(Info->Mesh.LoadSynchronous());
		Comp->SetHiddenInGame(false);
		//Armor += Info->Armor;
	}
}

void AInventoryCharacter::UnEquipItem(EEquipSlot Slot, FName ItemId)
{
	UStaticMeshComponent * Comp = GetEquipComponent(Slot);
	if (Comp)
	{
		Comp->SetHiddenInGame(true);
		Comp = nullptr;
		//Armor -= Info->Armor;
	}
}

UStaticMeshComponent* AInventoryCharacter::GetEquipComponent(EEquipSlot EquipSlot)
{
	FName Tag;
	switch (EquipSlot)
	{
		case EEquipSlot::Es_Head: Tag = "Head"; break;
		case EEquipSlot::Es_Armor: Tag = "Armor"; break;
		case EEquipSlot::Es_Hands: Tag = "Hands"; break;
		default: return nullptr;
	}
	TArray<UActorComponent *> Found = GetComponentsByTag(UStaticMeshComponent::StaticClass(), Tag);
	return Found.IsValidIndex(0) ? Cast<UStaticMeshComponent>(Found[0]) : nullptr;	
}

