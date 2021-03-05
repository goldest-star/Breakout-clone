#include "BatInputComponent.h"

void
BatInputComponent::update(GameObject &bat, const olc::PixelGameEngine &pge, World &world)
{
	auto prevPosition{bat.position()};
	auto batSpeed{bat.velocity().mag()};
	auto batWidth{bat.size().x};
	// Handle user input
	if (pge.GetKey(olc::Key::LEFT).bHeld || pge.GetKey(olc::Key::A).bHeld)
		bat.position().x -= batSpeed * pge.GetElapsedTime();
	if (pge.GetKey(olc::Key::RIGHT).bHeld || pge.GetKey(olc::Key::D).bHeld)
		bat.position().x += batSpeed * pge.GetElapsedTime();

	 // Limit bat movement 
	if (float leftWallEdge{1.0f};
			bat.position().x < leftWallEdge)
		bat.position().x = leftWallEdge;
	if (float rightWallEdge{world.width() - 1.0f};
			bat.position().x + batWidth > rightWallEdge)
		bat.position().x = rightWallEdge - batWidth;

	// clear previous position
	for (int x = prevPosition.x; x < prevPosition.x + batWidth; ++x)
		world[prevPosition.y * world.width() + x] = 0;
	// update with new position
	for (int x = bat.position().x; x < bat.position().x + batWidth; ++x)
		world[bat.position().y * world.width() + x] = 20;
}
