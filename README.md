# Bible VR Game - Unreal Engine 5 Project

An immersive virtual reality experience exploring biblical stories and encounters.

## System Requirements

- **Unreal Engine**: 5.4 or later
- **Operating System**: Windows 10/11 or macOS
- **RAM**: 16GB minimum, 32GB recommended
- **GPU**: RTX 2070 or equivalent for VR
- **VR Headset**: Meta Quest 2/3, Valve Index, or similar

## Quick Start

### 1. Open the Project

1. Launch Unreal Engine 5.4+
2. Click **Browse** and navigate to this folder
3. Select `BibleVRGame.uproject`
4. Click **Open**

### 2. Compile C++ Code

When prompted, click **Yes** to compile the C++ code.

If compilation fails:
1. Right-click the `.uproject` file
2. Select **Generate Visual Studio project files**
3. Open the `.sln` file in Visual Studio
4. Build the solution (F7)

### 3. Create Character Blueprints

After the project loads, run the auto-generation script:

1. Go to **Window > Developer Tools > Output Log**
2. In the command field at the bottom, type:
   ```
   py Content/EditorUtilities/CreateCharacterBlueprints.py
   ```
3. Press Enter

This creates all character Blueprints automatically.

### 4. Install Required Plugins

Some plugins need to be installed from the marketplace:

1. **Cesium for Unreal** - Real-world terrain
   - Epic Games Launcher > Marketplace > Search "Cesium"

2. **MetaHumans** - Realistic characters
   - Epic Games Launcher > Marketplace > Search "MetaHuman"

## Project Structure

```
BibleVRGame/
├── Config/                    # Engine configuration
├── Content/
│   ├── Blueprints/
│   │   └── Characters/        # Character Blueprints (BP_*)
│   │       ├── Companions/
│   │       ├── Apostles/
│   │       ├── NPCs/
│   │       └── Enemy/
│   ├── Maps/                  # Level files
│   ├── Materials/             # Materials and shaders
│   ├── Textures/              # Texture assets
│   ├── Audio/                 # Sound effects and music
│   ├── VFX/                   # Niagara effects
│   └── UI/                    # User interface
└── Source/
    └── BibleVRGame/
        ├── Public/            # Header files (.h)
        │   ├── Characters/
        │   └── Enemy/
        └── Private/           # Source files (.cpp)
            ├── Characters/
            └── Enemy/
```

## Characters Included

### Companions (6)
- Peter - Leadership, Protection
- Mary Magdalene - Comfort, Inspiration
- John - Wisdom, Knowledge
- Paul - Knowledge, Inspiration
- Solomon - Wisdom, Guidance
- The Guide - Guidance, Comfort, Knowledge

### The 12 Apostles
1. Simon Peter
2. Andrew
3. James (Greater)
4. John
5. Philip
6. Bartholomew
7. Matthew
8. Thomas
9. James (Lesser)
10. Thaddaeus
11. Simon the Zealot
12. Judas Iscariot

### NPCs
- **Romans**: Centurion, Pontius Pilate, Soldiers
- **Religious Leaders**: Caiaphas, Nicodemus, Pharisees
- **Angels**: Gabriel, Michael
- **Women**: Mary Mother, Martha, Mary of Bethany, Woman at Well
- **Civilians**: Merchants, Farmers, Crowd members

### Special Characters
- **Jesus Christ** - Miracles, Parables, Ministry periods
- **The Devil** - 7 forms, Temptation system

## VR Controls

| Action | Oculus | Index |
|--------|--------|-------|
| Move | Left Stick | Left Touchpad |
| Teleport | Right Trigger | Right Trigger |
| Interact | A Button | A Button |
| Grab | Grip | Grip |
| Menu | Start | Start |

## Creating New Content

### Add a New Character

1. Create a C++ class inheriting from `ABiblicalCharacterBase`
2. Add to `BibleVRGame.Build.cs` if needed
3. Compile
4. Create Blueprint from the C++ class
5. Set up mesh, animations, and dialogue

### Add a Quest

1. Create Data Table using `FQuestData` struct
2. Add scenes with dialogue and choices
3. Set up triggers in the level
4. Connect to Quest Manager

## Building for VR

### Meta Quest

1. **File > Package Project > Android**
2. Ensure OpenXR plugin is enabled
3. Set texture compression to ASTC

### PC VR (Steam)

1. **File > Package Project > Windows**
2. Enable SteamVR plugin
3. Build in Shipping configuration

## Troubleshooting

### "Module could not be loaded"
- Recompile C++ code
- Delete Binaries and Intermediate folders
- Regenerate project files

### Blueprints not showing C++ properties
- Close editor
- Delete Saved folder
- Reopen project

### VR not working
- Ensure OpenXR runtime is installed
- Check headset connection
- Verify SteamVR/Oculus software is running

## Resources

- [Unreal Engine Documentation](https://docs.unrealengine.com)
- [VR Development Guide](https://docs.unrealengine.com/5.0/en-US/developing-for-xr-experiences-in-unreal-engine/)
- [MetaHuman Documentation](https://docs.metahuman.unrealengine.com)

## License

Educational and personal use.

---

*"For God so loved the world that he gave his one and only Son, that whoever believes in him shall not perish but have eternal life." - John 3:16*
