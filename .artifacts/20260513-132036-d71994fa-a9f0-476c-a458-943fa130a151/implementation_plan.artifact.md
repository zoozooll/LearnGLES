# Update GenSceneByName in SceneHelper.h

Update `SceneHelper.h` to include headers for all tutorial scenes and implement the `GenSceneByName` function to return the correct scene based on the tutorial ID.

## Proposed Changes

### C++ Source Files

#### [SceneHelper.h](file:///E:/workspaces/android/LearnGLES/tutorial/src/main/cpp/SceneHelper.h)

- Add `#include` statements for all new scene classes organized by category.
- Update `GenSceneByName` with a sequence of `if` statements to handle all tutorial IDs from `SampleData.kt`.

```cpp
inline std::unique_ptr<Scene> GenSceneByName(const std::string& tutorial) {
    if (tutorial == "basic_gles") {
        return std::make_unique<BasicGlesScene>();
    } else if (tutorial == "depth_testing") {
        return std::make_unique<DepthTestingScene>();
    }
    // ... add more if-else statements for all tutorials
    return nullptr;
}
```

## Verification Plan

### Automated Tests
- Run `:tutorial:assembleDebug` to ensure compilation and that all includes are valid.

### Manual Verification
- Verify that `GenSceneByName` covers all IDs defined in `SampleData.kt`.
