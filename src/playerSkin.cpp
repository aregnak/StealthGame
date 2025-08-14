#include "playerSkin.h"

void PlayerSkin::_ready()
{
    // These should be under another class, or at least another file
    // TODO: cleanup these variables and anim functions.

    anim_player = get_node<godot::AnimationPlayer>("AnimationPlayer");

    anim_tree = get_node<godot::AnimationTree>("PlayerSkin/AnimationTree");
    anim_tree->set_active(true);
    move_state_machine = anim_tree->get("parameters/MoveStateMachine/playback");
    attack_one_shot = anim_tree->get("parameters/AttackOneShot");
}