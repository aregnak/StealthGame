#include "enemyController.h"
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

EnemyController::EnemyController()
    : run_speed(4.8f)
    , walk_speed(1.f)
    , player_in_area(false)
    , player_seen(false)
{
}

void EnemyController::_ready()
{
    godot::Array player = get_tree()->get_nodes_in_group("Player");
    if (player.size() > 0)
    {
        player_node = Object::cast_to<PlayerController>(player[0]);
    }

    anim_player = get_node<godot::AnimationPlayer>("Skin/AnimationPlayer");
    anim_tree = get_node<godot::AnimationTree>("Skin/AnimationTree");
    anim_tree->set_active(true);
    move_state_machine = anim_tree->get("parameters/MoveStateMachine/playback");

    enemy_skin = get_node<godot::Node3D>("Skin");
    ray = get_node<godot::RayCast3D>("WallRay");
    player_ray = get_node<godot::RayCast3D>("PlayerRay");
    turn_timer = get_node<godot::Timer>("TurnTimer");
    alert_timer = get_node<godot::Timer>("AlertTimer");

    fov = get_node<godot::Area3D>("Area3D");
    fov->connect("body_entered", godot::Callable(this, "_on_body_entered"));
    fov->connect("body_exited", godot::Callable(this, "_on_body_exited"));

    state = State::PATROL;
}

void EnemyController::_physics_process(double delta)
{
    if (godot::Engine::get_singleton()->is_editor_hint())
    {
        return;
    }

    godot::Vector3 velocity = get_velocity();

    // Gravity
    if (!is_on_floor())
    {
        velocity += get_gravity() * delta;
    }

    godot::Vector3 direction;

    if (state == State::IDLE)
    {
        if (turn_timer->is_stopped())
        {
            state = State::PATROL;
        }

        velocity.x = 0;
        velocity.z = 0;
    }

    else if (state == State::PATROL)
    {
        if (ray->is_colliding() && turn_timer->is_stopped())
        {
            turn_timer->start();

            godot::Vector3 rotation = enemy_skin->get_rotation();
            target_yaw = rotation.y + Math_PI; // flip direction

            state = State::IDLE;
        }

        godot::Basis basis = enemy_skin->get_global_transform().basis;
        direction = basis.get_column(2).normalized();

        if (player_in_area)
        {
            // Checks if the player is in plain view
            player_pos = player_node->get_global_position();
            godot::Vector3 to_player = (player_pos - enemy_skin->get_global_position());

            player_ray->set_target_position(to_player);

            if (player_ray->is_colliding())
            {
                godot::Object* collider = player_ray->get_collider();

                if (collider == player_node)
                {
                    player_seen = false;
                    state = State::ALERT;
                }
            }
        }

        velocity.x = direction.x * walk_speed;
        velocity.z = direction.z * walk_speed;
    }
    else if (state == State::ALERT)
    {
        player_pos = player_node->get_global_position();
        godot::Vector3 to_player = (player_pos - enemy_skin->get_global_position());

        player_ray->set_target_position(to_player);

        if (player_ray->is_colliding())
        {
            godot::Object* collider = player_ray->get_collider();

            if (collider == player_node && player_in_area)
            {
                velocity.x = 0;
                velocity.z = 0;

                player_pos = player_node->get_global_position();
                godot::Vector3 to_player =
                    (player_pos - enemy_skin->get_global_position()).normalized();
                target_yaw = godot::Math::atan2(to_player.z, -to_player.x);

                // While player is in plain view
                if (!player_seen)
                {
                    alert_timer->start();
                    player_seen = true;
                }
                else
                {
                    if (alert_timer->is_stopped())
                    {
                        state = State::CHASE;
                        player_seen = false;
                    }
                }
            }
            else
            {
                state = State::PATROL;
            }
        }
    }
    else if (state == State::CHASE)
    {
        player_pos = player_node->get_global_position();
        godot::Vector3 direction = (player_pos - enemy_skin->get_global_position()).normalized();
        godot::Vector3 to_player = (player_pos - enemy_skin->get_global_position()).normalized();
        target_yaw = godot::Math::atan2(to_player.z, -to_player.x);

        velocity.x = direction.x * walk_speed;
        velocity.z = direction.z * walk_speed;
    }

    godot::Vector3 rotation = enemy_skin->get_rotation(); // Euler angles in radians

    rotation.y = godot::Math::lerp_angle(static_cast<double>(rotation.y), target_yaw, delta * 5);

    enemy_skin->set_rotation(rotation);

    godot::Vector3 rot_buffer = ray->get_rotation();
    rot_buffer.y = rotation.y;
    ray->set_rotation(rot_buffer);

    rot_buffer = fov->get_rotation();
    rot_buffer.y = rotation.y;
    fov->set_rotation(rot_buffer);

    set_velocity(velocity);
    move_and_slide();

    // Animation handling
    if (state == State::IDLE)
    {
        move_state_machine->travel("Idle");
    }
    else if (state == State::PATROL)
    {
        move_state_machine->travel("Walking");
    }
    else if (state == State::ALERT)
    {
        move_state_machine->travel("Alert");
    }
}

void EnemyController::_on_body_entered(godot::Node* body)
{
    godot::print_line("in area");
    player_in_area = true;
}

void EnemyController::_on_body_exited(godot::Node* body)
{
    godot::print_line("out area");
    player_in_area = false;
}

void EnemyController::_bind_methods()
{
    godot::ClassDB::bind_method(godot::D_METHOD("_on_body_entered", "body"),
                                &EnemyController::_on_body_entered);
    godot::ClassDB::bind_method(godot::D_METHOD("_on_body_exited", "body"),
                                &EnemyController::_on_body_exited);
}
