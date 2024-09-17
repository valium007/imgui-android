#include "main.h"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"

// Data
static EGLDisplay g_EglDisplay = EGL_NO_DISPLAY;
static EGLSurface g_EglSurface = EGL_NO_SURFACE;
static EGLContext g_EglContext = EGL_NO_CONTEXT;
bool g_Initialized = false;
static char g_LogTag[] = "ImGuiExample";

int dpi_scale = 3;
ImFont* tab_text1;
static bool menu = false;

int init(int screen_x, int screen_y) {
  if (g_Initialized)
    return 0;

  native_window =
      externFunction.createNativeWindow("Valium", screen_x, screen_y, false);
  ANativeWindow_acquire(native_window);

  // Initialize EGL
  // This is mostly boilerplate code for EGL...
  {
    g_EglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (g_EglDisplay == EGL_NO_DISPLAY)
      __android_log_print(
          ANDROID_LOG_ERROR, g_LogTag, "%s",
          "eglGetDisplay(EGL_DEFAULT_DISPLAY) returned EGL_NO_DISPLAY");

    if (eglInitialize(g_EglDisplay, 0, 0) != EGL_TRUE)
      __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s",
                          "eglInitialize() returned with an error");

    const EGLint egl_attributes[] = {EGL_SURFACE_TYPE,
                                     EGL_WINDOW_BIT,
                                     EGL_RENDERABLE_TYPE,
                                     EGL_OPENGL_ES2_BIT,
                                     EGL_BLUE_SIZE,
                                     5,  //-->delete
                                     EGL_GREEN_SIZE,
                                     6,  //-->delete
                                     EGL_RED_SIZE,
                                     5,  //-->delete
                                     EGL_BUFFER_SIZE,
                                     32,  //-->new field
                                     EGL_DEPTH_SIZE,
                                     16,
                                     EGL_STENCIL_SIZE,
                                     8,
                                     EGL_NONE};
    EGLint num_configs = 0;
    if (eglChooseConfig(g_EglDisplay, egl_attributes, nullptr, 0,
                        &num_configs) != EGL_TRUE)
      __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s",
                          "eglChooseConfig() returned with an error");
    if (num_configs == 0)
      __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s",
                          "eglChooseConfig() returned 0 matching config");

    // Get the first matching config
    EGLConfig egl_config;
    eglChooseConfig(g_EglDisplay, egl_attributes, &egl_config, 1, &num_configs);
    EGLint egl_format;
    eglGetConfigAttrib(g_EglDisplay, egl_config, EGL_NATIVE_VISUAL_ID,
                       &egl_format);
    ANativeWindow_setBuffersGeometry(native_window, 0, 0, egl_format);

    const EGLint egl_context_attributes[] = {EGL_CONTEXT_CLIENT_VERSION, 3,
                                             EGL_NONE};
    g_EglContext = eglCreateContext(g_EglDisplay, egl_config, EGL_NO_CONTEXT,
                                    egl_context_attributes);

    if (g_EglContext == EGL_NO_CONTEXT)
      __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s",
                          "eglCreateContext() returned EGL_NO_CONTEXT");

    g_EglSurface =
        eglCreateWindowSurface(g_EglDisplay, egl_config, native_window, NULL);
    eglMakeCurrent(g_EglDisplay, g_EglSurface, g_EglSurface, g_EglContext);
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  // Disable loading/saving of .ini file from disk.
  // FIXME: Consider using LoadIniSettingsFromMemory() /
  // SaveIniSettingsToMemory() to save in appropriate location for Android.
  io.IniFilename = NULL;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplAndroid_Init(native_window);
  ImGui_ImplOpenGL3_Init("#version 300 es");

  ImFontConfig font_cfg;
  font_cfg.SizePixels = 22.0f;
  // io.Fonts->AddFontFromFileTTF("font.ttf", 16 * dpi_scale);
  io.Fonts->AddFontFromMemoryTTF(inter_medium, sizeof(inter_medium),
                                 16 * dpi_scale, &font_cfg,
                                 io.Fonts->GetGlyphRangesCyrillic());
  ImGui::GetStyle().ScaleAllSizes(3.0f);
  g_Initialized = true;
  return 1;
}

void tick() {
  ImGuiIO& io = ImGui::GetIO();
  if (g_EglDisplay == EGL_NO_DISPLAY)
    return;

  // Our state
  static bool show_another_window = false;
  static ImVec4 clear_color = ImVec4(0, 0, 0, 0);
  static ImVec4 custom_color = ImVec4(0, 0, 0, 0);

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplAndroid_NewFrame();
  ImGui::NewFrame();

  // Show simple window
  {
    static float f = 0.0f;
    static int counter = 0;
    ImGui::SetNextWindowSize(ImVec2(300 * dpi_scale, 200 * dpi_scale), 0);
    ImGui::Begin("Hello, world!", &menu,
                 ImGuiWindowFlags_NoResize);  // Create a window called "Hello,
                                              // world!" and append into it.
    ImGui::SliderFloat("float", &f, 0.0f,
                       1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f

    if (ImGui::Button("Button"))  // Buttons return true when clicked (most
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    if (ImGui::Button("Exit"))  // Buttons return true when clicked (most
      exit(0);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
  }

  // Rendering
  ImGui::Render();
  glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  eglSwapBuffers(g_EglDisplay, g_EglSurface);
}

void shutdown() {
  if (!g_Initialized)
    return;

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplAndroid_Shutdown();
  ImGui::DestroyContext();

  if (g_EglDisplay != EGL_NO_DISPLAY) {
    eglMakeCurrent(g_EglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE,
                   EGL_NO_CONTEXT);

    if (g_EglContext != EGL_NO_CONTEXT)
      eglDestroyContext(g_EglDisplay, g_EglContext);

    if (g_EglSurface != EGL_NO_SURFACE)
      eglDestroySurface(g_EglDisplay, g_EglSurface);

    eglTerminate(g_EglDisplay);
  }

  g_EglDisplay = EGL_NO_DISPLAY;
  g_EglContext = EGL_NO_CONTEXT;
  g_EglSurface = EGL_NO_SURFACE;
  ANativeWindow_release(native_window);

  g_Initialized = false;
}

int main(int argc, char** argv) {
  screen_config();
  if (!init(screen_x, screen_y)) {
    exit(0);
  }
  new std::thread(TouchThread);
  while (true) {
    tick();
  }

  shutdown();
  return 0;
}
