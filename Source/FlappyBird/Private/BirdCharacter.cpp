#include "BirdCharacter.h"
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

	CapsuleColliderTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleTrigger"));
	CapsuleColliderTrigger->SetupAttachment(RootComponent);
	CapsuleColliderTrigger->InitCapsuleSize(8., 11.);
	CapsuleColliderTrigger->SetCollisionProfileName(TEXT("Trigger"));
	
	GetCapsuleComponent()->InitCapsuleSize(8., 8.);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
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
			OnBirdDiedDelegate.Broadcast();
			bCastedDeath = true;
		}

		if (ObstacleHitTags.Contains(Name) && !bCastedObstacleHit)
		{
			OnBirdHitObstacleDelegate.Broadcast();
			bCastedObstacleHit = true;
		}

		if (ObstaclePassedTags.Contains(Name) && !bCastedObstaclePass && !bIsBirdDead)
		{
			OnBirdPassedObstacleDelegate.Broadcast();
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
			OnBirdDiedDelegate.Broadcast();
			bCastedDeath = true;
		}

		if (ObstacleHitTags.Contains(Name) && !bCastedObstacleHit)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
				FString::Printf(TEXT("Collision-tag: %s"), *Name.ToString()));
			OnBirdHitObstacleDelegate.Broadcast();
			bCastedObstacleHit = true;
		}

		if (GroundHitTags.Contains(Name) && !bCastedGroundHit)
		{
			OnBirdHitGroundDelegate.Broadcast();
			bCastedGroundHit = true;
		}
	}
}

// void
// ABirdCharacter::ColliderTriggerBeginOverlap(
// 	UPrimitiveComponent* OverlappedComponent,
// 	AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp,
// 	const int32 OtherBodyIndex,
// 	const bool bFromSweep,
// 	const FHitResult& SweepResult
// )
// {
// 	bool bCastedGroundHit = false;
// 	
// 	for (const auto Name : OtherComp->ComponentTags)
// 	{
// 		if (!GroundHitTags.Contains(Name) || bCastedGroundHit || bIsBirdDead)
// 			continue;
// 		
// 		OnBirdDiedDelegate.Broadcast();
// 		OnBirdHitGroundDelegate.Broadcast();
// 		bCastedGroundHit = true;
// 	}
// }

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

	OnBirdStartedDelegate.AddDynamic(this, &ABirdCharacter::BirdStarted);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABirdCharacter::ColliderBeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABirdCharacter::ColliderHit);
	// CapsuleColliderTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABirdCharacter::ColliderTriggerBeginOverlap);

	OnBirdDiedDelegate.AddDynamic(this, &ABirdCharacter::ABirdCharacter::BirdDied);
	OnBirdHitGroundDelegate.AddDynamic(this, &ABirdCharacter::ABirdCharacter::BirdHitGround);

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
		OnBirdStartedDelegate.Broadcast();

	LaunchCharacter({0, 0, FlyVelocity}, false, true);
	OnBirdFlapDelegate.Broadcast();
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
