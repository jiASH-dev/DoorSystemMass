#include "MyTriggerBox.h"
#include "Components/ShapeComponent.h"
#include "Containers/Array.h"
#include "Algo/Accumulate.h"


AMyTriggerBox::AMyTriggerBox()
{
}

void AMyTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyTriggerBox::BeginOverlapObject);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &AMyTriggerBox::EndOverlapObject);
}

void AMyTriggerBox::BeginOverlapObject
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	PrintOverlappedComponentsTotalMass();
}

void AMyTriggerBox::EndOverlapObject(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TArray<UPrimitiveComponent*> OverlappedComponents = GetOverlappedComponents();

	if (OverlappedComponents.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger box is empty now"));
	}
	else
	{
		PrintOverlappedComponentsTotalMass();
	}
}

void AMyTriggerBox::PrintOverlappedComponentsTotalMass()
{
	TArray<UPrimitiveComponent*> OverlappedComponents = GetOverlappedComponents();

	float OverlappedComponentsTotalMass = Algo::Accumulate(
		OverlappedComponents,
		0,
		[](float TotalMass, UPrimitiveComponent* Component) {
			return Component->IsSimulatingPhysics() ? TotalMass + Component->GetMass() : 0.f;
		}
	);

	UE_LOG(LogTemp, Warning, TEXT("Total mass of the overlapped components is : %f"), OverlappedComponentsTotalMass);
}

TArray<UPrimitiveComponent*> AMyTriggerBox::GetOverlappedComponents()
{
	TArray<UPrimitiveComponent*> OverlappedComponents;
	GetCollisionComponent()->GetOverlappingComponents(OverlappedComponents);
	return OverlappedComponents;
}

