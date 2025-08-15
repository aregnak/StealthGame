#pragma once

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>
#include <godot_cpp/classes/animation_node_one_shot.hpp>
#include <godot_cpp/classes/timer.hpp>

class EnemyController : public godot::CharacterBody3D
{
    GDCLASS(EnemyController, godot::CharacterBody3D);

    godot::AnimationPlayer* anim_player = nullptr;
    godot::AnimationTree* anim_tree = nullptr;
    godot::Ref<godot::AnimationNodeStateMachinePlayback> move_state_machine;

    godot::Node3D* enemy_skin = nullptr;
    godot::RayCast3D* ray = nullptr;
    godot::Timer* turn_timer = nullptr;

    const float speed;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void _physics_process(double delta) override;

    EnemyController();
    ~EnemyController() = default;
};
