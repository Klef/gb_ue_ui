// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralWidgetStyle.h"
#include "InventoryData.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCloseButton)

class UUniformGridPanel;
class UInventoryCellWidget;
class UInventoryComponent;
class UButton;
class UTextBlock;


UCLASS()
class LONGDAY_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void Init(int32 ItemsCount);

	bool AddItem(const FInventorySlotInfo & InSlot, const FInventoryItemInfo & Info, int32 SlotIndex);

	FOnItemDrop OnItemDrop;
	FOnCloseButton OnCloseButton;

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FGeneralStyle WidgetStyle;

	UFUNCTION()
	UInventoryComponent * GetParentInventory();
	UFUNCTION()
	void SetParentInventory(UInventoryComponent * InInventoryComponent);
	
	UFUNCTION()
	UInventoryCellWidget * GetMoneyCell() const;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	int32 ItemsInRow = 5;
	
	UPROPERTY(BlueprintReadOnly, Meta=(BindWidgetOptional))
	UUniformGridPanel * CellsPanel;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellWidget> CellWidgetClass;

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidgetOptional))
	UInventoryCellWidget * MoneyCell;

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidgetOptional))
	UButton * CloseButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	UTextBlock * CloseText;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<UInventoryCellWidget *> CellWidgets;

	UPROPERTY()
	UInventoryComponent * ParentInventory;
	
	UInventoryCellWidget * CreateCell();

	UFUNCTION()
	void OnItemDropFunction(UInventoryCellWidget * From, UInventoryCellWidget * To);

	UFUNCTION()
	void OnCloseButtonClick();

	UFUNCTION()
	void InitCell(UInventoryCellWidget * NewCell);

	//FOnCloseButtonMulticastDelegate * OnCloseButtonMulticastDelegate;
};
