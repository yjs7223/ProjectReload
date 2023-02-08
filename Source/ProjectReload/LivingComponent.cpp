// Fill out your copyright notice in the Description page of Project Settings.


#include "LivingComponent.h"

// Sets default values for this component's properties
ULivingComponent::ULivingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULivingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULivingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULivingComponent::Ondamage(float damage)
{
	HealthPoint -= damage;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("health : %f"), HealthPoint));

	if (HealthPoint <= 0.f) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, ("Die"));
		isDie = true;
	}
}

