// BiblicalCharacterBase.h
// Base class for all biblical characters in the game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/AudioComponent.h"
#include "BiblicalCharacterBase.generated.h"

// Character role types
UENUM(BlueprintType)
enum class EBiblicalRole : uint8
{
    Companion       UMETA(DisplayName = "Companion"),
    Apostle         UMETA(DisplayName = "Apostle"),
    Prophet         UMETA(DisplayName = "Prophet"),
    Angel           UMETA(DisplayName = "Angel"),
    RomanSoldier    UMETA(DisplayName = "Roman Soldier"),
    ReligiousLeader UMETA(DisplayName = "Religious Leader"),
    Civilian        UMETA(DisplayName = "Civilian"),
    Messiah         UMETA(DisplayName = "Messiah")
};

// Emotional state for dialogue
UENUM(BlueprintType)
enum class EEmotionalState : uint8
{
    Neutral     UMETA(DisplayName = "Neutral"),
    Happy       UMETA(DisplayName = "Happy"),
    Sad         UMETA(DisplayName = "Sad"),
    Angry       UMETA(DisplayName = "Angry"),
    Fearful     UMETA(DisplayName = "Fearful"),
    Peaceful    UMETA(DisplayName = "Peaceful"),
    Inspired    UMETA(DisplayName = "Inspired"),
    Sorrowful   UMETA(DisplayName = "Sorrowful")
};

// Character emotional profile
USTRUCT(BlueprintType)
struct FEmotionalProfile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Empathy = 5;      // 1-10

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Energy = 5;       // 1-10

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Formality = 5;    // 1-10

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Playfulness = 5;  // 1-10

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Directness = 5;   // 1-10
};

// Dialogue patterns
USTRUCT(BlueprintType)
struct FDialoguePatterns
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Greetings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Farewells;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Affirmations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> SignatureExpressions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> QuestionStyles;
};

// Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueStarted, ABiblicalCharacterBase*, Character, FString, DialogueLine);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEmotionChanged, EEmotionalState, NewState);

UCLASS()
class BIBLEVRGAME_API ABiblicalCharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    ABiblicalCharacterBase();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // ============================================
    // IDENTITY
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Identity")
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Identity")
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Identity")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Identity")
    EBiblicalRole Role;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Identity")
    FString ScriptureReference;

    // ============================================
    // PERSONALITY
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Personality")
    FEmotionalProfile EmotionalProfile;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Personality")
    FDialoguePatterns DialoguePatterns;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Personality")
    EEmotionalState CurrentEmotion;

    // ============================================
    // APPEARANCE
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Appearance")
    USkeletalMesh* CharacterMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Appearance")
    UMaterialInterface* ClothingMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Appearance")
    FLinearColor PrimaryColor;

    // ============================================
    // AUDIO
    // ============================================

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UAudioComponent* VoiceComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Audio")
    USoundBase* VoiceSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Audio")
    float VoicePitch = 1.0f;

    // ============================================
    // INTERACTION
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Interaction")
    float InteractionRadius = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Interaction")
    bool bCanBeFollowed = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Interaction")
    bool bIsInteractable = true;

    // ============================================
    // RELATIONSHIP
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Relationship")
    int32 RelationshipLevel = 0;  // 0-100

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Relationship")
    int32 TrustLevel = 50;  // 0-100

    // ============================================
    // EVENTS
    // ============================================

    UPROPERTY(BlueprintAssignable, Category = "Character|Events")
    FOnDialogueStarted OnDialogueStarted;

    UPROPERTY(BlueprintAssignable, Category = "Character|Events")
    FOnEmotionChanged OnEmotionChanged;

    // ============================================
    // FUNCTIONS
    // ============================================

    UFUNCTION(BlueprintCallable, Category = "Character|Dialogue")
    virtual FString GetGreeting();

    UFUNCTION(BlueprintCallable, Category = "Character|Dialogue")
    virtual FString GetFarewell();

    UFUNCTION(BlueprintCallable, Category = "Character|Dialogue")
    virtual void SpeakLine(const FString& Line);

    UFUNCTION(BlueprintCallable, Category = "Character|Emotion")
    virtual void SetEmotion(EEmotionalState NewEmotion);

    UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
    virtual void OnPlayerInteract(ACharacter* Player);

    UFUNCTION(BlueprintCallable, Category = "Character|Relationship")
    virtual void ModifyRelationship(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Character|Movement")
    virtual void FollowPlayer(ACharacter* Player);

    UFUNCTION(BlueprintCallable, Category = "Character|Movement")
    virtual void StopFollowing();

protected:
    UPROPERTY()
    ACharacter* PlayerToFollow;

    bool bIsFollowing;
};
