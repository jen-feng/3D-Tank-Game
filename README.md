# Tank Game in 3D
- Start the game and move around, try to shoot the enemy.
- Player aims to get as many points as possible. 
- Once the player collides with the tank, game is over and can be restart.
- Player loses 1 live if gets hit by the enemy bullet. Player can then restart when no more lives is left.


## How to run
- `make`

## Movement
Key | Movement

W | Forward

A | Rotate Left

S | Backwards

D | Rotate Right

Space | Fire Gun


## Camera

Key | Movement

Up | Forward

Down | Back

Right | Right

Left | Left

Shift + Up | Up

Shift + Down | Down

Shift + Right | Look Up

Shift + Left  | Look Down

## Notes
- The world is imported as an obj file which was created using Blender.
- The enemy tank's behaviour is very simple. It shoots randomly and it turns randomly. It also turns to other direction when it hits the wall.
- The game is not perfect and will have bugs when shooting and moving backwards.

## log.txt
- log.txt to shows the commit logs in github for the group

## References:
- obj loader: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
- obj file： https://free3d.com/3d-model/wwii-tank-uk-cromwell-v1--490653.html
- collision dectection: https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection

