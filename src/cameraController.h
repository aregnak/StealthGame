#pragma once

#include <godot_cpp/classes/spring_arm3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>

class CameraController : public godot::SpringArm3D
{
    GDCLASS(CameraController, godot::SpringArm3D);

    float cameraSens;
    bool mouse_captured;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _input(const godot::Ref<godot::InputEvent>& event) override;

    void set_mouse_mode();
    void set_sens(float p_value);
    float get_sens();

    CameraController();
    ~CameraController() = default;
};