// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidget.h"
#include "GameFramework/Actor.h"
#include "InventaryBox.generated.h"

class UInventoryManagerComponent;
class UInventoryComponent;

UCLASS()
class LONGDAY_API AInventaryBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInventaryBox();
	
	UPROPERTY(EditDefaultsOnly)
	UInventoryManagerComponent * InventoryManager;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	UInventoryComponent * BoxInventory;
};
