// Android entry point for Isometric MUD
#include <android/native_activity.h>
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "IsometricMUD", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "IsometricMUD", __VA_ARGS__))

// Android native activity entry point
void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {
    LOGI("Isometric MUD Android - Starting");
    
    // Initialize SFML and game client for Android
    // This would need proper SFML Android setup
    
    LOGI("Isometric MUD Android - Initialized");
}
