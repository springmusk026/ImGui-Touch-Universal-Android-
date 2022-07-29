
#define HOOK(ret, func, ...) \
    ret (*orig##func)(__VA_ARGS__); \
    ret my##func(__VA_ARGS__)

HOOK(void, Input, void *thiz, void *ex_ab, void *ex_ac){ 
    origInput(thiz, ex_ab, ex_ac);
    ImGui_ImplAndroid_HandleInputEvent((AInputEvent *)thiz); 
    return;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void * reserved)
{
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    void *sym_input = DobbySymbolResolver(("/system/lib/libinput.so"), ("_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE")); 
    if (NULL != sym_input){
        DobbyHook((void *)sym_input, (void *) myInput, (void **)&origInput);
    }
    return JNI_VERSION_1_6;
}
