// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryData.generated.h"

UENUM()
enum class EItemType : uint8
{
	It_Misc,		//разное
	It_Currency,	//валюта
	It_Equip,		//обмундирование
	It_Weapon,		//оружие
	It_Consumable,	//расходники
};

UENUM()
enum class EItemRarity : uint8
{
	Ir_Common,
	Ir_Rare,
	Ir_Epic,
};

class UInventoryCellWidget;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellWidget * /*from*/, UInventoryCellWidget * /*to*/)


USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="General")
	FName Id = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category="General")
	FText Name;
	
	UPROPERTY(EditDefaultsOnly, Category="Type")
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, Category="Type")
	EItemRarity Rare;

	UPROPERTY(EditDefaultsOnly, Category="Visual")
	TSoftObjectPtr<UTexture2D>  Icon;
	
	UPROPERTY(EditDefaultsOnly, Category="Visual")
	TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, Category="Stats")
	int32 Damage = 0;

	UPROPERTY(EditDefaultsOnly, Category="Stats")
	int32 Armor = 0;
	
};

USTRUCT(BlueprintType)
struct FInventorySlotInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Id;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Count;

};
