//
// Created by 周秀敏 on 2020/8/30.
//

#include <cstring>
#include <jni.h>
#include "matrix.h"

extern "C" JNIEXPORT jstring JNICALL
Java_top_zhouxiumin_audio_MatrixUtil_matrixTest( JNIEnv* env, jclass thiz){
    mat::test();
    return env->NewStringUTF("hello");
}