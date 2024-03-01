// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdCharacter.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PawnMovementComponent.h"

DEFINE_LOG_CATEGORY(LogBirdCharacter);

ABirdCharacter::ABirdCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(8., 8.);
}

void
ABirdCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
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
}



void
ABirdCharacter::Fly(
	const FInputActionValue& Value
)
{
	LaunchCharacter({0, 0, FlyVelocity}, true, true);
	if (auto movementComp = GetMovementComponent())
		GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Green, FString::Printf(TEXT("Velocity: %f"), movementComp->Velocity[2]));
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
