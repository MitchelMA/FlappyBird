// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SpeedComponent.h"

DEFINE_LOG_CATEGORY(LogSpeedComponent)

void
USpeedComponent::BeginPlay()
{
	Super::BeginPlay();
}

void
USpeedComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

double
USpeedComponent::GetSpeed()
{
	UE_LOG(LogSpeedComponent, Error, TEXT("IMPLEMENTATION NOT DEFINED: There's no implementation of GetSpeed()"));
	return 0.;
}
