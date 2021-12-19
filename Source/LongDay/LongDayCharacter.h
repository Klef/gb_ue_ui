// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "GameStructs.h"
#include "Damageble.h"
#include "GeneralHUD.h"
#include "HealthBar.h"
#include "InventoryCharacter.h"
#include "SMiniMap.h"
#include "LongDayCharacter.generated.h"

class AGeneralHUD;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewPositionPlayer, FVector2D, PositionPlayer);

UCLASS(config=Game, Blueprintable)
class ALongDayCharacter : public AInventoryCharacter, public IDamageble
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	

public:
	ALongDayCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnHeathChange(float Damage);

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnDie();

  	UFUNCTION(BlueprintCallable, Category = "Health")
 	virtual void TakeDamage(const FDamageData& DamageData) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float ReverseDamage = 1.0f;

	UPROPERTY(BlueprintAssignable)
	FNewPositionPlayer NewPositionPlayer;
protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void Pause();

	void Build();
	void InventoryWork();

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent * HealthWidgetComp;
	UPROPERTY(VisibleAnywhere)
	class UHealthBar * HealthBarWidget;
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	
	bool bIsDeath = false;
	UPROPERTY()
	AGeneralHUD * GHUD;
	UPROPERTY()
    UUserWidget * MiniMap;
	UPROPERTY()
	UUserWidget * BuildMenu;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UX")
	TSubclassOf<class UUserWidget> WidgetMiniMapClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UX")
	TSubclassOf<class UUserWidget> WidgetBuildMenu;
	SMiniMap * MiniMapWidget;
	bool bIsBuildVisibility;
	UPROPERTY()
	AGeneralHUD * GeneralHud;
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	virtual void BeginPlay() override;

};

