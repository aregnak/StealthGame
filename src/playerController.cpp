#include "playerController.h"
#include "godot_cpp/variant/vector2.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/math.hpp>

PlayerController::PlayerController()
    : speed(5.f)
    , jumpVelocity(4.5f)
    , ground_friction(3.5f)
    , air_friction(1.f)
{
}

void PlayerController::_ready()
{
    camera = get_node<CameraController>("CameraController");
    if (!camera)
    {
        godot::UtilityFunctions::printerr("CameraController not found!");
    }
}

void PlayerController::_physics_process(double delta)
{
    godot::Vector3 velocity = get_velocity();

    godot::Input* input = godot::Input::get_singleton();

    if (!is_on_floor())
    {
        velocity += get_gravity() * delta;
    }

    if (input->is_action_pressed("jump") && is_on_floor())
    {
        velocity.y = jumpVelocity;
    }

    godot::Vector2 input_dir =
        input->get_vector("move_left", "move_right", "move_forward", "move_back")
            .rotated(-camera->get_global_rotation().y);

    godot::Vector3 direction =
        (get_transform().basis.xform(godot::Vector3(input_dir.x, 0, input_dir.y)).normalized());

    godot::Vector2 vel2d(velocity.x, velocity.z);

    if (direction != godot::Vector3())
    {
        vel2d.x += direction.x * speed;
        vel2d.y += direction.z * speed;
        vel2d = vel2d.limit_length(speed);

        velocity.x = vel2d.x;
        velocity.z = vel2d.y;
    }
    else
    {
        float friction = 0;

        if (is_on_floor())
        {
            friction = ground_friction;
        }
        else
        {
            friction = air_friction;
        }

        velocity.x = godot::Math::move_toward(velocity.x, 0, float(speed * delta * friction));
        velocity.z = godot::Math::move_toward(velocity.z, 0, float(speed * delta * friction));
    }

    //velocity = velocity.normalized();

    set_velocity(velocity);
    move_and_slide();
}

void PlayerController::_bind_methods() {}