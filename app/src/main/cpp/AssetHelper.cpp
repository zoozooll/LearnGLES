//
// Created by Aaron Lee on 2022/9/23.
//

#include "AssetHelper.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <cstdlib>

extern AAssetManager* mgr;

void LoadDataFromAsset(const char *const assetPath, void **buffer, size_t *size) {
    AAsset* file = AAssetManager_open(mgr, assetPath, AASSET_MODE_BUFFER);
    *size = AAsset_getLength(file);
    *buffer = malloc(*size);
    AAsset_read(file, *buffer, *size);
    AAsset_close(file);
}
