// CompanionCharacter.cpp
// Implementation of companion characters

#include "CompanionCharacter.h"

// ============================================
// BASE COMPANION
// ============================================

ACompanionCharacter::ACompanionCharacter()
{
    Role = EBiblicalRole::Companion;
    bCanBeFollowed = true;
    bIsActiveCompanion = false;
    LoyaltyLevel = 50;
}

void ACompanionCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ACompanionCharacter::ActivateAsCompanion()
{
    bIsActiveCompanion = true;
    // Notify game state
}

void ACompanionCharacter::DeactivateCompanion()
{
    bIsActiveCompanion = false;
    StopFollowing();
}

void ACompanionCharacter::UseAbility(ECompanionAbility Ability)
{
    if (!HasAbility(Ability)) return;

    switch (Ability)
    {
        case ECompanionAbility::Leadership:
            // Boost player's influence in conversations
            break;
        case ECompanionAbility::Healing:
            // Restore player's faith/health
            break;
        case ECompanionAbility::Wisdom:
            // Reveal hidden knowledge
            break;
        case ECompanionAbility::Protection:
            // Reduce temptation effects
            break;
        case ECompanionAbility::Inspiration:
            // Boost faith gain
            break;
        case ECompanionAbility::Knowledge:
            // Unlock scripture references
            break;
        case ECompanionAbility::Comfort:
            // Restore from fear/doubt
            break;
        case ECompanionAbility::Guidance:
            // Show quest objectives
            break;
    }
}

bool ACompanionCharacter::HasAbility(ECompanionAbility Ability)
{
    return Abilities.Contains(Ability);
}

FString ACompanionCharacter::GetCompanionAdvice()
{
    // Override in subclasses for specific advice
    return TEXT("Trust in the Lord with all your heart.");
}

// ============================================
// PETER - The Rock
// ============================================

APeterCompanion::APeterCompanion()
{
    CharacterName = TEXT("Peter");
    Title = TEXT("The Rock");
    Description = TEXT("Simon Peter, fisherman turned apostle, known for his bold faith and leadership.");
    ScriptureReference = TEXT("Matthew 16:18");

    // Emotional profile
    EmotionalProfile.Empathy = 8;
    EmotionalProfile.Energy = 9;
    EmotionalProfile.Formality = 4;
    EmotionalProfile.Playfulness = 6;
    EmotionalProfile.Directness = 9;

    // Abilities
    Abilities.Add(ECompanionAbility::Leadership);
    Abilities.Add(ECompanionAbility::Protection);

    // Dialogue patterns
    DialoguePatterns.Greetings = {
        TEXT("Peace be with you, friend!"),
        TEXT("Ah, there you are! I was just thinking of you."),
        TEXT("Welcome! Come, let us walk together.")
    };

    DialoguePatterns.Farewells = {
        TEXT("Go with strength, my friend."),
        TEXT("May His peace guide your steps."),
        TEXT("Until we meet again - stay bold!")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("By the nets of Galilee!"),
        TEXT("As sure as the sea is deep..."),
        TEXT("Lord, you know that I love you.")
    };

    // Voice characteristics
    VoiceTone = TEXT("Bold and passionate");
    SpeakingStyle = TEXT("Direct, enthusiastic, sometimes impulsive");
    VoicePitch = 0.95f;

    CompanionQuote = TEXT("Upon this rock I will build my church.");

    // Appearance
    PrimaryColor = FLinearColor(0.6f, 0.4f, 0.2f); // Earthy brown
}

// ============================================
// MARY MAGDALENE - Faithful Follower
// ============================================

AMaryMagdaleneCompanion::AMaryMagdaleneCompanion()
{
    CharacterName = TEXT("Mary Magdalene");
    Title = TEXT("Faithful Follower");
    Description = TEXT("First witness to the resurrection, devoted follower of Jesus.");
    ScriptureReference = TEXT("John 20:11-18");

    // Emotional profile
    EmotionalProfile.Empathy = 10;
    EmotionalProfile.Energy = 7;
    EmotionalProfile.Formality = 5;
    EmotionalProfile.Playfulness = 4;
    EmotionalProfile.Directness = 7;

    // Abilities
    Abilities.Add(ECompanionAbility::Comfort);
    Abilities.Add(ECompanionAbility::Inspiration);

    // Dialogue patterns
    DialoguePatterns.Greetings = {
        TEXT("Grace and peace to you."),
        TEXT("How beautiful to see you again."),
        TEXT("Come, there is much to share.")
    };

    DialoguePatterns.Farewells = {
        TEXT("May His love surround you."),
        TEXT("Go in grace."),
        TEXT("Remember - He is always with you.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("I have seen the Lord!"),
        TEXT("Let your heart be open..."),
        TEXT("In His presence, all is transformed.")
    };

    // Voice characteristics
    VoiceTone = TEXT("Warm and compassionate");
    SpeakingStyle = TEXT("Gentle, thoughtful, deeply sincere");
    VoicePitch = 1.1f;

    CompanionQuote = TEXT("I have seen the Lord!");

    // Appearance
    PrimaryColor = FLinearColor(0.5f, 0.2f, 0.3f); // Deep rose
}

// ============================================
// JOHN - The Beloved
// ============================================

AJohnCompanion::AJohnCompanion()
{
    CharacterName = TEXT("John");
    Title = TEXT("The Beloved Disciple");
    Description = TEXT("Author of the Gospel of John, known for his deep spiritual insight.");
    ScriptureReference = TEXT("John 21:20-24");

    // Emotional profile
    EmotionalProfile.Empathy = 9;
    EmotionalProfile.Energy = 6;
    EmotionalProfile.Formality = 6;
    EmotionalProfile.Playfulness = 5;
    EmotionalProfile.Directness = 6;

    // Abilities
    Abilities.Add(ECompanionAbility::Wisdom);
    Abilities.Add(ECompanionAbility::Knowledge);

    // Dialogue patterns
    DialoguePatterns.Greetings = {
        TEXT("Beloved friend, welcome."),
        TEXT("Peace to you, child of light."),
        TEXT("Let us reason together.")
    };

    DialoguePatterns.Farewells = {
        TEXT("Abide in His love."),
        TEXT("Walk in the light."),
        TEXT("May truth guide your path.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("God is love..."),
        TEXT("In the beginning was the Word..."),
        TEXT("Let us love one another.")
    };

    // Voice characteristics
    VoiceTone = TEXT("Contemplative and warm");
    SpeakingStyle = TEXT("Poetic, philosophical, deeply loving");
    VoicePitch = 1.0f;

    CompanionQuote = TEXT("God is love, and whoever abides in love abides in God.");

    // Appearance
    PrimaryColor = FLinearColor(0.2f, 0.3f, 0.5f); // Deep blue
}

// ============================================
// PAUL - Apostle to the Gentiles
// ============================================

APaulCompanion::APaulCompanion()
{
    CharacterName = TEXT("Paul");
    Title = TEXT("Apostle to the Gentiles");
    Description = TEXT("Formerly Saul of Tarsus, transformed by Christ on the road to Damascus.");
    ScriptureReference = TEXT("Acts 9:1-19");

    // Emotional profile
    EmotionalProfile.Empathy = 7;
    EmotionalProfile.Energy = 9;
    EmotionalProfile.Formality = 7;
    EmotionalProfile.Playfulness = 3;
    EmotionalProfile.Directness = 10;

    // Abilities
    Abilities.Add(ECompanionAbility::Knowledge);
    Abilities.Add(ECompanionAbility::Inspiration);

    // Dialogue patterns
    DialoguePatterns.Greetings = {
        TEXT("Grace and peace from God our Father."),
        TEXT("Greetings in Christ!"),
        TEXT("Ah, a fellow laborer!")
    };

    DialoguePatterns.Farewells = {
        TEXT("Run the race set before you."),
        TEXT("Stand firm in the faith."),
        TEXT("The grace of the Lord be with you.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("For I am not ashamed of the gospel..."),
        TEXT("If God is for us, who can be against us?"),
        TEXT("I can do all things through Christ.")
    };

    // Voice characteristics
    VoiceTone = TEXT("Authoritative and passionate");
    SpeakingStyle = TEXT("Logical, eloquent, intensely devoted");
    VoicePitch = 0.9f;

    CompanionQuote = TEXT("I have fought the good fight, I have finished the race.");

    // Appearance
    PrimaryColor = FLinearColor(0.4f, 0.3f, 0.5f); // Royal purple
}

// ============================================
// SOLOMON - The Wise King
// ============================================

ASolomonCompanion::ASolomonCompanion()
{
    CharacterName = TEXT("Solomon");
    Title = TEXT("The Wise King");
    Description = TEXT("King of Israel, renowned for wisdom and author of Proverbs.");
    ScriptureReference = TEXT("1 Kings 3:5-14");

    // Emotional profile
    EmotionalProfile.Empathy = 6;
    EmotionalProfile.Energy = 5;
    EmotionalProfile.Formality = 8;
    EmotionalProfile.Playfulness = 4;
    EmotionalProfile.Directness = 7;

    // Abilities
    Abilities.Add(ECompanionAbility::Wisdom);
    Abilities.Add(ECompanionAbility::Guidance);

    // Dialogue patterns
    DialoguePatterns.Greetings = {
        TEXT("Seek wisdom, and you have found me."),
        TEXT("A word to the wise is sufficient."),
        TEXT("Welcome, seeker of understanding.")
    };

    DialoguePatterns.Farewells = {
        TEXT("Remember: the fear of the Lord is the beginning of wisdom."),
        TEXT("Apply your heart to instruction."),
        TEXT("Go, and walk in wisdom's ways.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Vanity of vanities..."),
        TEXT("There is nothing new under the sun."),
        TEXT("A soft answer turns away wrath.")
    };

    // Voice characteristics
    VoiceTone = TEXT("Measured and regal");
    SpeakingStyle = TEXT("Proverbs, measured wisdom, thoughtful pauses");
    VoicePitch = 0.85f;

    CompanionQuote = TEXT("The fear of the Lord is the beginning of wisdom.");

    // Appearance
    PrimaryColor = FLinearColor(0.8f, 0.7f, 0.2f); // Royal gold
}

// ============================================
// THE GUIDE - Narrator
// ============================================

ATheGuideCompanion::ATheGuideCompanion()
{
    CharacterName = TEXT("The Guide");
    Title = TEXT("Your Companion");
    Description = TEXT("A gentle presence to help you navigate your spiritual journey.");
    ScriptureReference = TEXT("Psalm 23:4");

    // Emotional profile
    EmotionalProfile.Empathy = 10;
    EmotionalProfile.Energy = 5;
    EmotionalProfile.Formality = 5;
    EmotionalProfile.Playfulness = 6;
    EmotionalProfile.Directness = 6;

    // Abilities
    Abilities.Add(ECompanionAbility::Guidance);
    Abilities.Add(ECompanionAbility::Comfort);
    Abilities.Add(ECompanionAbility::Knowledge);

    // Dialogue patterns
    DialoguePatterns.Greetings = {
        TEXT("Welcome, traveler."),
        TEXT("I am here to guide you."),
        TEXT("What would you like to explore?")
    };

    DialoguePatterns.Farewells = {
        TEXT("I will be here when you need me."),
        TEXT("Go with peace."),
        TEXT("May your journey be blessed.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Let me show you..."),
        TEXT("Consider this..."),
        TEXT("There is much to discover here.")
    };

    // Voice characteristics
    VoiceTone = TEXT("Calm and reassuring");
    SpeakingStyle = TEXT("Patient, clear, encouraging");
    VoicePitch = 1.0f;

    CompanionQuote = TEXT("Even though I walk through the valley of the shadow of death, I will fear no evil.");

    // Appearance
    PrimaryColor = FLinearColor(1.0f, 1.0f, 1.0f); // Pure white
}
