#pragma once

#include <godot_cpp/classes/character_body3d.hpp>

class PlayerController : public godot::CharacterBody3D
{
    GDCLASS(PlayerController, godot::CharacterBody3D);

    const float speed;
    const float jumpVelocity;

protected:
    static void _bind_methods();

public:
    void _physics_process(double delta) override;

    PlayerController();
    ~PlayerController() = default;
};
