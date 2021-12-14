// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class LONGDAY_API SMiniMap : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SMiniMap)
	{}
	SLATE_ARGUMENT(TArray<FVector2D>, Border1)
	SLATE_ARGUMENT(TArray<FVector2D>, Border2)
	SLATE_ATTRIBUTE(FVector2D, PlayerPosition)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
	void SetPlayerPosition(FVector2D PlayerPositionValue);
	void SetEnemy(FString NameValue, FVector2D PositionValue , bool isAlive);
	
protected:

	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;
	TArray<FVector2D> Border1;
	TArray<FVector2D> Border2;
	TArray<FString> EnemyName;
	TArray<FVector2D> EnemyPosition;
	FVector2D PlayerPosition;
};


