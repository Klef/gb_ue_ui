// Fill out your copyright notice in the Description page of Project Settings.

#include "SMiniMap.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "SlateOptMacros.h"
#include "Brushes/SlateBoxBrush.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMiniMap::Construct(const FArguments& InArgs)
{
	Border1 = InArgs._Border1;
	Border2 = InArgs._Border2;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SMiniMap::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const{
	const FVector2D LocalSize = AllottedGeometry.GetLocalSize();
	
	int i1 = Border1.Num();
	for (int Element = 0; Element < Border1.Num(); ++Element)
	{
		TArray<FVector2D> Border;
		Border.Add(Border1[Element]);
		Border.Add(Border2[Element]);
		FSlateDrawElement::MakeLines(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			Border,
			ESlateDrawEffect::None,
			FLinearColor::Gray
			);
	}
	
	FSlateBrush Brush;
	Brush.ImageSize = FVector2D(10.0f, 10.0f);
	
	FVector2D HandleSize = FVector2D(0.1f,0.1f);
	FSlateDrawElement::MakeBox(
		OutDrawElements,
		++LayerId,
		AllottedGeometry.ToPaintGeometry(PlayerPosition - Brush.ImageSize * 0.5f, Brush.ImageSize),
		&Brush,
		ESlateDrawEffect::None,
		FLinearColor::Yellow
		
	);
	
	
	return 0;
}

FVector2D SMiniMap::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return FVector2D(400.f);
}

 void SMiniMap::SetPlayerPosition(FVector2D PlayerPositionValue)
{
	PlayerPosition = PlayerPositionValue;
}

void SMiniMap::SetEnemy(FString NameValue, FVector2D PositionValue , bool isAlive)
{
	if (isAlive)
	{
		if (int32 Element = EnemyName.Find(NameValue))
		{
			EnemyPosition[Element] = PositionValue;
		}
		else
		{
			EnemyName.Add(NameValue);
			EnemyPosition.Add(PositionValue);
		}
	}
	else
	{
		if (int32 Element = EnemyName.Find(NameValue))
		{
			EnemyName.RemoveAt(Element);
			EnemyPosition.RemoveAt(Element);
		}
	}
	
}
