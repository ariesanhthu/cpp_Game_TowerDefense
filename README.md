# 🎯 Tower Defense Game (C++ OOP Project with WinAPI & Design Patterns)

This is a C++ tower defense game developed as a final project for the Object-Oriented Programming (OOP) course at the University of Science, VNU-HCM (HCMUS). The project demonstrates the use of **Object-Oriented Design Principles** along with classic **design patterns**, and utilizes **WinAPI32** for UI rendering and image handling.

---

## 🎮 Game Overview

Players must place towers strategically to stop waves of enemies from reaching their destination along a predefined path. Each tower and enemy type features unique behaviors and attributes, requiring the player to think critically and adapt their strategy.

![Main screen](https://github.com/ariesanhthu/cpp_Game_TowerDefense/blob/main/Assets/MainScreen.PNG)

---

## 🧱 Architecture & Design Patterns

This project was built following **modular architecture** and applies common **design patterns** including:

- **Singleton** – for central game state management and configuration  
- **Factory Method** – to create different types of towers and enemies  
- **Strategy** – for defining tower attack behaviors  
- **Observer** – for UI updates and game state notifications  
- **MVC Pattern** – separating game logic, rendering, and user input  

---

## 📁 Project Structure

```

cpp\_Game\_TowerDefense/
├── Assets/        # Images, sounds
├── Entities/      # Tower, Enemy base classes & derived types
├── Game/          # Main game controller and loop
├── Graphics/      # UI rendering with WinAPI
├── Manager/       # GameManager, ResourceManager, etc.
├── Storage/       # Save/load game state
├── User/          # Input handling, player interaction
├── TowerDefense.sln
└── ...

````

### 🔑 Key Files

- `TowerDefense.cpp / .h` – Entry point, application control  
- `game.cpp / .h` – Main game loop, scene control  
- `Utils.cpp / .h` – Utility functions (math, file I/O, etc.)  

---

## 🖼️ UI and Image Rendering (WinAPI32)

The graphical user interface (GUI) was implemented using **Win32 API**, offering direct control over Windows messaging, rendering, and user input.

Images are loaded using `LoadImage` from the WinAPI, allowing flexible integration of `.bmp` files into buttons, backgrounds, and character sprites.

```cpp
HBITMAP hBitmap = (HBITMAP)LoadImage(
    NULL,
    L"assets\\tower.bmp",
    IMAGE_BITMAP,
    0,
    0,
    LR_LOADFROMFILE
);
````

This method ensures smooth and lightweight image loading in the Windows environment.

---

## 🛠️ Game Features

* 🏰 Multiple tower types with unique attack strategies
* 👾 Varied enemy types (flying, fast, tanky)
* 🎨 Custom WinAPI-rendered UI with image loading
* 🔊 Integrated sound effects
* 💾 Save/load game state functionality
* 🧠 Applied OOP and Design Pattern principles

---

## 🚀 Getting Started

### ✅ Prerequisites

* Windows OS
* [Microsoft Visual Studio](https://visualstudio.microsoft.com/) with C++ toolset
* Basic knowledge of C++ and Windows programming

### ⚙️ Setup

```bash
git clone https://github.com/ariesanhthu/cpp_Game_TowerDefense.git
cd cpp_Game_TowerDefense
```

1. Open `TowerDefense.sln` with Visual Studio
2. Build the solution
3. Run the game from Visual Studio or execute the `.exe` from the `Debug/Release` folder

---

## 👥 Contributors

* **Instructor**: Trương Toàn Thịnh
* **Team Leader**: Nguyễn Anh Thư
* **Members**:

  * Trần Hải Đức
  * Bùi Quang Hùng

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

---

## 📚 References

* Microsoft. *Your first Windows program*. Microsoft Learn. Retrieved November 15, 2024, from [https://learn.microsoft.com/vi-vn/windows/win32/learnwin32/your-first-windows-program](https://learn.microsoft.com/vi-vn/windows/win32/learnwin32/your-first-windows-program)
* *Game Programming Patterns*. Game Programming Patterns. Retrieved November 15, 2024.
* Petzold, C. (2012). *Programming Windows* (5th ed.). Microsoft Press.
* Oualline, S. (2003). *Practical C++ Programming*. O'Reilly Media.
* Blagy, D. (n.d.). *dewcin\_yt* \[GitHub repository]. GitHub. Retrieved November 15, 2024, from [https://github.com/danielblagy/dewcin\_yt](https://github.com/danielblagy/dewcin_yt)
* Refactoring Guru. (n.d.). *Refactoring and Design Patterns*. Retrieved November 15, 2024, from [https://refactoring.guru/](https://refactoring.guru/)
