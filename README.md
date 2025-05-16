# GPIO Module Simulation Project

A simulated **GPIO module for microcontroller** design in C language, targeting x86_64 systems (Windows). 

## Features

- Toggle **green LED** on/off with button 1
- Change **red LED** blink interval (500ms, 1000ms, 2000ms) with button 2
- Support push button 
    - a. Support debounce
    - b. active low and active high
    - c. edge trigger
- Support LED
    - a. active low and active high
    - b. constant on/off
    - c. support fast blink and slow blink
- Non-block control without using interrupts
- Keyboard simulates GPIO input 
- 'printf()' simulates GPIO state change

## Project Structure

```text
GPIO-module-design/
├── main.c          # Application entry point
├── led.c           # LED control (toggle, blink)
├── button.c        # Debounce, edge/level trigger
├── gpio.h          # Shared types/enums/declarations
├── .vscode/        # Optional: build tasks config
├── .gitignore
└── README.md

