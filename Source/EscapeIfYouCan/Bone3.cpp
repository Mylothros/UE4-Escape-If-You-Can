// Fill out your copyright notice in the Description page of Project Settings.


#include "Bone3.h"
#include "Engine/World.h"
#include "MainCharacter.h"
#include "Engine/Engine.h"

// Sets default values
ABone3::ABone3()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Bone3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bon3"));
	Bone3->SetupAttachment(RootComponent);
	TriggerCapsule3 = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapseul3"));
	TriggerCapsule3->InitCapsuleSize(55.f, 96.f);
	TriggerCapsule3->SetupAttachment(RootComponent);
	TriggerCapsule3->SetCollisionProfileName("Overlap");
	TriggerCapsule3->OnComponentBeginOverlap.AddDynamic(this, &ABone3::OnOverlapBegin);
	TriggerCapsule3->OnComponentEndOverlap.AddDynamic(this, &ABone3::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ABone3::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABone3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABone3::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor != GetWorld()->GetFirstPlayerController()->GetPawn()) && (OtherActor == Vase3) && OtherComponent)
	{
		AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SetBooleans->ThirdBone = true;
		// if(GEngine)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("YES"));
		// }
	}
}

void ABone3::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if(OtherActor && (OtherActor != GetWorld()->GetFirstPlayerController()->GetPawn()) && OtherComponent)
	{
		AMainCharacter* SetBooleans = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SetBooleans->ThirdBone = false;
		// if(GEngine)
		// {
		// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NO"));
		// }
	}

}

