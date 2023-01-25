// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECTRELOAD_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable)
		bool Fire();

	// ���� �̵� ó��
	UFUNCTION()
		void MoveForward(float Value);

	// �¿� �̵� ó��
	UFUNCTION()
		void MoveRight(float Value);

	// Ű�� ������ ���� �÷��׸� �����մϴ�.
	UFUNCTION()
		void StartJump();

	// Ű�� ���� ���� �÷��׸� ����ϴ�.
	UFUNCTION()
		void StopJump();

	// Ű�� ������ �߻��մϴ�
	UFUNCTION()
		void StartFire();

	UFUNCTION()
		void StopFire();

	UFUNCTION()
		void StartRun();

	UFUNCTION()
		void StopRun();

	UFUNCTION()
		void Reload();

	UFUNCTION()
		void Crouching();

	UFUNCTION()
		void StartAiming();

	UFUNCTION()
		void StopAiming();

	UFUNCTION()
		void RotateInit();

	// FPS ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* FollowSpringArm;

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




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float TargetArmLenght;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		AActor* testactor;
};
