// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabba.h"
#include "Engine\Classes\GameFramework\PlayerController.h"
#include "Core\Public\Math\Color.h"
#include "Engine\Classes\Components\InputComponent.h"
#include "Engine\World.h"
#include "Engine\Classes\GameFramework\Actor.h"
#include "Engine\Classes\Kismet\GameplayStatics.h"
#include "Engine\Public\DrawDebugHelpers.h"
#include "Engine\Public\CollisionQueryParams.h"

#define OUT

// Sets default values for this component's properties
UGrabba::UGrabba()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabba::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsComponent();
	FindPhysicsInput();
	SetupInputComponent();
}


// Called every frame
void UGrabba::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabba::FindPhysicsComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) 
	{

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("physics handle not found on: %s"), *GetOwner()->GetName());
	}
}

void UGrabba::FindPhysicsInput()
{

}

void UGrabba::SetupInputComponent()
{
	PhysicsInput = GetOwner()->FindComponentByClass<UInputComponent>();
	if (PhysicsInput)
	{
		PhysicsInput->BindAction("Grab", IE_Pressed, this, &UGrabba::Grab);
		PhysicsInput->BindAction("Grab", IE_Released, this, &UGrabba::Release);
		UE_LOG(LogTemp, Warning, TEXT("physics input found on: %s"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("physics input not found on: %s"), *GetOwner()->GetName());
	}
}

void UGrabba::Grab()
{
	GetFirstPhysicsBodyInReach();
}

void UGrabba::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("grab released"));
}

const FHitResult UGrabba::GetFirstPhysicsBodyInReach()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRoatation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRoatation
	);
	// UE_LOG(LogTemp, Warning, TEXT("ploc: %s, prot: %s"), 
	// 	*PlayerViewPointLocation.ToString(),
	// 	*PlayerViewPointRoatation.ToString()
	// );
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRoatation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(), 
		PlayerViewPointLocation, 
		LineTraceEnd, 
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	FHitResult TargetHit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT TargetHit, 
		PlayerViewPointLocation, 
		LineTraceEnd, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	AActor* ActorHit = TargetHit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("works: %s"), *ActorHit->GetName());
	}
	return TargetHit;
}