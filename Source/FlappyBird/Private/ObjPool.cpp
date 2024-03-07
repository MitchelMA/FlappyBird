// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjPool.h"

void AObjPool::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const auto PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AObjPool, ActorType))
	{
		if(!ActorType->IsChildOf(AActor::StaticClass()))
			ActorType = nullptr;
	}
}

// Sets default values
AObjPool::AObjPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjPool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor*
AObjPool::RequestObject(
	const FVector& SpawnLocation
) noexcept
{
	if (Pool.IsEmpty())
	{
		return GetWorld()->SpawnActor(
			ActorType, // Type
			// Name
			&SpawnLocation, // Location
			nullptr // Rotation
			// Actor-template
			// No-Collision-Fail
			// Remote-Owned
			// Owner
			// Instigator
			// No-Fail
			// Override-Level
			// Defer-construction
		);
	}
	
	AActor* LastObject = Pool.Pop();
	LastObject->SetActorLocation(SpawnLocation, false, nullptr, ETeleportType::ResetPhysics);
	ActivateObject(LastObject);
	return LastObject;
}

bool
AObjPool::StoreObject(
	AActor* Object
) noexcept
{
	if (Object == nullptr && !Cast<UClass>(Object)->IsChildOf(ActorType))
		return false;

	DeactivateObject(Object);
	Pool.AddUnique(Object);
	return true;
}

void
AObjPool::ActivateObject(
	AActor* Object
) noexcept
{
	Object->SetActorHiddenInGame(false);
	Object->SetActorEnableCollision(true);
}

void
AObjPool::DeactivateObject(
	AActor* Object
) noexcept
{
	Object->SetActorHiddenInGame(true);
	Object->SetActorEnableCollision(false);
}

