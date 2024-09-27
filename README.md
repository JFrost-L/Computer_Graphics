# Computer Graphics Project

This repository contains a collection of computer graphics techniques implemented using **OpenGL** and **C++**. The project explores various graphics rendering algorithms and techniques, ranging from basic 2D graphics to complex 3D rendering with lighting, shading, and textures.

## Table of Contents
1. [Overview](#overview)
2. [Technologies Used](#technologies-used)
3. [Key Features](#key-features)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Project Structure](#project-structure)
7. [License](#license)

## Overview

**Computer Graphics** involves the creation, manipulation, and rendering of 2D and 3D objects. This project demonstrates fundamental and advanced concepts in computer graphics, including:

- 2D and 3D object rendering
- Basic transformations (translation, rotation, scaling)
- Projection (orthographic and perspective)
- Lighting models (Phong, Gouraud)
- Texturing and texture mapping
- Advanced rendering techniques like shadow mapping, reflection, and refraction

This project can serve as a foundational tool for anyone interested in learning computer graphics and OpenGL programming.

## Technologies Used

- **C++**: The main programming language used for the project.
- **OpenGL**: The graphics API used to render 2D and 3D objects.
- **GLFW**: A library to create windows, handle input, and manage the OpenGL context.
- **GLEW**: A library to load OpenGL extensions and handle function pointers.
- **GLM**: A mathematics library for vector and matrix operations.
- **SOIL**: A library used to load textures and image files.
- **ImGui**: A graphical user interface library for debugging and interactive control.

## Key Features

1. **2D and 3D Object Rendering**:
   - Basic shapes like cubes, spheres, and planes.
   - Complex models loaded from external 3D files (e.g., .obj).
   - Object rendering with different shading models.

2. **Transformations**:
   - Implementations of translation, rotation, and scaling in both 2D and 3D spaces using matrix transformations.
   - Real-time interactive control of transformations via GUI.

3. **Lighting Models**:
   - **Phong Lighting**: Provides realistic lighting using ambient, diffuse, and specular components.
   - **Gouraud Shading**: Vertex-based shading technique for smooth color transitions across surfaces.
   - **Blinn-Phong Shading**: Optimized shading model for specular highlights.

4. **Projection Methods**:
   - **Orthographic Projection**: Suitable for 2D games or technical illustrations where depth perspective is not required.
   - **Perspective Projection**: 3D view with depth perception, giving a sense of realism to scenes.

5. **Texturing and Texture Mapping**:
   - Application of 2D textures to 3D surfaces for realistic rendering.
   - Support for multiple texture types (diffuse, specular, normal maps).

6. **Advanced Rendering**:
   - **Shadow Mapping**: Create realistic shadows by simulating how light interacts with objects.
   - **Reflection and Refraction**: Implementation of mirror-like surfaces and water-like effects using cube maps and shaders.
   - **Depth Buffering and Stencil Testing**: For accurate rendering of overlapping objects and complex visual effects.

7. **User Interaction**:
   - Keyboard and mouse input for controlling camera movements and object interactions.
   - Interactive GUI using ImGui for tweaking object properties and rendering parameters in real-time.

## Installation

To run this project on your local machine, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/computer-graphics.git
   cd computer-graphics
