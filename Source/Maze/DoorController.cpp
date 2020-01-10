// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorController.h"

// Sets default values
ADoorController::ADoorController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoorController::CheckOverlap()
{

}

// Called every frame
void ADoorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckOverlap();
}

