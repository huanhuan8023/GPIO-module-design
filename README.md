# GPIO Module Simulation Project

A C-language simulation of GPIO button and LED interactions with non-blocking logic, debouncing, and callback-based design. Designed for command-line interaction with real-time feedback.

## Features

- Toggle **green LED** on/off with button 1
- Change **red LED** blink interval (500ms, 1000ms, 2000ms) with button 2
- Non-blocking loop with `Sleep(10)`
- Keyboard simulation with `GetAsyncKeyState()` (real-time response)
- Debouncing logic (50ms)
- Clean modular design: `main.c`, `led.c`, `button.c`, `gpio.h`

## How to Run

1. Make sure you have `gcc` installed 
2. Compile with:

```bash
gcc main.c led.c button.c -o gpio.exe
