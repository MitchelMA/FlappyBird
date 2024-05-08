#pragma once

#include "PaperSpriteComponent.h"

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "GameFramework/Actor.h"
#include "SlidingBackground.generated.h"


UCLASS(Abstract)
class FLAPPYBIRD_API ASlidingBackground : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category=Sprite, EditAnywhere,
		BlueprintGetter=GetBackgroundSource, BlueprintSetter=SetBackgroundSource)
	UPaperSprite* BackgroundSource = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> PanelOffset = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperSpriteComponent> PanelZero = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperSpriteComponent> PanelOne = nullptr;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;
#endif // WITH_EDITOR
	
public:	
	// Sets default values for this actor's properties
	ASlidingBackground();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category=Movement, EditAnywhere,
		BlueprintSetter=SetDirectionMultiplier)
	float HorizontalDirectionMultiplier = -1;

	UPROPERTY(Category=Movement, VisibleAnywhere,
		BlueprintGetter=GetProgression,BlueprintSetter=SetProgression)
	float Progression = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE UPaperSprite* GetBackgroundSource() const { return BackgroundSource; }

	UFUNCTION(BlueprintCallable)
	void SetBackgroundSource(UPaperSprite* NewSource);

	UFUNCTION(BlueprintPure)
	FORCEINLINE FVector2D GetPanelSize() const
	{
		if (!IsValid(PanelZero) || !IsValid(PanelZero->GetSprite()))
			return {0, 0};
		const auto Extent = PanelZero->GetSprite()->GetRenderBounds().BoxExtent * 2;
		return {Extent[0], Extent[1]};
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual double CalcNextProgression(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SetProgression(float NewProgression);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetProgression() const { return Progression; }

	UFUNCTION(BlueprintCallable)
	void SetDirectionMultiplier(float NewDirectionMultiplier);
};
