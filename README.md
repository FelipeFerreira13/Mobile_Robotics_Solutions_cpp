# MOBILE ROBOTICS 
This Mobile Robotics project aimed at providing straightforward tools for controlling mobile robots and interfacing with peripherals. It offers simple solutions for controlling robot movement and facilitates easy integration with various hardware components such as sensors and actuators. With clear documentation and a modular architecture, developers can quickly implement these tools into their projects. 

## Install
  1. Clone the package from github :

    git clone https://github.com/FelipeFerreira13/Mobile_Robotics_Solutions_cpp.git

  2. Clean the package :

    make clean

  3. Build the package :

    make
     
  4. Run the project :

    make run


## OMNIDIRECTIONAL ROBOT
Provide a solution for controlling the movement of an omnidirectional robot.


| **Function**   | **Parameters** | **Description**                            |
|----------------|-----------------|--------------------------------------------|
| `SetPosition`    | float *x*, float *y*, float *th* | Redefine the value of x, y and th          |
| `PositionDriver` | float *desired_x*, float *desired_y*, float *desired_th* | Drives the robot to reach the desired goal |


## DIFFERENTIAL ROBOT
Provide a solution for controlling the movement of an differential robot.

| **Function**   | **Parameters** | **Description**                            |
|----------------|-----------------|--------------------------------------------|
| `SetPosition`    | float *x*, float *y*, float *th* | Redefine the value of x, y and th          |
| `PositionDriver` | float *desired_x*, float *desired_y*, float *desired_th* | Drives the robot to reach the desired goal |


## OBJECT MANAGEMENT SYSTEM
Provide a solution for controlling an oms with one dc motor for elevation, one servo motor for gripper and two limit switches.

| **Function**     | **Parameters** | **Description**                            |
|------------------|-----------------|--------------------------------------------|
| `setHeight`      | float *set_height* | Redefine the value of Height          |
| `setGripper`     | int *set*            | Set the gripper angle (GRIPPER_CLOSE, GRIPPER_OPEN, etc) |
| `reset`          | int *direction*      | Send the oms either up (direction = 1) or down (direction=-1) to reset the oms elevation |
| `OMSDriver` | float *desired_height* | Drives the oms to reach the desired height |

## HARDWARE
This project were created in a way that you can use any hardware you want, making it easy to swap from one microcontroller to another. The Hardware used as reference is called VMX pi with a Raspberry pi, but the main codes can be also used for other technologies.

### Class Analog
| **Method**     | **Parameters** | **Description**                            |
|------------------|-|-------------------------------------------|
| `Init`     | int *channel* | Initialize the peripheral |
| `GetIRDistance`     | | Return the measured distance in cm          |
| `GetRawVoltage`     | | Return the Raw analog value |

### Class digitalInput
| **Method**     | **Parameters** | **Description**                            |
|------------------|-|-------------------------------------------|
| `Init`     | int *channel* | Initialize the peripheral |
| `Get`     |      |Return the measured state of the pin|

### Class digitalOutput
| **Method**     | **Parameters** | **Description**                            |
|------------------|------|--------------------------------------------|
| `Init`     | int *channel* | Initialize the peripheral |
| `SetPinState`     | bool *state* | Return the measured state of the pin    |

### Class EncoderMotor 
| **Method**     | **Parameters** | **Description**                            |
|------------------|-|-------------------------------------------|
| `Init`     | int *encoder* | Initialize the peripheral |
| `GetEncoderCount`     |  Return the ticks count of the encoder    |

### Class PWM
| **Method**     | **Parameters** | **Description**                            |
|------------------|------|--------------------------------------------|
| `Init`     | int *channel* | Initialize the peripheral |
| `SetAngle`     | double *angle* | Defines the angle of the servo motor    |
| `GetAngle`     |  | Return the current angle of the servo motor   |

### Class PWM_Motor 
| **Method**     | **Parameters** | **Description**                            |
|------------------|-|-------------------------------------------|
| `Init`     | int *INA*, int *INB* | Initialize the peripheral |
| `SetMotorPWM`     |  Defines the motor PWM    |
