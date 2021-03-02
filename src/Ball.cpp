#include "Ball.h"
#include "Bat.h"
#include "BreakOut.h"

#include <algorithm>
#include <cmath>
#include <iostream>

Ball::Ball(olc::PixelGameEngine &game, World &blocks, Bat &bat)
		  : game_(game), blocks_(blocks), bat_(bat)
{
	sprBall = std::make_unique<olc::Sprite>("../assets/gfx/ballGrey_16x16.png");
	radius_ = sprBall->width / 2.0f; // NOTE: unit is in screen space
	reset(blocks_.width() / 2.0f, blocks_.height()/ 2.0f);
} 

void
Ball::update(float fElapsedTime)
{
	if (game_.GetKey(olc::Key::R).bPressed)
		reset(blocks_.width() / 2.0f, blocks_.height()/ 2.0f);

	auto potentialPos = position_ + velocity_ * fElapsedTime;

	// area of detection
	olc::vi2d currentCell = position_.floor();
	olc::vi2d targetCell = potentialPos; // why no ceiling
	olc::vi2d worldSize{ int(blocks_.width()), int(blocks_.height()) };
	olc::vi2d areaTopleft = (currentCell.min(targetCell) - olc::vi2d(1, 1)).max({ 0, 0 });
	olc::vi2d areBottomRight = (currentCell.max(targetCell) + olc::vi2d(1, 1)).min(worldSize - olc::vi2d(1, 1));
	// iterate through the cells in the limited area
	olc::vi2d cell;
	olc::vi2d cellSize{ 1, 1 };
	for (cell.y = areaTopleft.y; cell.y <= areBottomRight.y; ++cell.y)
		for (cell.x = areaTopleft.x; cell.x <= areBottomRight.x; ++cell.x) {
			auto &tile{blocks_[cell.y * blocks_.width() + cell.x]};
			olc::vf2d contactPnt;
			if (tile > 0 && circleVsRect(potentialPos, cell, cellSize, contactPnt)) {
				olc::vf2d normal{contactNormal(contactPnt, cell, cellSize)};
				std::cout << -(position_ - contactPnt).norm() << '\n';
				// reflection ray equation: r = d - 2n(d * n)
				auto incedentRay{velocity_.norm()};
				auto reflectedRay{incedentRay - 2 * normal * incedentRay.dot(normal)};
				velocity_ = reflectedRay * velocity_.mag();
				if (tile < 10) --tile;
			}
		}
	position_ += velocity_ * fElapsedTime;

	// should use state pattern instead
	if (position_.y > blocks_.height())
		isOutOfBounds = true;
	if (isOutOfBounds)
		reset(blocks_.width() / 2.0f, blocks_.height() / 2.0f);
	if (isOutOfBounds && game_.GetKey(olc::Key::SPACE).bPressed)
		isOutOfBounds = false;
}

void
Ball::draw()
{
	if (isOutOfBounds) {
		auto msg = std::string("PRESS SPACE BAR");
		game_.DrawString(olc::vi2d((blocks_.width() - msg.size() / 2) / 2, blocks_.height() / 2) * blocks_.blockSize(), msg, olc::WHITE);
	} else {
		olc::vf2d offset{ radius_ / blocks_.blockSize().x, radius_ / blocks_.blockSize().y }; // to set origin at centre of sprite
		game_.DrawSprite((position_ - offset) * blocks_.blockSize(), sprBall.get());
	}
}

void 
Ball::reset(const olc::vf2d &postion)
{
	reset(postion.x, postion.y);
}

void
Ball::reset(float x, float y)
{
	// change 1.0f to 2.0f to get an angle value between 0 and 2PI (360 degrees) as well.
	float angle_{randomf(0.1f, 0.9f) * 1.0f * float(M_PI)};
	olc::vf2d direction_{ cosf(angle_), sinf(angle_) };
	float speed_{20.0f};
	velocity_ = speed_ * direction_;
	position_ = { x, y };
}

bool
Ball::circleVsRect(const olc::vf2d &pos, const olc::vf2d &rectPos, const olc::vf2d &rSize,
		           olc::vf2d &contactPnt)
{
	olc::vf2d nearestPnt;
	nearestPnt.x = std::max(rectPos.x, std::min(rectPos.x + rSize.x, pos.x));
	nearestPnt.y = std::max(rectPos.y, std::min(rectPos.y + rSize.y, pos.y));
	olc::vf2d nearestRay{nearestPnt - pos};
	float overlap{(radius_ / float(blocks_.blockSize().x)) - nearestRay.mag()};
	if (std::isnan(overlap)) overlap = 0;
	if (overlap > 0) { // collision
		auto dir{nearestRay.norm()};
		contactPnt = (pos - dir * overlap) + dir * (radius_ / 16);; 
		return true;
	}
	return false;
}

olc::vf2d
Ball::contactNormal(const olc::vf2d &point, const olc::vf2d &rect, const olc::vf2d &rSize)
{
	auto [height, width]{rSize};
	olc::vf2d rectCentre{ rect.x + height / 2.0f, rect.y + width / 2.0f };
	auto ballPosition{ point - rectCentre };
	auto [a, b]{ballPosition};
	if (std::abs(a) < width / 2 && b == -height / 2) // top edge
		return { 0.0f, -1.0f };
	if (std::abs(a) < width / 2 && b == height / 2) // bottom edge
		return { 0.0f, 1.0f };
	if (a == -width / 2 && std::abs(b) < height / 2) // left edge
		return { -1.0f, 0.0f };
	if (a == width / 2 && std::abs(b) < height / 2) // right edge
		return { 1.0f, 0.0f };
	return ballPosition.norm(); // corners: left-top/right and bottom-left/right
}
