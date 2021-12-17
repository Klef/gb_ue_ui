// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LONGDAY_API AUIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUIPlayerController(const FObjectInitializer & Obj);

	FSimpleMulticastDelegate OnMouseButtonUp;

protected:
	void SetupInputComponent() override;
	void OnLeftMouseButtonUp();	
};
