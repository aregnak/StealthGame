#pragma once

#include <godot_cpp/classes/character_body3d.hpp>

class EnemyController : public godot::CharacterBody3D
{
    GDCLASS(EnemyController, godot::CharacterBody3D);

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _physics_process(double delta) override;

    EnemyController();
    ~EnemyController() = default;
};
