// CompanionCharacter.h
// Base class for companion characters that can follow and assist the player

#pragma once

#include "CoreMinimal.h"
#include "../BiblicalCharacterBase.h"
#include "CompanionCharacter.generated.h"

// Companion abilities
UENUM(BlueprintType)
enum class ECompanionAbility : uint8
{
    Leadership      UMETA(DisplayName = "Leadership"),
    Healing         UMETA(DisplayName = "Healing"),
    Wisdom          UMETA(DisplayName = "Wisdom"),
    Protection      UMETA(DisplayName = "Protection"),
    Inspiration     UMETA(DisplayName = "Inspiration"),
    Knowledge       UMETA(DisplayName = "Knowledge"),
    Comfort         UMETA(DisplayName = "Comfort"),
    Guidance        UMETA(DisplayName = "Guidance")
};

UCLASS()
class BIBLEVRGAME_API ACompanionCharacter : public ABiblicalCharacterBase
{
    GENERATED_BODY()

public:
    ACompanionCharacter();

protected:
    virtual void BeginPlay() override;

public:
    // ============================================
    // COMPANION PROPERTIES
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Companion")
    TArray<ECompanionAbility> Abilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Companion")
    FString CompanionQuote;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Companion")
    bool bIsActiveCompanion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Companion")
    int32 LoyaltyLevel;  // 0-100

    // Voice characteristics
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Companion|Voice")
    FString VoiceTone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Companion|Voice")
    FString SpeakingStyle;

    // ============================================
    // FUNCTIONS
    // ============================================

    UFUNCTION(BlueprintCallable, Category = "Companion")
    void ActivateAsCompanion();

    UFUNCTION(BlueprintCallable, Category = "Companion")
    void DeactivateCompanion();

    UFUNCTION(BlueprintCallable, Category = "Companion")
    void UseAbility(ECompanionAbility Ability);

    UFUNCTION(BlueprintCallable, Category = "Companion")
    bool HasAbility(ECompanionAbility Ability);

    UFUNCTION(BlueprintCallable, Category = "Companion")
    FString GetCompanionAdvice();
};

// ============================================
// PETER - The Rock
// ============================================
UCLASS()
class BIBLEVRGAME_API APeterCompanion : public ACompanionCharacter
{
    GENERATED_BODY()

public:
    APeterCompanion();
};

// ============================================
// MARY MAGDALENE - Faithful Follower
// ============================================
UCLASS()
class BIBLEVRGAME_API AMaryMagdaleneCompanion : public ACompanionCharacter
{
    GENERATED_BODY()

public:
    AMaryMagdaleneCompanion();
};

// ============================================
// JOHN - The Beloved
// ============================================
UCLASS()
class BIBLEVRGAME_API AJohnCompanion : public ACompanionCharacter
{
    GENERATED_BODY()

public:
    AJohnCompanion();
};

// ============================================
// PAUL - Apostle to the Gentiles
// ============================================
UCLASS()
class BIBLEVRGAME_API APaulCompanion : public ACompanionCharacter
{
    GENERATED_BODY()

public:
    APaulCompanion();
};

// ============================================
// SOLOMON - The Wise King
// ============================================
UCLASS()
class BIBLEVRGAME_API ASolomonCompanion : public ACompanionCharacter
{
    GENERATED_BODY()

public:
    ASolomonCompanion();
};

// ============================================
// THE GUIDE - Narrator
// ============================================
UCLASS()
class BIBLEVRGAME_API ATheGuideCompanion : public ACompanionCharacter
{
    GENERATED_BODY()

public:
    ATheGuideCompanion();
};
