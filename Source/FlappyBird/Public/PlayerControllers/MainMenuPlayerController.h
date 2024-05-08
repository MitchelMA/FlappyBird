#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMainMenuPlayerController, Log, All)

UCLASS()
class FLAPPYBIRD_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

	TSubclassOf<UUserWidget> MainMenuWidget;

public:
	AMainMenuPlayerController();

	virtual void BeginPlay() override;
};
