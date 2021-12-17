// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "Damageble.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"


// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shoot Effect"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Effect"));
	AudioEffect->SetupAttachment(ProjectileSpawnPoint);

}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	bIsReadyToFire = true;
}




void ACannon::Fire()
{
	if (bIsReadyToFire)
	{
		if (ShootEffect)
		{
			ShootEffect->ActivateSystem();
		}
		if (AudioEffect)
		{
			AudioEffect->Play();
		}
		if (Type == ECannonType::FireProjectile)
		{
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
			if (Projectile)
			{
				Projectile->SetInstigator(GetInstigator());
				Projectile->Start();
			}
		}
		if (Type == ECannonType::FireTrace)
		{
			//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Green, TEXT("Fire Trace"));
			FHitResult HitResult;
			FVector TraceStart = ProjectileSpawnPoint->GetComponentLocation();
			FVector TraceEnd = ProjectileSpawnPoint->GetComponentLocation() + ProjectileSpawnPoint->GetForwardVector() * FireRange;
			FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
			TraceParams.bReturnPhysicalMaterial = false;
			if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
			{
				DrawDebugLine(GetWorld(), TraceStart, HitResult.Location, FColor::Red, false, 0.5f, 0, 10.0f);
				if (HitResult.Actor.IsValid() && HitResult.Component.IsValid(), HitResult.Component->GetCollisionObjectType() == ECC_Destructible)
				{
					HitResult.Actor->Destroy();
				}
				else if (IDamageble* Damageable = Cast<IDamageble>(HitResult.Actor))
				{
					if (HitResult.Actor != GetInstigator())
					{
						FDamageData DamageData;
						DamageData.DamageValue = FireDamage;
						DamageData.Instigator = GetInstigator();
						DamageData.DamageMaker = this;
						Damageable->TakeDamage(DamageData);
					}
				}
			}
			else
			{
				GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1.0f / FireRate, false);
			}
		}
	}
	
}


void ACannon::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
}


void ACannon::Reload()
{
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Yellow, TEXT("Ready"));
	bIsReadyToFire = true;
}

bool ACannon::IsReadyToFire()
{
	return bIsReadyToFire;
}
