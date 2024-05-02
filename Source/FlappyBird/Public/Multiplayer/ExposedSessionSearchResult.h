// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OnlineSessionSettings.h"
#include "CoreMinimal.h"
#include "ExposedSessionSearchResult.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FLAPPYBIRD_API FExposedSessionSearchResult
{
	GENERATED_BODY()

private:
	FOnlineSessionSearchResult SearchResult;

public:
	FExposedSessionSearchResult() = default;
	explicit FExposedSessionSearchResult(const FOnlineSessionSearchResult& Result) :
		SearchResult(Result)
	{}

	FORCEINLINE FOnlineSessionSearchResult AsSearchResult() const { return SearchResult; }
	FORCEINLINE FString GetSessionName() const { return SearchResult.GetSessionIdStr(); };
	FORCEINLINE int32 GetMaxConnections() const { return SearchResult.Session.NumOpenPublicConnections; }
	FORCEINLINE int32 GetCurrentPing() const { return SearchResult.PingInMs; }	
};
