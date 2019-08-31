// Fill out your copyright notice in the Description page of Project Settings.


#include "RepoPos.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
URepoPos::URepoPos()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URepoPos::BeginPlay()
{
	Super::BeginPlay();
	FString ObjectName = GetOwner()->GetName();

	//FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	// ...
	
}


// Called every frame
void URepoPos::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

