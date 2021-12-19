// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralWidgetStyle.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "InventoryChoiseWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChoiceCharacter, FInventorySlotInfo *)

class UButton;
class UTextBlock;
UCLASS()
class LONGDAY_API UInventoryChoiseWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	UPROPERTY()
	TMap<FString, UDataTable*> ChoicePreSet;
	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FGeneralStyle WidgetStyle;

	
	
public:
	UPROPERTY(BlueprintReadWrite, Meta=(BindWidget))
	UButton * OneButton;
	UPROPERTY(BlueprintReadWrite, Meta=(BindWidget))
	UButton * TwoButton;
	UPROPERTY(BlueprintReadWrite, Meta=(BindWidget))
	UButton * ThreeButton;
	UPROPERTY(BlueprintReadWrite, Meta=(BindWidget))
	UTextBlock * OneText;
	UPROPERTY(BlueprintReadWrite, Meta=(BindWidget))
	UTextBlock * TwoText;
	UPROPERTY(BlueprintReadWrite, Meta=(BindWidget))
	UTextBlock * ThreeText;
	void OnClickOne();
	void OnClickTwo();
	void OnClickThree();
	//void OnChoice(FInventorySlotInfo * Value);
	FOnChoiceCharacter * OnChoiceCharacter;
};
