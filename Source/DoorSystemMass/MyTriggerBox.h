#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DoorSystem.h"
#include "MyTriggerBox.generated.h"


UCLASS()
class DOORSYSTEMMASS_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	AMyTriggerBox();
	UFUNCTION()
		void BeginOverlapObject
		(
			UPrimitiveComponent* OverlappedComp, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
	UFUNCTION()
		void EndOverlapObject(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	TArray<UPrimitiveComponent*> GetOverlappedComponents();
	void PrintOverlappedComponentsTotalMass();
};
