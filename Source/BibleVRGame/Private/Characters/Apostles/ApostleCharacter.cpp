// ApostleCharacter.cpp
// Implementation of all 12 Apostle characters

#include "ApostleCharacter.h"

// ============================================
// BASE APOSTLE
// ============================================

AApostleCharacter::AApostleCharacter()
{
    Role = EBiblicalRole::Apostle;
    bCanBeFollowed = true;
    ApostleNumber = 0;
}

// ============================================
// SIMON PETER
// ============================================

APeterApostle::APeterApostle()
{
    CharacterName = TEXT("Simon Peter");
    Title = TEXT("The Rock");
    Profession = TEXT("Fisherman");
    Description = TEXT("Leader of the apostles, first pope, bold yet sometimes impulsive.");
    ScriptureReference = TEXT("Matthew 4:18-20");
    CallingStory = TEXT("Called while casting nets into the Sea of Galilee");
    Symbol = EApostleSymbol::Keys;
    FeastDay = TEXT("June 29");
    ApostleNumber = 1;

    EmotionalProfile.Empathy = 8;
    EmotionalProfile.Energy = 9;
    EmotionalProfile.Directness = 9;

    DialoguePatterns.Greetings = {
        TEXT("Peace be with you!"),
        TEXT("Friend! Good to see you."),
        TEXT("Come, walk with me.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("You are the Christ, the Son of the living God."),
        TEXT("Lord, to whom shall we go?"),
        TEXT("Even if all fall away, I will not.")
    };

    PrimaryColor = FLinearColor(0.6f, 0.4f, 0.2f);
    VoicePitch = 0.95f;
}

// ============================================
// ANDREW
// ============================================

AAndrewApostle::AAndrewApostle()
{
    CharacterName = TEXT("Andrew");
    Title = TEXT("The First-Called");
    Profession = TEXT("Fisherman");
    Description = TEXT("Brother of Peter, first disciple called, known for bringing others to Jesus.");
    ScriptureReference = TEXT("John 1:40-42");
    CallingStory = TEXT("First disciple of John the Baptist to follow Jesus");
    Symbol = EApostleSymbol::XCross;
    FeastDay = TEXT("November 30");
    ApostleNumber = 2;

    EmotionalProfile.Empathy = 8;
    EmotionalProfile.Energy = 6;
    EmotionalProfile.Directness = 7;

    DialoguePatterns.Greetings = {
        TEXT("We have found the Messiah!"),
        TEXT("Come and see."),
        TEXT("Peace to you, friend.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Come and see for yourself."),
        TEXT("There is a boy here with five loaves..."),
        TEXT("Sir, we wish to see Jesus.")
    };

    PrimaryColor = FLinearColor(0.3f, 0.5f, 0.7f);
    VoicePitch = 1.0f;
}

// ============================================
// JAMES (Greater)
// ============================================

AJamesGreaterApostle::AJamesGreaterApostle()
{
    CharacterName = TEXT("James");
    Title = TEXT("Son of Zebedee");
    Profession = TEXT("Fisherman");
    Description = TEXT("Brother of John, one of the inner three, first apostle martyred.");
    ScriptureReference = TEXT("Matthew 4:21-22");
    CallingStory = TEXT("Called while mending nets with his father Zebedee");
    Symbol = EApostleSymbol::Shell;
    FeastDay = TEXT("July 25");
    ApostleNumber = 3;

    EmotionalProfile.Empathy = 6;
    EmotionalProfile.Energy = 8;
    EmotionalProfile.Directness = 8;

    DialoguePatterns.Greetings = {
        TEXT("Shalom, friend."),
        TEXT("The Lord's blessing upon you."),
        TEXT("Greetings in His name.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Lord, do you want us to call fire down from heaven?"),
        TEXT("We are able."),
        TEXT("Grant us to sit at your right and left.")
    };

    PrimaryColor = FLinearColor(0.7f, 0.3f, 0.2f);
    VoicePitch = 0.9f;
}

// ============================================
// JOHN
// ============================================

AJohnApostle::AJohnApostle()
{
    CharacterName = TEXT("John");
    Title = TEXT("The Beloved Disciple");
    Profession = TEXT("Fisherman");
    Description = TEXT("Brother of James, author of Gospel, known for deep love and spiritual insight.");
    ScriptureReference = TEXT("John 21:20-24");
    CallingStory = TEXT("Called with his brother James from their fishing boat");
    Symbol = EApostleSymbol::Eagle;
    FeastDay = TEXT("December 27");
    ApostleNumber = 4;

    EmotionalProfile.Empathy = 9;
    EmotionalProfile.Energy = 6;
    EmotionalProfile.Directness = 6;

    DialoguePatterns.Greetings = {
        TEXT("Beloved friend, peace."),
        TEXT("Grace to you."),
        TEXT("Let us walk in love.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("God is love."),
        TEXT("In the beginning was the Word."),
        TEXT("Little children, love one another.")
    };

    PrimaryColor = FLinearColor(0.2f, 0.3f, 0.6f);
    VoicePitch = 1.0f;
}

// ============================================
// PHILIP
// ============================================

APhilipApostle::APhilipApostle()
{
    CharacterName = TEXT("Philip");
    Title = TEXT("Of Bethsaida");
    Profession = TEXT("Unknown");
    Description = TEXT("From Bethsaida, brought Nathanael to Jesus, practical and questioning.");
    ScriptureReference = TEXT("John 1:43-46");
    CallingStory = TEXT("Jesus found Philip and said 'Follow me'");
    Symbol = EApostleSymbol::Loaves;
    FeastDay = TEXT("May 3");
    ApostleNumber = 5;

    EmotionalProfile.Empathy = 7;
    EmotionalProfile.Energy = 5;
    EmotionalProfile.Directness = 6;

    DialoguePatterns.Greetings = {
        TEXT("Come and see!"),
        TEXT("Peace be with you."),
        TEXT("Friend, welcome.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Come and see."),
        TEXT("Lord, show us the Father."),
        TEXT("Where can we buy bread for these people?")
    };

    PrimaryColor = FLinearColor(0.5f, 0.6f, 0.3f);
    VoicePitch = 1.05f;
}

// ============================================
// BARTHOLOMEW (Nathanael)
// ============================================

ABartholomewApostle::ABartholomewApostle()
{
    CharacterName = TEXT("Bartholomew");
    Title = TEXT("Nathanael");
    Profession = TEXT("Unknown");
    Description = TEXT("Also called Nathanael, known for his honesty and initial skepticism.");
    ScriptureReference = TEXT("John 1:45-51");
    CallingStory = TEXT("Brought by Philip, recognized Jesus as Son of God");
    Symbol = EApostleSymbol::Knife;
    FeastDay = TEXT("August 24");
    ApostleNumber = 6;

    EmotionalProfile.Empathy = 6;
    EmotionalProfile.Energy = 5;
    EmotionalProfile.Directness = 8;

    DialoguePatterns.Greetings = {
        TEXT("Shalom."),
        TEXT("Peace, friend."),
        TEXT("Good to meet you.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Can anything good come from Nazareth?"),
        TEXT("Rabbi, you are the Son of God!"),
        TEXT("You are the King of Israel!")
    };

    PrimaryColor = FLinearColor(0.4f, 0.4f, 0.5f);
    VoicePitch = 1.0f;
}

// ============================================
// MATTHEW (Levi)
// ============================================

AMatthewApostle::AMatthewApostle()
{
    CharacterName = TEXT("Matthew");
    Title = TEXT("Levi the Tax Collector");
    Profession = TEXT("Tax Collector");
    Description = TEXT("Former tax collector, author of the Gospel of Matthew.");
    ScriptureReference = TEXT("Matthew 9:9-13");
    CallingStory = TEXT("Called from his tax booth - left everything immediately");
    Symbol = EApostleSymbol::MoneyBag;
    FeastDay = TEXT("September 21");
    ApostleNumber = 7;

    EmotionalProfile.Empathy = 7;
    EmotionalProfile.Energy = 6;
    EmotionalProfile.Directness = 7;

    DialoguePatterns.Greetings = {
        TEXT("Grace to you, friend."),
        TEXT("Welcome."),
        TEXT("Peace be upon you.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("I was a sinner, yet He called me."),
        TEXT("It is not the healthy who need a doctor."),
        TEXT("Follow me - those were His words.")
    };

    PrimaryColor = FLinearColor(0.5f, 0.4f, 0.3f);
    VoicePitch = 0.95f;
}

// ============================================
// THOMAS (Didymus)
// ============================================

AThomasApostle::AThomasApostle()
{
    CharacterName = TEXT("Thomas");
    Title = TEXT("Didymus (The Twin)");
    Profession = TEXT("Unknown");
    Description = TEXT("Known for doubt, but also for profound faith once convinced.");
    ScriptureReference = TEXT("John 20:24-29");
    CallingStory = TEXT("Called among the Twelve");
    Symbol = EApostleSymbol::Spear;
    FeastDay = TEXT("July 3");
    ApostleNumber = 8;

    EmotionalProfile.Empathy = 6;
    EmotionalProfile.Energy = 5;
    EmotionalProfile.Directness = 9;

    DialoguePatterns.Greetings = {
        TEXT("Shalom."),
        TEXT("Friend."),
        TEXT("Peace to you.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Unless I see... I will not believe."),
        TEXT("Let us also go, that we may die with him."),
        TEXT("My Lord and my God!")
    };

    PrimaryColor = FLinearColor(0.5f, 0.5f, 0.5f);
    VoicePitch = 0.98f;
}

// ============================================
// JAMES (Lesser)
// ============================================

AJamesLesserApostle::AJamesLesserApostle()
{
    CharacterName = TEXT("James");
    Title = TEXT("Son of Alphaeus");
    Profession = TEXT("Unknown");
    Description = TEXT("Called James the Less, possibly brother or cousin of Jesus.");
    ScriptureReference = TEXT("Mark 3:18");
    CallingStory = TEXT("Called among the Twelve");
    Symbol = EApostleSymbol::Club;
    FeastDay = TEXT("May 3");
    ApostleNumber = 9;

    EmotionalProfile.Empathy = 7;
    EmotionalProfile.Energy = 5;
    EmotionalProfile.Directness = 5;

    DialoguePatterns.Greetings = {
        TEXT("Peace be with you."),
        TEXT("Shalom, friend."),
        TEXT("Grace to you.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Faith without works is dead."),
        TEXT("Let your yes be yes."),
        TEXT("Draw near to God.")
    };

    PrimaryColor = FLinearColor(0.4f, 0.5f, 0.4f);
    VoicePitch = 1.02f;
}

// ============================================
// THADDAEUS
// ============================================

AThaddaeusApostle::AThaddaeusApostle()
{
    CharacterName = TEXT("Thaddaeus");
    Title = TEXT("Judas son of James");
    Profession = TEXT("Unknown");
    Description = TEXT("Also called Judas (not Iscariot), known for asking how Jesus would reveal himself.");
    ScriptureReference = TEXT("John 14:22");
    CallingStory = TEXT("Called among the Twelve");
    Symbol = EApostleSymbol::Axe;
    FeastDay = TEXT("October 28");
    ApostleNumber = 10;

    EmotionalProfile.Empathy = 7;
    EmotionalProfile.Energy = 6;
    EmotionalProfile.Directness = 6;

    DialoguePatterns.Greetings = {
        TEXT("Peace, friend."),
        TEXT("Grace be with you."),
        TEXT("Shalom.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Lord, how will you manifest yourself to us?"),
        TEXT("Contend for the faith."),
        TEXT("Keep yourselves in the love of God.")
    };

    PrimaryColor = FLinearColor(0.5f, 0.4f, 0.5f);
    VoicePitch = 1.0f;
}

// ============================================
// SIMON THE ZEALOT
// ============================================

ASimonZealotApostle::ASimonZealotApostle()
{
    CharacterName = TEXT("Simon");
    Title = TEXT("The Zealot");
    Profession = TEXT("Zealot (Political Activist)");
    Description = TEXT("Former member of the Zealots, passionate for Israel's freedom.");
    ScriptureReference = TEXT("Luke 6:15");
    CallingStory = TEXT("Called among the Twelve, leaving political activism for Christ");
    Symbol = EApostleSymbol::Saw;
    FeastDay = TEXT("October 28");
    ApostleNumber = 11;

    EmotionalProfile.Empathy = 5;
    EmotionalProfile.Energy = 8;
    EmotionalProfile.Directness = 9;

    DialoguePatterns.Greetings = {
        TEXT("Shalom, friend."),
        TEXT("Peace be upon you."),
        TEXT("Greetings.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("For the kingdom!"),
        TEXT("There is a greater freedom than Rome can give or take."),
        TEXT("I was zealous, but now I follow the true King.")
    };

    PrimaryColor = FLinearColor(0.6f, 0.3f, 0.3f);
    VoicePitch = 0.92f;
}

// ============================================
// JUDAS ISCARIOT
// ============================================

AJudasApostle::AJudasApostle()
{
    CharacterName = TEXT("Judas");
    Title = TEXT("Iscariot");
    Profession = TEXT("Treasurer");
    Description = TEXT("Keeper of the money bag, betrayed Jesus for thirty pieces of silver.");
    ScriptureReference = TEXT("Matthew 26:14-16");
    CallingStory = TEXT("Called among the Twelve");
    Symbol = EApostleSymbol::Coins;
    FeastDay = TEXT("None");
    ApostleNumber = 12;

    bHasBetrayed = false;

    EmotionalProfile.Empathy = 4;
    EmotionalProfile.Energy = 6;
    EmotionalProfile.Directness = 5;

    DialoguePatterns.Greetings = {
        TEXT("Shalom."),
        TEXT("Friend."),
        TEXT("Peace.")
    };

    DialoguePatterns.SignatureExpressions = {
        TEXT("Why was this perfume not sold?"),
        TEXT("What will you give me if I deliver him?"),
        TEXT("Greetings, Rabbi!")
    };

    PrimaryColor = FLinearColor(0.3f, 0.3f, 0.3f);
    VoicePitch = 1.0f;
}

void AJudasApostle::TriggerBetrayal()
{
    bHasBetrayed = true;
    // Update dialogue patterns after betrayal
    DialoguePatterns.SignatureExpressions = {
        TEXT("I have sinned by betraying innocent blood."),
        TEXT("What have I done?"),
        TEXT("...")
    };

    SetEmotion(EEmotionalState::Sorrowful);
}
