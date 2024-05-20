# MOBILE ROBOTICS 
This Mobile Robotics project aimed at providing straightforward tools for controlling mobile robots and interfacing with peripherals. It offers simple solutions for controlling robot movement and facilitates easy integration with various hardware components such as sensors and actuators. With clear documentation and a modular architecture, developers can quickly implement these tools into their projects. 

## Install
  1. Clone the package from github :

    git clone https://github.com/FelipeFerreira13/Mobile_Robot_VMXpi_HAL.git

  2. Build the package :

    make
     
  3. Run the project :

    make run

## OMNIDIRECTIONAL ROBOT
Provide a solution for controlling the movement of an omnidirectional robot.


| **Function**   | **return type** | **Description**                            |
|----------------|-----------------|--------------------------------------------|
| `SetPosition`    | void            | Redefine the value of x, y and th          |
| `PositionDriver` | void            | Drives the robot to reach the desired goal |

## DIFFERENTIAL ROBOT
Provide a solution for controlling the movement of an differential robot.


| **Function**   | **return type** | **Description**                            |
|----------------|-----------------|--------------------------------------------|
| `SetPosition`    | void            | Redefine the value of x, y and th          |
| `PositionDriver` | void            | Drives the robot to reach the desired goal |

## OBJECT MANAGEMENT SYSTEM
Provide a solution for controlling an oms with one dc motor for elevation, one servo motor for gripper and two limit switches.

| **Function**     | **return type** | **Description**                            |
|------------------|-----------------|--------------------------------------------|
| `setHeight`      | void            | Redefine the value of Height          |
| `setGripper`     | void            | Set the gripper angle          |
| `reset`          | void            | Send the oms either up (direction = 1) or down (direction=-1) to reset the oms elevation |
| `PositionDriver` | void            | Drives the oms to reach the desired height |
