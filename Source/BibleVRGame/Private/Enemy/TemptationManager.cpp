// TemptationManager.cpp
// Implementation of the desert temptation sequence manager

#include "TemptationManager.h"
#include "Kismet/GameplayStatics.h"
#include "MediaPlayer.h"
#include "NiagaraFunctionLibrary.h"

ATemptationManager::ATemptationManager()
{
    PrimaryActorTick.bCanEverTick = false;

    CurrentSceneIndex = 0;
    bSequenceActive = false;
}

void ATemptationManager::BeginPlay()
{
    Super::BeginPlay();

    // Initialize the three biblical temptations
    InitializeBiblicalTemptations();
}

void ATemptationManager::InitializeBiblicalTemptations()
{
    TemptationScenes.Empty();

    // ============================================
    // FIRST TEMPTATION: Stones to Bread
    // ============================================
    FTemptationScene Scene1;
    Scene1.SceneId = TEXT("temptation_bread");
    Scene1.TemptationType = ETemptationType::StonesToBread;
    Scene1.DevilDialogue = {
        TEXT("You have fasted forty days and forty nights."),
        TEXT("Your body weakens. Your hunger consumes you."),
        TEXT("If you are the Son of God, command these stones to become bread."),
        TEXT("Why should you suffer when you hold such power?")
    };
    Scene1.JesusResponse = {
        TEXT("It is written:"),
        TEXT("'Man shall not live by bread alone,"),
        TEXT("but by every word that comes from the mouth of God.'")
    };
    Scene1.ScriptureReference = TEXT("Matthew 4:4 / Deuteronomy 8:3");
    Scene1.DesertLocation = FVector(0, 0, 0);
    TemptationScenes.Add(Scene1);

    // Choices for bread temptation
    TArray<FTemptationChoice> BreadChoices;

    FTemptationChoice Bread1;
    Bread1.ChoiceText = TEXT("Trust in God's provision");
    Bread1.bIsRighteous = true;
    Bread1.ResultText = TEXT("You resist the temptation. God's word sustains you.");
    Bread1.FaithChange = 10;
    BreadChoices.Add(Bread1);

    FTemptationChoice Bread2;
    Bread2.ChoiceText = TEXT("The hunger is too great...");
    Bread2.bIsRighteous = false;
    Bread2.ResultText = TEXT("You reach for the stone. Doubt fills your heart.");
    Bread2.FaithChange = -5;
    BreadChoices.Add(Bread2);

    TemptationChoices.Add(ETemptationType::StonesToBread, BreadChoices);

    // ============================================
    // SECOND TEMPTATION: Test God's Protection
    // ============================================
    FTemptationScene Scene2;
    Scene2.SceneId = TEXT("temptation_temple");
    Scene2.TemptationType = ETemptationType::TestGod;
    Scene2.DevilDialogue = {
        TEXT("He brings you to the holy city, to the pinnacle of the temple."),
        TEXT("If you are the Son of God, throw yourself down."),
        TEXT("For it is written: 'He will command his angels concerning you,'"),
        TEXT("'and they will lift you up in their hands,'"),
        TEXT("'so that you will not strike your foot against a stone.'")
    };
    Scene2.JesusResponse = {
        TEXT("It is also written:"),
        TEXT("'Do not put the Lord your God to the test.'")
    };
    Scene2.ScriptureReference = TEXT("Matthew 4:7 / Deuteronomy 6:16");
    Scene2.DesertLocation = FVector(1000, 0, 500);
    TemptationScenes.Add(Scene2);

    // Choices for temple temptation
    TArray<FTemptationChoice> TempleChoices;

    FTemptationChoice Temple1;
    Temple1.ChoiceText = TEXT("Faith does not require proof");
    Temple1.bIsRighteous = true;
    Temple1.ResultText = TEXT("You stand firm. True faith needs no test.");
    Temple1.FaithChange = 10;
    TempleChoices.Add(Temple1);

    FTemptationChoice Temple2;
    Temple2.ChoiceText = TEXT("Perhaps I should prove my faith...");
    Temple2.bIsRighteous = false;
    Temple2.ResultText = TEXT("You look down. Fear grips you.");
    Temple2.FaithChange = -5;
    TempleChoices.Add(Temple2);

    TemptationChoices.Add(ETemptationType::TestGod, TempleChoices);

    // ============================================
    // THIRD TEMPTATION: Worldly Power
    // ============================================
    FTemptationScene Scene3;
    Scene3.SceneId = TEXT("temptation_kingdoms");
    Scene3.TemptationType = ETemptationType::WorldlyPower;
    Scene3.DevilDialogue = {
        TEXT("He takes you to a very high mountain."),
        TEXT("He shows you all the kingdoms of the world and their splendor."),
        TEXT("All this I will give you..."),
        TEXT("...if you will bow down and worship me.")
    };
    Scene3.JesusResponse = {
        TEXT("Away from me, Satan!"),
        TEXT("For it is written:"),
        TEXT("'Worship the Lord your God, and serve him only.'")
    };
    Scene3.ScriptureReference = TEXT("Matthew 4:10 / Deuteronomy 6:13");
    Scene3.DesertLocation = FVector(2000, 0, 1000);
    TemptationScenes.Add(Scene3);

    // Choices for kingdoms temptation
    TArray<FTemptationChoice> KingdomChoices;

    FTemptationChoice Kingdom1;
    Kingdom1.ChoiceText = TEXT("Worship God alone");
    Kingdom1.bIsRighteous = true;
    Kingdom1.ResultText = TEXT("The devil flees. Angels come to attend you.");
    Kingdom1.FaithChange = 15;
    KingdomChoices.Add(Kingdom1);

    FTemptationChoice Kingdom2;
    Kingdom2.ChoiceText = TEXT("Such power could do much good...");
    Kingdom2.bIsRighteous = false;
    Kingdom2.ResultText = TEXT("You hesitate. The darkness draws closer.");
    Kingdom2.FaithChange = -10;
    KingdomChoices.Add(Kingdom2);

    TemptationChoices.Add(ETemptationType::WorldlyPower, KingdomChoices);
}

void ATemptationManager::StartTemptationScene(int32 SceneIndex)
{
    if (SceneIndex < 0 || SceneIndex >= TemptationScenes.Num())
    {
        return;
    }

    CurrentSceneIndex = SceneIndex;
    FTemptationScene& Scene = TemptationScenes[SceneIndex];

    // Set up desert environment
    SetupDesertEnvironment();

    // Play scene video if available
    if (CinematicPlayer && Scene.SceneVideo)
    {
        CinematicPlayer->OpenSource(Scene.SceneVideo);
        CinematicPlayer->Play();
    }

    // Broadcast scene started
    OnDesertSceneStarted.Broadcast(Scene);

    bSequenceActive = true;
}

void ATemptationManager::PlayFullDesertSequence()
{
    // Start from first temptation
    StartTemptationScene(0);
}

void ATemptationManager::SetupDesertEnvironment()
{
    // Play desert ambience
    if (DesertAmbience)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), DesertAmbience);
    }

    // Spawn wind/sand effect
    if (DesertWindEffect)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            DesertWindEffect,
            FVector::ZeroVector,
            FRotator::ZeroRotator,
            FVector(1.0f),
            true,
            true
        );
    }
}

void ATemptationManager::MakeChoice(ETemptationType Temptation, int32 ChoiceIndex)
{
    if (!TemptationChoices.Contains(Temptation))
    {
        return;
    }

    TArray<FTemptationChoice>& Choices = TemptationChoices[Temptation];
    if (ChoiceIndex < 0 || ChoiceIndex >= Choices.Num())
    {
        return;
    }

    FTemptationChoice& Choice = Choices[ChoiceIndex];

    // Broadcast player choice
    OnPlayerChoice.Broadcast(Choice, Choice.bIsRighteous);

    // Apply faith change through your game state/player stats system
    // Example: GetWorld()->GetGameState<ABibleVRGameState>()->AddFaith(Choice.FaithChange);

    // Advance to next scene
    AdvanceToNextScene();
}

TArray<FTemptationChoice> ATemptationManager::GetChoicesForTemptation(ETemptationType Temptation)
{
    if (TemptationChoices.Contains(Temptation))
    {
        return TemptationChoices[Temptation];
    }
    return TArray<FTemptationChoice>();
}

void ATemptationManager::AdvanceToNextScene()
{
    CurrentSceneIndex++;

    if (CurrentSceneIndex < TemptationScenes.Num())
    {
        // Play next scene
        StartTemptationScene(CurrentSceneIndex);
    }
    else
    {
        // All temptations complete
        CompleteSequence();
    }
}

void ATemptationManager::CompleteSequence()
{
    bSequenceActive = false;
    CurrentSceneIndex = 0;

    // Stop any playing media
    if (CinematicPlayer)
    {
        CinematicPlayer->Close();
    }

    // Broadcast completion
    OnAllTemptationsComplete.Broadcast();
}

void ATemptationManager::SkipCurrentScene()
{
    if (!bSequenceActive) return;

    // Stop current video
    if (CinematicPlayer)
    {
        CinematicPlayer->Close();
    }

    // Advance to next
    AdvanceToNextScene();
}
