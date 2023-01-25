// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "LivingComponent.h"


APlayerCharacter::APlayerCharacter()
{
// Sets default values
PrimaryActorTick.bCanEverTick = true;


FollowSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FollowSpringArm"));
FollowSpringArm->SetupAttachment(RootComponent);
FollowSpringArm->bUsePawnControlRotation = true;

FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
FollowCamera->SetupAttachment(FollowSpringArm, USpringArmComponent::SocketName);
FollowSpringArm->bUsePawnControlRotation = false;

FollowSpringArm->SocketOffset = camerapos;
TargetArmLenght = 300;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// 5 초간 디버그 메시지를 표시합니다. (첫 인수인) -1 "Key" 값은 이 메시지를 업데이트 또는 새로고칠 필요가 없음을 나타냅니다.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
}
// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	movevec.Normalize();
	movevec *= 0.5f;
	if (isRun) {
		movevec *= 6.0f;
		RotateInit();
	}

	AddMovementInput(FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X), movevec.X);
	AddMovementInput(FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y), movevec.Y);

	if (movevec != FVector::ZeroVector) {
		RotateInit();
	}

	FollowSpringArm->SetRelativeLocation(GetMesh()->GetBoneLocation(TEXT("spine_01"), EBoneSpaces::ComponentSpace));
	FollowSpringArm->SocketOffset = camerapos;

	FollowSpringArm->TargetArmLength = FMath::Lerp(FollowSpringArm->TargetArmLength, TargetArmLenght, 0.25f);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// "movement" 바인딩 구성
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// "look" 바인딩 구성
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

	// "action" 바인딩을 구성합니다.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::Crouching);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);

	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &APlayerCharacter::StartAiming);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &APlayerCharacter::StopAiming);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::StopRun);
}

bool APlayerCharacter::Fire()
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
		testactor = result.GetActor();



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

void APlayerCharacter::MoveForward(float Value)
{
	movevec.X = Value;
}

void APlayerCharacter::MoveRight(float Value)
{
	movevec.Y = Value;
}

void APlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::StartFire()
{
	isFire = true;

}

void APlayerCharacter::StopFire()
{
	isFire = false;
}

void APlayerCharacter::StartRun()
{
	isRun = true;
}

void APlayerCharacter::StopRun()
{
	isRun = false;
}

void APlayerCharacter::Reload()
{
	isReload = true;
}

void APlayerCharacter::Crouching()
{
	if (CanCrouch()) {
		Crouch();
		if (!bIsCrouched) {
			camerapos += camerapos_Crouch;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("%d"), bIsCrouched));
		}
	}
	else {
		UnCrouch();
		if (bIsCrouched) {
			camerapos -= camerapos_Crouch;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("%d"), bIsCrouched));

		}
	}
}

void APlayerCharacter::StartAiming()
{
	isAiming = true;
	TargetArmLenght = 100.f;
}

void APlayerCharacter::StopAiming()
{
	isAiming = false;
	TargetArmLenght = 300.f;
}

void APlayerCharacter::RotateInit()
{
	FRotator temprot = GetActorRotation();
	temprot.Yaw = Controller->GetControlRotation().Yaw;
	SetActorRotation(temprot);
}

