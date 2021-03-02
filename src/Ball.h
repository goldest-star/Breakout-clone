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
	void roll();
private:
	olc::PixelGameEngine &game_;
	World &world_;
	Bat &bat_;
	std::unique_ptr<olc::Sprite> sprBall{nullptr};
	float radius_{0.0f};
	olc::vf2d position_{ 0.0f, 0.0f };
	olc::vf2d velocity_{ 0.0f, 0.0f };
	bool circleVsRect(const olc::vf2d &pos, const olc::vf2d &rectPos,
			          const olc::vf2d &recSize, olc::vf2d &contactPnt);
	olc::vf2d contactNormal(const olc::vf2d &point, const olc::vf2d &rect, const olc::vf2d &rSize);
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
