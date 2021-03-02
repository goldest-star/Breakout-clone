#include "Bat.h"
#include "World.h"
#include <memory> 

Bat::Bat(olc::PixelGameEngine &game, World &blocks) : game_(game), blocks_(blocks) {}

void
Bat::update(float fElapsedTime)
{
	auto prevPosition{position_};

	// Handle user input
	if (game_.GetKey(olc::Key::LEFT).bHeld || game_.GetKey(olc::Key::A).bHeld)
		position_.x -= speed_ * fElapsedTime;
	if (game_.GetKey(olc::Key::RIGHT).bHeld || game_.GetKey(olc::Key::D).bHeld)
		position_.x += speed_ * fElapsedTime;

	 // Limit bat movement 
	if (float leftWallEdge = 1.0f; position_.x < leftWallEdge)
		position_.x = leftWallEdge;
	if (float rightWallEdge = blocks_.width() - 1.0f; position_.x + width_ > rightWallEdge)
		position_.x = rightWallEdge - width_;

	// clear previous position
	for (int x = prevPosition.x; x < prevPosition.x + width_; ++x)
		blocks_[prevPosition.y * blocks_.width() + x] = 0;
	// update with new position
	for (int x = position_.x; x < position_.x + width_; ++x)
		blocks_[position_.y * blocks_.width() + x] = 20;
}

void
Bat::draw()
{
	game_.DrawSprite(position_ * blocks_.blockSize(), sprBat.get());
}
