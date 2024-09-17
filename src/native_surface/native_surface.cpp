#include "native_surface.h"
#include "extern_function.h"

void *get_createNativeWindow() {
    void *handle;
    printf("android api level:%d\n", get_android_api_level());
    if (get_android_api_level() == 33) {
        exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
        handle = dlblob(&native_surface_13_64, sizeof(native_surface_13_64));
#else
        handle = dlblob(&native_surface_13_32,sizeof(native_surface_13_32));
#endif
    } else if (get_android_api_level() == /*__ANDROID_API_S__*/ 32) {
        exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
        handle = dlblob(&native_surface_12_1_64, sizeof(native_surface_12_1_64));
#else
        handle = dlblob(&native_surface_12_1_32,
                        sizeof(native_surface_12_1_32));
#endif
    } else if (get_android_api_level() == /*__ANDROID_API_S__*/ 31) {
        exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
        handle = dlblob(&native_surface_12_64, sizeof(native_surface_12_64));
#else
        handle = dlblob(&native_surface_12_32,
                        sizeof(native_surface_12_32));
#endif
//            funcPointer.func_more_createNativeWindow = dlsym(handle, "_Z18createNativeWindowPKcjjjjb");
    } else if (get_android_api_level() == /*__ANDROID_API_R__*/ 30) {
#ifdef __aarch64__
        handle = dlblob(&native_surface_11_64, sizeof(native_surface_11_64));
#else
        handle = dlblob(&native_surface_11_32,
                        sizeof(native_surface_11_32));
#endif
    } else if (get_android_api_level() == /*__ANDROID_API_Q__*/ 29) {
#ifdef __aarch64__
        handle = dlblob(&native_surface_10_64, sizeof(native_surface_10_64));
#else
        handle = dlblob(&native_surface_10_32,
                        sizeof(native_surface_10_32));
#endif
    } else if (get_android_api_level() == /*__ANDROID_API_P__*/28) {
#ifdef __aarch64__
        handle = dlblob(&native_surface_9_64, sizeof(native_surface_9_64));
#else
        handle = dlblob(&native_surface_9_32, sizeof(native_surface_9_32));
#endif
    } else {
        printf("Sorry, level:%d Don't Support~\n", get_android_api_level());
        exit(0);
    }
    void *sy = dlsym(handle, "_Z18createNativeWindowPKcjj");
    if (sy != nullptr) {
        return sy;
    } else {
        sy = dlsym(handle, "_Z18createNativeWindowPKcjjb");
        if (sy != nullptr) {
            return sy;
        } else {
            printf("createNativeWindow _ null~\n");
            exit(0);
        }
    }

}


static void *handle;
static FuncPointer funcPointer;

ExternFunction::ExternFunction() {
    if (!handle) {
        printf("android api level:%d\n", get_android_api_level());
        if (get_android_api_level() == 33) {
            exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
            handle = dlblob(&native_surface_13_64, sizeof(native_surface_13_64));
#else
            handle = dlblob(&native_surface_13_32,
                            sizeof(native_surface_13_32));
#endif
        } else if (get_android_api_level() == /*__ANDROID_API_S__*/ 32) {
            exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
            handle = dlblob(&native_surface_12_1_64, sizeof(native_surface_12_1_64));
#else
            handle = dlblob(&native_surface_12_1_32,
                            sizeof(native_surface_12_1_32));
#endif
        } else if (get_android_api_level() == /*__ANDROID_API_S__*/ 31) {
            exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
            handle = dlblob(&native_surface_12_64, sizeof(native_surface_12_64));
#else
            handle = dlblob(&native_surface_12_32,
                            sizeof(native_surface_12_32));
#endif
//            funcPointer.func_more_createNativeWindow = dlsym(handle, "_Z18createNativeWindowPKcjjjjb");
        } else if (get_android_api_level() == /*__ANDROID_API_R__*/ 30) {
#ifdef __aarch64__
            handle = dlblob(&native_surface_11_64, sizeof(native_surface_11_64));
#else
            handle = dlblob(&native_surface_11_32,
                            sizeof(native_surface_11_32));
#endif
        } else if (get_android_api_level() == /*__ANDROID_API_Q__*/ 29) {
#ifdef __aarch64__
            handle = dlblob(&native_surface_10_64, sizeof(native_surface_10_64));
#else
            handle = dlblob(&native_surface_10_32,
                            sizeof(native_surface_10_32));
#endif
        } else if (get_android_api_level() == /*__ANDROID_API_P__*/28) {
#ifdef __aarch64__
            handle = dlblob(&native_surface_9_64, sizeof(native_surface_9_64));
#else
            handle = dlblob(&native_surface_9_32,
                            sizeof(native_surface_9_32));
#endif
        } else {
            exit(0);
        }
        funcPointer.func_createNativeWindow = dlsym(handle, "_Z18createNativeWindowPKcjjb");
        funcPointer.func_getDisplayInfo = dlsym(handle, "_Z14getDisplayInfov");
    }

}

ANativeWindow *
ExternFunction::createNativeWindow(const char *surface_name, uint32_t screen_width,
                                   uint32_t screen_height,
                                   bool author) {
    return ((ANativeWindow *(*)(
            const char *, uint32_t, uint32_t, bool))
            (funcPointer.func_createNativeWindow))(surface_name, screen_width, screen_height,
                                                   author);
}

ANativeWindow *
ExternFunction::createNativeWindow(const char *surface_name, uint32_t screen_width,
                                   uint32_t screen_height,
                                   uint32_t format, uint32_t flags, bool author) {
    return ((ANativeWindow *(*)(
            const char *, uint32_t, uint32_t, uint32_t, uint32_t, bool))
            (funcPointer.func_more_createNativeWindow))(surface_name, screen_width, screen_height,
                                                        format, flags,
                                                        author);
}


MDisplayInfo ExternFunction::getDisplayInfo() {
    return ((MDisplayInfo(*)()) (funcPointer.func_getDisplayInfo))();
}
