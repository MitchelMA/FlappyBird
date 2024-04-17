#include "ScoreCounter.h"

#include "Components/TextRenderComponent.h"

// Sets default values
AScoreCounter::AScoreCounter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	DefaultSceneRoot->Mobility = EComponentMobility::Static;
	RootComponent = DefaultSceneRoot;
	
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Score Text"));
	ScoreText->Mobility = EComponentMobility::Static;
	ScoreText->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void
AScoreCounter::BeginPlay()
{
	Super::BeginPlay();

	Score = 0;
	SetDisplayScore(0);
}

// Called every frame
void
AScoreCounter::Tick(
	 const float DeltaTime
)
{
	Super::Tick(DeltaTime);

}

void
AScoreCounter::IncreaseScore(
	const int64 Amount
)
{
	if (Amount == 0)
		return;
	
	Score += Amount;
	SetDisplayScore(Score);
	
	OnScoreIncreasedDelegate.Broadcast(Score, Amount);
}

void
AScoreCounter::SetDisplayScore(
	const int64 DisplayScore
) noexcept
{
	auto ScoreStr = FString::FromInt(DisplayScore);
	const int32 Diff = ScoreMinimalDisplaylength - ScoreStr.Len();

	for (int32 i = 0; i < Diff; i++)
		ScoreStr.InsertAt(0, '0');

	ScoreText->SetText(FText::FromString(ScoreStr));
}