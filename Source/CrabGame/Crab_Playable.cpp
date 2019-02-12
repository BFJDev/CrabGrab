// Fill out your copyright notice in the Description page of Project Settings.

#include "Crab_Playable.h"
#include "Coin.h"
#include "CrabGameGameMode.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Classes/Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

/** Copied over code from base class, refined it to fit new Crab playable character
*/
ACrab_Playable::ACrab_Playable()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//initialize score to 0
	Score = 0;
	
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(40.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	/**
	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	//SideViewCameraComponent->SetupAttachment(RootComponent);
	SideViewCameraComponent->RelativeLocation = FVector(0.0f, CameraLength, 0.0f);
	SideViewCameraComponent->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;        */
	GetCharacterMovement()->bOrientRotationToMovement = false;
	
	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;
}

void ACrab_Playable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ACrabGameGameMode* gm = (ACrabGameGameMode*)GetWorld()->GetAuthGameMode();
	if (!(gm->GameOver))
	{
		//pulled this code from the BatteryCollector tutorial project

		TArray<AActor *> CollectedActors;
		GetCapsuleComponent()->GetOverlappingActors(CollectedActors);
		//For each collected actor
		for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
		{
			//Cast the actor to a pickup
			ACoin* const TestCoin = Cast<ACoin>(CollectedActors[iCollected]);
			//If cast is succcessful and pickup is VALID && ACTIVE
			if (TestCoin && !TestCoin->IsPendingKill())
			{
				Score += 100;

				TestCoin->Destroy();
			}
		}
	}
	

	if (CurrentVelocity.Y != 0 )
	{
		GetSprite()->SetFlipbook(MovingAnimation);
	}
	else
	{
		GetSprite()->SetFlipbook(IdleAnimation);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

// Called to bind functionality to input
void ACrab_Playable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Crawl" key is pressed or released.
	//InputComponent->BindAction("Crawl", IE_Pressed, this, &ACrab_Playable::StartMoving);
	//InputComponent->BindAction("Crawl", IE_Released, this, &ACrab_Playable::StopMoving);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &ACrab_Playable::MoveX);

}

void ACrab_Playable::MoveX(float AxisValue)
{
	// Move at 10 units per second right or left
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 1.0f;
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), AxisValue);
}

void ACrab_Playable::StartMoving()
{
	GetSprite()->SetFlipbook(MovingAnimation);
}

void ACrab_Playable::StopMoving()
{
	GetSprite()->SetFlipbook(IdleAnimation);
}

