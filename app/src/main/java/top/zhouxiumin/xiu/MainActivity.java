package top.zhouxiumin.xiu;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Build;
import android.os.Bundle;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.util.Log;
import android.widget.Button;

import top.zhouxiumin.audio.MatrixUtil;

/**
 * @author zhouxiumin
 */
public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    private static final long[] WIRELESS_VIBRATION_TIME = {
            200, 200, 200, 200, 200, 200, 200, 200, 200, // ramp-up sampling rate = 40ms
            200, 200, 200, 200, 200, 200, 200 // ramp-down sampling rate = 40ms
    };
    private static final int[] WIRELESS_VIBRATION_AMPLITUDE = {
            1, 4, 11, 25, 44, 67, 91, 114, 123, // ramp-up amplitude (from 0 to 50%)
            103, 79, 55, 34, 17, 7, 2 // ramp-up amplitude
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button button = findViewById(R.id.button_mat);
        button.setOnClickListener((v)->{
            Log.d(TAG, "on click");
            String s = MatrixUtil.matrixTest();
            Log.d(TAG, "matrixTest " + s);

        });

        Button button2 = findViewById(R.id.button_test2);
        button2.setOnClickListener((v)->{
            Vibrator vibrator = (Vibrator)this.getSystemService(VIBRATOR_SERVICE);
            boolean flag;
            flag = vibrator.hasVibrator();
            Log.d(TAG, "hasVibrator " + flag);
            flag = vibrator.hasAmplitudeControl();
            Log.d(TAG, "hasAmplitudeControl " + flag);
            VibrationEffect effect = null;
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.Q) {
                effect = VibrationEffect.createPredefined(VibrationEffect.EFFECT_HEAVY_CLICK);
                vibrator.vibrate(effect);
            } else {
                effect = VibrationEffect.createOneShot(1000,10);
                vibrator.vibrate(effect);
            }
        });

        Button button3 = findViewById(R.id.button_test3);
        button3.setOnClickListener((v)->{
            Vibrator vibrator = (Vibrator)this.getSystemService(VIBRATOR_SERVICE);
            boolean flag;
            flag = vibrator.hasVibrator();
            Log.d(TAG, "hasVibrator " + flag);
            flag = vibrator.hasAmplitudeControl();
            Log.d(TAG, "hasAmplitudeControl " + flag);
            VibrationEffect effect = null;
            effect=VibrationEffect.createWaveform(WIRELESS_VIBRATION_TIME, WIRELESS_VIBRATION_AMPLITUDE,
                    -1);
            vibrator.vibrate(effect);
        });
    }
}