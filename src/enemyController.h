#pragma once

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>

class EnemyController : public godot::CharacterBody3D
{
    GDCLASS(EnemyController, godot::CharacterBody3D);

    godot::Node3D* enemy_skin = nullptr;
    godot::RayCast3D* ray = nullptr;

    godot::Vector3 direction;

    const float speed;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _physics_process(double delta) override;

    EnemyController();
    ~EnemyController() = default;
};
