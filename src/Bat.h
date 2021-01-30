#ifndef BAT_H
#define BAT_H

#include "../include/olcPixelGameEngine.h"
#include "Blocks.h"
#include <memory>

class PixelGameEngine;
class Bat {
public:
	Bat(olc::PixelGameEngine &game, Blocks &blocks);
	void update(float fElapsedTime);
	void draw();
	olc::vf2d position();
	float width() const;
	float height() const;
	float speed() const;
private:
	olc::PixelGameEngine &game_;
	Blocks &blocks_;
	std::unique_ptr<olc::Sprite> sprBat{std::make_unique<olc::Sprite>("../assets/gfx/paddleRed_64x16.png")};
	float width_{sprBat->width / float(blocks_.blockSize().x)};
	float height_{sprBat->height / float(blocks_.blockSize().x)};
	float speed_{20.0f};
	olc::vf2d position_{ (blocks_.width() / 2.0f) - (width_ / 2.0f), float(blocks_.height()) - 1.0f };
};
#endif /* ifndef BAT_H */
