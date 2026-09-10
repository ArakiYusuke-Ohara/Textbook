#pragma once
#include "Component.h"

class Renderer : public Component
{
public:
	Renderer() = default;
	virtual ~Renderer() = default;

	virtual void Render() = 0;
};
