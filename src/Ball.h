#ifndef BALL_H
#define BALL_H

#include "../include/olcPixelGameEngine.h"
#include "Entity.h"
#include <memory>

class Ball : public Entity {
public:
	Ball();
	void update() override;
	void draw(olc::PixelGameEngine *) override;
	olc::vf2d dir() const;
	float radius() const;
	float speed() const;
private:
	olc::vf2d direction = { 0.0f, 0.0f };
	float radius_ = 5.5f;
	float speed_ = 20.0f;
	std::unique_ptr<olc::Sprite> sprBall;
	olc::vi2d vBlockSize = { 11, 11 };	
};
#endif /* ifndef BALL_H */
