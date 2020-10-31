extends KinematicBody2D

const WALK_FORCE = 1500
const WALK_MAX_SPEED = 1000
const STOP_FORCE = 1500
const JUMP_SPEED = 800

var velocity = Vector2()

onready var gravity = ProjectSettings.get_setting("physics/2d/default_gravity")

func _physics_process(delta):
	var walk = WALK_FORCE * (Input.get_action_strength("move_right") - Input.get_action_strength("move_left"))# Slow down the player if they're not trying to move.
	if abs(walk) < WALK_FORCE * 0.2:
		velocity.x = move_toward(velocity.x, 0, STOP_FORCE * delta)
	else:
		
		velocity.x += walk * delta
	velocity.x = clamp(velocity.x, -WALK_MAX_SPEED, WALK_MAX_SPEED)

	velocity.y += 15*gravity * delta

	velocity = move_and_slide_with_snap(velocity, Vector2.DOWN, Vector2.UP)

	if is_on_floor() and Input.is_action_just_pressed("jump") and not Input.is_action_pressed("down"):
		velocity.y = -JUMP_SPEED
	if is_on_wall() and Input.is_action_just_pressed("jump") and not Input.is_action_pressed("down"):
		velocity.y = -JUMP_SPEED


	if is_on_wall() and Input.is_action_pressed("move_right") and Input.is_action_just_pressed("jump") and not Input.is_action_pressed("down"):
# warning-ignore:integer_division
		velocity.x = -WALK_MAX_SPEED/2
	if is_on_wall() and Input.is_action_pressed("move_left") and Input.is_action_just_pressed("jump") and not Input.is_action_pressed("down"):
# warning-ignore:integer_division
		velocity.x = WALK_MAX_SPEED/2
	if is_on_wall() and Input.is_action_pressed("move_right") and Input.is_action_just_pressed("jump") and Input.is_action_pressed("down"):
		velocity.x = -WALK_MAX_SPEED
		velocity.y = -JUMP_SPEED*0.1
	if is_on_wall() and Input.is_action_pressed("move_left") and Input.is_action_just_pressed("jump") and Input.is_action_pressed("down"):
		velocity.y = -JUMP_SPEED*0.1
		velocity.x = WALK_MAX_SPEED
	if is_on_wall() and velocity.y >= 200:
		velocity.y=400
	if is_on_floor() and Input.is_action_pressed("move_right") and Input.is_action_just_pressed("jump") and Input.is_action_pressed("down"):
		velocity.y = -JUMP_SPEED*0.3
		velocity.x = WALK_MAX_SPEED*1.5
	if is_on_floor() and Input.is_action_pressed("move_left") and Input.is_action_just_pressed("jump") and Input.is_action_pressed("down"):
		velocity.y = -JUMP_SPEED*0.3
		velocity.x = -WALK_MAX_SPEED*1.5
	if not is_on_floor() and velocity.y>1500:
		velocity.y = 1500

