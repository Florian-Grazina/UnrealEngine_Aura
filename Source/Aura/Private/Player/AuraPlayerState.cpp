


#include "Player/AuraPlayerState.h"
#include <AbilitySystem\AuraAbilitySystemComponent.h>
#include <AbilitySystem\AuraAttributeSet.h>

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	//Replicating means the server will change the value of the variable on the clients
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	// update player state on the server for multiplayer
	NetUpdateFrequency = 100.f;
}


UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
