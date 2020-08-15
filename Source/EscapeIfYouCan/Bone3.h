// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Bone3.generated.h"

UCLASS()
class ESCAPEIFYOUCAN_API ABone3 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABone3();

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* TriggerCapsule3;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Bone3;

	UPROPERTY(EditAnywhere)
		AActor* Vase3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

};
