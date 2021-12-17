#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
	FireTrace = 1  UMETA(DisplayName = "Use trace"),
	FireHealth = 2  UMETA(DisplayName = "Use health")
};

UCLASS()
class LONGDAY_API ACannon : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent * Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UArrowComponent * ProjectileSpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UParticleSystemComponent * ShootEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UAudioComponent * AudioEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TSubclassOf<class UCameraShakeBase> ShootShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditComdition = "Type == ECannonType::FireTrace;", EditConditionHides), Category = "Fire params")
	float FireRange = 2000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireDamage = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float ChargeTime = 5.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	ECannonType Type = ECannonType::FireProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditComdition = "Type == ECannonType::FireProjectile;", EditConditionHides), Category = "Fire params")
	TSubclassOf<class AProjectile> ProjectileClass;

private:
	FTimerHandle ReloadTimerHandle;
	bool bIsReadyToFire = false;
	float RangeToPosition;
public:
	ACannon();
	void Fire();
	bool IsReadyToFire();
	float GetZSpawn();
	bool GetIsSmallAgile();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	void Reload();

};
