/// --- With the help of the following document --- ///
/// https://cedric-neukirchen.net/docs/session-management/sessions-in-cpp/
/// ----------------------------------------------- ///

#pragma once

#include "ExposedSessionSearchResult.h"
#include "JoinSessionResult.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnCreateSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnUpdateSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnStartSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnEndSessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnDestroySessionComplete, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCSOnFindSessionComplete, const TArray<FExposedSessionSearchResult>&, SessionResults, bool, Successful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCSOnJoinSessionComplete, EJoinSessionResult, Result);

UCLASS()
class FLAPPYBIRD_API UMultiplayerSubsystem : public UGameInstanceSubsystem
{
GENERATED_BODY()

public:

	UMultiplayerSubsystem();

	// --- Creating --- //

	UFUNCTION(BlueprintCallable)
	void CreateGameSession(int32 NumPublicConnections, bool IsLANMatch);
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FCSOnCreateSessionComplete OnCreateSessionCompleteEvent;

	// --- Updating --- //

	UFUNCTION(BlueprintCallable)
	void UpdateGameSession();
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FCSOnUpdateSessionComplete OnUpdateSessionCompleteEvent;

	// --- Starting --- //

	UFUNCTION(BlueprintCallable)
	void StartGameSession();
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FCSOnStartSessionComplete OnStartSessionCompleteEvent;

	// --- Ending --- //

	UFUNCTION(BlueprintCallable)
	void EndGameSession();
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FCSOnEndSessionComplete OnEndSessionCompleteEvent;

	// --- Destroying --- //

	UFUNCTION(BlueprintCallable)
	void DestroyGameSession();
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FCSOnDestroySessionComplete OnDestroySessionCompleteEvent;

	// --- Finding --- //

	UFUNCTION(BlueprintCallable)
	void FindGameSession(int32 MaxSearchResults, bool IsLANQuery);
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FCSOnFindSessionComplete OnFindSessionCompleteEvent;

	// --- Joining --- //
	
	UFUNCTION(BlueprintCallable)
	void JoinGameSession(const FExposedSessionSearchResult& SessionResult);
	UPROPERTY(Blueprintable, BlueprintAssignable)
	FCSOnJoinSessionComplete OnJoinSessionCompleteEvent;

	// --- Traveling --- //

	UFUNCTION(BlueprintCallable)
	bool TryTravelToCurrentSession();

	UFUNCTION(BlueprintCallable)
	static void ServerTravel(UObject* WorldContextObject, const FString& LevelName);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString GetSearchSessionName(const FExposedSessionSearchResult& SearchResult) { return SearchResult.GetSessionName(); }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 GetSearchSessionPing(const FExposedSessionSearchResult& SearchResult) { return SearchResult.GetCurrentPing(); }
	
	

protected:
	
	// --- Creating --- //
	
	void OnCreateSessionCompleted(FName SessionName, bool Successful);

	// --- Updating --- //
	
	void OnUpdateSessionCompleted(FName SessionName, bool Successful);

	// --- Starting --- //
	
	void OnStartSessionCompleted(FName SessionName, bool Successful);

	// --- Ending --- //
	
	void OnEndSessionCompleted(FName SessionName, bool Successful);

	// --- Destroying --- //

	void OnDestroySessionCompleted(FName SessionName, bool Successful);

	// --- Finding --- //

	void OnFindSessionCompleted(bool Successful);

	// --- Joining --- //

	void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	// --- Creating --- //
	
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FDelegateHandle CreateSessionCompleteDelegateHandle;

	// --- Updating --- //

	FOnUpdateSessionCompleteDelegate UpdateSessionCompleteDelegate;
	FDelegateHandle UpdateSessionCompleteDelegateHandle;

	// --- Starting --- //
	
	FOnStartSessionCompleteDelegate StartSessionCompleteDelegate;
	FDelegateHandle StartSessionCompleteDelegateHandle;

	// --- Ending --- //

	FOnEndSessionCompleteDelegate EndSessionCompleteDelegate;
	FDelegateHandle EndSessionCompleteDelegateHandle;

	// --- Destroying --- //

	FOnDestroySessionCompleteDelegate DestroySessionCompleteDelegate;
	FDelegateHandle DestroySessionCompleteDelegateHandle;

	// --- Finding --- //

	TSharedPtr<FOnlineSessionSearch> LastSessionSearch;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;

	// --- Joining --- //

	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
	FDelegateHandle JoinSessionCompleteDelegateHandle;
};
