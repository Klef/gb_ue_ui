// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryCellWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryDropOperation.generated.h"


UCLASS()
class LONGDAY_API UInventoryDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UInventoryCellWidget* FromCell;
};
