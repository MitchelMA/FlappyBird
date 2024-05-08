#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

UCLASS()
class FLAPPYBIRD_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

	

public:
	AMainMenuPlayerController();

	virtual void BeginPlay() override;
};
