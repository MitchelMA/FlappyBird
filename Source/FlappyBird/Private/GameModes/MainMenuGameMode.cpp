
#include "GameModes/MainMenuGameMode.h"
#include "PlayerControllers/MainMenuPlayerController.h"

AMainMenuGameMode::AMainMenuGameMode()
{
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
}
