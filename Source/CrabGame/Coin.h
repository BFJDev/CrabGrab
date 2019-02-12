// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class CRABGAME_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Min Fall Speed
	//UPROPERTY lets us play with this in UE4 editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float FallSpeedRangeLow;
	//Max Fall Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float FallSpeedRangeHigh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class USphereComponent* CollisionComponent;

	//Sprite to use upon item spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		class UPaperSprite* Sprite;
		//class UPaperSpriteComponent* CoinSprite;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**Toggles whether or not spawn volume spawns pickups */
	UFUNCTION(BlueprintCallable, Category = "Sprite")
		void SetSprite(UPaperSprite* NewSprite);

	/**Toggles whether or not spawn volume spawns pickups */
	UFUNCTION(BlueprintCallable, Category = "Sprite")
		void SetSprite2(UPaperSprite* NewSprite);

private:

	float FallSpeed;

	class UPaperSpriteComponent* CoinSprite;

};
