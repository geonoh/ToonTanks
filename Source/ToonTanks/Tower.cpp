// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATower::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Tank)
	{
		const FVector& TankLocation = Tank->GetActorLocation();
		const float Distance = FVector::Dist(GetActorLocation(), TankLocation);
		if (Distance > FireRange)
		{
			return;
		}

		RotateTurret(TankLocation);
	}
}
