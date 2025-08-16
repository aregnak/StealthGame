#include "enemyController.h"
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

EnemyController::EnemyController()
    : run_speed(4.8f)
    , walk_speed(1.f)
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

    state = State::PATROL;
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

    godot::Vector3 direction;

    if (state == State::IDLE && turn_timer->is_stopped())
    {
        state = State::PATROL;
    }

    if (state == State::PATROL)
    {
        if (ray->is_colliding() && turn_timer->is_stopped())
        {
            turn_timer->start();

            godot::Vector3 rotation = enemy_skin->get_rotation();
            target_yaw = rotation.y + Math_PI; // flip direction

            state = State::IDLE;
            velocity.x = 0;
            velocity.z = 0;
            set_velocity(velocity);
            move_and_slide();
        }

        godot::Basis basis = enemy_skin->get_global_transform().basis;
        direction = basis.get_column(2).normalized();

        float current_speed;

        if (state == State::IDLE)
        {
            current_speed = 0;
        }
        else if (state == State::PATROL)
        {
            current_speed = walk_speed;
        }
        else if (state == State::CHASE)
        {
            current_speed = run_speed;
        }

        velocity.x = direction.x * current_speed;
        velocity.z = direction.z * current_speed;
    }

    godot::Vector3 rotation = enemy_skin->get_rotation(); // Euler angles in radians

    rotation.y = godot::Math::lerp_angle(static_cast<double>(rotation.y), target_yaw, delta * 5);

    enemy_skin->set_rotation(rotation);

    godot::Vector3 ray_rotation = ray->get_rotation();
    ray_rotation.y = rotation.y;
    ray->set_rotation(ray_rotation);
    set_velocity(velocity);
    move_and_slide();

    // Animation handling
    if (state == State::IDLE)
    {
        move_state_machine->travel("Idle");
    }
    else if (state == State::PATROL)
    {
        move_state_machine->travel("Walking");
    }
}

void EnemyController::_bind_methods() {}
