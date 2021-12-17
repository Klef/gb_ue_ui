// Copyright Epic Games, Inc. All Rights Reserved.

#include "LongDayCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ALongDayCharacter

ALongDayCharacter::ALongDayCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	
 	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
  	HealthComponent->OnHeathChange.AddDynamic(this, &ALongDayCharacter::OnHeathChange);
  	HealthComponent->OnDie.AddDynamic(this, &ALongDayCharacter::OnDie);
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	HealthWidgetComp  = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	
	
	///dfdgfgds
}

void ALongDayCharacter::OnHeathChange_Implementation(float Damage)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, TEXT("Hit"));
}

void ALongDayCharacter::OnDie_Implementation()
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::Red, TEXT("Die"));
	AGeneralHUD * GeneralHud = Cast<AGeneralHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	GeneralHud->ShowWidget(EWidgetID::Wid_Death, 3);
}




 void ALongDayCharacter::TakeDamage(const FDamageData& DamageData)
 {
 	HealthComponent->TakeDamage(DamageData);
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthBar(HealthComponent->GetHealhtState());
	}
 }



//////////////////////////////////////////////////////////////////////////
// Input

void ALongDayCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("PauseMenu", IE_Pressed, this, &ALongDayCharacter::Pause);
	PlayerInputComponent->BindAction("Build", IE_Pressed, this, &ALongDayCharacter::Build);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALongDayCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALongDayCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALongDayCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALongDayCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ALongDayCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ALongDayCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ALongDayCharacter::OnResetVR);
}

void ALongDayCharacter::BeginPlay()
{
	Super::BeginPlay();
	//тут ужасно )
	FString CurentLevel = GetWorld()->GetMapName();
	CurentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	if (CurentLevel == TEXT("MainMenu"))
	{
		AGeneralHUD * GeneralHud = Cast<AGeneralHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		GeneralHud->ShowWidget(EWidgetID::Wid_MainMenu, 1);
	}
	else
	{
		HealthBarWidget = Cast<UHealthBar>(HealthWidgetComp->GetUserWidgetObject());
		if (WidgetMiniMapClass)
		{
			MiniMap = CreateWidget(GetWorld(), WidgetMiniMapClass);
			MiniMap->AddToViewport();
			NewPositionPlayer.Broadcast(FVector2D(GetActorLocation().X,GetActorLocation().Y));
		}
		if (WidgetBuildMenu)
		{
			BuildMenu = CreateWidget(GetWorld(), WidgetBuildMenu);
		}
		bIsBuildVisibility = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	}
}


void ALongDayCharacter::OnResetVR()
{
	// If LongDay is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in LongDay.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ALongDayCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ALongDayCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ALongDayCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALongDayCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALongDayCharacter::Pause()
{
	AGeneralHUD * GeneralHud = Cast<AGeneralHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	GeneralHud->ShowWidget(EWidgetID::Wid_PauseMenu, 2);
}

void ALongDayCharacter::Build()
{
	if (BuildMenu)
	{
		if (bIsBuildVisibility)
		{
			BuildMenu->RemoveFromParent();
			bIsBuildVisibility = false;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		}
		else
		{
			BuildMenu->AddToViewport();
			bIsBuildVisibility = true;
			//GetWorld()->GetFirstPlayerController()
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
			GetWorld()->GetFirstPlayerController(), nullptr, EMouseLockMode::DoNotLock, false);
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		}
	}
}


void ALongDayCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		if (NewPositionPlayer.IsBound())
		{
			NewPositionPlayer.Broadcast(FVector2D(GetActorLocation().X,GetActorLocation().Y));
		}
	}
}

void ALongDayCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
		if (NewPositionPlayer.IsBound())
		{
			NewPositionPlayer.Broadcast(FVector2D(GetActorLocation().X,GetActorLocation().Y));
		}
	}
}
