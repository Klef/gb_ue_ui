// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryChoiseWidget.h"

#include "StyleSet.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UInventoryChoiseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WidgetStyle = FStyleSet::Get().GetWidgetStyle<FGeneralStyle>("DarkStyle");
	if (OneButton)
	{
		OneButton->WidgetStyle = WidgetStyle.ButtonStyle;
		OneButton->OnClicked.AddDynamic(this, &UInventoryChoiseWidget::OnClickOne);
	}
	if (TwoButton)
	{
		TwoButton->WidgetStyle = WidgetStyle.ButtonStyle;
		TwoButton->OnClicked.AddDynamic(this, &UInventoryChoiseWidget::OnClickTwo);
	}
	if (ThreeButton)
	{
		ThreeButton->WidgetStyle = WidgetStyle.ButtonStyle;
		ThreeButton->OnClicked.AddDynamic(this, &UInventoryChoiseWidget::OnClickThree);
	}
	if (OneText)
	{
		OneText->SetColorAndOpacity(WidgetStyle.TextStyle.ColorAndOpacity);
		OneText->SetShadowColorAndOpacity(WidgetStyle.TextStyle.ShadowColorAndOpacity);
		OneText->SetFont(WidgetStyle.TextStyle.Font);
		OneText->SetText(FText::FromString("Normal"));
	}
	if (TwoText)
	{
		TwoText->SetColorAndOpacity(WidgetStyle.TextStyle.ColorAndOpacity);
		TwoText->SetShadowColorAndOpacity(WidgetStyle.TextStyle.ShadowColorAndOpacity);
		TwoText->SetFont(WidgetStyle.TextStyle.Font);
		OneText->SetText(FText::FromString("Rich"));
	}
	if (ThreeText)
	{
		ThreeText->SetColorAndOpacity(WidgetStyle.TextStyle.ColorAndOpacity);
		ThreeText->SetShadowColorAndOpacity(WidgetStyle.TextStyle.ShadowColorAndOpacity);
		ThreeText->SetFont(WidgetStyle.TextStyle.Font);
		OneText->SetText(FText::FromString("More Brick"));
	}
}


void UInventoryChoiseWidget::OnClickOne()
{
	//OnChoiceCharacter->Broadcast(LoadObject<FInventorySlotInfo>(NULL, UTF8_TO_TCHAR("DataTable'/Game/Widget/Inventory/DA_PreSetDefault'")));
}

void UInventoryChoiseWidget::OnClickTwo()
{
	//OnChoiceCharacter->Broadcast(LoadObject<FInventorySlotInfo>(NULL, UTF8_TO_TCHAR("DataTable'/Game/Widget/Inventory/DA_PreSetRich'")));
}

void UInventoryChoiseWidget::OnClickThree()
{
	//OnChoiceCharacter->Broadcast(LoadObject<FInventorySlotInfo>(NULL, UTF8_TO_TCHAR("DataTable'/Game/Widget/Inventory/DA_PreSetBrick'")));
}


