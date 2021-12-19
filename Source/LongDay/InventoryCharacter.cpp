// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCharacter.h"
#include "InventoryComponent.h"
#include "InventoryManagerComponent.h"



// Sets default values
AInventoryCharacter::AInventoryCharacter()
{
	LocalInventory  = CreateDefaultSubobject<UInventoryComponent>("LocalInventory");
	InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
	
}

void AInventoryCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ChoiseWidgetClass)
	{
		ChoiseWidget  = CreateWidget<UInventoryChoiseWidget>(GetWorld(), ChoiseWidgetClass);
		
	}
	else
	{
		InventoryManager->Init(LocalInventory);
	}
	
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

void AInventoryCharacter::ChoiseEnd(FInventorySlotInfo *)
{
	
}

