# Rock-Paper-Scissors: RPG Edition 🎮

## About the Project
This project transforms the classic "Rock-Paper-Scissors" game into a rich, console-based RPG-lite experience. Developed in C++, it demonstrates not only core programming fundamentals but also advanced game design principles, including meta-progression, in-game economy, and dynamic difficulty scaling.

I used this project to practice feature scoping, balancing game mechanics, and structuring a multi-layered application architecture.

## Core Game Mechanics & Features
* **Dynamic Difficulty System:** AI behavior and game logic adjust based on the selected difficulty level, offering varied challenges for the player.
* **Economy & Meta-Progression:** * **Points System & Win Streaks:** Players earn currency based on performance and consecutive victories.
  * **In-Game Shop:** An interactive store system where players can spend earned points on various game-enhancing items.
* **Boss Encounters:** Special high-stakes matches featuring unique "Boss" logic, requiring strategic item use and planning.
* **Achievement System:** A tracked set of milestones that rewards player exploration and mastery of the game mechanics.

## Tech Stack & Tools
* **Language:** C++
* **Environment:** VS Code / Visual Studio 
* **Version Control:** Git / GitHub

## Project Management Approach
To handle the growing complexity of the game's features, the development was structured into iterative sprints:
1. **Core Loop:** Establishing the basic rock-paper-scissors logic and input validation.
2. **Economy Integration:** Designing the points system, win streak multipliers, and shop interface.
3. **Advanced Mechanics:** Implementing Boss fights and integrating items into the battle logic.
4. **Balancing & Polish:** Tuning item costs, Boss difficulty, and achievement criteria to ensure a rewarding player experience.

## How to Run

1. Clone the repository:
   ```bash
   git clone [https://github.com/aStyxxx/Rock-Paper-Scissors.git](https://github.com/aStyxxx/Rock-Paper-Scissors.git)
   ```

2. Navigate to the project folder:
   ```bash
   cd Rock-Paper-Scissors
   ```

3. Compile the code (using a standard C++ compiler like MSVC or GCC):
   ```bash
   g++ "Rock-Paper-Scissors (game).cpp" -o rps_game
   ```

4. Run the executable to start the adventure:
   * On Windows:
     ```cmd
     rps_game.exe
     ```
   * On macOS/Linux:
     ```bash
     ./rps_game
     ```
