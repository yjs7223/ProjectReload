// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "testAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRELOAD_API UtestAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UtestAnimInstance();

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeUninitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
		void HitAnimation(const FVector2D& enenmyDirection);

	UFUNCTION(BlueprintCallable)
		bool PlayMontage(bool isplaying, UAnimMontage* ainmMontage);

	UPROPERTY(EditDefaultsOnly)
		TMap<FName, UAnimMontage*> AnimMontageMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UAnimMontage* testMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isMoveing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isFall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isFireEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float forwardValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float rightValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isRun;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isAimChangeFinish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float speed;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float AimYaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float AimPitch;
};
