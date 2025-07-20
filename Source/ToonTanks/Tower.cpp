// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!InFireRange())
	{
		return;
	}

	if (!Tank)
	{
		return;
	}

	RotateTurret(Tank->GetActorLocation());
}

void ATower::CheckFireCondition()
{
	if (!InFireRange())
	{
		return;
	}

	Fire();
}

bool ATower::InFireRange() const
{
	if (!Tank)
	{
		return false;
	}

	const FVector& TankLocation = Tank->GetActorLocation();
	const float Distance = FVector::Dist(GetActorLocation(), TankLocation);
	if (Distance > FireRange)
	{
		return false;
	}

	return true;
}
