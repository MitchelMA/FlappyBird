// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"
#include "PipeObstacle.h"
#include "ObjPool.h"
#include "Components/BoxComponent.h"

DEFINE_LOG_CATEGORY(LogObstacleSpawner);

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	DefaultSceneRoot->Mobility = EComponentMobility::Static;
	RootComponent = DefaultSceneRoot;

	SpawnTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Trigger"));
	SpawnTrigger->Mobility = EComponentMobility::Static;
	SpawnTrigger->SetupAttachment(DefaultSceneRoot);

}

// Called when the game starts or when spawned
void
AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void
AObstacleSpawner::Tick(
	const float DeltaTime
)
{
	Super::Tick(DeltaTime);
}

APipeObstacle*
AObstacleSpawner::SpawnPipe()
noexcept
{
	if (!IsValid(ObjectPool))
		return nullptr;

	const auto Pipe = Cast<APipeObstacle>(ObjectPool->RequestObject(GetActorLocation()));

	if (!IsValid(Pipe))
		UE_LOG(LogObstacleSpawner, Warning, TEXT("Failed to cast requested object from pool to a pipe obstacle"));
	
	return Pipe;
}

