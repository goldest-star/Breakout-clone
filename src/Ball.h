#ifndef BALL_H
#define BALL_H

#include "../include/olcPixelGameEngine.h"
#include <memory>
#include <random>

class Blocks;
class Bat;
class Ball {
public:
	Ball(olc::PixelGameEngine &game, Blocks &blocks, Bat &bat);
	void update(float fElapsedTime);
	void draw();
	bool isOutOfBounds = false;
	void reset(const olc::vf2d &postion);
	void reset(float x, float y);
private:
	olc::vf2d direction_{ 0.0f, 0.0f };
	olc::vf2d position_{ 0.0f, 0.0f };
	olc::vf2d potentialPos_{ 0.0f, 0.0f };
	olc::vf2d tileRadialDimensions_{ 0.0f, 0.0f };
	float radius_{0.0f};
	float speed_{0.0f};
	float angle_{0.0f};
	std::unique_ptr<olc::Sprite> sprBall{nullptr};
	bool testResolveCollision(const olc::vf2d &point);
	olc::PixelGameEngine &game_;
	Blocks &blocks_;
	Bat &bat_;
	olc::vf2d hitpos{0.0f, 0.0f};
	int hitID = 0;
	bool hasHitTile = false;
	bool intersectBat(Bat *bat);
};

inline
float randomf(float from, float to)
{
	static std::default_random_engine e(time(nullptr));
	e.discard(1);
	static std::uniform_real_distribution<float> u(from, to);
	return u(e);
}
#endif /* ifndef BALL_H */
