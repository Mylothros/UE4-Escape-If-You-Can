// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideTheLastDoor.h"
#include "MainCharacter.h"
#include "Grabber.h"

// Sets default values for this component's properties
USlideTheLastDoor::USlideTheLastDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlideTheLastDoor::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = GetOwner()->GetActorLocation();
	CloseLocation = CurrentLocation.Z;
	FindAudioComponent();
	
}

void USlideTheLastDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}

// Called every frame
void USlideTheLastDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USlideTheLastDoor::SlideTheDoor(float Deltatime)
{
	AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	UActorComponent* AC = SetBooleans->FindComponentByClass<UGrabber>();
	UGrabber* UC = Cast<UGrabber>(AC);

	if(DoOnceForClosed == true && released3 == true && UC->AddedImpulseOrNot == false)
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

void USlideTheLastDoor::CloseSlideTheDoor(float Deltatime)
{
	
	if(DoOnceAgain == false)
	{
		AudioComponent->Play();
		AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SetBooleans->CLOSING1 = false;
		DoOnceAgain = true;
		Opened = GetWorld()->GetTimeSeconds();
	}
	if(GetWorld()->GetTimeSeconds() - Opened > Delay)
	{
		AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SetBooleans->CLOSING1 = true;
		DoOnceForClosed = true;
		DoOnce = false;	
	}

	CurrentLocation.Z = FMath::FInterpTo(CurrentLocation.Z, CloseLocation, Deltatime, 2);
	GetOwner()->SetActorLocation(CurrentLocation);
}