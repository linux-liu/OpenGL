package com.liuxin.opengl;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.core.content.PermissionChecker;

import java.io.File;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.List;

public class YUVPlayActivity extends AppCompatActivity {
    private LxSurfaceView view;
    private OpenGlUtils nativeOpengl;
    private boolean isexit = true;
    private FileInputStream fis;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activtiy_yuvplay);
        view=findViewById(R.id.view);
        nativeOpengl = new OpenGlUtils();
        view.setNativeOpengl(nativeOpengl);


        if (PackageManager.PERMISSION_GRANTED != ContextCompat.checkSelfPermission(this,
                Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
            if (Build.VERSION.SDK_INT >= 23) {
                try {
                    List<String> permissions = new ArrayList<>();
                    if (PackageManager.PERMISSION_GRANTED != PermissionChecker.checkCallingOrSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                        permissions.add(Manifest.permission.WRITE_EXTERNAL_STORAGE);
                    }
                    if (permissions.size() != 0) {
                        ActivityCompat.requestPermissions(this,
                                (String[]) permissions.toArray(new String[permissions.size()]),
                                200);

                    }
                } catch (Exception e) {
                    e.printStackTrace();

                }
            }

        } else {
            //已经授权过了
        }
    }


    public void play(View view) {
        if(isexit)
        {
            isexit = false;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    int w = 352;
                    int h = 288;
                    try {
                        String path= Environment.getExternalStorageDirectory().getPath()+"/out_352_288.yuv";
                        fis = new FileInputStream(new File(path));
                        byte[]y = new byte[w * h];
                        byte[]u = new byte[w * h / 4];
                        byte[]v = new byte[w * h / 4];

                        while (true)
                        {
                            if(isexit)
                            {
                                break;
                            }
                            int ysize = fis.read(y);
                            int usize = fis.read(u);
                            int vsize = fis.read(v);
                            if(ysize > 0 && usize > 0 && vsize > 0)
                            {
                                nativeOpengl.setYUVData(y, u, v, w, h);
                                Thread.sleep(40);
                            }
                            else
                            {
                                isexit = true;
                            }
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }).start();
        }


    }

    public void stop(View view) {
        isexit = true;
    }
}
