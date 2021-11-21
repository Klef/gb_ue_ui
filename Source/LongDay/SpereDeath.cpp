// Fill out your copyright notice in the Description page of Project Settings.


#include "SpereDeath.h"
#include "Kismet/KismetMathLibrary.h"
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
}

// Called when the game starts or when spawned
void ASpereDeath::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ASpereDeath::OnMeshHit(class UPrimitiveComponent* HittedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (PlayerPawn == OtherActor)
	{
		Cast<ALongDayCharacter>(PlayerPawn)->SetDeath();

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

