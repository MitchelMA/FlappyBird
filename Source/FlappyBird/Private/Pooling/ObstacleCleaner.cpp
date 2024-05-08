#include "Pooling/ObstacleCleaner.h"

#include "Components/BoxComponent.h"
#include "Pooling/ObjPool.h"

DEFINE_LOG_CATEGORY(LogObstacleCleaner);

void
AObstacleCleaner::OnCleanTrigger(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	const int32 OtherBodyIndex,
	const bool bFromSweep,
	const FHitResult& SweepResult
)
{
	bool ContainsTag = false;
	for (const auto& Tag : OtherActor->Tags)
	{
		if (!ObstacleTags.Contains(Tag))
			continue;

		ContainsTag = true;
	}

	if (!ContainsTag)
		return;

	
	if (!IsValid(ObjectPool))
		UE_LOG(LogObstacleCleaner, Warning, TEXT("No reference was set for the ObjectPool"));

	if (!ObjectPool->StoreObject(OtherActor))
		UE_LOG(LogObstacleCleaner, Warning,
			TEXT("Failed to store object %s, possible type-confliction"), *FString(OtherActor->GetName()));
}

// Sets default values
AObstacleCleaner::AObstacleCleaner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	DefaultSceneRoot->Mobility = EComponentMobility::Static;
	RootComponent = DefaultSceneRoot;

	CleanTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Cleaning Trigger"));
	CleanTrigger->Mobility = EComponentMobility::Static;
	CleanTrigger->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AObstacleCleaner::BeginPlay()
{
	
	Super::BeginPlay();

	// TODO! Let op overlaps, zijn heavy!
	CleanTrigger->OnComponentBeginOverlap.AddDynamic(this, &AObstacleCleaner::OnCleanTrigger);
	if (!IsValid(ObjectPool))
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red,
			TEXT("Missing Reference of ObjectPool"));
}

// Called every frame
void AObstacleCleaner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

