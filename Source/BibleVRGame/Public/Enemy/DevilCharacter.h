// DevilCharacter.h
// Devil enemy that randomly tempts players and triggers desert temptation sequence

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"
#include "DevilCharacter.generated.h"

// Devil's various disguise forms
UENUM(BlueprintType)
enum class EDevilForm : uint8
{
    Serpent         UMETA(DisplayName = "Serpent"),
    Merchant        UMETA(DisplayName = "Merchant"),
    Scholar         UMETA(DisplayName = "Scholar"),
    Beggar          UMETA(DisplayName = "Beggar"),
    Angel           UMETA(DisplayName = "False Angel"),
    Shadow          UMETA(DisplayName = "Shadow Figure"),
    TrueForm        UMETA(DisplayName = "True Form")
};

// Temptation types matching biblical narrative
UENUM(BlueprintType)
enum class ETemptationType : uint8
{
    StonesToBread   UMETA(DisplayName = "Turn Stones to Bread"),
    TestGod         UMETA(DisplayName = "Test God's Protection"),
    WorldlyPower    UMETA(DisplayName = "Offer Worldly Power"),
    MaterialWealth  UMETA(DisplayName = "Material Wealth"),
    Pride           UMETA(DisplayName = "Pride and Glory"),
    Doubt           UMETA(DisplayName = "Doubt and Fear")
};

// Delegate for temptation events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTemptationTriggered, ETemptationType, TemptationType, ADevilCharacter*, Devil);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDevilFormChanged, EDevilForm, NewForm);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDesertSequenceComplete);

UCLASS()
class BIBLEVRGAME_API ADevilCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ADevilCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // ============================================
    // COMPONENTS
    // ============================================

    // Interaction sphere for player detection
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* InteractionSphere;

    // Detection sphere for random appearances
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* DetectionSphere;

    // Audio for whispers and temptations
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAudioComponent* WhisperAudio;

    // VFX for transformation and effects
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UNiagaraComponent* TransformationVFX;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UNiagaraComponent* AuraVFX;

    // ============================================
    // DEVIL PROPERTIES
    // ============================================

    // Current disguise form
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Form")
    EDevilForm CurrentForm;

    // Skeletal meshes for each form
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Form")
    TMap<EDevilForm, USkeletalMesh*> FormMeshes;

    // Animation blueprints for each form
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Form")
    TMap<EDevilForm, TSubclassOf<UAnimInstance>> FormAnimations;

    // ============================================
    // TEMPTATION SETTINGS
    // ============================================

    // Minimum time between random appearances (seconds)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Temptation")
    float MinTimeBetweenAppearances;

    // Maximum time between random appearances (seconds)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Temptation")
    float MaxTimeBetweenAppearances;

    // Chance to appear when timer triggers (0-1)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Temptation")
    float AppearanceChance;

    // How long devil remains visible before disappearing
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Temptation")
    float VisibilityDuration;

    // Distance from player to spawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Temptation")
    float SpawnDistanceFromPlayer;

    // Current temptation being offered
    UPROPERTY(BlueprintReadOnly, Category = "Devil|Temptation")
    ETemptationType CurrentTemptation;

    // ============================================
    // DESERT SEQUENCE
    // ============================================

    // Media player for desert temptation video
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Desert")
    class UMediaPlayer* DesertVideoPlayer;

    // Media source for the video
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Desert")
    class UMediaSource* DesertVideoSource;

    // Level to stream for desert scene
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Desert")
    TSoftObjectPtr<UWorld> DesertLevel;

    // Duration of desert sequence (auto-detected from video if 0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Desert")
    float DesertSequenceDuration;

    // Player's saved location before teleport
    UPROPERTY(BlueprintReadOnly, Category = "Devil|Desert")
    FTransform SavedPlayerTransform;

    // ============================================
    // DIALOGUE
    // ============================================

    // Temptation dialogue lines
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Dialogue")
    TMap<ETemptationType, TArray<FString>> TemptationDialogue;

    // Whisper lines for random appearances
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Dialogue")
    TArray<FString> WhisperLines;

    // ============================================
    // AUDIO
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Audio")
    USoundBase* AppearSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Audio")
    USoundBase* DisappearSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Audio")
    USoundBase* TransformSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Audio")
    USoundBase* TemptationMusic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Devil|Audio")
    TMap<EDevilForm, USoundBase*> FormVoices;

    // ============================================
    // EVENTS
    // ============================================

    UPROPERTY(BlueprintAssignable, Category = "Devil|Events")
    FOnTemptationTriggered OnTemptationTriggered;

    UPROPERTY(BlueprintAssignable, Category = "Devil|Events")
    FOnDevilFormChanged OnDevilFormChanged;

    UPROPERTY(BlueprintAssignable, Category = "Devil|Events")
    FOnDesertSequenceComplete OnDesertSequenceComplete;

    // ============================================
    // PUBLIC FUNCTIONS
    // ============================================

    // Change devil's disguise form
    UFUNCTION(BlueprintCallable, Category = "Devil|Form")
    void ChangeForm(EDevilForm NewForm);

    // Transform to random different form
    UFUNCTION(BlueprintCallable, Category = "Devil|Form")
    void TransformToRandomForm();

    // Reveal true form
    UFUNCTION(BlueprintCallable, Category = "Devil|Form")
    void RevealTrueForm();

    // Appear near player
    UFUNCTION(BlueprintCallable, Category = "Devil|Appearance")
    void AppearNearPlayer();

    // Disappear with effects
    UFUNCTION(BlueprintCallable, Category = "Devil|Appearance")
    void Disappear();

    // Trigger temptation interaction
    UFUNCTION(BlueprintCallable, Category = "Devil|Temptation")
    void TriggerTemptation(ETemptationType Temptation);

    // Start desert sequence
    UFUNCTION(BlueprintCallable, Category = "Devil|Desert")
    void StartDesertSequence();

    // End desert sequence and return player
    UFUNCTION(BlueprintCallable, Category = "Devil|Desert")
    void EndDesertSequence();

    // Get dialogue for current temptation
    UFUNCTION(BlueprintCallable, Category = "Devil|Dialogue")
    FString GetTemptationDialogue();

    // Whisper to player (subtle temptation)
    UFUNCTION(BlueprintCallable, Category = "Devil|Dialogue")
    void WhisperToPlayer();

private:
    // Timer handle for random appearances
    FTimerHandle AppearanceTimerHandle;

    // Timer handle for visibility duration
    FTimerHandle VisibilityTimerHandle;

    // Timer handle for desert sequence
    FTimerHandle DesertSequenceTimerHandle;

    // Is devil currently visible
    bool bIsVisible;

    // Is desert sequence active
    bool bDesertSequenceActive;

    // Reference to player character
    UPROPERTY()
    ACharacter* PlayerCharacter;

    // Schedule next random appearance
    void ScheduleNextAppearance();

    // Called when appearance timer fires
    void OnAppearanceTimerFired();

    // Called when visibility timer fires
    void OnVisibilityTimerFired();

    // Initialize default dialogue
    void InitializeDialogue();

    // Get random spawn location near player
    FVector GetSpawnLocationNearPlayer();

    // Overlap events
    UFUNCTION()
    void OnInteractionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
