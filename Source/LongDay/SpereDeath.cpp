// Fill out your copyright notice in the Description page of Project Settings.


#include "SpereDeath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WidgetComponent.h"
#include "LongDayCharacter.h"

// Sets default values
ASpereDeath::ASpereDeath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentHit.AddDynamic(this, &ASpereDeath::OnMeshHit);
	RootComponent = Mesh;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComponent->OnHeathChange.AddDynamic(this, &ASpereDeath::OnHeathChange);
	HealthComponent->OnDie.AddDynamic(this, &ASpereDeath::OnDie);
	HealthWidgetComp  = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASpereDeath::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	HealthBarWidget = Cast<UHealthBar>(HealthWidgetComp->GetUserWidgetObject());
}

void ASpereDeath::OnMeshHit(class UPrimitiveComponent* HittedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (OtherActor->GetClass() == GetClass())
	{
		return;
	}
	if (PlayerPawn == OtherActor)
	{
		FDamageData DamageData;
		DamageData.DamageValue = DeliverDamage;
		DamageData.Instigator = PlayerPawn->GetInstigator();
		DamageData.DamageMaker = PlayerPawn;
		TakeDamage(DamageData);
	}
	if (IDamageble* Damageable = Cast<IDamageble>(OtherActor))
	{
		FDamageData DamageData;
		DamageData.DamageValue = DeliverDamage;
		DamageData.Instigator = GetInstigator();
		DamageData.DamageMaker = this;
		Damageable->TakeDamage(DamageData);
	}
}

// Called every frame
void ASpereDeath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector TargetLocation = PlayerPawn->GetActorLocation();
	FVector CurentLocation = GetActorLocation();
	FVector TargetVector = TargetLocation - CurentLocation;
	TargetVector.Normalize();
	FVector NextPosition = CurentLocation + TargetVector * MoveSpeed * DeltaTime;
	SetActorLocation(NextPosition, true);

}

void ASpereDeath::OnHeathChange_Implementation(float Damage)
{

}

void ASpereDeath::OnDie_Implementation()
{
	Destroy();
}

void ASpereDeath::TakeDamage(const FDamageData& DamageData)
{
	HealthComponent->TakeDamage(DamageData);
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthBar(HealthComponent->GetHealhtState());
	}
}