#pragma once

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>
#include "cameraController.h"

class PlayerController : public godot::CharacterBody3D
{
    GDCLASS(PlayerController, godot::CharacterBody3D);

    CameraController* camera = nullptr;
    godot::Node3D* player_skin = nullptr;
    godot::AnimationPlayer* anim_player = nullptr;
    godot::AnimationTree* anim_tree = nullptr;
    godot::Ref<godot::AnimationNodeStateMachinePlayback> playback;

    const float speed;
    const float jump_velocity;

    const float ground_friction;
    const float air_friction;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _physics_process(double delta) override;

    PlayerController();
    ~PlayerController() = default;
};
