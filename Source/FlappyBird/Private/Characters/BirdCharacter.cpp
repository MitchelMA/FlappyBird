#include "Characters/BirdCharacter.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

DEFINE_LOG_CATEGORY(LogBirdCharacter);

ABirdCharacter::ABirdCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(8., 8.);
}

void
ABirdCharacter::BirdStarted()
{
	GetMovementComponent()->Activate();
}

void
ABirdCharacter::ColliderBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	const int32 OtherBodyIndex,
	const bool bFromSweep,
	const FHitResult& SweepResult
)
{
	bool bCastedDeath = false;
	bool bCastedObstacleHit = false;
	bool bCastedObstaclePass = false;
	
	for (const auto Name : OtherComp->ComponentTags)
	{
		if (DeathTags.Contains(Name) && !bCastedDeath && !bIsBirdDead)
		{
			OnBirdDied.Broadcast();
			bCastedDeath = true;
		}

		if (ObstacleHitTags.Contains(Name) && !bCastedObstacleHit)
		{
			OnBirdHitObstacle.Broadcast();
			bCastedObstacleHit = true;
		}

		if (ObstaclePassedTags.Contains(Name) && !bCastedObstaclePass && !bIsBirdDead)
		{
			OnBirdPassedObstacle.Broadcast();
			bCastedObstaclePass = true;
		}
	}
}

void
ABirdCharacter::ColliderHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	const FVector NormalImpulse,
	const FHitResult& Hit)
{
	bool bCastedDeath = false;
	bool bCastedObstacleHit = false;
	bool bCastedGroundHit = false;
	
	for (const auto Name : OtherComp->ComponentTags)
	{
		if (DeathTags.Contains(Name) && !bCastedDeath && !bIsBirdDead)
		{
			OnBirdDied.Broadcast();
			bCastedDeath = true;
		}

		if (ObstacleHitTags.Contains(Name) && !bCastedObstacleHit)
		{
			OnBirdHitObstacle.Broadcast();
			bCastedObstacleHit = true;
		}

		if (GroundHitTags.Contains(Name) && !bCastedGroundHit)
		{
			OnBirdHitGround.Broadcast();
			bCastedGroundHit = true;
		}
	}
}

void
ABirdCharacter::BirdDied()
{
	if (bIsBirdDead)
		return;
	
	bIsBirdDead = true;
	GetSprite()->Stop();
}

void
ABirdCharacter::BirdHitGround()
{
	if (bIsBirdOnGround)
		return;
	
	bIsBirdOnGround = true;
}


void
ABirdCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnBirdStarted.AddDynamic(this, &ABirdCharacter::BirdStarted);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABirdCharacter::ColliderBeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABirdCharacter::ColliderHit);

	OnBirdDied.AddDynamic(this, &ABirdCharacter::ABirdCharacter::BirdDied);
	OnBirdHitGround.AddDynamic(this, &ABirdCharacter::ABirdCharacter::BirdHitGround);

	if(!GConfig->GetFloat(
		TEXT("/Script/Engine.PhysicsSettings"),
		TEXT("DefaultTerminalVelocity"),
		TerminalVelocity,
		GEngineIni)
	)
		UE_LOG(LogBirdCharacter, Error, TEXT("Failed to read terminal velocity"));

	GetMovementComponent()->Deactivate();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void
ABirdCharacter::Tick(
	float DeltaSeconds
)
{
	if (bIsBirdOnGround)
		return;
	
	const auto MovementComp = GetMovementComponent();
	const auto FallingVelocity = MovementComp->Velocity[2];
	const auto YRotationPercentage = FallingVelocity / TerminalVelocity;
	
	// GEngine->AddOnScreenDebugMessage(-1, .05f, FColor::Orange, FString::Printf(TEXT("Velocity: %f"), FallingVelocity));

	if(const auto SpriteComp = GetSprite())
		SpriteComp->SetRelativeRotation({YRotationPercentage * VelocityRotationDeg, 0, 0});
}



void
ABirdCharacter::Fly(
	const FInputActionValue& Value
)
{
	if (bIsBirdDead)
		return;
	
	const auto MovementComp = GetMovementComponent();
	if (!MovementComp->IsActive())
		OnBirdStarted.Broadcast();

	LaunchCharacter({0, 0, FlyVelocity}, false, true);
	OnBirdFlapped.Broadcast();
}

void
ABirdCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent
)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// flying action
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Triggered, this, &ABirdCharacter::Fly);
		UE_LOG(LogBirdCharacter, Log, TEXT("Successfully setup input components"));

	}
	else
	{
		UE_LOG(LogBirdCharacter, Error, TEXT("'%s' Failed to setup input component"), *GetNameSafe(this));
	}
}
