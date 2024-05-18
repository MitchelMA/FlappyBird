#pragma once

#include "CoreMinimal.h"
#include "FlappyBirdGameMode.h"
#include "GameFramework/GameMode.h"
#include "FlappyBirdGameModeSingle.generated.h"

UCLASS(BlueprintType)
class FLAPPYBIRD_API AFlappyBirdGameModeSingle : public AFlappyBirdGameMode
{
	GENERATED_BODY()
public:
	AFlappyBirdGameModeSingle();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
