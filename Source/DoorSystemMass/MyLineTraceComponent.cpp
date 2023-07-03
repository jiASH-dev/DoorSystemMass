#define WRITE_UPPER_STACK
#define MY_CUSTOM_CHANNEL ECC_GameTraceChannel2

#include "MyLineTraceComponent.h"
#include "DrawDebugHelpers.h"

UMyLineTraceComponent::UMyLineTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	TraceMaxDistance = 500.f;
	SweepSphereRadius = 50.f;
}

void UMyLineTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

void UMyLineTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UPrimitiveComponent* UMyLineTraceComponent::DoSweepSingleByObjectType()
{
	if (Owner)
	{
		FHitResult Hit;

		FVector StartLocation = Owner->GetActorLocation();
		FVector EndLocation = StartLocation + Owner->GetActorForwardVector() * TraceMaxDistance;

		FCollisionShape Sphere = FCollisionShape::MakeSphere(SweepSphereRadius);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(Owner);

		DrawDebugSphere(GetWorld(), EndLocation, SweepSphereRadius, 12, FColor::Blue, false, 5.f);

		bool IsSmthSweeped = GetWorld()->SweepSingleByObjectType(
			WRITE_UPPER_STACK Hit,
			StartLocation,
			EndLocation,
			FQuat::Identity,
			FCollisionObjectQueryParams(ECollisionChannel::MY_CUSTOM_CHANNEL),
			Sphere,
			TraceParams
		);

		if (IsSmthSweeped)
		{
			return Hit.GetComponent();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Sweeped nothing."));
			return nullptr;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Line trace component has no Owner!"));
	return nullptr;
}

