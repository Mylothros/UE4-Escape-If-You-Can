// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MainCharacter.generated.h"

UCLASS()
class ESCAPEIFYOUCAN_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Camera_Mc")
		UCameraComponent* Camera_Mc;

	UPROPERTY(EditAnywhere, Category = "Physic")
		UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(EditAnywhere)
		AActor* LastDoor;

public:
	// Sets default values for this character's properties
	AMainCharacter();

	void MoveForward(float Val);
	void MoveRight(float Val);
	void CheckForLastDoor(float DeltaTime);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool FirstBone = false;
	bool SecondBone = false;
	bool ThirdBone = false;
	bool CLOSING1 = false;
};
