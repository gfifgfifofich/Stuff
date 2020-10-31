extends Area2D
func _on_Area2D_body_entered(body):
	if body.name == "gamer":
# warning-ignore:return_value_discarded
		get_tree().change_scene("res://levelz/world4.tscn")
