#include "cameraController.h"

#include <godot_cpp/core/class_db.hpp>
#include "godot_cpp/core/math.hpp"
#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/godot.hpp>

CameraController::CameraController()
    : cameraSens(0.003)
    , mouse_captured(false)
{
}

void CameraController::_ready()
{
    set_mouse_mode();
    //
}

void CameraController::_input(const godot::Ref<godot::InputEvent>& event)
{
    // Mouse look controls
    if (event->is_class("InputEventMouseMotion"))
    {
        if (!mouse_captured)
        {
            godot::Ref<godot::InputEventMouseMotion> mouse_event = event;
            godot::Vector3 rotation = get_rotation();

            rotation.y -= mouse_event->get_relative().x * cameraSens;
            rotation.x -= mouse_event->get_relative().y * cameraSens;
            rotation.x = godot::CLAMP(rotation.x, -0.4, 0.2);
            set_rotation(rotation);
        }
    }

    // Mouse mode controls
    if (event->is_class("InputEventKey"))
    {
        godot::Ref<godot::InputEventKey> inputKey = event;
        if (inputKey->is_action_pressed("mouse_mode"))
        {
            set_mouse_mode();
        }
    }
}

void CameraController::set_mouse_mode()
{
    godot::Input* input = godot::Input::get_singleton();
    if (mouse_captured)
    {
        mouse_captured = false;
        input->set_mouse_mode(input->MOUSE_MODE_CAPTURED);
    }
    else if (!mouse_captured)
    {
        mouse_captured = true;
        input->set_mouse_mode(input->MOUSE_MODE_VISIBLE);
    }
}

void CameraController::set_sens(float p_value) { cameraSens = p_value; }
float CameraController::get_sens() { return cameraSens; }

void CameraController::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("ready"), &CameraController::_ready);
    godot::ClassDB::bind_method(godot::D_METHOD("set_sens", "value"), &CameraController::set_sens);
    godot::ClassDB::bind_method(godot::D_METHOD("get_sens"), &CameraController::get_sens);

    ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "camera_sens"), "set_sens", "get_sens");
}