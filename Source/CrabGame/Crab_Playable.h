// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Crab_Playable.generated.h"

/**
 * 
 */
UCLASS()
class CRABGAME_API ACrab_Playable : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	virtual void Tick(float DeltaSeconds) override;
protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* MovingAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float CameraLength = 50;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Score)
	int Score;
	
public:
	ACrab_Playable();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Input functions
	void MoveX(float AxisValue);
	void StartMoving();
	void StopMoving();

	//Input variables
	FVector CurrentVelocity;


};
