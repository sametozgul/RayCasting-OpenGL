#include "UserInterface.h"
#include <string>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void UserInterface::init(OGLRenderData &renderData)
{
    // Calls to ImGUI_CHECKVERSION and Imgui::CreateContext() are required from the IMGUI side
    // Imgui::CreateContext() searheds for a file named imgui.ini, if it does exist it creates.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // GLFW backend is initialized
    ImGui_ImplGlfw_InitForOpenGL(renderData.rdWindow, true);
    const char* glslVersion = "#version 460 core";
    // Crates the widgets and fill them with the data
    ImGui_ImplOpenGL3_Init(glslVersion);
}

void UserInterface::createFrame(OGLRenderData &renderData)
{
    // Create OpenGL Frame
    ImGui_ImplOpenGL3_NewFrame();
    // Create GLFW Backend Frame
    ImGui_ImplGlfw_NewFrame();
    // Create ImGui Frame
    ImGui::NewFrame();
    // Allow changing some of the properties of the ImGui
    ImGuiWindowFlags imguiWindowFlags = 0;
    // Set transprancy
    ImGui::SetNextWindowBgAlpha(0.7f);
    // Starts a new ImGui Window
    ImGui::Begin("Control",nullptr,imguiWindowFlags);
    // Calculate FPS
    static float newFps = 0.0f;
    /* avoid inf values (division by zero) */
    if (renderData.rdFrameTime > 0.0) {
        newFps = 1.0f / renderData.rdFrameTime * 1000.f;
    }
    /* make an averge value to avoid jumps */
    framesPerSecond = (averagingAlpha * framesPerSecond) + (1.0f - averagingAlpha) * newFps;


    // Create a line with text
    ImGui::Text("Triangles");
    ImGui::SameLine();
    ImGui::Text("%s", std::to_string(renderData.rdTriangleCount).c_str());
    std::string windowDims = std::to_string(renderData.rdWidth) + "x" + std::to_string(renderData.rdHeight);
    ImGui::Text("Window Dimensions:");
    ImGui::SameLine();
    ImGui::Text("%s",windowDims.c_str());
    std::string imgWindowPos = std::to_string(static_cast<int>(ImGui::GetWindowPos().x)) + "/" + std::to_string(static_cast<int>(ImGui::GetWindowPos().y));
    ImGui::Text("Window Position:");
    ImGui::SameLine();
    ImGui::Text("%s",imgWindowPos.c_str());
    ImGui::Text("Max Vertex Attributes:");
    ImGui::SameLine();
    ImGui::Text("%s",std::to_string(renderData.rdNrAttributes).c_str());
    ImGui::Text("FPS:");
    ImGui::SameLine();
    ImGui::Text("%s",std::to_string(framesPerSecond).c_str());
    static bool isColorChangedCxBx = false;
    ImGui::Checkbox("Change Color",&isColorChangedCxBx);
    if(isColorChangedCxBx){
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text,IM_COL32(0,255,0,255));
        ImGui::Text("Red");
        ImGui::PopStyleColor();
        renderData.rdIsColorChanged = true;
    }else{
        renderData.rdIsColorChanged = false;
    }
    // Add CheckBox to change polygone mode.
    static bool isPolycheckBoxChecked = false;

    ImGui::Checkbox("Polygone Mode",&isPolycheckBoxChecked);
    if(isPolycheckBoxChecked){
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text,IM_COL32(0,255,0,255));
        ImGui::Text("Opened");
        ImGui::PopStyleColor();
        renderData.rdUsePolygonMode = true;
    }else{
        renderData.rdUsePolygonMode = false;
    }
    ImGui::Separator();
    ImGui::Text("Add/Remove Cube");
    ImGui::InputInt("##spinbox",&renderData.cubeCount,1);
    if(renderData.cubeCount>10){
        renderData.cubeCount = 10;
    }
    else if(renderData.cubeCount<1)
    {
        renderData.cubeCount = 1;
    }
    ImGui::End();
}

void UserInterface::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::cleanUp()
{
    // Destroy OpenGL
    ImGui_ImplOpenGL3_Shutdown();
    // Destroy GLFW backend
    ImGui_ImplGlfw_Shutdown();
    // Free the internal ImGui data
    ImGui::DestroyContext();
}
