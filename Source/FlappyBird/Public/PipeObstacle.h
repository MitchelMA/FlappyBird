#pragma once

#include "CoreMinimal.h"
#include "PipeObstacle.generated.h"

class UPaperSprite;
class UPaperSpriteComponent;
class UBoxComponent;



/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API APipeObstacle final : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot = nullptr;

	UPROPERTY(Category=Sprite, EditAnywhere,
		BlueprintSetter=SetTopSpriteSource)
	UPaperSprite* TopSpriteSource;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSpriteComponent> TopPanel = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> TopCollisionBox = nullptr;
	

	UPROPERTY(Category=Sprite, EditAnywhere,
		BlueprintSetter=SetBottomSpriteSource,
		meta=(EditCondition="!bMirrorTop", EditConditionHides=true))
	UPaperSprite* BottomSpriteSource;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSpriteComponent> BottomPanel = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> BottomCollisionBox = nullptr;


	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> PassCollisionBox = nullptr;

	
	UPROPERTY(Category=Sprite, EditAnywhere, AdvancedDisplay,
		BlueprintGetter=GetUseTopSpriteForBottom)
	bool bMirrorTop;

	UPROPERTY(Category=Movement, EditAnywhere)
	FVector2D DirectionMultiplier = {-1, 0};

	UPROPERTY(Category=Movement, EditAnywhere)
	float Speed = 0.1f;

	UPROPERTY(Category=Positioning, EditAnywhere)
	float GapHeight = 50.f;

	UPROPERTY(Category=Positioning, EditAnywhere)
	float HeightOffset = 0.f;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void BeginPlay() override;

public:
	APipeObstacle();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetTopSpriteSource(UPaperSprite* NewSpriteSource);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetBottomSpriteSource(UPaperSprite* NewSpriteSource);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool GetUseTopSpriteForBottom() const { return bMirrorTop; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE double GetPassBarrierXPosition() const;
};
