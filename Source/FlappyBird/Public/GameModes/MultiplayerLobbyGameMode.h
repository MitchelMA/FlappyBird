#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerLobbyGameMode.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AMultiplayerLobbyGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined, APlayerController*, PlayerController);
	
	AMultiplayerLobbyGameMode();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerJoined OnPlayerJoinedEvent;

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
