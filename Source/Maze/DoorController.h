// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "DoorController.generated.h"

UCLASS()
class MAZE_API ADoorController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void CheckOverlap();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	ATriggerBox* Lock;

	UPROPERTY(EditAnywhere)
	AActor* Key;

};
