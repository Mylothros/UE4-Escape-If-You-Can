// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "SlideTheLastDoor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera_Mc = CreateDefaultSubobject<UCameraComponent>(TEXT("Fps camera of MC"));
	Camera_Mc->SetWorldLocation(FVector(20.f, -160.f, 108.f));
	Camera_Mc->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Handle Of MainCharacter"));
	//Camera_Mc->AttachTo(GetMesh(), "HeadSocket");
	//Camera_Mc->SetWorldRotation(FRotator(268.f, -2.75f, 89.140f));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();	
}
// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckForLastDoor(DeltaTime);
}

void AMainCharacter::CheckForLastDoor(float DeltaTime)
{
	if(FirstBone == true && SecondBone == true && ThirdBone == true)
	{		
		UActorComponent* AC = LastDoor->FindComponentByClass<USlideTheLastDoor>();
		USlideTheLastDoor* UC = Cast<USlideTheLastDoor>(AC);

		UC->SlideTheDoor(DeltaTime);
	}

	if((FirstBone == false || SecondBone == false || ThirdBone == false) || CLOSING1 == false)
	{
		UActorComponent* AC = LastDoor->FindComponentByClass<USlideTheLastDoor>();
		USlideTheLastDoor* UC = Cast<USlideTheLastDoor>(AC);
		
		UC->CloseSlideTheDoor(DeltaTime);
	}	
}
// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
}

void AMainCharacter::MoveForward(float Val)
{
	// FRotator Rotation = Controller->GetControlRotation();
	// FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(GetActorForwardVector(),Val);
}

void AMainCharacter::MoveRight(float Val)
{
	// FRotator Rotation = Controller->GetControlRotation();
	// FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(GetActorRightVector(),Val);
}