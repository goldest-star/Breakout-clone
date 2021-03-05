#ifndef BALL_GRAPHICS_COMPONENT_H
#define BALL_GRAPHICS_COMPONENT_H

#include "GraphicsComponent.h"
#include "GameObject.h"
#include <memory>

class BallGraphicsComponent : public GraphicsComponent {
public:
	void update(GameObject &ball, olc::PixelGameEngine &pge) override;
private:
	std::unique_ptr<olc::Sprite> sprBall{std::make_unique<olc::Sprite>("../assets/gfx/ballGrey_16x16.png")};
	olc::vi2d tileSize{ 16, 16 };
};
#endif /* ifndef BALL_GRAPHICS_COMPONENT_H */
