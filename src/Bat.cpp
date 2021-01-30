#include "Bat.h"
#include "Blocks.h"
#include <memory> 

Bat::Bat(olc::PixelGameEngine &game, Blocks &blocks) : game_(game), blocks_(blocks) {}

void
Bat::update(float fElapsedTime)
{
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
}

void
Bat::draw()
{
	game_.DrawSprite(position_ * blocks_.blockSize(), sprBat.get());
}

olc::vf2d Bat::position() { return position_; }
float Bat::width() const { return width_; }
float Bat::height() const { return height_; }
float Bat::speed() const { return speed_; }
