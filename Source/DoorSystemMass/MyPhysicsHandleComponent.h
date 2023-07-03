#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "MyLineTraceComponent.h"
#include "MyPhysicsHandleComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DOORSYSTEMMASS_API UMyPhysicsHandleComponent : public UPhysicsHandleComponent
{
	GENERATED_BODY()

private:
	AActor* Owner;

public:
	UPROPERTY(EditAnywhere)
		UMyLineTraceComponent* LineTraceComponent;
	UPROPERTY(EditAnywhere)
		float MaxDist;

protected:
	void BeginPlay() override;

public:
	UMyPhysicsHandleComponent();
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OnUnregister() override;
	void StartDragComponent();
	void StopDragComponent();
};
