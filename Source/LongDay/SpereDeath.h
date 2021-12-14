// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damageble.h"
#include "GameStructs.h"
#include "SpereDeath.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNewPositionEnemy, FString, NameEnemy, FVector2D, PositionEnemy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeath, FString, NameEnemy);
UCLASS()
class LONGDAY_API ASpereDeath : public AActor, public IDamageble
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpereDeath();
	UPROPERTY(BlueprintAssignable)
	FNewPositionEnemy NewPositionEnemy;
	UPROPERTY(BlueprintAssignable)
	FDeath DeathEnemy;
private:
	UPROPERTY()
	class APawn* PlayerPawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float MoveSpeed = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float DeliverDamage = 1.0f;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent * HealthWidgetComp;
	UPROPERTY(VisibleAnywhere)
	class UHealthBar * HealthBarWidget;
	UFUNCTION()
	virtual void OnMeshHit(class UPrimitiveComponent* HittedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector  NormalImpulse, const FHitResult& HitResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void TakeDamage(const FDamageData& DamageData) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnHeathChange(float Damage);

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnDie();
};
