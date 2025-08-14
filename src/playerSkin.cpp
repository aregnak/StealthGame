#include "playerSkin.h"

#include <godot_cpp/core/class_db.hpp>

PlayerSkin::PlayerSkin()
    : is_attacking(false)
{
    //
}

void PlayerSkin::_ready()
{
    anim_player = get_node<godot::AnimationPlayer>("AnimationPlayer");

    anim_tree = get_node<godot::AnimationTree>("AnimationTree");
    anim_tree->set_active(true);

    move_state_machine = anim_tree->get("parameters/MoveStateMachine/playback");

    attack_one_shot = anim_tree->get("parameters/AttackOneShot");
    attack_state_machine = anim_tree->get("parameters/AttackStateMachine/playback");
    second_attack_timer = get_node<godot::Timer>("SecondAttackTimer");
}

void PlayerSkin::play_attack_anim()
{
    if (!is_attacking)
    {
        if (second_attack_timer->get_time_left() > 0)
        {
            attack_state_machine->travel("HSlice");
        }
        else
        {
            attack_state_machine->travel("Chop");
        }
        anim_tree->set("parameters/AttackOneShot/request",
                       (int)godot::AnimationNodeOneShot::ONE_SHOT_REQUEST_FIRE);
    }
}

void PlayerSkin::set_move_state(godot::StringName state)
{
    move_state_machine->travel(state); //
}

void PlayerSkin::attacking(bool state)
{
    is_attacking = state;
    //
}

void PlayerSkin::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("play_attack_anim"), &PlayerSkin::play_attack_anim);
    godot::ClassDB::bind_method(godot::D_METHOD("set_move_state", "state"),
                                &PlayerSkin::set_move_state);
    godot::ClassDB::bind_method(godot::D_METHOD("attacking", "state"), &PlayerSkin::attacking);
}