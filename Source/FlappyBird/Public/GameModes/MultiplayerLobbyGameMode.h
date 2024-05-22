#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerLobbyGameMode.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API AMultiplayerLobbyGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLogin, AController*, NewPlayer);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLogout, AController*, Exiting);

	AMultiplayerLobbyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerLogin OnPlayerLoginEvent;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerLogout OnPlayerLogoutEvent;
};
