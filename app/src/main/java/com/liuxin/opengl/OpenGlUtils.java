package com.liuxin.opengl;

import android.view.Surface;

public class OpenGlUtils {
    static {
        System.loadLibrary("native-lib");
    }

    public native  void onSurfaceCreated(Surface surface);

    public native void  onSurfaceChanged(int width,int height);

    public native void  onSurfaceDestory();

    public native void  onSurfaceChangeFilter();
    public native void imgData(int w, int h, int length, byte[] data);

    public native void setYUVData(byte[]y,byte[]u,byte[]v, int width, int height);
}
