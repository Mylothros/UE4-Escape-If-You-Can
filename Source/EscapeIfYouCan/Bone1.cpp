// Fill out your copyright notice in the Description page of Project Settings.


#include "Bone1.h"
#include "Engine/World.h"
#include "MainCharacter.h"
#include "Engine/Engine.h"

// Sets default values
ABone1::ABone1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Bone1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bon1"));
	Bone1->SetupAttachment(RootComponent);
	TriggerCapsule1 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapseule"));
	TriggerCapsule1->InitCapsuleSize(55.f, 96.f);
	TriggerCapsule1->SetupAttachment(RootComponent);
	TriggerCapsule1->SetCollisionProfileName("Overlap");
	TriggerCapsule1->OnComponentBeginOverlap.AddDynamic(this, &ABone1::OnOverlapBegin);
	TriggerCapsule1->OnComponentEndOverlap.AddDynamic(this, &ABone1::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABone1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABone1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABone1::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != GetWorld()->GetFirstPlayerController()->GetPawn()) && (OtherActor == Vase1) && OtherComponent)
	{
		AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SetBooleans->FirstBone = true;
		// if(GEngine)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("YES"));
		// }
	}
}

void ABone1::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if(OtherActor && (OtherActor != GetWorld()->GetFirstPlayerController()->GetPawn()) && OtherComponent)
	{
		AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SetBooleans->FirstBone = false;
		// if(GEngine)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NO"));
		// }
	}

}
