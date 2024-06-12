#pragma once

#include "CoreMinimal.h"
#include "Characters/BirdCharacter.h"
#include "GameFramework/PlayerState.h"
#include "FlappyBirdPlayerState.generated.h"



UCLASS(BlueprintType)
class FLAPPYBIRD_API AFlappyBirdPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(       FOnBirdStarted, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(          FOnBirdDied, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBirdPassedObstacle, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(   FOnBirdHitObstacle, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(     FOnBirdHitGround, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(       FOnBirdFlapped, ABirdCharacter*, PlayerCharacter);

	AFlappyBirdPlayerState();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	FOnBirdStarted				 OnBirdStartedEvent;
	FOnBirdDied						OnBirdDiedEvent;
	FOnBirdPassedObstacle OnBirdPassedObstacleEvent;
	FOnBirdHitObstacle		 OnBirdHitObstacleEvent;
	FOnBirdHitGround		   OnBirdHitGroundEvent;
	FOnBirdFlapped				 OnBirdFlappedEvent;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACharacter* GetPlayerCharacter() const;

protected:

	UFUNCTION(BlueprintCallable)
	void OnBirdStarted();

	UFUNCTION(BlueprintCallable)
	void OnBirdDied();
	
	UFUNCTION(BlueprintCallable)
	void OnBirdPassedObstacle();

	UFUNCTION(BlueprintCallable)
	void OnBirdHitObstacle();

	UFUNCTION(BlueprintCallable)
	void OnBirdHitGround();

	UFUNCTION(BlueprintCallable)
	void OnBirdFlapped();

private:
	
	ABirdCharacter::FOnBirdStarted::FDelegate			    OnBirdStartedDelegate;
	ABirdCharacter::FOnBirdDied::FDelegate                     OnBirdDiedDelegate;
	ABirdCharacter::FOnBirdPassedObstacle::FDelegate OnBirdPassedObstacleDelegate;
	ABirdCharacter::FOnBirdHitObstacle::FDelegate       OnBirdHitObstacleDelegate;
	ABirdCharacter::FOnBirdHitGround::FDelegate           OnBirdHitGroundDelegate;
	ABirdCharacter::FOnBirdFlapped::FDelegate               OnBirdFlappedDelegate;

	UFUNCTION(Server, Reliable)
	void BindEvents();
	UFUNCTION(Server, Reliable)
	void UnBindEvents();
};
