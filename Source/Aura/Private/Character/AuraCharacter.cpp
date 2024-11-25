#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h" // Add this include
#include <Player\AuraPlayerState.h>


AAuraCharacter::AAuraCharacter()
{
	// Character aligns with the direction of the movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Define how quick the character rotates to the direction of the movement
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	// Constrain movement to 2D plane
	GetCharacterMovement()->bConstrainToPlane = true;
	// Snap the character to the plane at the start
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Disable controller rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor for the server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor for the client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	// Init ability actor for the server
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
