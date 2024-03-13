#include "ResetInstigator.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogResetInstigator);

// Sets default values
AResetInstigator::AResetInstigator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void
AResetInstigator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void
AResetInstigator::Tick(
	const float DeltaTime
)
{
	Super::Tick(DeltaTime);

}

void
AResetInstigator::ResetAll()
const
{
	const auto LevelName = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld()));
	UGameplayStatics::OpenLevel(GetWorld(), LevelName, true);
}

