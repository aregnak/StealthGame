#include "cameraController.h"

#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/ref.hpp>

CameraController::CameraController() {}

void CameraController::_input(const godot::Ref<godot::InputEvent>& event)
{
    if (event->is_class("InputEventMouseMotion"))
    {
        godot::Ref<godot::InputEventMouseMotion> mouse_event = event;
        godot::Vector3 rotation = get_rotation();

        rotation.y += mouse_event->get_relative().x;
        rotation.x += mouse_event->get_relative().y;

        set_rotation(rotation);
    }
}

void CameraController::_bind_methods() {}