#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerLobbyGameMode.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AMultiplayerLobbyGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AMultiplayerLobbyGameMode();
};
