// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "SlideTheDoor.h"
#include "SlideTheSecondDoor.h"
#include "MainCharacter.h"
#include "Blueprint/UserWidget.h"
#include "SlideTheLastDoor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	findPhysicsHandle();
	SetupInputComponent();

}

void UGrabber::findPhysicsHandle()
{
	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if(!PhysicsHandle)
	{

	}	
}

void UGrabber::SetupInputComponent()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	if(Input)
	{
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
		Input->BindAction("AddImpulse", IE_Pressed, this, &UGrabber::AddImpulse);
	}
}

void UGrabber::Grab()
{
	AddedImpulseOrNot = false;
	ThrowObject = Grabit;
	dist = Grabit.Distance;
	FVector EndOfLineForGrab = ViewPointLoc + ViewPointRot.Vector() * dist;	
	
	UPrimitiveComponent* ComponentToGrab = Grabit.GetComponent();

	if(Grabit.GetActor() && StopGrabing == false)
	{	
		setReleasedValuesToFalseToOpenDoor();

		if(!PhysicsHandle)
		{
			return;
		}
		if(Grabit.GetActor() == firststatue || Grabit.GetActor() == secondstatue || Grabit.GetActor() == firstbone || Grabit.GetActor() == secondbone || Grabit.GetActor() == thirdbone)
		{
			persistenoutline = false;
			PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, EndOfLineForGrab, ViewPointRot);
		}	
	}
}

void UGrabber::Release()
{
	
	setReleasedValuesToTrueToOpenDoor();
	persistenoutline = true;

	if(!PhysicsHandle)
	{
		return;
	}
	
	PhysicsHandle->ReleaseComponent();
	
	dist = 290;
}

void UGrabber::AddImpulse()
{
	AddedImpulseOrNot = true;

	if(persistenoutline == false)
	{	
		Release();

		AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(ThrowObject.GetActor()->GetRootComponent());
		
		if(RootComp)
		{
			RootComp->AddImpulse(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorForwardVector() * 100000.f);
		}
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawTheLine();

	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocationAndRotation(EndOfLine, ViewPointRot);
	}
}

void UGrabber::setReleasedValuesToFalseToOpenDoor()
{
	UActorComponent* AC1 = released->FindComponentByClass<USlideTheDoor>();
	USlideTheDoor* UC = Cast<USlideTheDoor>(AC1);
	UC->released = false;

	UActorComponent* AC2 = released2->FindComponentByClass<USlideTheSecondDoor>();
	USlideTheSecondDoor* UC2 = Cast<USlideTheSecondDoor>(AC2);
	UC2->released2 = false;
	
	UActorComponent* AC3 = released3->FindComponentByClass<USlideTheLastDoor>();
	USlideTheLastDoor* UC3 = Cast<USlideTheLastDoor>(AC3);
	UC3->released3 = false;
}

void UGrabber::setReleasedValuesToTrueToOpenDoor()
{
	UActorComponent* AC1 = released->FindComponentByClass<USlideTheDoor>();
	USlideTheDoor* UC = Cast<USlideTheDoor>(AC1);
	UC->released = true;

	UActorComponent* AC2 = released2->FindComponentByClass<USlideTheSecondDoor>();
	USlideTheSecondDoor* UC2 = Cast<USlideTheSecondDoor>(AC2);
	UC2->released2 = true;
	
	UActorComponent* AC3 = released3->FindComponentByClass<USlideTheLastDoor>();
	USlideTheLastDoor* UC3 = Cast<USlideTheLastDoor>(AC3);
	UC3->released3 = true;
}

void UGrabber::DrawTheLine()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewPointLoc, ViewPointRot);

	EndOfLine = ViewPointLoc + ViewPointRot.Vector() * dist;	
	//DrawDebugLine(GetWorld(), ViewPointLoc, EndOfLine, FColor(0, 255, 0), false, 0.f, 0.f, 4.f);
	FHitResult Hit;
	FCollisionQueryParams Params(FName(TEXT("")), false, GetOwner());

	if(persistenoutline == true)
	{
		GetWorld()->LineTraceSingleByObjectType(Hit, ViewPointLoc, EndOfLine, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), Params);
	}
	
	Grabit = Hit;
	edgedetection();
}

void UGrabber::edgedetection()
{
	if(!firststatue)
	{
		return;
	}

	if(!secondstatue)
	{
		return;
	}

	if(!firstbone)
	{
		return;
	}

	if(!secondbone)
	{
		return;
	}

	if(!thirdbone)
	{
		return;
	}
	
	if(Grabit.GetActor() == firststatue)
	{
		GrabWidget();
		firststatue->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(true);
		first = true;
		return;
	}
	else if (first == true && persistenoutline == true)
	{	
		firststatue->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(false);
		first = false;
		return;
	}

	if(Grabit.GetActor() == secondstatue)
	{
		GrabWidget();
		secondstatue->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(true);
		second = true;
		return;
	}
	else if (second == true && persistenoutline == true)
	{
		secondstatue->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(false);
		second = false;
		return;
	}

	if(Grabit.GetActor() == firstbone)
	{
		GrabWidget();
		firstbone->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(true);
		third = true;
		return;
	}
	else if (third == true && persistenoutline == true)
	{
		firstbone->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(false);
		third = false;
		return;
	}

	if(Grabit.GetActor() == secondbone)
	{
		GrabWidget();
		secondbone->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(true);
		forth = true;
		return;
	}
	else if (forth == true && persistenoutline == true)
	{
		secondbone->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(false);
		forth = false;
		return;
	}

	if(Grabit.GetActor() == thirdbone)
	{
		GrabWidget();
		thirdbone->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(true);
		fifth = true;
		return;
	}
	else if (fifth == true && persistenoutline == true)
	{
		thirdbone->FindComponentByClass<UPrimitiveComponent>()->SetRenderCustomDepth(false);
		fifth = false;
		return;
	}
}

void UGrabber::GrabWidget()
{
	if(DoOnceGrabWidget == false)
	{
		DoOnceGrabWidget = true;

		if(ControllsWidgetGrabDefault)
		{
			ControllsWidgetGrab = CreateWidget<UUserWidget>(GetWorld(), ControllsWidgetGrabDefault);
			ControllsWidgetGrab->AddToViewport();
		}
	}
}



