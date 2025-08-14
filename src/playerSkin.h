#pragma once

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>
#include <godot_cpp/classes/animation_node_one_shot.hpp>

class PlayerSkin : public godot::Node3D
{
    GDCLASS(PlayerSkin, godot::Node3D);

    godot::AnimationPlayer* anim_player = nullptr;
    godot::AnimationTree* anim_tree = nullptr;
    godot::Ref<godot::AnimationNodeStateMachinePlayback> move_state_machine;
    godot::Ref<godot::AnimationNodeOneShot> attack_one_shot;

protected:
    static void _bind_methods();

public:
    void _ready() override;

    PlayerSkin();
    ~PlayerSkin() = default;
};
