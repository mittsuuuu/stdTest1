#pragma once
#include "Scene.h"

class Title : public Scene
{
	public:
		Title();
		virtual ~Title();
		virtual Scene* update() override;
		virtual void draw() const override;
};
