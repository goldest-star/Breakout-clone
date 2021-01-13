
#include "Ball.h"
#include "../include/olcPixelGameEngine.h"
#include <memory>

Ball::Ball()
{
	position() = { 12, 15 };
	sprBall = std::make_unique<olc::Sprite>("../assets/gfx/ballGrey_11x11.png");
}

void
Ball::update()
{
}

void
Ball::draw(olc::PixelGameEngine *pge)
{
	pge->DrawSprite(position() * vBlockSize, sprBall.get());
}

olc::vf2d
Ball::dir() const
{
	return direction;
}

float
Ball::radius() const
{
	return radius_;
}

float
Ball::speed() const
{
	return speed_;
}
