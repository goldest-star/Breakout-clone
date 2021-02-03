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
	Ball(olc::PixelGameEngine &game, World &blocks, Bat &bat);
	void update(float fElapsedTime);
	void draw();
	bool isOutOfBounds = false;
	void reset(const olc::vf2d &postion);
	void reset(float x, float y);
private:
	olc::PixelGameEngine &game_;
	World &blocks_;
	Bat &bat_;
	std::unique_ptr<olc::Sprite> sprBall{nullptr};
	float radius_{0.0f};
	olc::vf2d position_{ 0.0f, 0.0f };
	olc::vf2d velocity_{ 0.0f, 0.0f };
	bool testResolveCollision(const olc::vf2d &position, const olc::vf2d &point);
	olc::vf2d hitpos{0.0f, 0.0f};
	int hitID = 0;
	bool hasHitTile = false;
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
