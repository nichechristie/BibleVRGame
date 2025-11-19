// JesusCharacter.h
// Jesus Christ character - special handling with reverence

#pragma once

#include "CoreMinimal.h"
#include "BiblicalCharacterBase.h"
#include "NiagaraComponent.h"
#include "JesusCharacter.generated.h"

// Jesus's ministry periods
UENUM(BlueprintType)
enum class EMinistryPeriod : uint8
{
    Childhood       UMETA(DisplayName = "Childhood"),
    Baptism         UMETA(DisplayName = "Baptism"),
    EarlyMinistry   UMETA(DisplayName = "Early Ministry"),
    Galilee         UMETA(DisplayName = "Galilean Ministry"),
    Judea           UMETA(DisplayName = "Judean Ministry"),
    FinalWeek       UMETA(DisplayName = "Final Week"),
    Crucifixion     UMETA(DisplayName = "Crucifixion"),
    Resurrection    UMETA(DisplayName = "Resurrection"),
    Ascension       UMETA(DisplayName = "Ascension")
};

// Miracles Jesus can perform
UENUM(BlueprintType)
enum class EMiracle : uint8
{
    HealingSick         UMETA(DisplayName = "Healing the Sick"),
    CastingOutDemons    UMETA(DisplayName = "Casting Out Demons"),
    RaisingDead         UMETA(DisplayName = "Raising the Dead"),
    FeedingMultitude    UMETA(DisplayName = "Feeding Multitude"),
    CalmingStorm        UMETA(DisplayName = "Calming Storm"),
    WalkingOnWater      UMETA(DisplayName = "Walking on Water"),
    WaterToWine         UMETA(DisplayName = "Water to Wine"),
    RestoringLimbs      UMETA(DisplayName = "Restoring Limbs")
};

// Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMiraclePerformed, EMiracle, Miracle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnParableSpoken, FString, Parable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBlessingGiven);

UCLASS()
class BIBLEVRGAME_API AJesusCharacter : public ABiblicalCharacterBase
{
    GENERATED_BODY()

public:
    AJesusCharacter();

protected:
    virtual void BeginPlay() override;

public:
    // ============================================
    // COMPONENTS
    // ============================================

    // Divine glow effect
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UNiagaraComponent* DivineGlow;

    // Halo effect
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UNiagaraComponent* HaloEffect;

    // ============================================
    // MINISTRY
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jesus|Ministry")
    EMinistryPeriod CurrentPeriod;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jesus|Ministry")
    TArray<FString> Parables;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jesus|Ministry")
    TArray<FString> Beatitudes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jesus|Ministry")
    TArray<FString> Teachings;

    // ============================================
    // VISUAL
    // ============================================

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jesus|Visual")
    float GlowIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jesus|Visual")
    bool bShowHalo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jesus|Visual")
    bool bTransfigured;

    // ============================================
    // EVENTS
    // ============================================

    UPROPERTY(BlueprintAssignable, Category = "Jesus|Events")
    FOnMiraclePerformed OnMiraclePerformed;

    UPROPERTY(BlueprintAssignable, Category = "Jesus|Events")
    FOnParableSpoken OnParableSpoken;

    UPROPERTY(BlueprintAssignable, Category = "Jesus|Events")
    FOnBlessingGiven OnBlessingGiven;

    // ============================================
    // FUNCTIONS
    // ============================================

    // Perform a miracle
    UFUNCTION(BlueprintCallable, Category = "Jesus|Miracles")
    void PerformMiracle(EMiracle Miracle);

    // Speak a parable
    UFUNCTION(BlueprintCallable, Category = "Jesus|Teaching")
    FString SpeakParable();

    // Give a teaching
    UFUNCTION(BlueprintCallable, Category = "Jesus|Teaching")
    FString GiveTeaching();

    // Bless the player
    UFUNCTION(BlueprintCallable, Category = "Jesus|Blessing")
    void BlessPlayer(ACharacter* Player);

    // Set ministry period (changes appearance/dialogue)
    UFUNCTION(BlueprintCallable, Category = "Jesus|Ministry")
    void SetMinistryPeriod(EMinistryPeriod Period);

    // Transfiguration effect
    UFUNCTION(BlueprintCallable, Category = "Jesus|Visual")
    void Transfigure(bool bEnable);

    // Override greeting for special handling
    virtual FString GetGreeting() override;

    // Override interaction
    virtual void OnPlayerInteract(ACharacter* Player) override;

private:
    void InitializeTeachings();
    void UpdateVisualForPeriod();
};
