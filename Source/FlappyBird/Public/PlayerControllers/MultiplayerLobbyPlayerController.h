#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayerLobbyPlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMultiplayerLobbyPlayerController, Log, All);

UCLASS()
class FLAPPYBIRD_API AMultiplayerLobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	TSubclassOf<UUserWidget> LobbyMenuWidgetHost;
	TSubclassOf<UUserWidget> LobbyMenuWidgetClient;

public:

	AMultiplayerLobbyPlayerController();

	virtual void BeginPlay() override;

	UFUNCTION(Reliable, Client)
	void ApplyWidget();
};
