// Fill out your copyright notice in the Description page of Project Settings.


#include "testAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


UtestAnimInstance::UtestAnimInstance()
{
}

void UtestAnimInstance::NativeBeginPlay()
{
	isFireEnd = true;
}

void UtestAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (APawn* pawn = TryGetPawnOwner()) {
		if (ACharacter* charcter = dynamic_cast<ACharacter*>(pawn)) {
			isFall = charcter->GetCharacterMovement()->MovementMode == MOVE_Falling;
			isMoveing = charcter->GetVelocity().Length() > 0;

			FRotator temprot = FMath::RInterpTo(FRotator(AimPitch, AimYaw, 0), charcter->GetControlRotation() - charcter->GetActorRotation(), DeltaSeconds, 15.f);
			AimPitch = FMath::ClampAngle((temprot.Pitch), -60, 60);
			AimYaw = FMath::ClampAngle((temprot.Yaw), -60, 60);

			direction = CalculateDirection(charcter->GetVelocity(), charcter->GetActorRotation());
			speed = charcter->GetVelocity().Length();

		} 
		if (APlayerCharacter* charcter = dynamic_cast<APlayerCharacter*>(pawn)) {
			isCrouching = charcter->bIsCrouched;
			isFire = charcter->isFire;

			forwardValue = charcter->movevec.X;
			rightValue = charcter->movevec.Y;

			isReload = charcter->isReload;
			isAiming = charcter->isAiming;
			isRun = charcter->isRun;
			isAimChangeFinish = charcter->FollowSpringArm->TargetArmLength >= 299.f ? true : charcter->FollowSpringArm->TargetArmLength <= 101.f;
		}
	}

}

void UtestAnimInstance::NativeUninitializeAnimation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("UNINITIALIZE")));
}

void UtestAnimInstance::HitAnimation(const FVector2D& enenmyDirection)
{
	APawn* pawn = TryGetPawnOwner();
	FVector2D targetvec = enenmyDirection - FVector2D(pawn->GetActorLocation());
	UAnimMontage* tempMotage = nullptr;

	if (targetvec.Dot(FVector2D(pawn->GetActorRotation().Vector())) > 0) {
		tempMotage = *AnimMontageMap.Find(TEXT("hitReactionFrontMontage"));

		//PlayMontage(true, hitReactionFrontMontage);
	}
	else {
		tempMotage = *AnimMontageMap.Find(TEXT("hitReactionBackMontage"));

		//PlayMontage(true, hitReactionBackMontage);
	}

	if (tempMotage != nullptr) {
		PlayMontage(true, tempMotage);

	}

}

bool UtestAnimInstance::PlayMontage(bool isplay, UAnimMontage* ainmMontage)
{
	if (!isplay) return false;
	if (Montage_IsPlaying(ainmMontage)) return false;

	Montage_Play(ainmMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.0f, true);
	return true;
}
