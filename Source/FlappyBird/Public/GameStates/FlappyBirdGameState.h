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
	// --- Delegates --- //

	// Starting
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(           FOnPlayerStarted, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(       FOnLeadPlayerStarted, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE         (       FOnAllPlayersStarted);

	// Dying
	
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(              FOnPlayerDied, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(          FOnLeadPlayerDied, ABirdCharacter*, PlayerCharacter);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE         (          FOnAllPlayersDied);

	// Passing Obstacles
	
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(    FOnPlayerPassedObstacle, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeadPlayerPassedObstacle, ABirdCharacter*, PlayerCharacter);

	// Hitting Obstacles
	
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(       FOnPlayerHitObstacle, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(   FOnLeadPlayerHitObstacle, ABirdCharacter*, PlayerCharacter);

	// Hitting Ground
	
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(         FOnPlayerHitGround, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(     FOnLeadPlayerHitGround, ABirdCharacter*, PlayerCharacter);

	// Wing Flapping
	
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(           FOnPlayerFlapped, ABirdCharacter*, PlayerCharacter);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(       FOnLeadPlayerFlapped, ABirdCharacter*, PlayerCharacter);
	

	AFlappyBirdGameState();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// --- Events --- //

	// Starting
	
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerStarted OnPlayerStartedEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnLeadPlayerStarted OnLeadPlayerStartedEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnAllPlayersStarted OnAllPlayersStartedEvent;

	// Dying
	
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerDied OnPlayerDiedEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnLeadPlayerDied OnLeadPlayerDiedEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnAllPlayersDied OnAllPlayersDiedEvent;

	// Passing Obstacles
	
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerPassedObstacle OnPlayerPassedObstacleEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnLeadPlayerPassedObstacle OnLeadPlayerPassedObstacleEvent;

	// Hitting Obstacles
	
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerHitObstacle OnPlayerHitObstacleEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnLeadPlayerHitObstacle OnLeadPlayerHitObstacleEvent;

	// Hitting grounds
	
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerHitGround OnPlayerHitGroundEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnLeadPlayerHitGround OnLeadPlayerHitGroundEvent;

	// Wing Flapping
	
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnPlayerFlapped OnPlayerFlappedEvent;
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FOnLeadPlayerFlapped OnLeadPlayerFlappedEvent;

	// --- Join and leave notifiers --- //

	UFUNCTION(BlueprintCallable)
	virtual void NotifyPlayerJoined(APlayerController* PlayerController);
	UFUNCTION(BlueprintCallable)
	virtual void NotifyPlayerLeft(AController* Controller);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual AController* GetLeadingPlayer() { return nullptr; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual bool IsLeadingPlayer(const AController* Player) { return false; }


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
