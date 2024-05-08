#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "PipeObstacle.generated.h"

class UPaperSprite;
class UPaperSpriteComponent;
class UBoxComponent;
class USpeedComponent;


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class FLAPPYBIRD_API APipeObstacle : public AActor
{
	GENERATED_BODY()

	// ----- PROPERTIES ----- //

	UPROPERTY(Category=Sprite, EditAnywhere,
		BlueprintSetter=SetTopSpriteSource)
	UPaperSprite* TopSpriteSource;

	UPROPERTY(Category=Sprite, EditAnywhere,
		BlueprintSetter=SetBottomSpriteSource,
		meta=(EditCondition="!bMirrorTop", EditConditionHides=true))
	UPaperSprite* BottomSpriteSource;

	UPROPERTY(Category=Sprite, EditAnywhere, AdvancedDisplay,
		BlueprintGetter=GetMirrorsTop, BlueprintSetter=SetMirrorsTop)
	bool bMirrorTop;

	UPROPERTY(Category=Movement, EditAnywhere)
	FVector2D DirectionMultiplier = {-1, 0};

	UPROPERTY(Category=Positioning, EditAnywhere,
		BlueprintGetter=GetGapHeight, BlueprintSetter=SetGapHeight)
	float GapHeight = 50.f;

	UPROPERTY(Category=Positioning, EditAnywhere)
	float HeightOffset = 0.f;

	// ----- COMPONENTS ----- //

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> DefaultSceneRoot = nullptr;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> PipesOffset = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSpriteComponent> TopPanel = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperSpriteComponent> BottomPanel = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> PassCollisionBox = nullptr;

	UPROPERTY(Category=Movement, VisibleAnywhere, BlueprintReadOnly,
		meta=(AllowPrivateAccess=true))
	TObjectPtr<USpeedComponent> SpeedComponent = nullptr;

	// ----- OVERRIDEN METHODS ----- //


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

	virtual void BeginPlay() override;

	// ----- UTILITY METHODS ----- //
	
	TPair<UE::Math::TVector<double>, UE::Math::TVector<double>> GetPipeExtends() const noexcept;
	TPair<UE::Math::TVector<double>, UE::Math::TVector<double>> GetPipeSizes() const noexcept;

public:
	APipeObstacle();

	virtual void Tick(float DeltaSeconds) override;

	// ----- BLUEPRINT CALLABLES ----- //

	UFUNCTION(BlueprintCallable)
	void SetTopSpriteSource(UPaperSprite* NewSpriteSource);
	
	UFUNCTION(BlueprintCallable)
	void SetBottomSpriteSource(UPaperSprite* NewSpriteSource);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool GetMirrorsTop() const { return bMirrorTop; }
	UFUNCTION(BlueprintCallable)
	void SetMirrorsTop(bool NewValue);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	double GetPassBarrierXPosition() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetGapHeight() const { return GapHeight; }
	UFUNCTION(BlueprintCallable)
	void SetGapHeight(float NewGapHeight);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetHeightOffset() const { return HeightOffset; }
	UFUNCTION(BlueprintCallable)
	void SetHeightOffset(float NewHeightOffset);
};
