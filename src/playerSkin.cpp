#include "playerSkin.h"

#include <godot_cpp/core/class_db.hpp>

PlayerSkin::PlayerSkin()
{
    //
}

void PlayerSkin::_ready()
{
    // anim_player = get_node<godot::AnimationPlayer>("AnimationPlayer");

    // anim_tree = get_node<godot::AnimationTree>("PlayerSkin/AnimationTree");
    // anim_tree->set_active(true);
    // move_state_machine = anim_tree->get("parameters/MoveStateMachine/playback");
    // attack_one_shot = anim_tree->get("parameters/AttackOneShot");
}

void PlayerSkin::play_attack_anim()
{
    // anim_tree->set("parameters/AttackOneShot/request",
    //                (int)godot::AnimationNodeOneShot::ONE_SHOT_REQUEST_FIRE);
}

void PlayerSkin::set_move_state(godot::StringName state)
{
    // move_state_machine->travel(state); //
}

void PlayerSkin::_bind_methods() {}