package com.minininja.learngles;

import android.content.res.AssetManager;

import java.util.Map;

public class NativeHelper {
    static {
        System.loadLibrary("learngles");
    }

    public static native void nativeOnInit(String tutorial);

    public static native void nativeSizeChanged(int width, int height);

    public static native void nativeDraw();

    public static native void nativeDestroy();

    public static native void setupNativeAsset(AssetManager am);

    public static native void setupInternalPath(String path);

    public static native void sendCommands(Map<String, Object> commands);
}
