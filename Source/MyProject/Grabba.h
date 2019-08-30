// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabba.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UGrabba : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabba();
	bool LineTracer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float Reach = 60.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* PhysicsInput = nullptr;

	void Grab();
	void Release();
	void FindPhysicsComponent();
	void FindPhysicsInput();
	void SetupInputComponent();
	const FHitResult GetFirstPhysicsBodyInReach();
	FVector FindReachEnd();
	UPhysicsHandleComponent *HandlerComp;
	UPrimitiveComponent *ComponentToGrab;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
