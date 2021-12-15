// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Styling/SlateTypes.h"

#include "GeneralWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct LONGDAY_API FGeneralStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FGeneralStyle();
	virtual ~FGeneralStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FGeneralStyle& GetDefault();
	
	UPROPERTY(EditAnywhere, Category = "Appearance")
	FCheckBoxStyle CheckBoxStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FTextBlockStyle TextStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FButtonStyle ButtonStyle;

	UPROPERTY(EditAnywhere, Category = "Appearance")
	FSliderStyle SlyderStyle;
	

	
	
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UGeneralWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category="Appearance", EditAnywhere, meta=(ShowOnlyInnerProperties))
	FGeneralStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}

	
};
