// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	FVector DesireMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f);

	if (!DesireMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesireMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);


		// If we bump into something, slide along the side of it.
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesireMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
			UE_LOG(LogTemp, Warning, TEXT("Valid Blocking Hit"));
		}
	}
}