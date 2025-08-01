using Godot;
using System;

public partial class Player : CharacterBody3D
{
	private GodotObject _controller;

	public override void _Ready()
	{
		var gdextScript = GD.Load<Script>("res://../src/playerController.h");

		if (gdextScript != null)
		{
			_controller = (GodotObject)gdextScript.Call("new");
			GD.Print("Controller loaded successfully.");
		}
		else
		{
			GD.PrintErr("Failed to load playerController.gdextension.");
		}
	}

	public override void _PhysicsProcess(double delta)
	{
		if (_controller == null)
		{
			GD.PrintErr("Controller is null! Did it fail to load?");
			return;
		}

		Vector2 inputVector = Input.GetVector("move_left", "move_right", "move_forward", "move_back");
		Vector3 direction = (Vector3)_controller.Call("calculate_movement", inputVector);

		Velocity = direction;
		MoveAndSlide();
	}
}
