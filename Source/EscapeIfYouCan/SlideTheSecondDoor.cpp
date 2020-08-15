// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideTheSecondDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "MainCharacter.h"
#include "Grabber.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USlideTheSecondDoor::USlideTheSecondDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void USlideTheSecondDoor::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = GetOwner()->GetActorLocation();
	CloseLocation = CurrentLocation.Z;	
	FindAudioComponent();
}

void USlideTheSecondDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}


// Called every frame
void USlideTheSecondDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(MassOfActors() == 100)//Trigger->IsOverlappingActor(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		if(!Trigger)
		{
			return;
		}
		
		Trigger->GetOverlappingActors(Statues);

		for(auto StatueActor : Statues)
		{
			if(!SecondDoorStatue)
			{
				return;
			}
			if(Statues[0] == SecondDoorStatue)
			{
				SlideTheDoor(DeltaTime);
			}
		}
	}
	if(MassOfActors() != 100 || CLOSING3 == false)
	{
		CloseSlideTheDoor(DeltaTime);
	}
	// ...
}

float USlideTheSecondDoor::MassOfActors()
{
	float WeightOfStatues = 0.f;
	TArray<AActor*> Statues;

	Trigger->GetOverlappingActors(Statues);

	for(auto StatueActor : Statues)
	{
		WeightOfStatues += StatueActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return WeightOfStatues;
}

void USlideTheSecondDoor::SlideTheDoor(float Deltatime)
{
	AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UActorComponent* AC = SetBooleans->FindComponentByClass<UGrabber>();
	UGrabber* UC = Cast<UGrabber>(AC);

	if(DoOnceForClosed == true && released2 == true && UC->AddedImpulseOrNot == false)
	{
		if(DoOnce == false)
		{
			AudioComponent->Play();
			DoOnce = true;
			UGrabber* UC = Cast<UGrabber>(AC);
			UC->StopGrabing = true;
			UC->Release();
			Opened = GetWorld()->GetTimeSeconds();
		}
		if(GetWorld()->GetTimeSeconds() - Opened > Delay)
		{
			DoOnceForClosed = false;
			DoOnceAgain = false;
			UGrabber* UC = Cast<UGrabber>(AC);
			UC->StopGrabing = false;				
		}
		CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, GoUpZ , Deltatime, 2);
		GetOwner()->SetActorLocation(CurrentLocation);	
	}
}

void USlideTheSecondDoor::CloseSlideTheDoor(float Deltatime)
{
	if(DoOnceAgain == false)
	{	
		AudioComponent->Play();
		CLOSING3 = false;
		DoOnceAgain = true;
		Opened = GetWorld()->GetTimeSeconds();
	}
	if(GetWorld()->GetTimeSeconds() - Opened > Delay)
	{
		CLOSING3 = true;
		DoOnceForClosed = true;
		DoOnce = false;	
	}
	CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, CloseLocation, Deltatime, 2);
	GetOwner()->SetActorLocation(CurrentLocation);
}