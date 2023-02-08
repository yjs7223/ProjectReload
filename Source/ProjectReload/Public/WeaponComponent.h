// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EFireMode : uint8
{
	Single UMETA(DisplayName = "Single"),
	Auto UMETA(DisplayName = "Auto"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRELOAD_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		int currentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		int holdingAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool isReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		EFireMode eFiremode;
		
};
