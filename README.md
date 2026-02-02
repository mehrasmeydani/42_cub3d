*This project has been created as part of the 42 curriculum by megardes, eprottun.*

## Description

cub3D is a graphics project that creates a realistic 3D representation of a maze from a first-person perspective inspired by Wolfenstein 3d (1992). The project uses the miniLibX graphics library and implements efficient ray-casting, allowing players to navigate through a 3D maze with textured walls.

### Features

*Mandatory:*
- First-person 3D view using ray-casting
- Textured walls with different textures for each direction (N, S, E, W)
- Configurable floor and ceiling colors
- Smooth player movement (W, A, S, D keys)
- Camera rotation (left/right arrow keys)
- Window management (minimize, close)
- Map parsing from `.cub` configuration files

*Bonus:*
- Interactive minimap display (toggle with Q)
- Ray visualization on minimap (toggle with R)
- Mouse-based camera rotation (toggle with M)
- Animated sprite textures

## Instructions

### Prerequisites

- Linux operating system with X11
- GCC compiler
- miniLibX library

### Compilation

```bash
# Clone the repository
git clone https://github.com//mehrasmeydani/42_cub3d.git
cd cub3D

# Compile mandatory version
make

# Compile bonus version
make bonus

# Clean object files
make clean

# Full clean (including executables)
make fclean

# Recompile
make re
```

### Execution

```bash
# Run mandatory version
./cub3D maps/wow.cub

# Run bonus version
./cub3D_bonus maps/wow_bonus.cub
```

### Map File Format (.cub)

The configuration file must have the `.cub` extension and have the following content:

**Elements**
- `NO`, `SO`, `WE`, `EA` - Texture paths for each wall direction
- `F` - Floor color (R,G,B format, values 0-255)
- `C` - Ceiling color (R,G,B format, values 0-255)
- Map chars:
  - `0` - Empty space
  - `1` - Wall
  - `N`, `S`, `E`, `W` - Player spawn position and orientation

**Map Rules:**
- Must be surrounded by walls
- Exactly one player spawn point
- Spaces are valid parts of the map

## Technical Implementation

### Ray-Casting Algorithm

The renderer uses a DDA (Digital Differential Analyzer) algorithm that casts rays for each vertical screen column:

1. For each column, calculate ray direction based on player position and FOV
2. Cast horizontal and vertical rays separately
3. Determine the closest wall intersection
4. Calculate wall height based on perpendicular distance (to avoid fisheye effect)
5. Apply appropriate texture based on wall orientation

### Key Constants

- `MINISQ` (64): Size of each map cell in pixels
- `ANGLE` (30.0): Half of the field of view in degrees
- `FPS` (16): Frame time in milliseconds (~60 FPS)
- `TEXT_SIZE` (2048): Maximum texture dimension

## Resources

### Ray-Casting Theory
- [Make Your Own Raycaster Part 1](https://www.youtube.com/watch?v=gYRrGTC7GtA)
- [Super Fast Ray Casting in Tiled Worlds using DDA](https://www.youtube.com/watch?v=NbSee-XM7WA)

### miniLibX
- [42 Docs - miniLibX](https://harm-smits.github.io/42docs/libs/minilibx)

### Context
- [Wolfenstein 3D information](https://fabiensanglard.net/gebbwolf3d/)

### AI Usage

AI tools (Claude, ChatGPT) were used to assist with:
- README documentation structure and formatting
- Code review and identification of potential issues
- Understanding ray-casting mathematics

All code implementation was done by the project authors with AI serving as a reference and review tool only.

## Authors

- **megardes** - [@megardes](https://github.com/megardes)
- **eprottun** - [@eprottun](https://github.com/eprottun)

## License

This project is part of the 42 school curriculum. All rights reserved.
