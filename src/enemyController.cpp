#include "enemyController.h"
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

EnemyController::EnemyController()
    : speed(5.f)
{
}

void EnemyController::_ready()
{
    direction = godot::UtilityFunctions::randf() < 0.5f ? godot::Vector3(-1, 0, 0)
                                                        : godot::Vector3(1, 0, 0);
}

void EnemyController::_physics_process(double delta)
{
    godot::Vector3 velocity = get_velocity();

    // Gravity
    if (!is_on_floor())
    {
        velocity += get_gravity() * delta;
    }

    velocity.x = direction.x * speed;
    velocity.z = direction.z * speed;

    set_velocity(velocity);
    move_and_slide();
}

void EnemyController::_bind_methods() {}
