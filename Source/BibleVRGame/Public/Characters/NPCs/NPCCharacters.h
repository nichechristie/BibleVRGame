// NPCCharacters.h
// NPC character classes for Romans, Religious Leaders, Angels, Civilians

#pragma once

#include "CoreMinimal.h"
#include "../BiblicalCharacterBase.h"
#include "NiagaraComponent.h"
#include "NPCCharacters.generated.h"

// ============================================
// ROMAN SOLDIER BASE
// ============================================

UENUM(BlueprintType)
enum class ERomanRank : uint8
{
    Legionary   UMETA(DisplayName = "Legionary"),
    Optio       UMETA(DisplayName = "Optio"),
    Centurion   UMETA(DisplayName = "Centurion"),
    Tribune     UMETA(DisplayName = "Tribune"),
    Prefect     UMETA(DisplayName = "Prefect")
};

UCLASS()
class BIBLEVRGAME_API ARomanSoldier : public ABiblicalCharacterBase
{
    GENERATED_BODY()

public:
    ARomanSoldier();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roman")
    ERomanRank Rank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roman")
    FString Legion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roman")
    bool bIsHostile;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roman")
    bool bIsOnDuty;

    UFUNCTION(BlueprintCallable, Category = "Roman")
    void IssueCommand(const FString& Command);

    UFUNCTION(BlueprintCallable, Category = "Roman")
    void SetHostility(bool bHostile);
};

// Specific Roman characters
UCLASS()
class BIBLEVRGAME_API ACenturionCharacter : public ARomanSoldier
{
    GENERATED_BODY()
public:
    ACenturionCharacter();
};

UCLASS()
class BIBLEVRGAME_API APontiusPilateCharacter : public ARomanSoldier
{
    GENERATED_BODY()
public:
    APontiusPilateCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pilate")
    bool bHasWashedHands;

    UFUNCTION(BlueprintCallable, Category = "Pilate")
    void WashHands();
};

// ============================================
// RELIGIOUS LEADERS
// ============================================

UENUM(BlueprintType)
enum class EReligiousTitle : uint8
{
    Pharisee        UMETA(DisplayName = "Pharisee"),
    Sadducee        UMETA(DisplayName = "Sadducee"),
    Scribe          UMETA(DisplayName = "Scribe"),
    HighPriest      UMETA(DisplayName = "High Priest"),
    Elder           UMETA(DisplayName = "Elder"),
    Rabbi           UMETA(DisplayName = "Rabbi")
};

UCLASS()
class BIBLEVRGAME_API AReligiousLeader : public ABiblicalCharacterBase
{
    GENERATED_BODY()

public:
    AReligiousLeader();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religious")
    EReligiousTitle ReligiousTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religious")
    bool bIsAntagonist;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religious")
    TArray<FString> ScripturalChallenges;

    UFUNCTION(BlueprintCallable, Category = "Religious")
    FString PoseChallenge();
};

// Specific religious leaders
UCLASS()
class BIBLEVRGAME_API ACaiaphasCharacter : public AReligiousLeader
{
    GENERATED_BODY()
public:
    ACaiaphasCharacter();
};

UCLASS()
class BIBLEVRGAME_API ANicodemusCharacter : public AReligiousLeader
{
    GENERATED_BODY()
public:
    ANicodemusCharacter();
};

UCLASS()
class BIBLEVRGAME_API APhariseeCharacter : public AReligiousLeader
{
    GENERATED_BODY()
public:
    APhariseeCharacter();
};

// ============================================
// ANGELS
// ============================================

UENUM(BlueprintType)
enum class EAngelType : uint8
{
    Messenger       UMETA(DisplayName = "Messenger Angel"),
    Guardian        UMETA(DisplayName = "Guardian Angel"),
    Archangel       UMETA(DisplayName = "Archangel"),
    Seraphim        UMETA(DisplayName = "Seraphim"),
    Cherubim        UMETA(DisplayName = "Cherubim")
};

UCLASS()
class BIBLEVRGAME_API AAngelCharacter : public ABiblicalCharacterBase
{
    GENERATED_BODY()

public:
    AAngelCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UNiagaraComponent* GlowEffect;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UNiagaraComponent* WingEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angel")
    EAngelType AngelType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angel")
    float GlowIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angel")
    bool bWingsVisible;

    UFUNCTION(BlueprintCallable, Category = "Angel")
    void DeliverMessage(const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "Angel")
    void SetGlow(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Angel")
    void ToggleWings(bool bVisible);
};

// Specific angels
UCLASS()
class BIBLEVRGAME_API AGabrielCharacter : public AAngelCharacter
{
    GENERATED_BODY()
public:
    AGabrielCharacter();
};

UCLASS()
class BIBLEVRGAME_API AMichaelCharacter : public AAngelCharacter
{
    GENERATED_BODY()
public:
    AMichaelCharacter();
};

// ============================================
// WOMEN OF THE BIBLE
// ============================================

UCLASS()
class BIBLEVRGAME_API ABiblicalWoman : public ABiblicalCharacterBase
{
    GENERATED_BODY()
public:
    ABiblicalWoman();
};

UCLASS()
class BIBLEVRGAME_API AMaryMotherCharacter : public ABiblicalWoman
{
    GENERATED_BODY()
public:
    AMaryMotherCharacter();
};

UCLASS()
class BIBLEVRGAME_API AMarthaCharacter : public ABiblicalWoman
{
    GENERATED_BODY()
public:
    AMarthaCharacter();
};

UCLASS()
class BIBLEVRGAME_API AMaryBethanyCharacter : public ABiblicalWoman
{
    GENERATED_BODY()
public:
    AMaryBethanyCharacter();
};

UCLASS()
class BIBLEVRGAME_API AWomanAtWellCharacter : public ABiblicalWoman
{
    GENERATED_BODY()
public:
    AWomanAtWellCharacter();
};

// ============================================
// CIVILIANS
// ============================================

UENUM(BlueprintType)
enum class ECivilianType : uint8
{
    Merchant        UMETA(DisplayName = "Merchant"),
    Farmer          UMETA(DisplayName = "Farmer"),
    Fisherman       UMETA(DisplayName = "Fisherman"),
    Shepherd        UMETA(DisplayName = "Shepherd"),
    Craftsman       UMETA(DisplayName = "Craftsman"),
    Beggar          UMETA(DisplayName = "Beggar"),
    Innkeeper       UMETA(DisplayName = "Innkeeper"),
    Child           UMETA(DisplayName = "Child")
};

UCLASS()
class BIBLEVRGAME_API ACivilianCharacter : public ABiblicalCharacterBase
{
    GENERATED_BODY()

public:
    ACivilianCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Civilian")
    ECivilianType CivilianType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Civilian")
    bool bCanTrade;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Civilian")
    TArray<FString> LocalRumors;

    UFUNCTION(BlueprintCallable, Category = "Civilian")
    FString ShareRumor();
};

// ============================================
// CROWD SYSTEM
// ============================================

UCLASS()
class BIBLEVRGAME_API ACrowdMember : public ABiblicalCharacterBase
{
    GENERATED_BODY()

public:
    ACrowdMember();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd")
    bool bCanBeIndividualized;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd")
    TArray<FString> CrowdChants;

    UFUNCTION(BlueprintCallable, Category = "Crowd")
    void JoinChant(const FString& Chant);
};
