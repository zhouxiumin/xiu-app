package top.zhouxiumin.audio;

/**
 * @author zhouxiumin
 */
public class MatrixUtil {
    private MatrixUtil(){}

    static {
        System.loadLibrary("audio");
    }

    public static native String matrixTest();
}
