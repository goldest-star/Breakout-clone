#include "BatPhysicsComponent.h"

void
BatPhysicsComponent::update(GameObject &bat, [[maybe_unused]]const olc::PixelGameEngine &pge, World &world)
{
	auto prevPosition{bat.position()};
	auto batWidth{bat.size().x};

	// clear previous position
	for (int x{int(prevPosition.x)}; x < prevPosition.x + batWidth; ++x)
		world[prevPosition.y * world.width() + x] = 0;
	// update with new position
	for (int x{int(bat.position().x)}; x < bat.position().x + batWidth; ++x)
		world[bat.position().y * world.width() + x] = 20;
}
