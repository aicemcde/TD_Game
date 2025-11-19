#include "Component.h"
#include "Actor.h"

Component::Component(Actor* actor, int updateOrder)
	:mOwner(actor)
	,mUpdateOrder(updateOrder)
{
}

Component::~Component()
{
}

void Component::Update(float deltaTime)
{
}