// JesusCharacter.cpp
// Implementation of Jesus Christ character

#include "JesusCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

AJesusCharacter::AJesusCharacter()
{
    // Identity
    CharacterName = TEXT("Jesus");
    Title = TEXT("The Christ");
    Description = TEXT("Jesus of Nazareth, the Son of God, Savior of the world.");
    ScriptureReference = TEXT("John 3:16");
    Role = EBiblicalRole::Messiah;

    // Create VFX components
    DivineGlow = CreateDefaultSubobject<UNiagaraComponent>(TEXT("DivineGlow"));
    DivineGlow->SetupAttachment(RootComponent);
    DivineGlow->bAutoActivate = false;

    HaloEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HaloEffect"));
    HaloEffect->SetupAttachment(RootComponent);
    HaloEffect->bAutoActivate = false;

    // Default settings
    CurrentPeriod = EMinistryPeriod::Galilee;
    GlowIntensity = 1.0f;
    bShowHalo = false;
    bTransfigured = false;
    bCanBeFollowed = true;

    // Emotional profile - perfect balance
    EmotionalProfile.Empathy = 10;
    EmotionalProfile.Energy = 7;
    EmotionalProfile.Formality = 5;
    EmotionalProfile.Playfulness = 5;
    EmotionalProfile.Directness = 8;

    // Dialogue patterns
    DialoguePatterns.Greetings = {
        TEXT("Peace be with you."),
        TEXT("Come, follow me."),
        TEXT("What do you seek?"),
        TEXT("Fear not.")
    };

    DialoguePatterns.Farewells = {
        TEXT("Go in peace."),
        TEXT("Your faith has made you well."),
        TEXT("Go and sin no more."),
        TEXT("I am with you always.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("I am the way, the truth, and the life."),
        TEXT("Love one another as I have loved you."),
        TEXT("Father, forgive them."),
        TEXT("It is finished."),
        TEXT("I am the resurrection and the life."),
        TEXT("Let the little children come to me."),
        TEXT("Blessed are the poor in spirit.")
    };

    // Appearance
    PrimaryColor = FLinearColor(1.0f, 1.0f, 1.0f); // Pure white
    VoicePitch = 1.0f;

    // Initialize teachings
    InitializeTeachings();
}

void AJesusCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Subtle divine glow always active
    if (DivineGlow)
    {
        DivineGlow->Activate();
    }

    UpdateVisualForPeriod();
}

void AJesusCharacter::InitializeTeachings()
{
    // Parables
    Parables = {
        TEXT("The kingdom of heaven is like a mustard seed..."),
        TEXT("A sower went out to sow his seed..."),
        TEXT("There was a man who had two sons..."),
        TEXT("The kingdom of heaven is like treasure hidden in a field..."),
        TEXT("A certain man went down from Jerusalem to Jericho..."),
        TEXT("There was a rich man who was dressed in purple..."),
        TEXT("The kingdom of heaven is like a merchant seeking fine pearls..."),
        TEXT("A farmer went out to plant his seed...")
    };

    // Beatitudes
    Beatitudes = {
        TEXT("Blessed are the poor in spirit, for theirs is the kingdom of heaven."),
        TEXT("Blessed are those who mourn, for they will be comforted."),
        TEXT("Blessed are the meek, for they will inherit the earth."),
        TEXT("Blessed are those who hunger and thirst for righteousness, for they will be filled."),
        TEXT("Blessed are the merciful, for they will be shown mercy."),
        TEXT("Blessed are the pure in heart, for they will see God."),
        TEXT("Blessed are the peacemakers, for they will be called children of God."),
        TEXT("Blessed are those who are persecuted because of righteousness, for theirs is the kingdom of heaven.")
    };

    // Core teachings
    Teachings = {
        TEXT("You shall love the Lord your God with all your heart, soul, and mind."),
        TEXT("Love your neighbor as yourself."),
        TEXT("Do unto others as you would have them do unto you."),
        TEXT("Judge not, that you be not judged."),
        TEXT("Ask, and it will be given to you; seek, and you will find."),
        TEXT("For God so loved the world that He gave His only Son."),
        TEXT("I am the light of the world."),
        TEXT("You are the salt of the earth."),
        TEXT("Let your light shine before others."),
        TEXT("Forgive us our debts, as we also have forgiven our debtors.")
    };
}

FString AJesusCharacter::GetGreeting()
{
    // Context-sensitive greeting based on ministry period
    switch (CurrentPeriod)
    {
        case EMinistryPeriod::Baptism:
            return TEXT("The Spirit of the Lord is upon me.");

        case EMinistryPeriod::Resurrection:
            return TEXT("Peace be with you. It is I; do not be afraid.");

        case EMinistryPeriod::Ascension:
            return TEXT("All authority in heaven and on earth has been given to me.");

        default:
            return Super::GetGreeting();
    }
}

void AJesusCharacter::OnPlayerInteract(ACharacter* Player)
{
    // Special interaction based on period
    switch (CurrentPeriod)
    {
        case EMinistryPeriod::Galilee:
        case EMinistryPeriod::Judea:
            // Teaching mode
            SpeakLine(GiveTeaching());
            break;

        case EMinistryPeriod::Resurrection:
            // Peace and reassurance
            BlessPlayer(Player);
            break;

        default:
            Super::OnPlayerInteract(Player);
            break;
    }

    // Always increase relationship
    ModifyRelationship(5);
}

void AJesusCharacter::PerformMiracle(EMiracle Miracle)
{
    FString MiracleText;

    switch (Miracle)
    {
        case EMiracle::HealingSick:
            MiracleText = TEXT("Your faith has healed you. Go in peace.");
            break;

        case EMiracle::CastingOutDemons:
            MiracleText = TEXT("Come out of him and never enter him again!");
            break;

        case EMiracle::RaisingDead:
            MiracleText = TEXT("I am the resurrection and the life. Come forth!");
            break;

        case EMiracle::FeedingMultitude:
            MiracleText = TEXT("Give them something to eat.");
            break;

        case EMiracle::CalmingStorm:
            MiracleText = TEXT("Peace! Be still!");
            break;

        case EMiracle::WalkingOnWater:
            MiracleText = TEXT("Take courage! It is I. Don't be afraid.");
            break;

        case EMiracle::WaterToWine:
            MiracleText = TEXT("Fill the jars with water.");
            break;

        case EMiracle::RestoringLimbs:
            MiracleText = TEXT("Stretch out your hand.");
            break;
    }

    SpeakLine(MiracleText);

    // Increase glow during miracle
    float OriginalGlow = GlowIntensity;
    GlowIntensity = 2.0f;

    // Broadcast event
    OnMiraclePerformed.Broadcast(Miracle);

    // Reset glow after short delay (would use timer in actual implementation)
    GlowIntensity = OriginalGlow;
}

FString AJesusCharacter::SpeakParable()
{
    if (Parables.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, Parables.Num() - 1);
        FString Parable = Parables[Index];
        SpeakLine(Parable);
        OnParableSpoken.Broadcast(Parable);
        return Parable;
    }
    return TEXT("");
}

FString AJesusCharacter::GiveTeaching()
{
    if (Teachings.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, Teachings.Num() - 1);
        return Teachings[Index];
    }
    return TEXT("Come, follow me.");
}

void AJesusCharacter::BlessPlayer(ACharacter* Player)
{
    SpeakLine(TEXT("Peace I leave with you; my peace I give you."));

    // Visual blessing effect
    if (DivineGlow)
    {
        // Pulse the glow
        GlowIntensity = 2.0f;
    }

    // Broadcast blessing
    OnBlessingGiven.Broadcast();

    // Could apply buffs to player here (faith increase, etc.)
}

void AJesusCharacter::SetMinistryPeriod(EMinistryPeriod Period)
{
    CurrentPeriod = Period;
    UpdateVisualForPeriod();
}

void AJesusCharacter::UpdateVisualForPeriod()
{
    switch (CurrentPeriod)
    {
        case EMinistryPeriod::Childhood:
            GlowIntensity = 0.3f;
            bShowHalo = false;
            break;

        case EMinistryPeriod::Baptism:
            GlowIntensity = 1.5f;
            bShowHalo = true;
            break;

        case EMinistryPeriod::Crucifixion:
            GlowIntensity = 0.5f;
            bShowHalo = false;
            SetEmotion(EEmotionalState::Sorrowful);
            break;

        case EMinistryPeriod::Resurrection:
            GlowIntensity = 2.0f;
            bShowHalo = true;
            SetEmotion(EEmotionalState::Peaceful);
            break;

        case EMinistryPeriod::Ascension:
            GlowIntensity = 3.0f;
            bShowHalo = true;
            Transfigure(true);
            break;

        default:
            GlowIntensity = 1.0f;
            bShowHalo = false;
            SetEmotion(EEmotionalState::Peaceful);
            break;
    }

    // Update halo visibility
    if (HaloEffect)
    {
        if (bShowHalo)
            HaloEffect->Activate();
        else
            HaloEffect->Deactivate();
    }
}

void AJesusCharacter::Transfigure(bool bEnable)
{
    bTransfigured = bEnable;

    if (bEnable)
    {
        GlowIntensity = 5.0f;
        bShowHalo = true;

        // Clothes become dazzling white
        // Face shines like the sun

        if (HaloEffect)
        {
            HaloEffect->Activate();
        }

        // Could spawn additional effects (Moses and Elijah appearing, etc.)
    }
    else
    {
        UpdateVisualForPeriod();
    }
}
