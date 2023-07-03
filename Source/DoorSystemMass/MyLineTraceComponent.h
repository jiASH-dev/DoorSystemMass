#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyLineTraceComponent.generated.h"


UCLASS()
class DOORSYSTEMMASS_API UMyLineTraceComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	AActor* Owner;

public:
	UPROPERTY(EditAnywhere)
		float TraceMaxDistance;
	UPROPERTY(EditAnywhere)
		float SweepSphereRadius;

protected:
	virtual void BeginPlay() override;

public:
	UMyLineTraceComponent();
	UPrimitiveComponent* DoSweepSingleByObjectType();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
