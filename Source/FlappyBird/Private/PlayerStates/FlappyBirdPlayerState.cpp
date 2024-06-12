#include "PlayerStates/FlappyBirdPlayerState.h"

AFlappyBirdPlayerState::AFlappyBirdPlayerState()
{
}

void
AFlappyBirdPlayerState::BeginPlay()
{
	Super::BeginPlay();

	BindEvents();
}

void
AFlappyBirdPlayerState::EndPlay(
	const EEndPlayReason::Type EndPlayReason
)
{
	Super::EndPlay(EndPlayReason);

	UnBindEvents();
}

ACharacter*
AFlappyBirdPlayerState::GetPlayerCharacter()
const
{
	const auto StateOwner = GetOwner();
	if (!StateOwner)
		return nullptr;

	const auto PlayerController = Cast<APlayerController>(StateOwner);
	if (!PlayerController)
		return nullptr;

	return PlayerController->GetCharacter();
}

void
AFlappyBirdPlayerState::OnBirdStarted()
{
	OnBirdStartedEvent.Broadcast(Cast<ABirdCharacter>(GetPlayerCharacter()));
}

void
AFlappyBirdPlayerState::OnBirdDied()
{
	OnBirdDiedEvent.Broadcast(Cast<ABirdCharacter>(GetPlayerCharacter()));
}

void
AFlappyBirdPlayerState::OnBirdPassedObstacle()
{
	OnBirdPassedObstacleEvent.Broadcast(Cast<ABirdCharacter>(GetPlayerCharacter()));
}

void
AFlappyBirdPlayerState::OnBirdHitObstacle()
{
	OnBirdHitObstacleEvent.Broadcast(Cast<ABirdCharacter>(GetPlayerCharacter()));
}

void
AFlappyBirdPlayerState::OnBirdHitGround()
{
	OnBirdHitGroundEvent.Broadcast(Cast<ABirdCharacter>(GetPlayerCharacter()));
}

void
AFlappyBirdPlayerState::OnBirdFlapped()
{
	OnBirdFlappedEvent.Broadcast(Cast<ABirdCharacter>(GetPlayerCharacter()));
}

void
AFlappyBirdPlayerState::BindEvents_Implementation()
{
	OnBirdStartedDelegate.BindDynamic(this, &ThisClass::OnBirdStarted);
	OnBirdDiedDelegate.BindDynamic(this, &ThisClass::OnBirdDied);
	OnBirdPassedObstacleDelegate.BindDynamic(this, &ThisClass::OnBirdPassedObstacle);
	OnBirdHitObstacleDelegate.BindDynamic(this, &ThisClass::OnBirdHitObstacle);
	OnBirdHitGroundDelegate.BindDynamic(this, &ThisClass::OnBirdHitGround);
	OnBirdFlappedDelegate.BindDynamic(this, &ThisClass::OnBirdFlapped);

	ABirdCharacter* PlayerCharacter = Cast<ABirdCharacter>(GetPlayerCharacter());
	if (PlayerCharacter == nullptr)
		return;

	PlayerCharacter->OnBirdStarted.Add(OnBirdStartedDelegate);
	PlayerCharacter->OnBirdDied.Add(OnBirdDiedDelegate);
	PlayerCharacter->OnBirdPassedObstacle.Add(OnBirdPassedObstacleDelegate);
	PlayerCharacter->OnBirdHitObstacle.Add(OnBirdHitObstacleDelegate);
	PlayerCharacter->OnBirdHitGround.Add(OnBirdHitGroundDelegate);
	PlayerCharacter->OnBirdFlapped.Add(OnBirdFlappedDelegate);
}

void
AFlappyBirdPlayerState::UnBindEvents_Implementation()
{
	OnBirdStartedDelegate.Unbind();
	OnBirdDiedDelegate.Unbind();
	OnBirdPassedObstacleDelegate.Unbind();
	OnBirdHitObstacleDelegate.Unbind();
	OnBirdHitGroundDelegate.Unbind();
	OnBirdFlappedDelegate.Unbind();

	ABirdCharacter* PlayerCharacter = Cast<ABirdCharacter>(GetPlayerCharacter());
	if (PlayerCharacter == nullptr)
		return;

	PlayerCharacter->OnBirdStarted.Remove(OnBirdStartedDelegate);
	PlayerCharacter->OnBirdDied.Remove(OnBirdDiedDelegate);
	PlayerCharacter->OnBirdPassedObstacle.Remove(OnBirdPassedObstacleDelegate);
	PlayerCharacter->OnBirdHitObstacle.Remove(OnBirdHitObstacleDelegate);
	PlayerCharacter->OnBirdHitGround.Remove(OnBirdHitGroundDelegate);
	PlayerCharacter->OnBirdFlapped.Remove(OnBirdFlappedDelegate);
}