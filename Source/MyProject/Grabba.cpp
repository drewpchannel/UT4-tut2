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
#include "Engine\Classes\PhysicsEngine\PhysicsHandleComponent.h"
#include "Engine\Classes\Components\PrimitiveComponent.h"

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
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(FindReachEnd());
	}
}

void UGrabba::FindPhysicsComponent()
{
	//if (PhysicsHandle) { return; }
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
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
	}
	else
	{
	}
}

void UGrabba::Grab()
{
	///if it returns null do we crash?
	auto HitResult = GetFirstPhysicsBodyInReach();
	ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if (ActorHit != nullptr)
	{
		ComponentToGrab = HitResult.GetComponent();
		if (!PhysicsHandle) {return;}
		PhysicsHandle->GrabComponent(
			ComponentToGrab, 
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabba::Release()
{
	if (!PhysicsHandle) {return;}
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabba::GetFirstPhysicsBodyInReach()
{	
	FVector PlayerViewPointLocation;
	DrawDebugLine(
		GetWorld(), 
		PlayerViewPointLocation, 
		FindReachEnd(), 
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
		FindReachEnd(), 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	AActor* ActorHit = TargetHit.GetActor();
	if (ActorHit) {
	}
	return TargetHit;
}

FVector UGrabba::FindReachEnd()
{	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRoatation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRoatation
	);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRoatation.Vector() * Reach;
	return LineTraceEnd;
}