#define WRITE_UPPER_STACK

#include "MyPhysicsHandleComponent.h"
#include "DoorSystemMassCharacter.h"


UMyPhysicsHandleComponent::UMyPhysicsHandleComponent()
{
	LineTraceComponent = CreateDefaultSubobject<UMyLineTraceComponent>(TEXT("LineTraceComponent"));
	MaxDist = 450.f;
}

void UMyPhysicsHandleComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (Owner)
	{
		Owner->InputComponent->BindAction("StartDragComponent", EInputEvent::IE_Pressed, this, &UMyPhysicsHandleComponent::StartDragComponent);
		Owner->InputComponent->BindAction("StopDragComponent", EInputEvent::IE_Pressed, this, &UMyPhysicsHandleComponent::StopDragComponent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle Component has no Owner!"));
	}
}

void UMyPhysicsHandleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Owner && GetGrabbedComponent())
	{
		FVector ViewPointLocation;
		FRotator ViewPointRotation;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(WRITE_UPPER_STACK ViewPointLocation, WRITE_UPPER_STACK ViewPointRotation);

		FVector OwnerLocation = Owner->GetActorLocation();
		FVector EndLocation = ViewPointRotation.Vector() * MaxDist;
		FVector NewComponentOwnerLocation = OwnerLocation + EndLocation;
		SetTargetLocation(NewComponentOwnerLocation);
	}
}

void UMyPhysicsHandleComponent::OnUnregister()
{
	Super::OnUnregister();

	if (LineTraceComponent)
	{
		LineTraceComponent->DestroyComponent();
	}
}

void UMyPhysicsHandleComponent::StartDragComponent()
{
	UPrimitiveComponent* SweepedComponent = LineTraceComponent->DoSweepSingleByObjectType();
	if (SweepedComponent)
	{
		GrabComponentAtLocation(SweepedComponent, NAME_None, SweepedComponent->GetComponentLocation());
	}
}

void UMyPhysicsHandleComponent::StopDragComponent()
{
	ReleaseComponent();
}

