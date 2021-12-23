// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipInterface.h"
#include "InventoryChoiseWidget.h"
#include "InventoryData.h"
#include "GameFramework/Character.h"
#include "InventoryCharacter.generated.h"

class UInventoryComponent;
class UEquipInventoryComponent;
class UInventoryManagerComponent;

UCLASS()
class LONGDAY_API AInventoryCharacter : public ACharacter, public IEquipInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInventoryCharacter();
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	UInventoryComponent * LocalInventory;
	UPROPERTY(EditDefaultsOnly)
	UEquipInventoryComponent * EquipInventory;
	UPROPERTY(EditDefaultsOnly)
	UInventoryManagerComponent * InventoryManager;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryChoiseWidget> ChoiceWidgetClass;
	UPROPERTY()
	UInventoryChoiseWidget * ChoiceWidget;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void InventoryWork();
	void ChoiceEnd(FInventorySlotInfo *);

	virtual void EquipItem(EEquipSlot Slot, FName ItemId) override;
	virtual void UnEquipItem(EEquipSlot Slot, FName ItemId) override;

	UStaticMeshComponent * GetEquipComponent(EEquipSlot EquipSlot);
};
