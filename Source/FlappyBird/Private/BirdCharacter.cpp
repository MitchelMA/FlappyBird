#include "BirdCharacter.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "ResetInstigator.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogBirdCharacter);

ABirdCharacter::ABirdCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleColliderTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleTrigger"));
	CapsuleColliderTrigger->SetupAttachment(RootComponent);
	CapsuleColliderTrigger->InitCapsuleSize(8., 11.);
	CapsuleColliderTrigger->SetCollisionProfileName(TEXT("Trigger"));
	
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
	for (const auto Name : OtherComp->ComponentTags)
	{
		if (DeathTags.Contains(Name))
			OnBirdDiedDelegate.Broadcast();

		if (ObstaclePassedTags.Contains(Name) && !bIsBirdDead)
			OnBirdPassedObstacleDelegate.Broadcast();
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
	for (const auto Name : OtherComp->ComponentTags)
	{
		if (DeathTags.Contains(Name))
			OnBirdDiedDelegate.Broadcast();

		if (GroundTags.Contains(Name))
		{
			OnBirdHitGroundDelegate.Broadcast();
			OnBirdDiedDelegate.Broadcast();
		}
	}
}

void
ABirdCharacter::ColliderTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	const int32 OtherBodyIndex,
	const bool bFromSweep,
	const FHitResult& SweepResult
)
{
	for (const auto Name : OtherComp->ComponentTags)
	{
		if (!GroundTags.Contains(Name))
			continue;

		OnBirdHitGroundDelegate.Broadcast();
		OnBirdDiedDelegate.Broadcast();
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

	OnBirdStartedDelegate.AddDynamic(this, &ABirdCharacter::BirdStarted);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABirdCharacter::ColliderBeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABirdCharacter::ColliderHit);
	CapsuleColliderTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABirdCharacter::ColliderTriggerBeginOverlap);

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
}

void
ABirdCharacter::ResetCallback(
	const FInputActionValue& Value
)
{
	if (!bIsBirdDead)
		return;
	
	const auto ResetActor = UGameplayStatics::GetActorOfClass(GetWorld(), AResetInstigator::StaticClass());
	if (ResetActor == nullptr)
		return;

	if (const auto ResetInstigator = Cast<AResetInstigator>(ResetActor); ResetInstigator != nullptr)
		ResetInstigator->ResetAll();
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
		// Reset Action
		EnhancedInputComponent->BindAction(ResetAction, ETriggerEvent::Triggered, this, &ABirdCharacter::ResetCallback);
		
		UE_LOG(LogBirdCharacter, Log, TEXT("Successfully setup input components"));

	}
	else
	{
		UE_LOG(LogBirdCharacter, Error, TEXT("'%s' Failed to setup input component"), *GetNameSafe(this));
	}
}
