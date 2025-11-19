// DevilCharacter.cpp
// Implementation of Devil enemy with temptation and desert sequence mechanics

#include "DevilCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Engine/LevelStreaming.h"

ADevilCharacter::ADevilCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create interaction sphere
    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetupAttachment(RootComponent);
    InteractionSphere->SetSphereRadius(200.0f);
    InteractionSphere->SetCollisionProfileName(TEXT("Trigger"));
    InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ADevilCharacter::OnInteractionSphereOverlap);

    // Create detection sphere
    DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
    DetectionSphere->SetupAttachment(RootComponent);
    DetectionSphere->SetSphereRadius(2000.0f);
    DetectionSphere->SetCollisionProfileName(TEXT("Trigger"));

    // Create audio component
    WhisperAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("WhisperAudio"));
    WhisperAudio->SetupAttachment(RootComponent);
    WhisperAudio->bAutoActivate = false;

    // Create VFX components
    TransformationVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TransformationVFX"));
    TransformationVFX->SetupAttachment(RootComponent);
    TransformationVFX->bAutoActivate = false;

    AuraVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("AuraVFX"));
    AuraVFX->SetupAttachment(RootComponent);
    AuraVFX->bAutoActivate = false;

    // Default settings
    CurrentForm = EDevilForm::Serpent;
    MinTimeBetweenAppearances = 120.0f;  // 2 minutes
    MaxTimeBetweenAppearances = 300.0f;  // 5 minutes
    AppearanceChance = 0.7f;
    VisibilityDuration = 30.0f;
    SpawnDistanceFromPlayer = 500.0f;
    DesertSequenceDuration = 0.0f;  // Auto-detect from video

    bIsVisible = false;
    bDesertSequenceActive = false;
    PlayerCharacter = nullptr;

    // Initialize dialogue
    InitializeDialogue();
}

void ADevilCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Get player reference
    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    // Start invisible
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    // Schedule first appearance
    ScheduleNextAppearance();
}

void ADevilCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Face player when visible
    if (bIsVisible && PlayerCharacter)
    {
        FVector Direction = PlayerCharacter->GetActorLocation() - GetActorLocation();
        Direction.Z = 0;
        if (!Direction.IsNearlyZero())
        {
            FRotator TargetRotation = Direction.Rotation();
            FRotator CurrentRotation = GetActorRotation();
            FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 3.0f);
            SetActorRotation(NewRotation);
        }
    }
}

void ADevilCharacter::InitializeDialogue()
{
    // Stones to Bread temptation
    TemptationDialogue.Add(ETemptationType::StonesToBread, {
        TEXT("You hunger... I can feel it. Why suffer when you have such power?"),
        TEXT("Command these stones to become bread. Satisfy yourself."),
        TEXT("Your Father won't feed you? Then feed yourself. It is your right."),
        TEXT("One word, and your suffering ends. Speak it.")
    });

    // Test God's Protection
    TemptationDialogue.Add(ETemptationType::TestGod, {
        TEXT("If you are truly His child, He will not let you fall."),
        TEXT("Throw yourself down. His angels will catch you... won't they?"),
        TEXT("Prove your faith. Prove His love. Test Him."),
        TEXT("Or do you doubt His promises?")
    });

    // Worldly Power
    TemptationDialogue.Add(ETemptationType::WorldlyPower, {
        TEXT("All these kingdoms... all this glory... it can be yours."),
        TEXT("I offer you dominion over all you see. One simple bow."),
        TEXT("Think of the good you could do with such power."),
        TEXT("Worship me, and the world is yours to save.")
    });

    // Material Wealth
    TemptationDialogue.Add(ETemptationType::MaterialWealth, {
        TEXT("Gold, silver, precious stones... what is faith without comfort?"),
        TEXT("The righteous deserve reward. Take what you are owed."),
        TEXT("Poverty is not virtue. Abundance is blessing."),
        TEXT("Let me show you treasures beyond imagination.")
    });

    // Pride
    TemptationDialogue.Add(ETemptationType::Pride, {
        TEXT("You are special. Chosen. Better than the others."),
        TEXT("Why hide your glory? Let them see your magnificence."),
        TEXT("You deserve recognition. Adoration. Worship."),
        TEXT("Humble is for the weak. You are strong.")
    });

    // Doubt
    TemptationDialogue.Add(ETemptationType::Doubt, {
        TEXT("Are you certain He hears your prayers?"),
        TEXT("So much suffering... where is your loving God?"),
        TEXT("Perhaps you imagined it all. Perhaps you are alone."),
        TEXT("Faith... or foolishness? How can you be sure?")
    });

    // Whisper lines
    WhisperLines = {
        TEXT("Such potential... wasted on righteousness."),
        TEXT("I know what you truly desire."),
        TEXT("Your secrets are safe with me."),
        TEXT("Even the faithful falter."),
        TEXT("One small compromise... who would know?"),
        TEXT("You grow weary of this path."),
        TEXT("I can ease your burden."),
        TEXT("Listen closely...")
    };
}

void ADevilCharacter::ScheduleNextAppearance()
{
    if (GetWorld())
    {
        float RandomDelay = FMath::RandRange(MinTimeBetweenAppearances, MaxTimeBetweenAppearances);
        GetWorld()->GetTimerManager().SetTimer(
            AppearanceTimerHandle,
            this,
            &ADevilCharacter::OnAppearanceTimerFired,
            RandomDelay,
            false
        );
    }
}

void ADevilCharacter::OnAppearanceTimerFired()
{
    // Check appearance chance
    if (FMath::FRand() <= AppearanceChance)
    {
        // Don't appear during desert sequence
        if (!bDesertSequenceActive)
        {
            AppearNearPlayer();
        }
    }

    // Schedule next appearance
    ScheduleNextAppearance();
}

void ADevilCharacter::AppearNearPlayer()
{
    if (!PlayerCharacter) return;

    // Get spawn location
    FVector SpawnLocation = GetSpawnLocationNearPlayer();
    SetActorLocation(SpawnLocation);

    // Choose random form (not true form for initial appearance)
    TArray<EDevilForm> DisguiseForms = {
        EDevilForm::Serpent,
        EDevilForm::Merchant,
        EDevilForm::Scholar,
        EDevilForm::Beggar,
        EDevilForm::Angel,
        EDevilForm::Shadow
    };
    int32 RandomIndex = FMath::RandRange(0, DisguiseForms.Num() - 1);
    ChangeForm(DisguiseForms[RandomIndex]);

    // Choose random temptation
    TArray<ETemptationType> Temptations = {
        ETemptationType::StonesToBread,
        ETemptationType::TestGod,
        ETemptationType::WorldlyPower,
        ETemptationType::MaterialWealth,
        ETemptationType::Pride,
        ETemptationType::Doubt
    };
    CurrentTemptation = Temptations[FMath::RandRange(0, Temptations.Num() - 1)];

    // Make visible
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    bIsVisible = true;

    // Play appear sound and effects
    if (AppearSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), AppearSound, GetActorLocation());
    }

    // Start aura VFX
    if (AuraVFX)
    {
        AuraVFX->Activate(true);
    }

    // Whisper to attract attention
    WhisperToPlayer();

    // Set visibility timer
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(
            VisibilityTimerHandle,
            this,
            &ADevilCharacter::OnVisibilityTimerFired,
            VisibilityDuration,
            false
        );
    }
}

FVector ADevilCharacter::GetSpawnLocationNearPlayer()
{
    if (!PlayerCharacter) return GetActorLocation();

    // Get player forward vector and randomize around it
    FVector PlayerLocation = PlayerCharacter->GetActorLocation();
    FVector PlayerForward = PlayerCharacter->GetActorForwardVector();

    // Random angle offset (-90 to +90 degrees, favoring in front)
    float RandomAngle = FMath::RandRange(-90.0f, 90.0f);
    FVector SpawnDirection = PlayerForward.RotateAngleAxis(RandomAngle, FVector::UpVector);

    // Calculate spawn position
    FVector SpawnLocation = PlayerLocation + (SpawnDirection * SpawnDistanceFromPlayer);

    // Trace to find ground
    FHitResult HitResult;
    FVector TraceStart = SpawnLocation + FVector(0, 0, 500);
    FVector TraceEnd = SpawnLocation - FVector(0, 0, 1000);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility))
    {
        SpawnLocation = HitResult.Location;
    }

    return SpawnLocation;
}

void ADevilCharacter::OnVisibilityTimerFired()
{
    // Player didn't interact, disappear
    Disappear();
}

void ADevilCharacter::Disappear()
{
    if (!bIsVisible) return;

    // Cancel visibility timer
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(VisibilityTimerHandle);
    }

    // Play disappear sound
    if (DisappearSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), DisappearSound, GetActorLocation());
    }

    // Deactivate VFX
    if (AuraVFX)
    {
        AuraVFX->Deactivate();
    }

    // Hide
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    bIsVisible = false;
}

void ADevilCharacter::ChangeForm(EDevilForm NewForm)
{
    if (CurrentForm == NewForm) return;

    EDevilForm OldForm = CurrentForm;
    CurrentForm = NewForm;

    // Play transformation VFX
    if (TransformationVFX)
    {
        TransformationVFX->Activate(true);
    }

    // Play transform sound
    if (TransformSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), TransformSound, GetActorLocation());
    }

    // Change mesh if available
    if (FormMeshes.Contains(NewForm) && FormMeshes[NewForm])
    {
        GetMesh()->SetSkeletalMesh(FormMeshes[NewForm]);
    }

    // Change animation blueprint if available
    if (FormAnimations.Contains(NewForm) && FormAnimations[NewForm])
    {
        GetMesh()->SetAnimInstanceClass(FormAnimations[NewForm]);
    }

    // Broadcast form change event
    OnDevilFormChanged.Broadcast(NewForm);
}

void ADevilCharacter::TransformToRandomForm()
{
    // Get all forms except current
    TArray<EDevilForm> AvailableForms;
    for (int32 i = 0; i < static_cast<int32>(EDevilForm::TrueForm); i++)
    {
        EDevilForm Form = static_cast<EDevilForm>(i);
        if (Form != CurrentForm)
        {
            AvailableForms.Add(Form);
        }
    }

    if (AvailableForms.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, AvailableForms.Num() - 1);
        ChangeForm(AvailableForms[RandomIndex]);
    }
}

void ADevilCharacter::RevealTrueForm()
{
    ChangeForm(EDevilForm::TrueForm);
}

void ADevilCharacter::OnInteractionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if player entered
    if (OtherActor == PlayerCharacter && bIsVisible)
    {
        // Trigger the temptation sequence
        TriggerTemptation(CurrentTemptation);
    }
}

void ADevilCharacter::TriggerTemptation(ETemptationType Temptation)
{
    CurrentTemptation = Temptation;

    // Cancel visibility timer
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(VisibilityTimerHandle);
    }

    // Broadcast temptation event
    OnTemptationTriggered.Broadcast(Temptation, this);

    // Play temptation music
    if (TemptationMusic)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), TemptationMusic);
    }

    // Start desert sequence
    StartDesertSequence();
}

void ADevilCharacter::StartDesertSequence()
{
    if (bDesertSequenceActive || !PlayerCharacter) return;

    bDesertSequenceActive = true;

    // Save player's current transform
    SavedPlayerTransform = PlayerCharacter->GetActorTransform();

    // Disable player input during sequence
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PC->SetIgnoreMoveInput(true);
        PC->SetIgnoreLookInput(true);
    }

    // Fade to black (you'd call this from your game mode or HUD)
    // UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(0.0f, 1.0f, 1.0f, FLinearColor::Black, false, true);

    // Stream in desert level if set
    if (!DesertLevel.IsNull())
    {
        FLatentActionInfo LatentInfo;
        UGameplayStatics::LoadStreamLevel(GetWorld(), DesertLevel.GetAssetName(), true, true, LatentInfo);
    }

    // Start video playback
    if (DesertVideoPlayer && DesertVideoSource)
    {
        DesertVideoPlayer->OpenSource(DesertVideoSource);
        DesertVideoPlayer->Play();

        // Get video duration or use set duration
        float Duration = DesertSequenceDuration;
        if (Duration <= 0.0f)
        {
            // Default to 3 minutes if not set
            Duration = 180.0f;
        }

        // Set timer to end sequence
        if (GetWorld())
        {
            GetWorld()->GetTimerManager().SetTimer(
                DesertSequenceTimerHandle,
                this,
                &ADevilCharacter::EndDesertSequence,
                Duration,
                false
            );
        }
    }
    else
    {
        // No video, end after a short delay
        if (GetWorld())
        {
            GetWorld()->GetTimerManager().SetTimer(
                DesertSequenceTimerHandle,
                this,
                &ADevilCharacter::EndDesertSequence,
                10.0f,
                false
            );
        }
    }
}

void ADevilCharacter::EndDesertSequence()
{
    if (!bDesertSequenceActive) return;

    // Stop video
    if (DesertVideoPlayer)
    {
        DesertVideoPlayer->Close();
    }

    // Unload desert level
    if (!DesertLevel.IsNull())
    {
        FLatentActionInfo LatentInfo;
        UGameplayStatics::UnloadStreamLevel(GetWorld(), DesertLevel.GetAssetName(), LatentInfo, false);
    }

    // Restore player transform
    if (PlayerCharacter)
    {
        PlayerCharacter->SetActorTransform(SavedPlayerTransform);
    }

    // Re-enable player input
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        PC->SetIgnoreMoveInput(false);
        PC->SetIgnoreLookInput(false);
    }

    // Fade from black
    // UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraFade(1.0f, 0.0f, 1.0f, FLinearColor::Black, false, false);

    bDesertSequenceActive = false;

    // Transform devil to different form after player returns
    TransformToRandomForm();

    // Disappear
    Disappear();

    // Broadcast completion
    OnDesertSequenceComplete.Broadcast();
}

FString ADevilCharacter::GetTemptationDialogue()
{
    if (TemptationDialogue.Contains(CurrentTemptation))
    {
        TArray<FString>& Lines = TemptationDialogue[CurrentTemptation];
        if (Lines.Num() > 0)
        {
            int32 RandomIndex = FMath::RandRange(0, Lines.Num() - 1);
            return Lines[RandomIndex];
        }
    }
    return TEXT("...");
}

void ADevilCharacter::WhisperToPlayer()
{
    if (WhisperLines.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, WhisperLines.Num() - 1);
        FString WhisperText = WhisperLines[RandomIndex];

        // Play whisper audio with the selected voice
        if (WhisperAudio && FormVoices.Contains(CurrentForm))
        {
            WhisperAudio->SetSound(FormVoices[CurrentForm]);
            WhisperAudio->Play();
        }

        // You can display this text via your dialogue system
        // For example, broadcast an event or call your dialogue manager
    }
}
