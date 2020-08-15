// Fill out your copyright notice in the Description page of Project Settings.


#include "Bone2.h"
#include "Engine/World.h"
#include "MainCharacter.h"
#include "Engine/Engine.h"

// Sets default values
ABone2::ABone2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Bone2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bon2"));
	Bone2->SetupAttachment(RootComponent);
	TriggerCapsule2 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapseule2"));
	TriggerCapsule2->InitCapsuleSize(55.f, 96.f);
	TriggerCapsule2->SetupAttachment(RootComponent);
	TriggerCapsule2->SetCollisionProfileName("Overlap");
	TriggerCapsule2->OnComponentBeginOverlap.AddDynamic(this, &ABone2::OnOverlapBegin);
	TriggerCapsule2->OnComponentEndOverlap.AddDynamic(this, &ABone2::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABone2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABone2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABone2::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != GetWorld()->GetFirstPlayerController()->GetPawn()) && (OtherActor == Vase2) && OtherComponent)
	{
		AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SetBooleans->SecondBone = true;
		// if(GEngine)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("YES"));
		// }
	}
}

void ABone2::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if(OtherActor && (OtherActor != GetWorld()->GetFirstPlayerController()->GetPawn()) && OtherComponent)
	{
		AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SetBooleans->SecondBone = false;
		// if(GEngine)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NO"));
		// }
	}

}