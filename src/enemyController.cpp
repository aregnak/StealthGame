#include "enemyController.h"
#include "godot_cpp/core/print_string.hpp"
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
    // Random direction for now
    // Will change to adapt to environment
    // direction = godot::UtilityFunctions::randf() < 0.5f ? godot::Vector3(-1, 0, 0)
    //                                                     : godot::Vector3(1, 0, 0);
    direction = godot::Vector3(0, 0, 0);

    enemy_skin = get_node<godot::Node3D>("Skin");
    ray = get_node<godot::RayCast3D>("Ray");
}

void EnemyController::_physics_process(double delta)
{
    godot::Vector3 velocity = get_velocity();

    // Gravity
    if (!is_on_floor())
    {
        velocity += get_gravity() * delta;
    }

    if (ray->is_colliding())
    {
        direction.x += 90;
    }

    double target_yaw = godot::Math::atan2(direction.x, direction.z);
    double current_rotation = enemy_skin->get_rotation().y; // Euler angles in radians

    current_rotation = godot::Math::lerp_angle(current_rotation, target_yaw, delta * 15);

    godot::Vector3 good_direction;
    good_direction.y = current_rotation;

    enemy_skin->set_rotation(good_direction);

    godot::Vector3 ray_rotation = ray->get_rotation();
    ray_rotation.y = current_rotation;
    ray->set_rotation(ray_rotation);

    // velocity.x = direction.x * speed;
    // velocity.z = direction.z * speed;

    set_velocity(velocity);
    move_and_slide();
}

void EnemyController::_bind_methods() {}
