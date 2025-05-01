#include <iostream>

// //////////////////////////////////////////////////////////////////////
// Some of this is the standard imGUI code that is required to use the
// imGUI framework.
// -- you don't need to bother with the details here.
// //////////////////////////////////////////////////////////////////////

// Dear ImGui: standalone example application for GLFW + OpenGL 3,
// using programmable pipeline (GLFW is a cross-platform general
// purpose library for handling windows, inputs, OpenGL/Vulkan/Metal
// graphics context creation, etc.)  If you are new to Dear ImGui,
// read documentation from the docs/ folder + read the top of
// imgui.cpp.  Read online:
// https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "implot.h"

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with
// VS2010 to maximize ease of testing and compatibility with old VS
// compilers.  To link with VS2010-era libraries, VS2015+ requires
// linking with legacy_stdio_definitions.lib, which we do using this
// pragma.  Your own project should not be affected, as you are likely
// to link with a newer binary of GLFW that is adequate for your
// version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

GLFWwindow *initialize_imGUI(const std::string_view &winTitle);
static void glfw_error_callback(int error, const char* description);

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
  // You can change the clear color
  // Colors are specified using RGBA, which stands for Red,
  // Green, Blue, and Alpha.  These are floating point values
  // that range from 0.0f to 1.0f.  You can consider these to be
  // percentages, so if R is 1.0f then we use 100% of the red channel.
  // You can look up RGB color tables on the internet.  The alpha channel
  // is for transparency which we probably won't utilize.
  ImVec4 m_clear_color( 0.25F, 0.25F, 0.5F, 1.0F );

  // variables to hold the data that the GUI fills
  float m_input_value = -3.459;

  // All the boilerplate imGUI initialization is in the following
  // function call.
  constexpr std::string_view windowTitle{ "imGUI Test" };
  GLFWwindow *windowPtr = initialize_imGUI( windowTitle );

  while (!glfwWindowShouldClose(windowPtr))
    {
      // Poll and handle events (inputs, window resize, etc.)
      // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
      // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
      // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
      // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
      glfwPollEvents();

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // ////////////////////////////////////////////////////////////
      // Want to see what imGUI is capable of?  Set show_demo_window to true here in this function and you'll get all the options.
      // 
      // Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
      // Uncomment the code below if you want to see many of the things imGUI can do
      //
      // bool show_demo_window = true;
      // ImGui::ShowDemoWindow(&show_demo_window);
      //
      // ////////////////////////////////////////////////////////////

      // Need to get a pointer to the main viewport that imGUI created.
      const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

      // /////////////////////////////////
      // Put your code here to create windows and other interface elements
      
      // 
      // //// such as creating a window...
      // 
      // First thing is to create a "window" to hold the user interface
      // We'll make this window 500 pixels by 200 pixels
      int windowWidth = 500;
      int windowHeight = 200;
      ImGui::SetNextWindowSize(ImVec2( windowWidth, windowHeight ), ImGuiCond_FirstUseEver);

      // We can place the initial position of the window The
      // coordinates are (0,0) in the upper left of the window and
      // (windowWidth, windowHeight) at the bottom right.
      // Using the work position
      ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 20, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);

      // Windows can be shown or not shown.  A boolean can control this.
      bool showInputWindow = true;
      ImGui::Begin("Magnetic Field Data", &showInputWindow);
      
      // ================================================
      // You can place all the input fields here that would go in this window.
      // Input fields and other GUI elements can be added here.

      ImGui::Text("Enter Magnetic Field Data");
      ImGui::InputFloat("Bt", &m_input_value);

      // Buttons return true when clicked (most widgets return true when edited/activated)
      if (ImGui::Button("Add Data")) {
	    std::cout << "Add data!" << ", " << m_input_value << std::endl;
      }

      // and should be done by here.
      // ================================================
	
      // This call ends the current "GUI" window above and ends the Begin call.
      ImGui::End();
      // /////////////////////////////////
      

      std::vector<int> bar_data(11);
      
      std::vector<float> x_data;
      std::vector<float> y_data;

      for (int i=0;i<1000;++i){
          x_data.push_back(i);
          y_data.push_back(cos(i));
      }

      ImGui::Begin("My Window");
      if (ImPlot::BeginPlot("My Plot")) {
          // ImPlot::PlotBars("My Bar Plot", bar_data, 11);
          ImPlot::PlotLine("My Line Plot", x_data.data(), y_data.data(), x_data.size());
          ImPlot::EndPlot();
      }
      ImGui::End();


      //
      // Final Rendering - do not edit below here.
      //
      ImGui::Render();
      int display_w, display_h;
      glfwGetFramebufferSize(windowPtr, &display_w, &display_h);
      glViewport(0, 0, display_w, display_h);
      glClearColor(m_clear_color.x * m_clear_color.w, m_clear_color.y * m_clear_color.w, m_clear_color.z * m_clear_color.w, m_clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwSwapBuffers(windowPtr);
    }

  std::cout << "Exiting\n";
  
  exit(EXIT_SUCCESS);
}


GLFWwindow *initialize_imGUI(const std::string_view &winTitle)
{
  // Setup window
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit()) {
    std::cerr << "Unable to initialize GLFW!\n";
    exit(EXIT_FAILURE);
  }

  // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100
  const char* glsl_version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
  // GL 3.2 + GLSL 150
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

  //
  // Create window with graphics context
  // 
  GLFWwindow* GLFWwindow_ptr = glfwCreateWindow(1280, 720, winTitle.data(), nullptr, nullptr);
  assert( GLFWwindow_ptr );

  glfwMakeContextCurrent(GLFWwindow_ptr);
  glfwSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImPlot::CreateContext();
  
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(GLFWwindow_ptr, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
  // - Read 'docs/FONTS.md' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  //io.Fonts->AddFontDefault();
  //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
  //IM_ASSERT(font != NULL);
  //  ImGuiIO& io = ImGui::GetIO();
  // io.Fonts->AddFontDefault();

  // Loading the Jetbrains font, which looks a bit nicer and is free to use
  io.Fonts->AddFontFromFileTTF("JetBrainsMono-Regular.ttf", 24);

  return GLFWwindow_ptr;
}

static void glfw_error_callback(int error, const char* description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

