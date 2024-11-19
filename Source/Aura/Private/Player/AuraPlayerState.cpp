


#include "Player/AuraPlayerState.h"
#include <AbilitySystem\AuraAbilitySystemComponent.h>
#include <AbilitySystem\AuraAttributeSet.h>

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	// update player state on the server for multiplayer
	NetUpdateFrequency = 100.f;
}


UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
