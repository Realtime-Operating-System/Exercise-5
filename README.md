# STM32 FreeRTOS Demonstrate access contention problems when using shared resources in a multitasking system

This project demonstrates the use of FreeRTOS on an STM32F401 microcontroller to implement priority-based preemptive multitasking. Two tasks control the blinking of a green and red LED, while a blue LED is used to indicate task interference during shared data access.

## Features
- **RTOS**: FreeRTOS with priority-based preemptive scheduling.
- **LED Control**:
  - Green LED: Controlled by a task with normal priority.
  - Red LED: Controlled by a task with above-normal priority.
  - Blue LED: Indicates collisions in shared data access.
- **Task Management**: Demonstrates task scheduling, preemption, and shared resource handling.
- **Collision Detection**: Blue LED toggles when task interference occurs.

## Hardware Requirements
- **Microcontroller**: STM32F401.
- **LEDs**:
  - Green LED: Connected to PA5.
  - Red LED: Connected to PB0.
  - Blue LED: Connected to PB7.
- **Development Environment**: STM32CubeIDE or compatible ARM GCC toolchain.

## Software Requirements
- **HAL Library**: STM32 HAL library for GPIO and system initialization.
- **FreeRTOS**: Real-Time Operating System for multitasking.

## Circuit Description
- **Green LED**: Connected to PA5 for visualizing the normal-priority task.
- **Red LED**: Connected to PB0 for visualizing the above-normal-priority task.
- **Blue LED**: Connected to PB7 for collision detection indication.
- Pull-down resistors are used for stabilization, with negative LED pins connected to ground.

## How It Works

### 1. Green LED Task (Normal Priority)
- Toggles the green LED every 500 ms.
- Represents a lower-priority task, preempted by the Red LED Task when required.

### 2. Red LED Task (Above-Normal Priority)
- Toggles the red LED every 100 ms.
- Represents a higher-priority task that preempts the Green LED Task.

### 3. Collision Detection
- Both tasks access a shared variable `start_flag`.
- If a collision occurs, the Blue LED toggles to indicate interference.

### 4. Scheduler
- FreeRTOS kernel handles task scheduling.
- The Red LED Task preempts the Green LED Task due to its higher priority.
- The Blue LED highlights any collision during shared data access.

## Steps to Run the Program

### 1. Setup STM32CubeMX
- Select the STM32F401 microcontroller.
- Enable GPIO pins for PA5, PB0, and PB7.
- Enable FreeRTOS middleware.

### 2. Configure Tasks
- Add two tasks:
  - **FlashGreenLEDTask**: Normal priority.
  - **FlashRedLEDTask**: Above-normal priority.

### 3. Generate Code
- Generate project code for STM32CubeIDE or your preferred IDE.

### 4. Build and Flash
- Build the project and flash it to the STM32F401 using an ST-Link or compatible programmer.

### 5. Observe Behavior
- The green LED toggles every 500 ms.
- The red LED toggles every 100 ms, preempting the Green LED Task.
- The blue LED toggles when a collision is detected during shared data access.

---

## Circuit Form
![rangkaian task indicator](https://github.com/user-attachments/assets/2adc1669-8599-47b5-87c8-a6995886f812)




