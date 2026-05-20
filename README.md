<h1 align="center">Num-Guess C</h1>

<p align="center">
  <strong>Windows-based number guessing game written in C.</strong><br>
  A beginner-friendly Win32 GUI project with hints, scoring, restart flow, and attempt tracking.
</p>



<p align="center">
  <img alt="GitHub Repo stars" src="https://img.shields.io/github/stars/AjaySoni-Dev/Num-Guess-C?style=social">
  <img alt="GitHub forks" src="https://img.shields.io/github/forks/AjaySoni-Dev/Num-Guess-C?style=social">
</p>

<p align="center">
  <img alt="status: learning project" src="https://img.shields.io/badge/status-learning%20project-blue">
  <img alt="stack: C / Win32" src="https://img.shields.io/badge/stack-C%20/%20Win32-informational">
  <img alt="license: MIT" src="https://img.shields.io/badge/license-MIT-green">

</p>

<p align="center">
  <a href="#overview">Overview</a> ·
  <a href="#features">Features</a> ·
  <a href="#files">Files</a> ·
  <a href="#run-locally">Run Locally</a> ·
  <a href="#limitations">Limitations</a>
</p>

---

## Overview

**Num-Guess C** is a simple desktop game built in the C language using the Windows API. The player guesses a hidden number between 1 and 10, receives high/low feedback, can request hints, and earns or loses points based on the number of attempts.

This repository is best understood as a **beginner C GUI project** rather than an advanced game engine. Its value is in showing how C logic can be connected to GUI controls, event handling, scoring, random number generation, and basic user feedback.

## Features

- Random number generation for each game round.
- Win32 window creation using `windows.h`.
- Input box for user guesses.
- Buttons for guessing, hints, and restart.
- Hint messages mapped to each target number.
- Attempt tracking.
- Score updates based on performance.
- Game over state after too many failed attempts.
- Screenshot included as `sample.png`.

## Files

| File | Purpose |
|---|---|
| `guess_game.c` | Main source code for the Windows GUI game. |
| `sample.png` | Visual sample/screenshot of the game interface. |
| `README.md` | Original project documentation. |
| `LICENSE.txt` | MIT license. |

## How It Works

```text
Application starts
        ↓
Random number is generated
        ↓
Player enters a guess
        ↓
Program compares guess with target
        ↓
Feedback is shown: too high, too low, correct, or game over
        ↓
Score and attempt state are updated
```

The project uses global game state for the secret number, attempt count, and points. GUI events are handled through the Windows message loop.

## Run Locally

This project is designed for Windows.

### Compile with GCC / MinGW

```bash
gcc guess_game.c -o num_guess.exe -mwindows
```

### Run

```bash
num_guess.exe
```

If you want console output while debugging, remove `-mwindows` during compilation.

## Limitations

- The game is Windows-only because it depends on `windows.h`.
- The code is useful for learning but not structured as a reusable game framework.
- GUI styling is basic and can be modernized.
- The game range is fixed to 1–10.
- No persistent leaderboard or saved scores are implemented.

## Recommended Improvements

- Add comments explaining the Win32 message loop.
- Separate game logic from UI code.
- Add difficulty levels.
- Add a persistent high-score file.
- Add screenshots directly in the README.

## License

This project is licensed under the MIT License.
