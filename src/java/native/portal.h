#ifndef ZLOG_JNI_PORTAL_H
#define ZLOG_JNI_PORTAL_H

#include <jni.h>
#include <cassert>

template<class PTR, class DERIVED> class ZlogNativeClass {
 public:
  static jclass getJClass(JNIEnv *env, const char *jclazz_name) {
    jclass jclazz = env->FindClass(jclazz_name);
    assert(jclazz != nullptr);
    return jclazz;
  }

  static jfieldID getHandleFieldID(JNIEnv *env) {
    static jfieldID fid = env->GetFieldID(
        DERIVED::getJClass(env), "nativeHandle_", "J");
    assert(fid != nullptr);
    return fid;
  }

  static PTR getHandle(JNIEnv *env, jobject jobj) {
    return reinterpret_cast<PTR>(
        env->GetLongField(jobj, getHandleFieldID(env)));
  }

  static void setHandle(JNIEnv *env, jobject jobj, PTR ptr) {
    env->SetLongField(jobj, getHandleFieldID(env),
        reinterpret_cast<jlong>(ptr));
  }
};

class ZlogJni : public ZlogNativeClass {
 public:
  static jclass getJClass(JNIEnv *env) {
    return ZlogNativeClass::getJClass(env, "com/cruzdb/Log");
  }
};

#endif
