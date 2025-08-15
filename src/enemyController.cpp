#include "enemyController.h"
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

EnemyController::EnemyController()
    : speed(4.f)
{
}

void EnemyController::_ready()
{
    anim_player = get_node<godot::AnimationPlayer>("Skin/AnimationPlayer");
    anim_tree = get_node<godot::AnimationTree>("Skin/AnimationTree");
    anim_tree->set_active(true);
    move_state_machine = anim_tree->get("parameters/MoveStateMachine/playback");

    enemy_skin = get_node<godot::Node3D>("Skin");
    ray = get_node<godot::RayCast3D>("Ray");
    turn_timer = get_node<godot::Timer>("TurnTimer");
}

void EnemyController::_physics_process(double delta)
{
    if (godot::Engine::get_singleton()->is_editor_hint())
    {
        return;
    }

    godot::Vector3 velocity = get_velocity();

    // Gravity
    if (!is_on_floor())
    {
        velocity += get_gravity() * delta;
    }

    static double target_yaw = 0;
    if (ray->is_colliding()) // && turn_timer->is_stopped())
    {
        // turn_timer->start();
        // if (turn_timer->get_time_left() > 0.5)
        // {
        //     velocity.x = 0;
        //     velocity.z = 0;
        //     set_velocity(velocity);
        //     move_and_slide();
        // }
        // else
        // {
        godot::Vector3 rotation = enemy_skin->get_rotation();
        target_yaw = rotation.y + Math_PI; // flip direction
        // }
    }

    godot::Basis basis = enemy_skin->get_global_transform().basis;
    godot::Vector3 direction = basis.get_column(2).normalized();

    godot::Vector3 rotation = enemy_skin->get_rotation(); // Euler angles in radians

    rotation.y = godot::Math::lerp_angle(static_cast<double>(rotation.y), target_yaw, delta * 15);

    enemy_skin->set_rotation(rotation);

    godot::Vector3 ray_rotation = ray->get_rotation();
    ray_rotation.y = rotation.y;
    ray->set_rotation(ray_rotation);

    velocity.x = direction.x * speed;
    velocity.z = direction.z * speed;

    set_velocity(velocity);
    move_and_slide();

    if (direction != godot::Vector3())
    {
        move_state_machine->travel("Running");
    }
    else
    {
        move_state_machine->travel("idle");
    }
}

void EnemyController::_bind_methods() {}
