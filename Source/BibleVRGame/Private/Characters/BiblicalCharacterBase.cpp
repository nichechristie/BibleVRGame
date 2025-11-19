// BiblicalCharacterBase.cpp
// Implementation of base biblical character class

#include "BiblicalCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

ABiblicalCharacterBase::ABiblicalCharacterBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create voice component
    VoiceComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("VoiceComponent"));
    VoiceComponent->SetupAttachment(RootComponent);
    VoiceComponent->bAutoActivate = false;

    // Default values
    CharacterName = TEXT("Unknown");
    Title = TEXT("");
    Description = TEXT("");
    Role = EBiblicalRole::Civilian;
    CurrentEmotion = EEmotionalState::Neutral;
    bIsFollowing = false;
    PlayerToFollow = nullptr;
}

void ABiblicalCharacterBase::BeginPlay()
{
    Super::BeginPlay();

    // Set voice sound if available
    if (VoiceSound)
    {
        VoiceComponent->SetSound(VoiceSound);
        VoiceComponent->SetPitchMultiplier(VoicePitch);
    }
}

void ABiblicalCharacterBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Follow player if enabled
    if (bIsFollowing && PlayerToFollow)
    {
        float Distance = FVector::Dist(GetActorLocation(), PlayerToFollow->GetActorLocation());

        if (Distance > 300.0f)
        {
            // Move towards player
            if (AAIController* AIController = Cast<AAIController>(GetController()))
            {
                AIController->MoveToActor(PlayerToFollow, 200.0f);
            }
        }
    }
}

FString ABiblicalCharacterBase::GetGreeting()
{
    if (DialoguePatterns.Greetings.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, DialoguePatterns.Greetings.Num() - 1);
        return DialoguePatterns.Greetings[Index];
    }
    return FString::Printf(TEXT("Greetings, I am %s."), *CharacterName);
}

FString ABiblicalCharacterBase::GetFarewell()
{
    if (DialoguePatterns.Farewells.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, DialoguePatterns.Farewells.Num() - 1);
        return DialoguePatterns.Farewells[Index];
    }
    return TEXT("Go in peace.");
}

void ABiblicalCharacterBase::SpeakLine(const FString& Line)
{
    // Play voice audio
    if (VoiceComponent && VoiceSound)
    {
        VoiceComponent->Play();
    }

    // Broadcast dialogue event
    OnDialogueStarted.Broadcast(this, Line);
}

void ABiblicalCharacterBase::SetEmotion(EEmotionalState NewEmotion)
{
    if (CurrentEmotion != NewEmotion)
    {
        CurrentEmotion = NewEmotion;
        OnEmotionChanged.Broadcast(NewEmotion);
    }
}

void ABiblicalCharacterBase::OnPlayerInteract(ACharacter* Player)
{
    // Speak greeting
    FString Greeting = GetGreeting();
    SpeakLine(Greeting);

    // Increase relationship
    ModifyRelationship(1);
}

void ABiblicalCharacterBase::ModifyRelationship(int32 Amount)
{
    RelationshipLevel = FMath::Clamp(RelationshipLevel + Amount, 0, 100);
}

void ABiblicalCharacterBase::FollowPlayer(ACharacter* Player)
{
    if (!bCanBeFollowed) return;

    PlayerToFollow = Player;
    bIsFollowing = true;
}

void ABiblicalCharacterBase::StopFollowing()
{
    PlayerToFollow = nullptr;
    bIsFollowing = false;

    // Stop AI movement
    if (AAIController* AIController = Cast<AAIController>(GetController()))
    {
        AIController->StopMovement();
    }
}
