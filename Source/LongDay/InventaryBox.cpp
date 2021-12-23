// Fill out your copyright notice in the Description page of Project Settings.


#include "InventaryBox.h"
#include "InventoryComponent.h"
#include "InventoryManagerComponent.h"

// Sets default values
AInventaryBox::AInventaryBox()
{
	BoxInventory  = CreateDefaultSubobject<UInventoryComponent>("LocalInventory");
	InventoryManager = CreateDefaultSubobject<UInventoryManagerComponent>("InventoryManager");
}

// Called when the game starts or when spawned
void AInventaryBox::BeginPlay()
{
	Super::BeginPlay();
	InventoryManager->Init(BoxInventory);
}


