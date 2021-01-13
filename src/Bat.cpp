#include "Bat.h"
#include <memory>

Bat::Bat(TileMap *m) : map(m)
{
	sprBat = std::make_unique<olc::Sprite>("../assets/gfx/paddleRed_64x16.png");
	position() = olc::vi2d(10, 29);
	update();
}

void
Bat::update()
{
	// clear the bat's track in tile map 
	auto y = position().y;
	for (size_t x = 1; x < map->width() - 1; ++x)
		map->blocks[y * map->width() + x] = 0;
	// update tile map with bat's new position
	for (auto x = position().x; x < position().x + width(); ++x)
		map->blocks[y * map->width() + x] = 11;
}

void
Bat::draw(olc::PixelGameEngine *game)
{
	auto vBlockSize = olc::vi2d(16, 16);	
	game->DrawSprite(position() * vBlockSize, sprBat.get());
}

float
Bat::width() const
{
	return width_;
}

float
Bat::speed() const
{
	return speed_;
}
