#include "playerController.h"
#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/input.hpp>

PlayerController::PlayerController()
    : speed(5.f)
    , jumpVelocity(4.5f)
{
}

void PlayerController::_physics_process(double delta)
{
    godot::Vector3 velocity = godot::Vector3();

    godot::Input* input = godot::Input::get_singleton();

    if (!is_on_floor())
    {
        velocity += get_gravity() * delta;
    }

    if (input->is_action_pressed("move_forward"))
    {
        velocity.z -= 1;
    }
    if (input->is_action_pressed("move_back"))
    {
        velocity.z += 1;
    }
    if (input->is_action_pressed("move_left"))
    {
        velocity.x -= 1;
    }
    if (input->is_action_pressed("move_right"))
    {
        velocity.x += 1;
    }
    if (input->is_action_pressed("jump"))
    {
        velocity.y += jumpVelocity;
    }

    velocity = velocity.normalized() * speed;

    set_velocity(velocity);
    move_and_slide();
}

void PlayerController::_bind_methods() {}