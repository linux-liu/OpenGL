package com.liuxin.opengl;

import android.content.Context;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class LxSurfaceView extends SurfaceView implements SurfaceHolder.Callback {

    private OpenGlUtils nativeOpengl;

    private OnInitListener listener;
    public void setNativeOpengl(OpenGlUtils nativeOpengl) {
        this.nativeOpengl = nativeOpengl;
    }

    public LxSurfaceView(Context context) {
        this(context, null);
    }

    public LxSurfaceView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public LxSurfaceView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        getHolder().addCallback(this);
    }

    public void setOnInitListener(OnInitListener listener){
        this.listener=listener;
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        if(nativeOpengl != null)
        {
            nativeOpengl.onSurfaceCreated(surfaceHolder.getSurface());
        }
        if(listener!=null){
            listener.init();
        }
    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int format, int width, int height) {
        if(nativeOpengl != null)
        {
            nativeOpengl.onSurfaceChanged(width, height);
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
        if(nativeOpengl != null)
        {
            nativeOpengl.onSurfaceDestory();
        }
    }

    public interface OnInitListener{
        void init();
    }
}
