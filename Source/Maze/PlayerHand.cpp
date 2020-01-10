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
	InitializeComponents();
	// ...
	
}

// Called every frame
void UPlayerHand::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Testing linetrace
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd());
	}

}

FHitResult UPlayerHand::LineTrace()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetOwner()->GetActorEyesViewPoint(PlayerLocation, PlayerRotation);

	FHitResult Hit;
	FCollisionQueryParams Trace(FName(TEXT("")), false, GetOwner());
	
	GetWorld()->LineTraceSingleByObjectType(Hit, PlayerLocation, LineTraceEnd(), ECC_PhysicsBody, Trace);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Following Actor Was Hit: %s"), *(ActorHit->GetName()));
	}
	return Hit;
}

void UPlayerHand::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab is Activated"));
	auto HitResult = LineTrace();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("ActorIsHit"));
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ActorHit->GetActorLocation(),
			true
		);
	}
	
}

void UPlayerHand::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab is Released"));
	PhysicsHandle->ReleaseComponent();
}

void UPlayerHand::InitializeComponents()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Interact", IE_Pressed, this, &UPlayerHand::Grab);
		InputComponent->BindAction("Interact", IE_Released, this, &UPlayerHand::Release);
	}

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s PH Is Initialized"), *(PhysicsHandle->GetName()));
	}

}

FVector UPlayerHand::LineTraceEnd()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	FVector LineTraceEnd;
	GetOwner()->GetActorEyesViewPoint(PlayerLocation, PlayerRotation);

	UE_LOG(LogTemp, Warning, TEXT("The LineTraceEnd repeates: %s"), *LineTraceEnd.ToString());

	return LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;
	
}