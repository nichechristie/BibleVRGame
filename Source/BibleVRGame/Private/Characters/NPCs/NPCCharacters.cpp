// NPCCharacters.cpp
// Implementation of NPC characters

#include "NPCCharacters.h"
#include "NiagaraFunctionLibrary.h"

// ============================================
// ROMAN SOLDIER
// ============================================

ARomanSoldier::ARomanSoldier()
{
    Role = EBiblicalRole::RomanSoldier;
    Rank = ERomanRank::Legionary;
    Legion = TEXT("X Fretensis");
    bIsHostile = false;
    bIsOnDuty = true;
    bCanBeFollowed = false;

    PrimaryColor = FLinearColor(0.7f, 0.2f, 0.2f); // Roman red

    DialoguePatterns.Greetings = {
        TEXT("Citizen."),
        TEXT("Move along."),
        TEXT("State your business.")
    };
}

void ARomanSoldier::IssueCommand(const FString& Command)
{
    SpeakLine(Command);
}

void ARomanSoldier::SetHostility(bool bHostile)
{
    bIsHostile = bHostile;
    if (bHostile)
    {
        SetEmotion(EEmotionalState::Angry);
    }
    else
    {
        SetEmotion(EEmotionalState::Neutral);
    }
}

// Centurion
ACenturionCharacter::ACenturionCharacter()
{
    CharacterName = TEXT("Centurion");
    Title = TEXT("Commander of 100");
    Rank = ERomanRank::Centurion;
    Description = TEXT("A Roman centurion of great faith.");
    ScriptureReference = TEXT("Matthew 8:5-13");

    EmotionalProfile.Directness = 9;
    EmotionalProfile.Formality = 8;

    DialoguePatterns.Greetings = {
        TEXT("I am a man under authority."),
        TEXT("Speak, and I will listen."),
        TEXT("Greetings.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Lord, I am not worthy for you to come under my roof."),
        TEXT("Just say the word, and my servant will be healed."),
        TEXT("Truly, this was the Son of God!")
    };

    VoicePitch = 0.85f;
}

// Pontius Pilate
APontiusPilateCharacter::APontiusPilateCharacter()
{
    CharacterName = TEXT("Pontius Pilate");
    Title = TEXT("Prefect of Judea");
    Rank = ERomanRank::Prefect;
    Description = TEXT("Roman governor who judged Jesus.");
    ScriptureReference = TEXT("Matthew 27:11-26");

    bHasWashedHands = false;

    EmotionalProfile.Empathy = 4;
    EmotionalProfile.Formality = 9;
    EmotionalProfile.Directness = 7;

    DialoguePatterns.Greetings = {
        TEXT("What accusation do you bring?"),
        TEXT("Speak."),
        TEXT("I will hear this matter.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("What is truth?"),
        TEXT("I find no fault in this man."),
        TEXT("I am innocent of this man's blood.")
    };

    PrimaryColor = FLinearColor(0.8f, 0.8f, 0.9f); // Imperial purple/white
    VoicePitch = 0.9f;
}

void APontiusPilateCharacter::WashHands()
{
    bHasWashedHands = true;
    SpeakLine(TEXT("I am innocent of this man's blood. See to it yourselves."));
}

// ============================================
// RELIGIOUS LEADERS
// ============================================

AReligiousLeader::AReligiousLeader()
{
    Role = EBiblicalRole::ReligiousLeader;
    ReligiousTitle = EReligiousTitle::Pharisee;
    bIsAntagonist = false;
    bCanBeFollowed = false;

    PrimaryColor = FLinearColor(0.2f, 0.2f, 0.4f); // Priestly blue

    DialoguePatterns.Greetings = {
        TEXT("Shalom."),
        TEXT("Peace be upon you."),
        TEXT("Greetings, friend.")
    };
}

FString AReligiousLeader::PoseChallenge()
{
    if (ScripturalChallenges.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, ScripturalChallenges.Num() - 1);
        return ScripturalChallenges[Index];
    }
    return TEXT("By what authority do you do these things?");
}

// Caiaphas
ACaiaphasCharacter::ACaiaphasCharacter()
{
    CharacterName = TEXT("Caiaphas");
    Title = TEXT("High Priest");
    ReligiousTitle = EReligiousTitle::HighPriest;
    Description = TEXT("High Priest who presided over Jesus's trial.");
    ScriptureReference = TEXT("Matthew 26:57-68");
    bIsAntagonist = true;

    EmotionalProfile.Empathy = 3;
    EmotionalProfile.Formality = 9;
    EmotionalProfile.Directness = 8;

    ScripturalChallenges = {
        TEXT("Are you the Christ, the Son of the Blessed One?"),
        TEXT("What further need do we have of witnesses?"),
        TEXT("You have heard the blasphemy!")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("It is better that one man die for the people."),
        TEXT("He has blasphemed!"),
        TEXT("What is your verdict?")
    };

    VoicePitch = 0.88f;
}

// Nicodemus
ANicodemusCharacter::ANicodemusCharacter()
{
    CharacterName = TEXT("Nicodemus");
    Title = TEXT("Pharisee and Teacher");
    ReligiousTitle = EReligiousTitle::Pharisee;
    Description = TEXT("Pharisee who came to Jesus by night, secret believer.");
    ScriptureReference = TEXT("John 3:1-21");
    bIsAntagonist = false;

    EmotionalProfile.Empathy = 7;
    EmotionalProfile.Formality = 7;
    EmotionalProfile.Directness = 5;

    DialoguePatterns.Greetings = {
        TEXT("Rabbi, we know you are a teacher from God."),
        TEXT("Peace to you."),
        TEXT("I seek understanding.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("How can a man be born when he is old?"),
        TEXT("How can these things be?"),
        TEXT("Does our law judge a man without hearing him?")
    };

    VoicePitch = 1.0f;
}

// Generic Pharisee
APhariseeCharacter::APhariseeCharacter()
{
    CharacterName = TEXT("Pharisee");
    Title = TEXT("Teacher of the Law");
    ReligiousTitle = EReligiousTitle::Pharisee;
    Description = TEXT("A Pharisee, strict observer of the Law.");
    bIsAntagonist = true;

    ScripturalChallenges = {
        TEXT("Why do your disciples break the tradition of the elders?"),
        TEXT("Is it lawful to heal on the Sabbath?"),
        TEXT("By what authority do you do these things?")
    };

    VoicePitch = 0.95f;
}

// ============================================
// ANGELS
// ============================================

AAngelCharacter::AAngelCharacter()
{
    Role = EBiblicalRole::Angel;
    AngelType = EAngelType::Messenger;
    GlowIntensity = 1.0f;
    bWingsVisible = false;
    bCanBeFollowed = false;

    // Create VFX components
    GlowEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("GlowEffect"));
    GlowEffect->SetupAttachment(RootComponent);

    WingEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WingEffect"));
    WingEffect->SetupAttachment(RootComponent);

    PrimaryColor = FLinearColor(1.0f, 1.0f, 1.0f); // Pure white

    DialoguePatterns.Greetings = {
        TEXT("Do not be afraid."),
        TEXT("Peace be with you."),
        TEXT("Greetings, favored one.")
    };
}

void AAngelCharacter::DeliverMessage(const FString& Message)
{
    SetGlow(2.0f);
    SpeakLine(Message);
}

void AAngelCharacter::SetGlow(float Intensity)
{
    GlowIntensity = Intensity;
    // Update material parameters
}

void AAngelCharacter::ToggleWings(bool bVisible)
{
    bWingsVisible = bVisible;
    if (WingEffect)
    {
        if (bVisible)
            WingEffect->Activate();
        else
            WingEffect->Deactivate();
    }
}

// Gabriel
AGabrielCharacter::AGabrielCharacter()
{
    CharacterName = TEXT("Gabriel");
    Title = TEXT("Messenger of God");
    AngelType = EAngelType::Archangel;
    Description = TEXT("Archangel who announced the births of John and Jesus.");
    ScriptureReference = TEXT("Luke 1:26-38");

    DialoguePatterns.SignatureExpressions = {
        TEXT("I am Gabriel. I stand in the presence of God."),
        TEXT("Do not be afraid, Mary."),
        TEXT("Nothing is impossible with God.")
    };

    VoicePitch = 1.1f;
    GlowIntensity = 1.5f;
}

// Michael
AMichaelCharacter::AMichaelCharacter()
{
    CharacterName = TEXT("Michael");
    Title = TEXT("Warrior of God");
    AngelType = EAngelType::Archangel;
    Description = TEXT("Archangel and leader of God's armies against evil.");
    ScriptureReference = TEXT("Revelation 12:7-9");

    DialoguePatterns.SignatureExpressions = {
        TEXT("The Lord rebuke you!"),
        TEXT("Who is like God?"),
        TEXT("Stand firm against the darkness.")
    };

    VoicePitch = 0.85f;
    GlowIntensity = 2.0f;
}

// ============================================
// WOMEN OF THE BIBLE
// ============================================

ABiblicalWoman::ABiblicalWoman()
{
    Role = EBiblicalRole::Civilian;
    bCanBeFollowed = false;
}

// Mary Mother of Jesus
AMaryMotherCharacter::AMaryMotherCharacter()
{
    CharacterName = TEXT("Mary");
    Title = TEXT("Mother of Jesus");
    Description = TEXT("Blessed virgin, mother of Jesus Christ.");
    ScriptureReference = TEXT("Luke 1:26-38");

    EmotionalProfile.Empathy = 10;
    EmotionalProfile.Energy = 5;
    EmotionalProfile.Formality = 6;

    DialoguePatterns.Greetings = {
        TEXT("Grace and peace to you."),
        TEXT("Welcome, child."),
        TEXT("Peace be with you.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("I am the Lord's servant."),
        TEXT("Let it be to me according to your word."),
        TEXT("My soul magnifies the Lord.")
    };

    PrimaryColor = FLinearColor(0.3f, 0.4f, 0.8f); // Mary blue
    VoicePitch = 1.15f;
}

// Martha
AMarthaCharacter::AMarthaCharacter()
{
    CharacterName = TEXT("Martha");
    Title = TEXT("Of Bethany");
    Description = TEXT("Sister of Mary and Lazarus, known for her hospitality.");
    ScriptureReference = TEXT("Luke 10:38-42");

    EmotionalProfile.Empathy = 7;
    EmotionalProfile.Energy = 8;
    EmotionalProfile.Directness = 8;

    DialoguePatterns.SignatureExpressions = {
        TEXT("Lord, do you not care that my sister has left me to serve alone?"),
        TEXT("Yes, Lord, I believe."),
        TEXT("If you had been here, my brother would not have died.")
    };

    VoicePitch = 1.05f;
}

// Mary of Bethany
AMaryBethanyCharacter::AMaryBethanyCharacter()
{
    CharacterName = TEXT("Mary");
    Title = TEXT("Of Bethany");
    Description = TEXT("Sister of Martha and Lazarus, sat at Jesus's feet.");
    ScriptureReference = TEXT("Luke 10:38-42");

    EmotionalProfile.Empathy = 9;
    EmotionalProfile.Energy = 4;
    EmotionalProfile.Formality = 5;

    DialoguePatterns.SignatureExpressions = {
        TEXT("Lord, if you had been here..."),
        TEXT("I anoint you for burial."),
        TEXT("Teach me, Lord.")
    };

    VoicePitch = 1.1f;
}

// Woman at the Well
AWomanAtWellCharacter::AWomanAtWellCharacter()
{
    CharacterName = TEXT("Samaritan Woman");
    Title = TEXT("Woman at the Well");
    Description = TEXT("The Samaritan woman who met Jesus at Jacob's well.");
    ScriptureReference = TEXT("John 4:1-42");

    EmotionalProfile.Empathy = 6;
    EmotionalProfile.Energy = 7;
    EmotionalProfile.Directness = 7;

    DialoguePatterns.SignatureExpressions = {
        TEXT("How is it that you ask me for a drink?"),
        TEXT("Sir, give me this water!"),
        TEXT("Come, see a man who told me everything I ever did!")
    };

    VoicePitch = 1.08f;
}

// ============================================
// CIVILIANS
// ============================================

ACivilianCharacter::ACivilianCharacter()
{
    Role = EBiblicalRole::Civilian;
    CivilianType = ECivilianType::Merchant;
    bCanTrade = false;
    bCanBeFollowed = false;

    DialoguePatterns.Greetings = {
        TEXT("Shalom, friend."),
        TEXT("Peace to you."),
        TEXT("Greetings, traveler.")
    };
}

FString ACivilianCharacter::ShareRumor()
{
    if (LocalRumors.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, LocalRumors.Num() - 1);
        return LocalRumors[Index];
    }
    return TEXT("Strange times we live in...");
}

// ============================================
// CROWD
// ============================================

ACrowdMember::ACrowdMember()
{
    CharacterName = TEXT("Crowd Member");
    bCanBeIndividualized = false;
    bCanBeFollowed = false;

    CrowdChants = {
        TEXT("Hosanna!"),
        TEXT("Blessed is he who comes!"),
        TEXT("Crucify him!")
    };
}

void ACrowdMember::JoinChant(const FString& Chant)
{
    SpeakLine(Chant);
}
