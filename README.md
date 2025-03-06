Here’s a **GitHub README** specifically for your **Connect 4** project:

---

# Connect 4 on MSP430

## Overview

This project implements the classic **Connect 4** game on an **MSP430** microcontroller using an **8x8 LED matrix**. Two players take turns dropping pieces into columns, aiming to connect four pieces in a row **horizontally, vertically, or diagonally**. The game features real-time LED updates and win detection.

## Features

- **Two-player mode** (Red vs. Green)
- ![Two Player Mode](connect%204%20images/two-player-mode.jpg)
- **LED matrix display** for real-time game updates
- **Win detection** (horizontal, vertical, and diagonal)
- **UART communication** with PUTTY for game tracking
- **Button-controlled gameplay**
- **Game reset functionality** for replaying rounds

## Hardware Requirements

- **MSP430 Microcontroller**
- **8x8 LED Matrix**
- **Push Buttons** for player input
- **UART interface** for debugging via PUTTY

## How It Works

1. The game initializes the **LED matrix** and sets up the playing field.
2. Players take turns selecting a column using **push buttons** on the MSP430.
3. The program determines the lowest available row in the chosen column and places the player's piece.
4. The **game checks for a win** condition after each move:
   - Four consecutive pieces in a row, column, or diagonal.
5. The winner is displayed by filling the matrix with their color.
   ![Red Wins](connect%204%20images/red-wins.jpg) ![Green Wins](connect%204%20images/green-wins.jpg)
7. If the board fills up without a winner, it’s a **draw**.
   ![Draw](connect%204%20images/two-player-mode.jpg)
9. The game can be restarted to play again.

## Code Structure

- **`main.c`** – Initializes hardware, manages game loop.
- **`mtxdisp.c / mtxdisp.h`** – Handles LED matrix operations.
- **`playermove.c / playermove.h`** – Manages player input and move placement.
- **`winner.c / winner.h`** – Implements win detection logic.

## Compilation & Deployment

1. Compile the code using an MSP430-compatible compiler.
2. Upload the firmware to the MSP430 microcontroller.
3. Connect the LED matrix and buttons as per the circuit design.
4. Open **PUTTY** (or another terminal) to monitor game progress via **UART**.

![Rough Diagram of Hardware](connect%204%20images/mechanical-diagram.png)

## Author
**loldwyer**  
