#include "cameraController.h"

#include <godot_cpp/core/class_db.hpp>
#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/ref.hpp>

CameraController::CameraController()
    : cameraSens(0.01)
{
}

void CameraController::_input(const godot::Ref<godot::InputEvent>& event)
{
    if (event->is_class("InputEventMouseMotion"))
    {
        godot::Ref<godot::InputEventMouseMotion> mouse_event = event;
        godot::Vector3 rotation = get_rotation();

        rotation.y += mouse_event->get_relative().x * cameraSens;
        rotation.x += mouse_event->get_relative().y * cameraSens;
        set_rotation(rotation);
    }
}

void CameraController::set_sens(float p_value) { cameraSens = p_value; }
float CameraController::get_sens() { return cameraSens; }

void CameraController::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("set_sens", "value"), &CameraController::set_sens);
    godot::ClassDB::bind_method(godot::D_METHOD("get_sens"), &CameraController::get_sens);

    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "camera_sens"), "set_sens", "get_sens");
}