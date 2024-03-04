#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BirdCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBirdStartedDelegate);

DECLARE_LOG_CATEGORY_EXTERN(LogBirdCharacter, Log, All);

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API ABirdCharacter final : public APaperCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	UInputAction* FlyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Flying, meta=(AllowPrivateAccess="true"))
	float FlyVelocity = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Flying, meta=(AllowPrivateAccess="true"))
	float VelocityRotationDeg;
	
	float TerminalVelocity = 0;

	UFUNCTION()
	void BirdStarted();

public:
	ABirdCharacter();

	UPROPERTY(BlueprintAssignable, Category=Events)
	FBirdStartedDelegate OnBirdStartedDelegate;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	void Fly(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
