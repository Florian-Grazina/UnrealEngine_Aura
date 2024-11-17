


#include "Player/AuraPlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	// when an entity changes in the server, the clients will be notified
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}


void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	* Line trace from cursor. Several scenarios:
	* 
	* A. LastActor is null && ThisActor is null
	*	- do nothing
	* 
	* B. LastActor is null && ThisActor is valid. We are hovering to the actor for the first time.
	*	- Highlight ThisActor
	* 
	* C. LastActor is valid && ThisActor is null. We are unhovering to an actor
	*	- UnHighlight LastActor
	* 
	* D. Both actors are valid, but LastActor != ThisActor
	*	- UnHighlight LastActor, Highlight ThisActor
	* 
	* E. Both actores are valide, LastActor == ThisActor
	*	- do nothing
	*/

	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr)
		{
			// Case A.
			// do nothing
		}
		else
		{
			// Case B.
			ThisActor->HighlightActor();
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C.
			LastActor->UnHighlightActor();
		}
		else // Both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D.
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E.
				// do nothing
			}

		}
	}
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

	// we add the mapping context so the PlayerController can retrieve data
	Subsystem->AddMappingContext(AuraContext, 0); 

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// set the input mode to game and UI
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// cast the property InputComponent to EnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// bind the action to the function Move
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
