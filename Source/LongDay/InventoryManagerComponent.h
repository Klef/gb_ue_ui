// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventaryBox.h"
#include "InventoryChoiseWidget.h"
#include "InventoryData.h"
#include "InventoryWidget.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryComponent;
class UInventoryWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LONGDAY_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryManagerComponent();
	void Init(UInventoryComponent * InInventoryComponent);
	void InitEquip(UInventoryComponent * InInventoryComponent);
	const FInventoryItemInfo * GetItemData(const FName & InId) const;
	UFUNCTION()
	void ShowWidget();
	UFUNCTION()
	void HideWidget();
	UFUNCTION()
	void FlipFlopWidget();
protected:
	bool bIsInventoryVisibility = false;
	UPROPERTY()
	UInventoryComponent * LocalInventoryComponent;

	UPROPERTY(EditAnywhere)
	UDataTable * ItemsData;

	UPROPERTY(EditAnywhere)
	TMap<FString, UDataTable*> ItemsPreSetType;
	
	UPROPERTY(EditAnywhere)
	int32 MinInventorySize = 20;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;
	
	UPROPERTY()
	UInventoryWidget * InventoryWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidget> EquipWidgetClass;
	
	UPROPERTY()
	UInventoryWidget * EquipWidget;
	
	UPROPERTY()
	AInventaryBox * Box = nullptr;
	
	void OnItemDropFunction(UInventoryCellWidget * From, UInventoryCellWidget * To);

	void FindBox();
	
};


