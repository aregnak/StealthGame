#pragma once

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>

class CameraController : public godot::Node3D
{
    GDCLASS(CameraController, godot::Node3D);

    float cameraSens;
    bool mouse_visible;

protected:
    static void _bind_methods();

public:
    void _input(const godot::Ref<godot::InputEvent>& event) override;

    void set_sens(float p_value);
    float get_sens();

    CameraController();
    ~CameraController() = default;
};