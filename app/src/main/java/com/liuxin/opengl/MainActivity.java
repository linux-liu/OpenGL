package com.liuxin.opengl;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
 private LxSurfaceView view;
    private OpenGlUtils nativeOpengl;
    private int index=-1;
    private int []ids={R.drawable.mingren,R.drawable.img_1,R.drawable.img_2,R.drawable.img_3};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        view=findViewById(R.id.view);
        nativeOpengl = new OpenGlUtils();
        view.setNativeOpengl(nativeOpengl);
        view.setOnInitListener(new LxSurfaceView.OnInitListener() {
            @Override
            public void init() {
               setTexture();
            }
        });


    }


    public void changeFilter(View view) {

        if(nativeOpengl!=null){
            nativeOpengl.onSurfaceChangeFilter();
        }
    }

    private void setTexture(){
        setIndex();
        final Bitmap bitmap = BitmapFactory.decodeResource(getResources(),
                ids[index]);
        ByteBuffer fcbuffer = ByteBuffer.allocate(bitmap.getHeight() * bitmap.getWidth() * 4);
        bitmap.copyPixelsToBuffer(fcbuffer);
        fcbuffer.flip();
        byte[] pixels = fcbuffer.array();
        nativeOpengl.imgData(bitmap.getWidth(), bitmap.getHeight(), pixels.length, pixels);
    }

    public void changeTeture(View view) {

        setTexture();
    }

    private void setIndex(){
        index++;
        if(index>=ids.length){
            index=0;
        }
    }



}
