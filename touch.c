
void orig_input(void *thiz, void *ex_ab, void *ex_ac);
void h_input(void *thiz, void *ex_ab, void *ex_ac){
    orig_input(thiz,ex_ac,ex_ac);
    ImGui_ImplAndroid_HandleInputEvent((AInputEvent *)thiz); 
    return;
}

void *sys_in = DobbySymbolResolver(OBFUSCATE("/system/lib/libinput.so"), OBFUSCATE("_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE"));
    
if (sys_in != NULL){
   DobbyHook((void *)sys_in, (void *) h_input, (void **)&orig_input);
}
