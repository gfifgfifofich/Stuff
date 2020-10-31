extends Area2D
func _on_Area2D_body_entered(body):
	if body.name == "gamer":
		get_tree().change_scene("res://levelz/world.tscn")
