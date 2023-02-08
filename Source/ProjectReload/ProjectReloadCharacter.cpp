// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectReloadCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "LivingComponent.h"

//////////////////////////////////////////////////////////////////////////
// AProjectReloadCharacter

AProjectReloadCharacter::AProjectReloadCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectReloadCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectReloadCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectReloadCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("Turn", this, &AProjectReloadCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("LookUp", this, &AProjectReloadCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AProjectReloadCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AProjectReloadCharacter::StopFire);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProjectReloadCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProjectReloadCharacter::TouchStopped);
}

bool AProjectReloadCharacter::Fire()
{
	//FireRate += DeltaTime;
	//if (FireCoolTime > FireRate) return;
	if (!isFire) return false;
	//FireRate = 0.f;
	FVector start;
	FRotator cameraRotation;
	FVector end;
	Controller->GetPlayerViewPoint(start, cameraRotation);
	end = start + (cameraRotation.Vector() * 1000);

	FHitResult result;
	FCollisionQueryParams param(NAME_None, true, this);

	DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 2.0f);
	if (GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility, param)) {

		auto temp = result.GetActor()->GetComponentByClass(asd);
		if (temp) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("actor1 : %s"), *temp->GetName()));
			dynamic_cast<ULivingComponent*>(temp)->Ondamage(10);
		}





		TSet<UActorComponent*> components = result.GetActor()->GetComponents();
		for (UActorComponent* item : components) {

			if (dynamic_cast<ULivingComponent*>(item)) {
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("actor2 : %s"), *item->GetName()));
				dynamic_cast<ULivingComponent*>(item)->Ondamage(10);
			}
		}


		//dynamic_cast<ULivingComponent*>(result.GetActor()->GetComponentByClass(TSubclassOf<ULivingComponent>()))->Ondamage(10);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("nonhit"));
	}

	RotateInit();
	return true;
}

void AProjectReloadCharacter::StartFire()
{
	isFire = true;
}

void AProjectReloadCharacter::StopFire()
{
	isFire = false;
}

void AProjectReloadCharacter::RotateInit()
{
	FRotator temprot = GetActorRotation();
	temprot.Yaw = Controller->GetControlRotation().Yaw;
	SetActorRotation(temprot);
}

//bool AProjectReloadCharacter::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible, int32* UserData) const
//{
//	FName Name_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));
//	FHitResult HitResults;
//	FVector SightTargetLocation = GetMesh()->GetSocketLocation("spine_05");
//
//	bool hit = GetWorld()->LineTraceSingleByChannel(HitResults, ObserverLocation, SightTargetLocation, ECC_Visibility, FCollisionQueryParams(Name_AILineOfSight, false, IgnoreActor));
//
//	if (!hit)
//	{
//		OutSeenLocation = SightTargetLocation;
//		OutSightStrength = 1;
//		return true;
//	}
//	OutSightStrength = 0;
//	return false;
//}

void AProjectReloadCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AProjectReloadCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AProjectReloadCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AProjectReloadCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AProjectReloadCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AProjectReloadCharacter::MoveRight(float Value)
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
	}
}
