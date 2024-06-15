// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameOverWidget.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UGameOverWidget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FLAPPYBIRD_API IGameOverWidget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetWidgetDisplayScore(const int64 DisplayScore);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetWidgetDisplayHighScore(const int64 DisplayHighScore);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SaveScore();
};
