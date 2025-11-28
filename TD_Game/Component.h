#pragma once
#include <cstdint>
#include "Graph_Types.h"

class Component
{
public:
	Component(class Actor* mOwner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t* keyState) {};
	int GetUpdateOrder() const { return mUpdateOrder; }

	Actor* GetOwner() const { return mOwner; }
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};