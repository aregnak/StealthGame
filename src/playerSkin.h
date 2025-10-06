#pragma once

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/animation_node.hpp>
#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>
#include <godot_cpp/classes/animation_node_one_shot.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

class PlayerSkin : public godot::Node3D
{
    GDCLASS(PlayerSkin, godot::Node3D);

    godot::AnimationPlayer* anim_player = nullptr;
    godot::AnimationTree* anim_tree = nullptr;
    godot::Ref<godot::AnimationNodeStateMachinePlayback> move_state_machine;
    godot::Ref<godot::AnimationNodeStateMachinePlayback> attack_state_machine;
    godot::Ref<godot::AnimationNodeOneShot> attack_one_shot;
    godot::Timer* second_attack_timer = nullptr;
    godot::Timer* dodge_timer = nullptr;
    godot::SceneTree* tree;

    bool is_attacking;
    bool is_dodging;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _process(double delta) override;

    void play_attack_anim();
    void play_dodge_anim(bool forward);
    void update_dodge(float value);
    bool get_dodge_state();
    void set_move_state(godot::StringName state);

    void attacking(bool state);
    void dodging(bool state);

    PlayerSkin();
    ~PlayerSkin() = default;
};
