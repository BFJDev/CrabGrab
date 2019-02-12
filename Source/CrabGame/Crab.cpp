// Fill out your copyright notice in the Description page of Project Settings.

#include "Crab.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"


// Sets default values
ACrab::ACrab()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

	//GetSprite()->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void ACrab::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACrab::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Crawl" key is pressed or released.
	InputComponent->BindAction("Crawl", IE_Pressed, this, &ACrab::StartMoving);
	InputComponent->BindAction("Crawl", IE_Released, this, &ACrab::StopMoving);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &ACrab::MoveX);

}

void ACrab::MoveX(float AxisValue)
{
	// Move at 10 units per second right or left
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 10.0f;
}

void ACrab::StartMoving()
{
	//GetSprite()->SetFlipbook(MovingAnimation);
}

void ACrab::StopMoving()
{
	//GetSprite()->SetFlipbook(IdleAnimation);
}