// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damageble.h"
#include "Turret.generated.h"



UCLASS()
class LONGDAY_API ATurret : public AActor, public IDamageble
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* CannonSetupPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* HitCollider;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent * HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	class TSubclassOf<class ACannon> CannonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingSpeed = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float Accuracy = 10.0f;
	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
    void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnHeathChange(float Damage);

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnDie();

private:
	UPROPERTY()
	class ACannon* Cannon;

	UPROPERTY()
	class APawn* PlayerPawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void TakeDamage(const FDamageData& DamageData) override;

};
