#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../include/olcPixelGameEngine.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

class GameObject {
public:
	GameObject(InputComponent *input, PhysicsComponent *physics,
			GraphicsComponent *graphics);
	void update(olc::PixelGameEngine *pge, World *world);
	void draw(olc::PixelGameEngine *pge);
	olc::vf2d& position();
	olc::vf2d& velocity();
	olc::vi2d& size();
private:
	olc::vf2d position_{ 0.0f, 0.0f };
	olc::vf2d velocity_{ 0.0f, 0.0f };
	olc::vi2d size_{ 0, 0 };
	InputComponent *input_{nullptr};
	PhysicsComponent *physics_{nullptr};
	GraphicsComponent *graphics_{nullptr};
};
#endif /* ifndef GAME_OBJECT_H */
