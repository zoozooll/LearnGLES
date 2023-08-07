package com.example.learngles;

import android.content.res.AssetManager;

public class NativeLibHelper {
    static {
        System.loadLibrary("nativegl");
    }

    public static native void nativeSurfaceCreate(String tutorial);

    public static native void nativeSurfaceChanged(int width, int height);

    public static native void nativeDraw();

    public static native void nativeDestroy();

    public static native void setupNativeAsset(AssetManager am);

    public static native void setupInternalPath(String path);
}
