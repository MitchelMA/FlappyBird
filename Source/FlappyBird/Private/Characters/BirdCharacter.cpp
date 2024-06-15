#include "Characters/BirdCharacter.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogBirdCharacter);

ABirdCharacter::ABirdCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(8., 8.);
}

void
ABirdCharacter::BirdStarted_Implementation()
{
	Cast<UCharacterMovementComponent>(GetMovementComponent())->GravityScale = 1.f;
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
			BroadcastPassedObstacle();
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
	const float DeltaSeconds
)
{
	Super::Tick(DeltaSeconds);
	
	if (bIsBirdOnGround)
		return;
	
	const auto MovementComp = GetMovementComponent();
	const auto FallingVelocity = MovementComp->Velocity[2];
	const auto YRotationPercentage = FallingVelocity / TerminalVelocity;

	if(const auto SpriteComp = GetSprite())
		SpriteComp->SetRelativeRotation({YRotationPercentage * VelocityRotationDeg, 0, 0});
}



void
ABirdCharacter::Fly_Implementation(
	const FInputActionValue& Value
)
{
	if (bIsBirdDead)
		return;

	const auto MovementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (MovementComp->GravityScale <= 0.0001f)
		BroadcastStarted();

	LaunchCharacter({0, 0, FlyVelocity}, false, true);
	BroadcastFlap();
}

void
ABirdCharacter::BroadcastFlap_Implementation()
{
	OnBirdFlapped.Broadcast();
}

void
ABirdCharacter::BroadcastStarted_Implementation()
{
	OnBirdStarted.Broadcast();
}

void
ABirdCharacter::BroadcastPassedObstacle_Implementation()
{
	OnBirdPassedObstacle.Broadcast();
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
