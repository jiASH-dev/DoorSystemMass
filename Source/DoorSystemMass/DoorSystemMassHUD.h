// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DoorSystemMassHUD.generated.h"

UCLASS()
class ADoorSystemMassHUD : public AHUD
{
	GENERATED_BODY()

public:
	ADoorSystemMassHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

