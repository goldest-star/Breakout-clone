#include "BallGraphicsComponent.h"

void
BallGraphicsComponent::update(GameObject &ball, olc::PixelGameEngine &pge)
{
	float radius{float(sprBall->width) / 16 / 2.0f};
	olc::vf2d offset{ radius, radius }; // to set origin at centre of sprite
	pge.DrawSprite((ball.position() - offset) * tileSize, sprBall.get());
}
