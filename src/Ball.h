#ifndef BALL_H
#define BALL_H

#include "../include/olcPixelGameEngine.h"
#include "World.h"
#include <memory>
#include <random>

class Bat; 
float randomf(float from, float to);

class Ball {
public:
	Ball(olc::PixelGameEngine &game, World &blocks, Bat &bat)
		: game_(game), blocks_(blocks), bat_(bat) {}
	void update(float fElapsedTime);
	void draw();
	bool isOutOfBounds = false;
	void reset(const olc::vf2d &postion);
	void reset(float x, float y);
private:
	olc::PixelGameEngine &game_;
	World &blocks_;
	Bat &bat_;
	std::unique_ptr<olc::Sprite> sprBall{std::make_unique<olc::Sprite>("../assets/gfx/ballGrey_11x11.png")};
	float radius_{sprBall->width / 2.0f}; // NOTE: unit is in screen space
	olc::vf2d tileRadialDimensions_{ radius_ / blocks_.blockSize().x, radius_ / blocks_.blockSize().y };
	olc::vf2d position_{ blocks_.width() / 2.0f, blocks_.height()/ 2.0f };
	olc::vf2d potentialPos_{ 0.0f, 0.0f };
	float speed_{20.0f};
	float angle_{randomf(0.1f, 0.9f) * 1.0f * float(M_PI)};
	olc::vf2d direction_{ cosf(angle_), sinf(angle_) };
	bool testResolveCollision(const olc::vf2d &point);
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
