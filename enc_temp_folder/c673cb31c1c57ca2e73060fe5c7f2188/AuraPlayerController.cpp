


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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
