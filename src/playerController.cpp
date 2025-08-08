#include "playerController.h"
#include <godot_cpp/core/math.hpp>
#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/math.hpp>

PlayerController::PlayerController()
    : speed(5.f)
    , jump_velocity(4.5f)
    , ground_friction(3.5f)
    , air_friction(1.f)
{
}

void PlayerController::_ready()
{
    camera = get_node<CameraController>("CameraController");

    player_skin = get_node<godot::Node3D>("PlayerSkin");

    anim_player = player_skin->get_node<godot::AnimationPlayer>("AnimationPlayer");

    anim_tree = get_node<godot::AnimationTree>("PlayerSkin/AnimationTree");
    anim_tree->set_active(true);
    move_state_machine = anim_tree->get("parameters/MoveStateMachine/playback");
}

void PlayerController::_physics_process(double delta)
{
    godot::Vector3 velocity = get_velocity();

    godot::Input* input = godot::Input::get_singleton();

    if (!is_on_floor())
    {
        velocity += get_gravity() * delta;
    }

    if (input->is_action_just_pressed("jump") && is_on_floor())
    {
        velocity.y = jump_velocity;
    }

    godot::Vector2 input_dir =
        input->get_vector("move_left", "move_right", "move_forward", "move_back")
            .rotated(-camera->get_global_rotation().y);

    godot::Vector3 direction =
        (get_transform().basis.xform(godot::Vector3(input_dir.x, 0, input_dir.y)).normalized());

    godot::Vector2 vel2d(velocity.x, velocity.z);

    bool is_moving = direction != godot::Vector3();

    if (is_moving)
    {
        vel2d.x += direction.x * speed;
        vel2d.y += direction.z * speed;
        vel2d = vel2d.limit_length(speed);

        velocity.x = vel2d.x;
        velocity.z = vel2d.y;

        // Get the angle to rotate on the Y-axis
        double target_yaw = godot::Math::atan2(direction.x, direction.z);

        double current_rotation = player_skin->get_rotation().y; // Euler angles in radians

        current_rotation = godot::Math::lerp_angle(current_rotation, target_yaw, delta * 15);

        godot::Vector3 good_direction;
        good_direction.y = current_rotation;

        player_skin->set_rotation(good_direction);
    }
    else
    {
        float friction = is_on_floor() ? ground_friction : air_friction;
        velocity.x = godot::Math::move_toward(velocity.x, 0, float(speed * delta * friction));
        velocity.z = godot::Math::move_toward(velocity.z, 0, float(speed * delta * friction));
    }

    // Animation logic
    if (!is_on_floor())
    {
        move_state_machine->travel("Jump_Idle");
    }
    else if (is_moving)
    {
        move_state_machine->travel("Running_A");
    }
    else
    {
        move_state_machine->travel("Idle");
    }

    //velocity = velocity.normalized();

    set_velocity(velocity);
    move_and_slide();
}

void PlayerController::_bind_methods() {}