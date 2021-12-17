#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class LONGDAY_API AProjectile : public AActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    class UStaticMeshComponent* Mesh;

// 	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
// 	class UParticleSystemComponent* DestroyVisualEffect;
// 	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
// 	class UAudioComponent* DestroySoundEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UParticleSystem* HitVisualEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UParticleSystemComponent* FireVisualEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USoundBase* HitSoundEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float FireRange = 10000.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float AgilitySmooth = 0.5;
	
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
    float Damage = 1.0f;



public:
    AProjectile();

    void Start();
    void Stop();
	virtual void Tick(float DeltaTime) override;
	float GetMoveSpeed();

protected:
    UFUNCTION()
    virtual void OnMeshHit(class UPrimitiveComponent* HittedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector  NormalImpulse, const FHitResult& HitResult);

private:
    FVector StarPosition;
	FVector Target = FVector::ZeroVector;
};
