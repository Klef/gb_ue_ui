// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryChoiseWidget.h"
#include "InventoryData.h"
#include "GameFramework/Character.h"
#include "InventoryCharacter.generated.h"

class UInventoryComponent;
class UInventoryManagerComponent;

UCLASS()
class LONGDAY_API AInventoryCharacter : public ACharacter
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
	UInventoryManagerComponent * InventoryManager;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryChoiseWidget> ChoiseWidgetClass;
	UPROPERTY()
	UInventoryChoiseWidget * ChoiseWidget;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void InventoryWork();
	void ChoiseEnd(FInventorySlotInfo *);
};
