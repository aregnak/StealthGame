#pragma once

#include <godot_cpp/classes/character_body3d.hpp>
#include "cameraController.h"

class PlayerController : public godot::CharacterBody3D
{
    GDCLASS(PlayerController, godot::CharacterBody3D);

    CameraController* camera = nullptr;

    const float speed;
    const float jumpVelocity;

    const float ground_friction;
    const float air_friction;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _physics_process(double delta) override;

    PlayerController();
    ~PlayerController() = default;
};
