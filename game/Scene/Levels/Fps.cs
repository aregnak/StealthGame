using Godot;
using System;

public partial class Fps : Label
{
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
		// Black fps counter for now
		AddThemeColorOverride("font_color", new Color(0f, 0f, 0f));
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
		var FPS = Engine.GetFramesPerSecond();

		Text = "FPS: " + FPS.ToString();
	}
}
