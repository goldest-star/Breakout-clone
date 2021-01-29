#ifndef BAT_H
#define BAT_H

#include "../include/olcPixelGameEngine.h"
#include <memory>

class Blocks;
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
	olc::vf2d position_{ 0.0f, 0.0f };
	float width_{0.0f};
	float height_{0.0f};
	float speed_{0.0f};
	std::unique_ptr<olc::Sprite> sprBat{nullptr};
	olc::PixelGameEngine &game_;
	Blocks &blocks_;
};
#endif /* ifndef BAT_H */
