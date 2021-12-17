// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameFramework/Actor.h"
#include "DragTurret.generated.h"

/**
 * 
 */
UCLASS()
class LONGDAY_API UDragTurret : public UUserWidget
{
	GENERATED_BODY()
public:
	void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	
	UFUNCTION()
	void OnDragRestore(UDragDropOperation * Operation);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DraggedActorClass;

	UPROPERTY()
	AActor * DraggedActor;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock * TurretText;
	
	UPROPERTY(EditAnywhere)
	FString TurretName;

	UPROPERTY()
	APlayerController* PlayerController;
	void OnMouseButtonUp();
protected:
	bool bIsInWidget = true;
	UFUNCTION()
	void WidgetHovered();
	UFUNCTION()
	void WidgetUnHovered();
	
	
};
