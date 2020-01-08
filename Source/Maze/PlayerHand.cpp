// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHand.h"

// Sets default values for this component's properties
UPlayerHand::UPlayerHand()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerHand::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerHand::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Testing linetrace
	LineTrace();
}

FHitResult UPlayerHand::LineTrace()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetOwner()->GetActorEyesViewPoint(PlayerLocation, PlayerRotation);

	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;
	FHitResult Hit;

	FCollisionQueryParams Trace(FName(TEXT("")), false, GetOwner());
	FCollisionResponseContainer Container;

	
	GetWorld()->LineTraceSingleByObjectType(Hit, PlayerLocation, LineTraceEnd, ECC_PhysicsBody, Trace);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		FVector HandLocation(50.0f, 50.0f, 50.0f);

		HandLocation += PlayerLocation;

		UE_LOG(LogTemp, Warning, TEXT("The Following Actor Was Hit: %s"), *(ActorHit->GetName()));
		if (true)
		{
			ActorHit->SetOwner(GetOwner());
			ActorHit->SetActorRelativeLocation(HandLocation, false, NULL, ETeleportType(0));
		}
	}

	return Hit;
}
