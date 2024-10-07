# SMP (Simple Media Player)

**SMP** is a versatile media player developed in C++ that can operate in two modes: audio player and video player. The project is designed for simplicity while providing functionality for both audio and video playback.

## Description
SMP allows users to switch between two modes: audio-only mode for listening to music or podcasts and video mode for watching media content. It offers a minimalistic interface and easy-to-use controls, making it a lightweight solution for media playback.

## Features
- Dual-mode operation: Audio player and Video player
- Simple and user-friendly interface
- Support for popular media formats
- Play, pause, and seek functionality

## Technologies
The project is developed using:
- **C++**
- **Qt 6**

## Installation and Running
### Requirements:
- A C++ compiler (e.g., g++)
- Required libraries for audio and video playback

### Building the project:
1. Clone the repository:
    ```bash
    git clone https://github.com/EralifeIX/Simple-Qt-video-audio-player.git
    cd smp
    ```
2. Build the project using CMake:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Run the program:
    ```bash
    ./SMP
    ```

## Usage
### Audio Player Mode:
- Load audio files and control playback (Play, Pause, Stop, Seek).

### Video Player Mode:
- Open video files for playback with basic controls (Play, Pause, Seek, Fullscreen).

## Controls
- **Spacebar** — Play/Pause
- **Arrow keys** — Seek forward/backward, Volume up/down
- **Double click** — Toggle fullscreen (for video mode)
- **Escape** — Quit

## Screenshots
------------------------------------------------------------------------------------------------------------------
![Screenshot](https://github.com/EralifeIX/Simple-Qt-video-audio-player/blob/main/screenshots/image1.png)
![Screenshot](https://github.com/EralifeIX/Simple-Qt-video-audio-player/blob/main/screenshots/image2.png)

