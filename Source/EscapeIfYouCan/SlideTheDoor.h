// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "SlideTheDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEIFYOUCAN_API USlideTheDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlideTheDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void FindAudioComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SlideTheDoor(float Deltatime);
	void CloseSlideTheDoor(float Deltatime);
	float MassOfActors();

	bool released = false;

private:

	FVector CurrentLocation;
	TArray<AActor*> Statues;
	float CloseLocation;
	
	UPROPERTY(EditAnywhere)
		ATriggerVolume* Trigger = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* FirstDoorStatue;
	
	UPROPERTY(EditAnywhere)
		float GoUpZ;
	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;

	float Delay = 2.f;
	float Opened = 0.f;
	bool DoOnce = false;
	bool DoOnceForClosed = true;
	bool DoOnceAgain = true;
	bool CLOSING2 = false;
	
};
