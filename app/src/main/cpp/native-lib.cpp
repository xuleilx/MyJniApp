#include <jni.h>
#include <string>
#include <iostream>
#include "ScopedJniEnv.h"

static JavaVM* gVm = NULL;
static jclass g_class;
static jobject g_object;
jmethodID messageCallbak;

void notifyMacAddress();

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myjniapp_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++ lalala";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_myjniapp_MainActivity_add(JNIEnv *env, jobject thiz, jint x, jint y) {
    // TODO: implement add()
    int result = x + y;
    return result;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myjniapp_MainActivity_initCallbacks(JNIEnv *env, jobject thiz) {
    // TODO: implement getMacAddress()
    env->GetJavaVM(&gVm);
    jclass jSdkClass = env->GetObjectClass(thiz);
    g_class = (jclass) env->NewGlobalRef(jSdkClass);
    g_object = env->NewGlobalRef(thiz);
    //直接用GetObjectClass找到Class, 也就是Sdk.class.
    if (jSdkClass == 0) {
        std::cout<<"Unable to find class"<<std::endl;
        return;
    }
    //找到需要调用的方法ID
    messageCallbak = env->GetMethodID(g_class,
                                      "onMessage", "(Ljava/lang/String;)V");
    return ;
}

void notifyMacAddress(){
    //进行回调，ret是java层的返回值（这个有些场景很好用）
    ScopedJniEnv env(gVm);
    jstring msg = (env)->NewStringUTF("Hello I`m Alex!OOOO");
    env->CallVoidMethod(g_object, messageCallbak, msg);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myjniapp_MainActivity_activeMessage(JNIEnv *env, jobject thiz) {
    // TODO: implement activeMessage()
    notifyMacAddress();
}