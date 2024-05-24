# Path Memorizing Robot

This project focuses on developing a path-memorizing robot that can remember and replicate paths using sensors and microcontrollers. The robot uses a joystick for manual control and can store paths in memory to replay them later.

## Features

- **Path Memorization and Replication**
- **Joystick Control**
- **Flexible Path Programming**

## Components

- Arduino or ESP32 microcontroller
- Motor drivers
- DC motors
- Joystick module
- Power supply
- Chassis for the robot

## Path Memorization Mechanism

The robot uses a joystick to manually navigate a path. The path data is stored in arrays, allowing the robot to replicate the path later.

### Hardware Components

- **Microcontroller**: Arduino or ESP32
- **Motors**: DC motors for movement
- **Joystick**: For manual control, connected to analog pins
- **Motor Drivers**: To control the motors
- **Power Supply**: To power the components

### Functionality

- **Learning Mode**: In this mode, the robot can be manually navigated using the joystick. The movements and corresponding times are recorded and stored.
- **Execution Mode**: The robot replicates the recorded path based on the stored data.

## Installation

1. **Hardware Setup**
    - Assemble the robot chassis and mount the motors, joystick, and microcontroller.
    - Connect the joystick to the analog pins of the microcontroller.
    - Connect the motor drivers to the motors and microcontroller.
    - Ensure power supply to all components.

2. **Software Setup**
    - Upload the provided code to the microcontroller.
    - Ensure all connections and configurations are correct.

## Usage

1. **Learning Mode**
    - Power on the robot and place it at the start of the desired path.
    - Use the joystick to manually navigate the path. The robot will record the movements.
    - The recorded movements are stored in arrays.

2. **Execution Mode**
    - To replay the stored path, activate the "Replay" mode using the joystick (specific joystick position or button press).
    - The robot will navigate the path based on the stored data.

## Contributing

We welcome contributions from the community. Please feel free to submit pull requests or open issues for any bugs or feature requests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
