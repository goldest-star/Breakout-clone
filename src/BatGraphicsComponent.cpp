#include "BatGraphicsComponent.h"

void
BatGraphicsComponent::update(GameObject &bat, olc::PixelGameEngine &pge)
{
	pge.DrawSprite(bat.position() * tileSize_, sprBat_.get());
}
