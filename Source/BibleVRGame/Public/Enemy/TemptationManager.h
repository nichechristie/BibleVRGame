// TemptationManager.h
// Manages the desert temptation cinematic sequence and player choices

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DevilCharacter.h"
#include "TemptationManager.generated.h"

// Temptation scene in the desert sequence
USTRUCT(BlueprintType)
struct FTemptationScene
{
    GENERATED_BODY()

    // Scene identifier
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SceneId;

    // Type of temptation
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETemptationType TemptationType;

    // Devil's dialogue lines
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> DevilDialogue;

    // Jesus's response lines
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> JesusResponse;

    // Scripture reference for Jesus's response
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ScriptureReference;

    // Video/cinematic to play
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UMediaSource* SceneVideo;

    // Location in desert for this scene
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector DesertLocation;
};

// Player's temptation choice
USTRUCT(BlueprintType)
struct FTemptationChoice
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ChoiceText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRighteous;  // True = resist temptation, False = give in

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ResultText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 FaithChange;  // Positive = gain faith, Negative = lose faith
};

// Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDesertSceneStarted, FTemptationScene, Scene);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerChoice, FTemptationChoice, Choice, bool, Resisted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllTemptationsComplete);

UCLASS()
class BIBLEVRGAME_API ATemptationManager : public AActor
{
    GENERATED_BODY()

public:
    ATemptationManager();

protected:
    virtual void BeginPlay() override;

public:
    // ============================================
    // DESERT SCENE CONFIGURATION
    // ============================================

    // The three biblical temptation scenes
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temptation|Scenes")
    TArray<FTemptationScene> TemptationScenes;

    // Player choices for each temptation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temptation|Choices")
    TMap<ETemptationType, TArray<FTemptationChoice>> TemptationChoices;

    // ============================================
    // DESERT ENVIRONMENT
    // ============================================

    // Desert skybox/environment material
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temptation|Environment")
    UMaterialInterface* DesertSkyMaterial;

    // Wind/sand particle effect
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temptation|Environment")
    class UNiagaraSystem* DesertWindEffect;

    // Ambient desert sound
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temptation|Environment")
    USoundBase* DesertAmbience;

    // ============================================
    // MEDIA PLAYERS
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temptation|Media")
    class UMediaPlayer* CinematicPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Temptation|Media")
    class UMediaTexture* CinematicTexture;

    // ============================================
    // EVENTS
    // ============================================

    UPROPERTY(BlueprintAssignable, Category = "Temptation|Events")
    FOnDesertSceneStarted OnDesertSceneStarted;

    UPROPERTY(BlueprintAssignable, Category = "Temptation|Events")
    FOnPlayerChoice OnPlayerChoice;

    UPROPERTY(BlueprintAssignable, Category = "Temptation|Events")
    FOnAllTemptationsComplete OnAllTemptationsComplete;

    // ============================================
    // FUNCTIONS
    // ============================================

    // Initialize with the three biblical temptations
    UFUNCTION(BlueprintCallable, Category = "Temptation")
    void InitializeBiblicalTemptations();

    // Start a specific temptation scene
    UFUNCTION(BlueprintCallable, Category = "Temptation")
    void StartTemptationScene(int32 SceneIndex);

    // Play the full desert sequence (all 3 temptations)
    UFUNCTION(BlueprintCallable, Category = "Temptation")
    void PlayFullDesertSequence();

    // Player makes a choice during temptation
    UFUNCTION(BlueprintCallable, Category = "Temptation")
    void MakeChoice(ETemptationType Temptation, int32 ChoiceIndex);

    // Get choices for a temptation type
    UFUNCTION(BlueprintCallable, Category = "Temptation")
    TArray<FTemptationChoice> GetChoicesForTemptation(ETemptationType Temptation);

    // Skip to end of current scene
    UFUNCTION(BlueprintCallable, Category = "Temptation")
    void SkipCurrentScene();

private:
    int32 CurrentSceneIndex;
    bool bSequenceActive;

    void SetupDesertEnvironment();
    void AdvanceToNextScene();
    void CompleteSequence();
};
