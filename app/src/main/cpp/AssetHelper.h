//
// Created by Aaron Lee on 2022/9/23.
//

#ifndef NATIVE3DENGINE_ASSETHELPER_H
#define NATIVE3DENGINE_ASSETHELPER_H

#include <cstdio>

bool LoadDataFromAsset(const char *const assetPath, void **buffer, size_t *size);

bool LoadStringFromAsset(const char *const assetPath, char **buffer, int *size);

#endif //NATIVE3DENGINE_ASSETHELPER_H
