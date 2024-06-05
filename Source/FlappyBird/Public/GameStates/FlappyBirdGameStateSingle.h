#pragma once

#include "CoreMinimal.h"
#include "FlappyBirdGameState.h"
#include "FlappyBirdGameStateSingle.generated.h"

UCLASS(BlueprintType)
class FLAPPYBIRD_API AFlappyBirdGameStateSingle : public AFlappyBirdGameState
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<AController*, ACharacter*> BoundCharacters;

public:
	AFlappyBirdGameStateSingle();

	virtual AController* GetLeadingPlayer() override;
	virtual bool IsLeadingPlayer(const AController* Player) override;

	virtual void OnPlayerStarted(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerDied(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerPassedObstacle(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerHitObstacle(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerHitGround(ABirdCharacter* PlayerCharacter) override;
	virtual void OnPlayerFlapped(ABirdCharacter* PlayerCharacter) override;
};
