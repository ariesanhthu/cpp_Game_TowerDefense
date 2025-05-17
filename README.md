# Tower Defense Game (C++ OOP Project)

This is a C++ tower defense game developed as a final project for the Object-Oriented Programming (OOP) course at the University of Science, VNU-HCM (HCMUS). The project showcases principles of object-oriented design, including encapsulation, inheritance, and polymorphism, applied in a game development context.

## 🎮 Game Overview

In this game, players strategically place towers to defend against waves of enemies following a predetermined path. Each tower type has unique attributes, and enemies vary in speed and health. The objective is to prevent enemies from reaching the end of the path by effectively utilizing different tower types and placements.

## 🧱 Project Structure

The project is organized into several modules to promote modularity and maintainability:

* **Assets/**: Contains game assets such as images and sounds.
* **Entities/**: Defines core game entities like towers and enemies.
* **Game/**: Manages the main game loop and overall game state.
* **Graphics/**: Handles rendering and graphical user interface components.
* **Manager/**: Includes classes responsible for managing game resources and events.
* **Storage/**: Manages data storage, including saving and loading game states.
* **User/**: Handles user input and interactions.([Wikipedia][1])

Key files include:

* `TowerDefense.cpp` / `TowerDefense.h`: Main application entry point and core logic.
* `game.cpp` / `game.h`: Implements the game loop and game state management.
* `Utils.cpp` / `Utils.h`: Provides utility functions used throughout the project.

## 🛠️ Features

* Multiple tower types with distinct behaviors and upgrade paths.
* Varied enemy types with different attributes.
* Graphical user interface for interactive gameplay.
* Sound effects to enhance the gaming experience.
* Save and load functionality for game states.([Microsoft Learn][2])

## 🖼️ UI and Image Handling

The game's graphical user interface (GUI) is built using the Win32 API. Images are loaded and displayed using the `LoadImage` function, which allows for the inclusion of bitmaps and other image formats in the application. This approach enables the integration of custom graphics for towers, enemies, and backgrounds, enhancing the visual appeal of the game.

For example, to load a bitmap image from a file:

```cpp
HBITMAP hBitmap = (HBITMAP)LoadImage(
    NULL,
    L"assets\\tower.bmp",
    IMAGE_BITMAP,
    0,
    0,
    LR_LOADFROMFILE
);
```



This method ensures that images are efficiently loaded and managed within the Win32 application framework.

## 🚀 Getting Started

### Prerequisites

* Microsoft Visual Studio with C++ development tools.
* Windows operating system.

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/ariesanhthu/cpp_Game_TowerDefense.git
   ```



2. Open the `TowerDefense.sln` solution file in Visual Studio.

3. Build the solution to compile the project.

4. Run the application from Visual Studio or execute the generated `.exe` file.

## 👥 Contributors

* **Instructor**: Trương Toàn Thịnh
* **Team Leader**: Nguyễn Anh Thư
* **Team Members**:

  * Trần Hải Đức
  * Bùi Quang Hưng

## 📄 License

This project is licensed under the MIT License. See the [LICENSE.txt](LICENSE.txt) file for details.

---

Feel free to customize this README further by adding specific details about gameplay mechanics, controls, or any other information that would be helpful to users and contributors.

[1]: https://en.wikipedia.org/wiki/Direct2D?utm_source=chatgpt.com "Direct2D"
[2]: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadimagea?utm_source=chatgpt.com "LoadImageA function (winuser.h) - Win32 apps - Learn Microsoft"
