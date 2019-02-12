// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Crab.generated.h"

UCLASS()
class CRABGAME_API ACrab : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACrab();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* MovingAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;
	
	//Input functions
	void MoveX( float AxisValue );
	void StartMoving();
	void StopMoving();

	//Input variables
	FVector CurrentVelocity;

};
