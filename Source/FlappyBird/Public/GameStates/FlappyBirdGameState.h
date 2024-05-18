#pragma once

#include "Characters/BirdCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PlayerStates/FlappyBirdPlayerState.h"
#include "FlappyBirdGameState.generated.h"



UCLASS(Abstract, BlueprintType)
class FLAPPYBIRD_API AFlappyBirdGameState : public AGameState
{
	GENERATED_BODY()


public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(       FOnPlayerStarted, ABirdCharacter*, PlayerCharacter);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(          FOnPlayerDied, ABirdCharacter*, PlayerCharacter);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE         (      FOnAllPlayersDied);	   
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerPassedObstacle, ABirdCharacter*, PlayerCharacter);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam   (FOnPlayerHitObstacle, ABirdCharacter*, PlayerCharacter);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(     FOnPlayerHitGround, ABirdCharacter*, PlayerCharacter);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(       FOnPlayerFlapped, ABirdCharacter*, PlayerCharacter);
	

	AFlappyBirdGameState();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// --- Events --- //

	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerStarted OnPlayerStartedEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerDied OnPlayerDiedEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnAllPlayersDied OnAllPlayersDiedEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerPassedObstacle OnPlayerPassedObstacleEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerHitObstacle OnPlayerHitObstacleEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerHitGround OnPlayerHitGroundEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerFlapped OnPlayerFlappedEvent;

	// --- Join and leave notifiers --- //

	UFUNCTION(BlueprintCallable)
	void NotifyPlayerJoined(APlayerController* PlayerController);
	UFUNCTION(BlueprintCallable)
	void NotifyPlayerLeft(AController* Controller);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual AController* GetLeadingPlayer() { return nullptr; }


protected:

	// --- Bound event callbacks to the bird --- //
	
	UFUNCTION()
	virtual void OnPlayerStarted(ABirdCharacter* PlayerCharacter) {}
	UFUNCTION()
	virtual void OnPlayerDied(ABirdCharacter* PlayerCharacter) {}
	UFUNCTION()
	virtual void OnPlayerPassedObstacle(ABirdCharacter* PlayerCharacter) {}
	UFUNCTION()
	virtual void OnPlayerHitObstacle(ABirdCharacter* PlayerCharacter) {}
	UFUNCTION()
	virtual void OnPlayerHitGround(ABirdCharacter* PlayerCharacter) {}
	UFUNCTION()
	virtual void OnPlayerFlapped(ABirdCharacter* PlayerCharacter) {}

private:
	
	// --- Event delegates to the player characters --- //

	AFlappyBirdPlayerState::FOnBirdStarted::FDelegate				OnBirdStartedDelegate;
	AFlappyBirdPlayerState::FOnBirdDied::FDelegate					   OnBirdDiedDelegate;
	AFlappyBirdPlayerState::FOnBirdPassedObstacle::FDelegate OnBirdPassedObstacleDelegate;
	AFlappyBirdPlayerState::FOnBirdHitObstacle::FDelegate		OnBirdHitObstacleDelegate;
	AFlappyBirdPlayerState::FOnBirdHitGround::FDelegate			  OnBirdHitGroundDelegate;
	AFlappyBirdPlayerState::FOnBirdFlapped::FDelegate				OnBirdFlappedDelegate;
};
