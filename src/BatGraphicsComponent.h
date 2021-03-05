#ifndef BAT_GRAPHICS_COMPONENT_H
#define BAT_GRAPHICS_COMPONENT_H

#include "GraphicsComponent.h"
#include "GameObject.h"
#include <memory>

class BatGraphicsComponent : public GraphicsComponent {
public:
	void update(GameObject &bat, olc::PixelGameEngine &pge) override;
private:
	std::unique_ptr<olc::Sprite> sprBat_{std::make_unique<olc::Sprite>("../assets/gfx/paddleRed_64x16.png")};
	olc::vi2d tileSize_{ 16, 16 };
};
#endif /* ifndef BAT_GRAPHICS_COMPONENT_H */
