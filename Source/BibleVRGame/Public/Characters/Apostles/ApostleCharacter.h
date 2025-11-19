// ApostleCharacter.h
// All 12 Apostle character classes

#pragma once

#include "CoreMinimal.h"
#include "../BiblicalCharacterBase.h"
#include "ApostleCharacter.generated.h"

// Apostle-specific symbol for iconography
UENUM(BlueprintType)
enum class EApostleSymbol : uint8
{
    Keys            UMETA(DisplayName = "Keys"),           // Peter
    XCross          UMETA(DisplayName = "X-Shaped Cross"), // Andrew
    Shell           UMETA(DisplayName = "Pilgrim Shell"),  // James
    Eagle           UMETA(DisplayName = "Eagle"),          // John
    Loaves          UMETA(DisplayName = "Loaves"),         // Philip
    Knife           UMETA(DisplayName = "Flaying Knife"),  // Bartholomew
    MoneyBag        UMETA(DisplayName = "Money Bag"),      // Matthew
    Spear           UMETA(DisplayName = "Spear"),          // Thomas
    Club            UMETA(DisplayName = "Club"),           // James Lesser
    Axe             UMETA(DisplayName = "Axe"),            // Thaddaeus
    Saw             UMETA(DisplayName = "Saw"),            // Simon
    Coins           UMETA(DisplayName = "Thirty Coins")    // Judas
};

// Base Apostle class
UCLASS()
class BIBLEVRGAME_API AApostleCharacter : public ABiblicalCharacterBase
{
    GENERATED_BODY()

public:
    AApostleCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apostle")
    EApostleSymbol Symbol;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apostle")
    FString CallingStory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apostle")
    FString Profession;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apostle")
    FString FeastDay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apostle")
    int32 ApostleNumber;  // Order called (1-12)
};

// ============================================
// SIMON PETER
// ============================================
UCLASS()
class BIBLEVRGAME_API APeterApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    APeterApostle();
};

// ============================================
// ANDREW
// ============================================
UCLASS()
class BIBLEVRGAME_API AAndrewApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    AAndrewApostle();
};

// ============================================
// JAMES (Son of Zebedee)
// ============================================
UCLASS()
class BIBLEVRGAME_API AJamesGreaterApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    AJamesGreaterApostle();
};

// ============================================
// JOHN
// ============================================
UCLASS()
class BIBLEVRGAME_API AJohnApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    AJohnApostle();
};

// ============================================
// PHILIP
// ============================================
UCLASS()
class BIBLEVRGAME_API APhilipApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    APhilipApostle();
};

// ============================================
// BARTHOLOMEW (Nathanael)
// ============================================
UCLASS()
class BIBLEVRGAME_API ABartholomewApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    ABartholomewApostle();
};

// ============================================
// MATTHEW (Levi)
// ============================================
UCLASS()
class BIBLEVRGAME_API AMatthewApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    AMatthewApostle();
};

// ============================================
// THOMAS (Didymus)
// ============================================
UCLASS()
class BIBLEVRGAME_API AThomasApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    AThomasApostle();
};

// ============================================
// JAMES (Son of Alphaeus)
// ============================================
UCLASS()
class BIBLEVRGAME_API AJamesLesserApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    AJamesLesserApostle();
};

// ============================================
// THADDAEUS (Judas son of James)
// ============================================
UCLASS()
class BIBLEVRGAME_API AThaddaeusApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    AThaddaeusApostle();
};

// ============================================
// SIMON THE ZEALOT
// ============================================
UCLASS()
class BIBLEVRGAME_API ASimonZealotApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    ASimonZealotApostle();
};

// ============================================
// JUDAS ISCARIOT
// ============================================
UCLASS()
class BIBLEVRGAME_API AJudasApostle : public AApostleCharacter
{
    GENERATED_BODY()
public:
    AJudasApostle();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Apostle|Judas")
    bool bHasBetrayed;

    UFUNCTION(BlueprintCallable, Category = "Apostle|Judas")
    void TriggerBetrayal();
};
