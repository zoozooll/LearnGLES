# Walkthrough - Create Tutorial C++ Classes and Update GenSceneByName

I have generated C++ header and implementation files for all tutorials listed in `SampleData.kt` and updated the `GenSceneByName` function to correctly instantiate these scenes.

## Changes

### C++ Classes Created

- **35 Classes (70 files)** were created across four categories: `basic`, `lighting`, `pbr`, and `advanced`.
- Each class inherits from `Scene` and provides empty implementations for the required lifecycle methods.
- **Note**: I fixed an inheritance issue where classes were using private inheritance by default. They now all use `public Scene`.

### SceneHelper.h Updated

- Included headers for all new scene classes.
- Implemented `GenSceneByName` with a complete mapping of all 35 tutorial IDs to their respective C++ scene classes.

### Directory Structure

The files are organized in `tutorial/src/main/cpp/`:
- `basic/`
- `lighting/`
- `pbr/`
- `advanced/`

## Verification Results

### Automated Tests
- Executed `:tutorial:assembleDebug` and the build finished successfully. This confirms:
    - All new files are correctly picked up by the build system.
    - All scene classes correctly inherit from `Scene`.
    - `GenSceneByName` is correctly implemented and compiles without errors.

### Manual Verification
- Verified that all 35 IDs from `SampleData.kt` are handled in `GenSceneByName`.
- Verified the inheritance fix across all generated header files.
