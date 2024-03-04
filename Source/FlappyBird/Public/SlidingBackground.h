#pragma once

#include "PaperSpriteComponent.h"

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "GameFramework/Actor.h"
#include "SlidingBackground.generated.h"

class USpeedComponent;

UCLASS(Config=game, BlueprintType, Blueprintable)
class FLAPPYBIRD_API ASlidingBackground final : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category=Sprite, EditAnywhere,
		BlueprintGetter=GetBackgroundSource, BlueprintSetter=SetBackgroundSource)
	UPaperSprite* BackgroundSource = nullptr;

	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot = nullptr;
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> PanelZero = nullptr;
	UPROPERTY()
	TObjectPtr<UPaperSpriteComponent> PanelOne = nullptr;

	UPROPERTY(Category=Movement, VisibleAnywhere)
	TObjectPtr<USpeedComponent> SpeedComponent = nullptr;
	

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;
	
public:	
	// Sets default values for this actor's properties
	ASlidingBackground();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category=Movement, EditAnywhere,
		BlueprintSetter=SetDirectionMultiplier)
	FVector2D DirectionMultiplier = {-1, 0};

	UPROPERTY(Category=Movement, VisibleAnywhere,
		BlueprintGetter=GetProgression,BlueprintSetter=SetProgression)
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

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetProgression() const { return Progression; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDirectionMultiplier(FVector2D NewDirectionMultiplier);
};
