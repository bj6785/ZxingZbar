#include <jni.h>
#include <malloc.h>

extern "C"

JNIEXPORT jbyteArray JNICALL
Java_com_google_zxing_client_android_DecodeHandlerJni_dataHandler(JNIEnv *env, jobject /* this */,
                                                                jbyteArray data, jint length,
                                                                jint width, jint height) {

    jbyte *rotatedData = (jbyte *) malloc(sizeof(jbyte) * length);
    jbyte *src = env->GetByteArrayElements(data, NULL);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            rotatedData[x * height + height - y - 1] = src[x + y * width];
    }

    jbyteArray jbyte_arr = env->NewByteArray(length);

    env->ReleaseByteArrayElements(jbyte_arr, rotatedData, 0);
    return jbyte_arr;
}
