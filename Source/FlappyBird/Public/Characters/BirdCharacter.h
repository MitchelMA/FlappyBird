#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BirdCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;



DECLARE_LOG_CATEGORY_EXTERN(LogBirdCharacter, Log, All);

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API ABirdCharacter : public APaperCharacter
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

	UPROPERTY(EditAnywhere, Category=Collision)
	TArray<FName> DeathTags;
	UPROPERTY(EditAnywhere, Category=Collision)
	TArray<FName> ObstaclePassedTags;
	UPROPERTY(EditAnywhere, Category=Collision)
	TArray<FName> GroundHitTags;
	UPROPERTY(EditAnywhere, Category=Collision)
	TArray<FName> ObstacleHitTags;

	float TerminalVelocity = 0;
	UPROPERTY(BlueprintGetter=GetIsBirdDead)
	bool bIsBirdDead = false;
	bool bIsBirdOnGround = false;

	UFUNCTION(NetMulticast, Reliable)
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
	void BirdDied();
	UFUNCTION()
	void BirdHitGround();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBirdStarted);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBirdDied);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBirdPassedObstacle);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBirdHitObstacle);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBirdHitGround);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBirdFlapped);
	
	ABirdCharacter();

	UPROPERTY(BlueprintAssignable, Category=Events)
	FOnBirdStarted OnBirdStarted;
	UPROPERTY(BlueprintAssignable, Category=Events)
	FOnBirdDied OnBirdDied;
	UPROPERTY(BlueprintAssignable, Category=Events)
	FOnBirdPassedObstacle OnBirdPassedObstacle;
	UPROPERTY(BlueprintAssignable, Category=Events)
	FOnBirdHitObstacle OnBirdHitObstacle;
	UPROPERTY(BlueprintAssignable, Category=Events)
	FOnBirdHitGround OnBirdHitGround;
	UPROPERTY(BlueprintAssignable, Category=Events)
	FOnBirdFlapped OnBirdFlapped;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Server, Reliable)
	void Fly(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Blueprintable, BlueprintPure)
	FORCEINLINE bool GetIsBirdDead() const noexcept { return bIsBirdDead; }
};
