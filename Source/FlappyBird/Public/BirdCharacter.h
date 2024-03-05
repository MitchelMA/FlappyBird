#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BirdCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBirdStartedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBirdDiedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBirdPassedObstacleDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBirdHitGroundDelegate);

DECLARE_LOG_CATEGORY_EXTERN(LogBirdCharacter, Log, All);

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API ABirdCharacter final : public APaperCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleColliderTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	UInputAction* FlyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Flying, meta=(AllowPrivateAccess="true"))
	float FlyVelocity = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Flying, meta=(AllowPrivateAccess="true"))
	float VelocityRotationDeg;

	UPROPERTY(EditAnywhere, Category=Collision)
	TArray<FName> DeathTags;
	UPROPERTY(EditAnywhere, Category=Collision)
	TArray<FName> ObstaclePassedTags;
	UPROPERTY(EditAnywhere, Category=Collision)
	TArray<FName> GroundTags;

	float TerminalVelocity = 0;
	bool bIsBirdDead = false;
	bool bIsBirdOnGround = false;

	UFUNCTION()
	void BirdStarted();
	UFUNCTION()
	void ColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							  const FHitResult & SweepResult);
	UFUNCTION()
	void ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
					 UPrimitiveComponent* OtherComp, FVector NormalImpulse,
					 const FHitResult& Hit);
	UFUNCTION()
	void ColliderTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
								     const FHitResult & SweepResult);

	UFUNCTION()
	void BirdDied();
	UFUNCTION()
	void BirdHitGround();

public:
	ABirdCharacter();

	UPROPERTY(BlueprintAssignable, Category=Events)
	FBirdStartedDelegate OnBirdStartedDelegate;
	UPROPERTY(BlueprintAssignable, Category=Events)
	FBirdDiedDelegate OnBirdDiedDelegate;
	UPROPERTY(BlueprintAssignable, Category=Events)
	FBirdPassedObstacleDelegate OnBirdPassedObstacleDelegate;
	UPROPERTY(BlueprintAssignable, Category=Events)
	FBirdHitGroundDelegate OnBirdHitGroundDelegate;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	void Fly(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
