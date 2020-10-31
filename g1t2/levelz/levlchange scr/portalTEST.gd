extends Area2D
func _on_Area2D_body_entered(body):
	if body.name == "gamer":
# warning-ignore:return_value_discarded
		get_tree().change_scene("res://levelz/TEST.tscn")


func _on_Area2D2_body_entered(body):
	pass # Replace with function body.
