#include "playerSkin.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/method_tweener.hpp>

PlayerSkin::PlayerSkin()
    : is_attacking(false)
    , is_dodging(false)
{
}

void PlayerSkin::_ready()
{
    anim_player = get_node<godot::AnimationPlayer>("AnimationPlayer");

    anim_tree = get_node<godot::AnimationTree>("AnimationTree");
    anim_tree->set_active(true);

    move_state_machine = anim_tree->get("parameters/MoveStateMachine/playback");
    // dodge_anim = anim_tree->get("parameters/DodgeAnim/playback");

    attack_one_shot = anim_tree->get("parameters/AttackOneShot");
    attack_state_machine = anim_tree->get("parameters/AttackStateMachine/playback");
    second_attack_timer = get_node<godot::Timer>("SecondAttackTimer");

    dodge_timer = get_node<godot::Timer>("DodgeTimer");
}

void PlayerSkin::_process(double delta)
{
    godot::print_line(dodge_timer->get_time_left());
    if (is_dodging && dodge_timer->is_stopped())
    {
        is_dodging = false;
        end_dodge_anim();
    }
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

void PlayerSkin::play_dodge_anim(bool forward)
{
    dodge_timer->start();
    godot::Ref<godot::Tween> tween = get_tree()->create_tween();

    float start_value = forward ? 0.0f : 1.0f;
    float end_value = forward ? 1.0f : 0.0f;
    tween->tween_method(godot::Callable(this, "update_dodge"), start_value, end_value, 0.2f)
        ->set_trans(godot::Tween::TRANS_SINE)
        ->set_ease(godot::Tween::EASE_IN_OUT);
    is_dodging = true;
}

void PlayerSkin::end_dodge_anim()
{
    godot::Ref<godot::Tween> tween = get_tree()->create_tween();

    // float start_value = false ? 0.0f : 1.0f;
    // float end_value = false ? 1.0f : 0.0f;
    tween->tween_method(godot::Callable(this, "update_dodge"), 1.0, 0.0, 0.2f)
        ->set_trans(godot::Tween::TRANS_SINE)
        ->set_ease(godot::Tween::EASE_IN_OUT);
}

void PlayerSkin::update_dodge(float value)
{
    anim_tree->set("parameters/MoveBlend/blend_amount", value);
}

bool PlayerSkin::get_dodge_state()
{
    return is_dodging;
    //
}

void PlayerSkin::set_dodge_state(bool state)
{
    is_dodging = state;
    //
}

void PlayerSkin::dodging(bool state)
{
    godot::print_line("PlayerSkin::dodging called");
    is_dodging = state;
    //
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

    godot::ClassDB::bind_method(godot::D_METHOD("play_dodge_anim", "forward"),
                                &PlayerSkin::play_dodge_anim);
    godot::ClassDB::bind_method(godot::D_METHOD("update_dodge", "value"),
                                &PlayerSkin::update_dodge);

    godot::ClassDB::bind_method(godot::D_METHOD("dodging", "state"), &PlayerSkin::dodging);
}