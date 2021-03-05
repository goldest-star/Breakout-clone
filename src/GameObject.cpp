#include "GameObject.h"

GameObject::GameObject(InputComponent *input, PhysicsComponent *physics,
		GraphicsComponent *graphics)
	    : input_(input), physics_(physics), graphics_(graphics) {}

void
GameObject::update(olc::PixelGameEngine *pge, World *world)
{
	input_->update(*this, *pge, *world);
	physics_->update(*this, *pge, *world);
}

void
GameObject::draw(olc::PixelGameEngine *pge)
{
	graphics_->update(*this, *pge);
}

olc::vf2d& GameObject::position() { return position_; }
olc::vf2d& GameObject::velocity() { return velocity_; }
olc::vi2d& GameObject::size() { return size_; }

