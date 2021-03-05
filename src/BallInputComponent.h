#ifndef BALL_INPUT_COMPONENT_H
#define BALL_INPUT_COMPONENT_H

#include "InputComponent.h"

class BallInputComponent : public InputComponent {
public:
	void update(GameObject &ball, const olc::PixelGameEngine &pge, World &world) override;
};
#endif /* ifndef BALL_INPUT_COMPONENT_H */
