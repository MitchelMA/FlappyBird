// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "GameFramework/Actor.h"
#include "SlidingBackground.generated.h"

UCLASS(Config=game, BlueprintType, Blueprintable)
class FLAPPYBIRD_API ASlidingBackground : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category=Sprite, EditAnywhere,
		BlueprintGetter=GetBackgroundSource, BlueprintSetter=SetBackgroundSource)
	UPaperSprite* BackgroundSource = nullptr;

	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> PanelZero = nullptr;
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> PanelOne = nullptr;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;
	
public:	
	// Sets default values for this actor's properties
	ASlidingBackground();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category=Settings, EditAnywhere)
	float SlideSpeed = 0.1;

	UPROPERTY(Category=Settings, EditAnywhere,
		BlueprintSetter=SetDirectionMultiplier)
	FVector2D DirectionMultiplier = {-1, 0};

	UPROPERTY(Category=Settings, VisibleAnywhere,
		BlueprintSetter=SetProgression)
	float Progression = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE UPaperSprite* GetBackgroundSource() const { return BackgroundSource; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetBackgroundSource(UPaperSprite* NewSource);

	UFUNCTION(BlueprintPure)
	FORCEINLINE FVector2D GetPanelSize() const
	{
		if (PanelZero == nullptr || PanelZero->GetSprite() == nullptr)
			return {0, 0};
		return PanelZero->GetSprite()->GetSourceSize();
			
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetProgression(float NewProgression);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDirectionMultiplier(FVector2D NewDirectionMultiplier);
};
