// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"

#include "CoreMinimal.h"
#include "OffsettingBackground.generated.h"

/**
 * 
 */
UCLASS(config=Game, BlueprintType, Blueprintable)
class FLAPPYBIRD_API AOffsettingBackground : public AActor
{
	GENERATED_UCLASS_BODY()

private:

	UPROPERTY(Category=Settings, EditAnywhere)
	float SlideSpeed;

	UPROPERTY(Category = Sprite, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeFunctionCategories = "Sprite"))
	TObjectPtr<class UPaperSpriteComponent> PanelZero;

	UPROPERTY(Category = Sprite, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeFunctionCategories = "Sprite"))
	TObjectPtr<class UPaperSpriteComponent> PanelOne;

	UPROPERTY(Category=Settings, VisibleAnywhere)
	float Width;

protected:

	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UPaperSpriteComponent* GetPanelZero() const { return PanelZero; }
	FORCEINLINE class UPaperSpriteComponent* GetPanelOne()  const { return PanelOne; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetWidth() const { return Width; }
};
