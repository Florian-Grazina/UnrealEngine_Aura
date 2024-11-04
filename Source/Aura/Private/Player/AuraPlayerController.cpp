


#include "Player/AuraPlayerController.h"
#include <EnhancedInputSubsystems.h>

AAuraPlayerController::AAuraPlayerController()
{
	// when an entity changes in the server, the clients will be notified
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	// base class BeginPlay
	Super::BeginPlay();

	// check if the context is valid and setted
	check(AuraContext);

	// local pointer Subsystem. ULocalPlayer is a static class to access data from the local player
	// Subsystems are singleton
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	// priority 0
	Subsystem->AddMappingContext(AuraContext, 0); 

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// set the input mode to game and UI
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}
