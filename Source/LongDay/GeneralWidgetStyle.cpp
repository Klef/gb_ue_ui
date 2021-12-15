// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralWidgetStyle.h"

FGeneralStyle::FGeneralStyle()
{
	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>("Checkbox");
	ButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>("Button");
	TextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");
	SlyderStyle = FCoreStyle::Get().GetWidgetStyle<FSliderStyle>("Slider");
}

FGeneralStyle::~FGeneralStyle()
{
}

const FName FGeneralStyle::TypeName(TEXT("FGeneralStyle"));

const FGeneralStyle& FGeneralStyle::GetDefault()
{
	static FGeneralStyle Default;
	return Default;
}

void FGeneralStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

