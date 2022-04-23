#ifndef BALL_PHYSICS_COMPONENT
#define BALL_PHYSICS_COMPONENT

#include "PhysicsComponent.h"
#include "GameObject.h"
#include <random>

class BallPhysicsComponent : public PhysicsComponent {
public:
	void update(GameObject &ball, const olc::PixelGameEngine &pge, World &world) override;
private:
	float radius_{0.5f}; // adjust according to sprite size
	bool isOutOfBounds{false};
	bool circleVsRect(const olc::vf2d &pos, const olc::vf2d &rectPos,
			     const olc::vf2d &rSize, olc::vf2d &contactPnt);
};

inline
float
randomf(float from, float to)
{
	static std::default_random_engine e(time(nullptr));
	e.discard(1);
	static std::uniform_real_distribution<float> u(from, to);
	return u(e);
}

inline
void
reset(GameObject &ball, float x, float y)
{
	ball.velocity() = { 0.0f, 0.0f };
	ball.position() = { x, y };
}

inline
void
roll(GameObject &ball)
{
	// change 1.0f to 2.0f to get an angle value between 0 and 2PI (360 degrees) as well.
	float angle_{randomf(0.1f, 0.9f) * 1.0f * float(M_PI)};
	olc::vf2d direction_{ cosf(angle_), sinf(angle_) };
	float speed_{20.0f};
	ball.velocity() = speed_ * direction_;
}

inline
olc::vf2d
contactNormal(const olc::vf2d &point, const olc::vf2d &rect, const olc::vf2d &rSize)
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

#endif /* ifndef BALL_PHYSICS_COMPONENT */
