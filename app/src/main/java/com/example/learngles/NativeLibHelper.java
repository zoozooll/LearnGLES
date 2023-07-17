package com.example.learngles;

public class NativeLibHelper {
    static {
        System.loadLibrary("nativegl");
    }

    public static native void nativeSurfaceCreate();

    public static native void nativeSurfaceChanged(int width, int height);

    public static native void nativeDraw();
}
