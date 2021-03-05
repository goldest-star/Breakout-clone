#ifndef BAT_INPUT_COMPONENT_H
#define BAT_INPUT_COMPONENT_H

#include "InputComponent.h"
#include "GameObject.h"
#include "World.h"

class BatInputComponent : public InputComponent {
public:
	void update(GameObject &bat, const olc::PixelGameEngine &pge, World &World) override;
};
#endif /* ifndef BAT_INPUT_COMPONENT_H */
