// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectReloadCharacter.generated.h"

UCLASS(config=Game)
class AProjectReloadCharacter : public ACharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AProjectReloadCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
		bool Fire();

	UFUNCTION()
		void StartFire();

	UFUNCTION()
		void StopFire();

	UFUNCTION()
		void RotateInit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool isRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector camerapos;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector camerapos_Crouch;

	UPROPERTY()
		FVector movevec;

	UPROPERTY()
		TSubclassOf<class ULivingComponent> asd;

	//virtual bool CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor = nullptr, const bool* bWasVisible = nullptr, int32* UserData = nullptr) const;
};

