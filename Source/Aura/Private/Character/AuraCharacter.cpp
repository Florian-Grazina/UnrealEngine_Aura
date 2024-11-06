#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h" // Add this include

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
