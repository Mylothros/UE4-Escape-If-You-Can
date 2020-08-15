// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideTheDoor.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "MainCharacter.h"
#include "Grabber.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USlideTheDoor::USlideTheDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlideTheDoor::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = GetOwner()->GetActorLocation();
	CloseLocation = CurrentLocation.Z;
	FindAudioComponent();
	
}

void USlideTheDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}

// Called every frame
void USlideTheDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(MassOfActors() == 110)//Trigger->IsOverlappingActor(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{	
		if(!Trigger)
		{
			return;
		}
		
		Trigger->GetOverlappingActors(Statues);

		for(auto StatueActor : Statues)
		{
			if(!FirstDoorStatue)
			{
				return;
			}
			if(Statues[0] == FirstDoorStatue)
			{	
				SlideTheDoor(DeltaTime);
			}
		}
	}
	if(MassOfActors() != 110 || CLOSING2 == false)
	{
		CloseSlideTheDoor(DeltaTime);
	}
}

float USlideTheDoor::MassOfActors()
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

void USlideTheDoor::SlideTheDoor(float Deltatime)
{
	AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UActorComponent* AC = SetBooleans->FindComponentByClass<UGrabber>();
	UGrabber* UC = Cast<UGrabber>(AC);

	if(DoOnceForClosed == true && released == true && UC->AddedImpulseOrNot == false)
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

void USlideTheDoor::CloseSlideTheDoor(float Deltatime)
{
	if(DoOnceAgain == false)
	{	
		AudioComponent->Play();
		CLOSING2 = false;
		DoOnceAgain = true;
		Opened = GetWorld()->GetTimeSeconds();
	}
	if(GetWorld()->GetTimeSeconds() - Opened > Delay)
	{
		CLOSING2 = true;
		DoOnceForClosed = true;
		DoOnce = false;	
	}
	CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, CloseLocation, Deltatime, 2);
	GetOwner()->SetActorLocation(CurrentLocation);
}
