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
	GetCapsuleComponent()->InitCapsuleSize(8., 8.);
}

void
ABirdCharacter::BirdStarted()
{
	GetMovementComponent()->Activate();
}


void
ABirdCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnBirdStartedDelegate.AddDynamic(this, &ABirdCharacter::BirdStarted);

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
	const auto MovementComp = GetMovementComponent();
	const auto FallingVelocity = MovementComp->Velocity[2];
	const auto YRotationPercentage = FallingVelocity / TerminalVelocity;
	
	GEngine->AddOnScreenDebugMessage(-1, .05f, FColor::Orange, FString::Printf(TEXT("Velocity: %f"), FallingVelocity));

	if(const auto SpriteComp = GetSprite())
		SpriteComp->SetRelativeRotation({YRotationPercentage * VelocityRotationDeg, 0, 0});
}



void
ABirdCharacter::Fly(
	const FInputActionValue& Value
)
{
	const auto MovementComp = GetMovementComponent();
	if (!MovementComp->IsActive())
		OnBirdStartedDelegate.Broadcast();
	
	LaunchCharacter({0, 0, FlyVelocity}, true, true);
}

void
ABirdCharacter::SetupPlayerInputComponent(
	UInputComponent* PlayerInputComponent
)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// jumping action
		EnhancedInputComponent->BindAction(FlyAction, ETriggerEvent::Triggered, this, &ABirdCharacter::Fly);
		UE_LOG(LogBirdCharacter, Log, TEXT("Successfully setup input components"));
	}
	else
	{
		UE_LOG(LogBirdCharacter, Error, TEXT("'%s' Failed to setup input component"), *GetNameSafe(this));
	}
}
