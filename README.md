<h1 align="center">Num-Guess-C</h1>

<p align="center">
  <strong>Native Win32 number-guessing game written in C.</strong><br>
  A small desktop programming project demonstrating window creation, event-driven controls, validation, hints, scoring, restart state, and the Windows message loop.
</p>

<p align="center">
  <img alt="Status" src="https://img.shields.io/badge/status-learning%20project-blue">
  <img alt="Language" src="https://img.shields.io/badge/language-C-00599C">
  <img alt="Platform" src="https://img.shields.io/badge/platform-Windows-lightgrey">
  <img alt="GUI" src="https://img.shields.io/badge/GUI-Win32-purple">
  <img alt="License" src="https://img.shields.io/badge/license-MIT-green">
</p>

<p align="center">
  <a href="#overview">Overview</a> ·
  <a href="#what-this-repo-contains">Contents</a> ·
  <a href="#features">Features</a> ·
  <a href="#game-flow">Game Flow</a> ·
  <a href="#build-and-run">Build & Run</a>
</p>

---

## Overview

**Num-Guess-C** is a Windows desktop guessing game implemented directly with the Win32 API.

Each round selects a random integer from **1 to 10**. The player has up to **five valid attempts**. The application reports whether each guess is too high or too low, exposes a hint after repeated attempts, awards points for a successful guess, subtracts points after a failed round, and allows the user to restart.

---

## What This Repo Contains

| File | Purpose |
|---|---|
| <code>guess_game.c</code> | Complete Win32 GUI and game logic. |
| <code>sample.png</code> | Screenshot / visual sample. |
| <code>README.md</code> | Project documentation. |
| <code>LICENSE.txt</code> | MIT License. |

---

## Features

| Area | Current Implementation |
|---|---|
| Random target | <code>rand() % 10 + 1</code> after seeding with current time. |
| GUI | Native Win32 window and child controls through <code>windows.h</code>. |
| Guess validation | Accepts only values from 1 through 10; invalid values do not consume an attempt. |
| Feedback | Too-high, too-low, success, and game-over messages. |
| Attempts | Maximum of five valid guesses per round. |
| Hints | Number-specific hint table; hint button becomes available after repeated attempts. |
| Scoring | Earlier success earns more points; an exhausted round subtracts two points. |
| Session score | Total points remain in memory while the process stays open. |
| Restart | Resets the target and round state while retaining total session points. |

---

## Game Flow

~~~text
Launch application
   ↓
Random number 1–10 is generated
   ↓
Enter a guess
   ↓
Validate range
   ↓
Compare with target
   ├── too low
   ├── too high
   └── correct
   ↓
Update attempts / score
   ↓
Show hint when eligible
   ↓
Restart for another round
~~~

---

## Architecture

~~~text
WinMain
   ↓
RegisterClassW
   ↓
CreateWindowW
   ↓
WM_CREATE → AddControls
   ↓
Message loop
   ↓
WindowProcedure
   ├── Guess button
   ├── Hint button
   ├── Restart button
   └── WM_DESTROY
~~~

Game state is stored in process-level variables for the selected number, attempts, round points, and total points.

---

## Repository Structure

~~~text
Num-Guess-C/
├── guess_game.c
├── sample.png
├── README.md
└── LICENSE.txt
~~~

---

## Build and Run

The project is Windows-specific because it uses <code>windows.h</code>.

~~~bash
gcc guess_game.c -o num_guess.exe -mwindows
~~~

Run:

~~~bash
num_guess.exe
~~~

A normal console-linked build can be used while debugging by omitting <code>-mwindows</code>.

---

## Validation & Current Maturity

This repository is a **small educational GUI project**. It demonstrates event-driven C programming, Win32 controls, stateful game logic, and basic input validation.

It does not include automated tests, cross-platform abstractions, persistent scores, difficulty modes, or a reusable game engine.

---

## License

Released under the **MIT License**. See <code>LICENSE.txt</code>.
