
#include "Multiplayer/MultiplayerSubsystem.h"

#include "OnlineSubsystemUtils.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

UMultiplayerSubsystem::UMultiplayerSubsystem()
	: CreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionCompleted)),
	UpdateSessionCompleteDelegate(FOnUpdateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnUpdateSessionCompleted)),
	StartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnStartSessionCompleted)),
	EndSessionCompleteDelegate(FOnEndSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnEndSessionCompleted)),
	DestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionCompleted)),
	FindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnFindSessionCompleted)),
	JoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionCompleted))
{
}

void
UMultiplayerSubsystem::CreateGameSession(
	const int32 NumPublicConnections,
	const bool IsLANMatch)
{
	const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());

	if (!SessionInterface.IsValid())
	{
		OnCreateSessionCompleteEvent.Broadcast(false);
		return;
	}

	LastSessionSettings = MakeShareable(new FOnlineSessionSettings());
	LastSessionSettings->NumPublicConnections = NumPublicConnections;
	LastSessionSettings->NumPrivateConnections = 0;
	LastSessionSettings->bAllowInvites = true;
	LastSessionSettings->bAllowJoinInProgress = true;
	LastSessionSettings->bAllowJoinViaPresence = true;
	LastSessionSettings->bAllowJoinViaPresenceFriendsOnly = true;
	LastSessionSettings->bIsDedicated = false;
	LastSessionSettings->bIsLANMatch = IsLANMatch;
	LastSessionSettings->bShouldAdvertise = true;

	LastSessionSettings->Set(SETTING_MAPNAME , FString(TEXT("FLAPPYBIRD__CREATE")), EOnlineDataAdvertisementType::ViaOnlineService);

	CreateSessionCompleteDelegateHandle =
		SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	if(const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController(); !SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *LastSessionSettings))
	{
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

		OnCreateSessionCompleteEvent.Broadcast(false);
	}
}

void
UMultiplayerSubsystem::UpdateGameSession()
{
	const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	if (!SessionInterface.IsValid())
	{
		OnUpdateSessionCompleteEvent.Broadcast(false);
		return;
	}

	const TSharedPtr<FOnlineSessionSettings> UpdatedSessionSettings = MakeShareable(new FOnlineSessionSettings(*LastSessionSettings));

	UpdatedSessionSettings->Set(SETTING_MAPNAME, FString(TEXT("FLAPPYBIRD__UPDATE")), EOnlineDataAdvertisementType::ViaOnlineService);

	UpdateSessionCompleteDelegateHandle =
		SessionInterface->AddOnUpdateSessionCompleteDelegate_Handle(UpdateSessionCompleteDelegate);

	if (!SessionInterface->UpdateSession(NAME_GameSession, *UpdatedSessionSettings))
	{
		SessionInterface->ClearOnUpdateSessionCompleteDelegate_Handle(UpdateSessionCompleteDelegateHandle);
		OnUpdateSessionCompleteEvent.Broadcast(false);
		return;
	}

	LastSessionSettings = UpdatedSessionSettings;
}

void
UMultiplayerSubsystem::StartGameSession()
{
	const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	if (!SessionInterface.IsValid())
	{
		OnStartSessionCompleteEvent.Broadcast(false);
		return;
	}

	StartSessionCompleteDelegateHandle =
		SessionInterface->AddOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegate);

	if (!SessionInterface->StartSession(NAME_GameSession))
	{
		SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);
		OnStartSessionCompleteEvent.Broadcast(false);
	}
}

void
UMultiplayerSubsystem::EndGameSession()
{
	const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	if (!SessionInterface.IsValid())
	{
		OnEndSessionCompleteEvent.Broadcast(false);
		return;
	}

	EndSessionCompleteDelegateHandle =
		SessionInterface->AddOnEndSessionCompleteDelegate_Handle(EndSessionCompleteDelegate);

	if (!SessionInterface->EndSession(NAME_GameSession))
	{
		SessionInterface->ClearOnEndSessionCompleteDelegate_Handle(EndSessionCompleteDelegateHandle);
		OnEndSessionCompleteEvent.Broadcast(false);
	}
}

void
UMultiplayerSubsystem::DestroyGameSession()
{
	const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	if (!SessionInterface.IsValid())
	{
		OnDestroySessionCompleteEvent.Broadcast(false);
		return;
	}

	DestroySessionCompleteDelegateHandle =
		SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegate);

	if (!SessionInterface->DestroySession(NAME_GameSession))
	{
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);
		OnDestroySessionCompleteEvent.Broadcast(false);
	}
}

void
UMultiplayerSubsystem::FindGameSession(
	const int32 MaxSearchResults,
	const bool IsLANQuery
)
{
	const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	if (!SessionInterface.IsValid())
	{
		OnFindSessionCompleteEvent.Broadcast(TArray<FExposedSessionSearchResult>(), false);
		return;
	}

	FindSessionsCompleteDelegateHandle =
		SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);

	LastSessionSearch = MakeShareable(new FOnlineSessionSearch());
	LastSessionSearch->MaxSearchResults = MaxSearchResults;
	LastSessionSearch->bIsLanQuery = IsLANQuery;

	LastSessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), LastSessionSearch.ToSharedRef()))
	{
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);
		OnFindSessionCompleteEvent.Broadcast(TArray<FExposedSessionSearchResult>(), false);
	}
}

void
UMultiplayerSubsystem::JoinGameSession(
	const FExposedSessionSearchResult& SessionResult
)
{
	const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	if (!SessionInterface.IsValid())
	{
		OnJoinSessionCompleteEvent.Broadcast(EJoinSessionResult::UnknownError);
		return;
	}

	JoinSessionCompleteDelegateHandle =
		SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionResult.AsSearchResult()))
	{
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);
		OnJoinSessionCompleteEvent.Broadcast(EJoinSessionResult::UnknownError);
	}
}


void
UMultiplayerSubsystem::ServerTravel(
	UObject* WorldContextObject,
	const FString& LevelName
)
{

	if (!IsValid(WorldContextObject))
		return;

	const auto World = WorldContextObject->GetWorld();
	World->ServerTravel(LevelName, false, false);
}

void
UMultiplayerSubsystem::OnCreateSessionCompleted(
	const FName SessionName,
	const bool Successful
)
{
	if(const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()))
		SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegateHandle);

	OnCreateSessionCompleteEvent.Broadcast(Successful);
}

void
UMultiplayerSubsystem::OnUpdateSessionCompleted(
	const FName SessionName,
	const bool Successful
)
{
	if(const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()); SessionInterface.IsValid())
		SessionInterface->ClearOnUpdateSessionCompleteDelegate_Handle(UpdateSessionCompleteDelegateHandle);

	OnUpdateSessionCompleteEvent.Broadcast(Successful);
}

void
UMultiplayerSubsystem::OnStartSessionCompleted(
	const FName SessionName,
	const bool Successful
)
{
	if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()); SessionInterface.IsValid())
		SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(StartSessionCompleteDelegateHandle);

	OnStartSessionCompleteEvent.Broadcast(Successful);
}

void
UMultiplayerSubsystem::OnEndSessionCompleted(
	const FName SessionName,
	const bool Successful
)
{
	if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()); SessionInterface.IsValid())
		SessionInterface->ClearOnEndSessionCompleteDelegate_Handle(EndSessionCompleteDelegateHandle);

	OnEndSessionCompleteEvent.Broadcast(Successful);
}

void
UMultiplayerSubsystem::OnDestroySessionCompleted(
	const FName SessionName,
	const bool Successful
)
{
	if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()); SessionInterface.IsValid())
		SessionInterface->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionCompleteDelegateHandle);

	OnDestroySessionCompleteEvent.Broadcast(Successful);
}

void
UMultiplayerSubsystem::OnFindSessionCompleted(
	bool Successful
)
{
	if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()); SessionInterface.IsValid())
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);

	if (LastSessionSearch->SearchResults.Num() <= 0)
	{
		OnFindSessionCompleteEvent.Broadcast(TArray<FExposedSessionSearchResult>(), Successful);
		return;
	}

	TArray<FExposedSessionSearchResult> CastedArray;
	CastedArray.Reserve(LastSessionSearch->SearchResults.Num());
	for (auto& Elem : LastSessionSearch->SearchResults)
		CastedArray.Emplace(FExposedSessionSearchResult(Elem));
	OnFindSessionCompleteEvent.Broadcast(CastedArray, Successful);
}

void
UMultiplayerSubsystem::OnJoinSessionCompleted(
	const FName SessionName,
	const EOnJoinSessionCompleteResult::Type Result
)
{
	if (const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld()); SessionInterface.IsValid())
		SessionInterface->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegateHandle);

	OnJoinSessionCompleteEvent.Broadcast(static_cast<EJoinSessionResult>(Result));
}

bool
UMultiplayerSubsystem::TryTravelToCurrentSession()
{
	const IOnlineSessionPtr SessionInterface = Online::GetSessionInterface(GetWorld());
	if (!SessionInterface.IsValid())
		return false;

	FString ConnectString;
	if (!SessionInterface->GetResolvedConnectString(NAME_GameSession, ConnectString))
		return false;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
	return true;
}
