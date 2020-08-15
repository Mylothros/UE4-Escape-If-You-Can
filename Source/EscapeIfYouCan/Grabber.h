// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/HUD.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEIFYOUCAN_API UGrabber : public UActorComponent{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
    	TSubclassOf<UUserWidget> ControllsWidgetGrabDefault;
	UPROPERTY(EditAnywhere,  BlueprintReadOnly, Category = "UMG")
    	UUserWidget* ControllsWidgetGrab;
	
	bool DoOnceGrabWidget = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void findPhysicsHandle();
	void DrawTheLine();
	void SetupInputComponent();
	void Grab();
	void AddImpulse();
	void edgedetection();
	void setReleasedValuesToFalseToOpenDoor();
	void setReleasedValuesToTrueToOpenDoor();
	void GrabWidget();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Release();
	FHitResult ThrowObject;
	FHitResult Grabit;
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	FVector EndOfLine;
	bool first;
	bool second;
	bool third;
	bool forth;
	bool fifth;
	bool persistenoutline = true;
	bool StopGrabing = false;
	bool AddedImpulseOrNot = false;
	float dist = 290;

	private:

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* Input = nullptr;
	
	UPROPERTY(EditAnywhere)
		AActor* firststatue;
	UPROPERTY(EditAnywhere)
		AActor* secondstatue;
	UPROPERTY(EditAnywhere)
		AActor* firstbone;
	UPROPERTY(EditAnywhere)
		AActor* secondbone;
	UPROPERTY(EditAnywhere)
		AActor* thirdbone;
	UPROPERTY(EditAnywhere)
		AActor* released;
	UPROPERTY(EditAnywhere)
		AActor* released2;
	UPROPERTY(EditAnywhere)
		AActor* released3;		
};
