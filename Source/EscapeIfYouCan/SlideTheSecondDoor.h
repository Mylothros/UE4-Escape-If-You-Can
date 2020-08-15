// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "SlideTheSecondDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEIFYOUCAN_API USlideTheSecondDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlideTheSecondDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SlideTheDoor(float Deltatime);
	void CloseSlideTheDoor(float Deltatime);
	float MassOfActors();
	void FindAudioComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector CurrentLocation;
	TArray<AActor*> Statues;
	float CloseLocation;
	bool released2 = false;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* Trigger = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* SecondDoorStatue;
	
	UPROPERTY(EditAnywhere)
		float GoUpZ;
	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;

	float Delay = 2.f;
	float Opened = 0.f;
	bool DoOnce = false;
	bool DoOnceForClosed = true;
	bool DoOnceAgain = true;
	bool CLOSING3 = false;
		
};
