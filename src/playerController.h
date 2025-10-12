#pragma once

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node3d.hpp>

#include "cameraController.h"
#include "playerSkin.h"

class PlayerController : public godot::CharacterBody3D
{
    GDCLASS(PlayerController, godot::CharacterBody3D);

    CameraController* camera = nullptr;
    PlayerSkin* player_skin = nullptr;

    const float speed;
    const float jump_velocity;

    const float ground_friction;
    const float air_friction;

    bool is_attacking;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _physics_process(double delta) override;

    void attack_anim();
    void attacking();

    PlayerController();
    ~PlayerController() = default;
};
