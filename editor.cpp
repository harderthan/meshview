#include "meshview/meshview_imgui.hpp"
#include "meshview/meshview.hpp"
#include "dialog/file_browser.hpp"
#include "Eigen/Core"
#include "Eigen/Geometry"
#include <iostream>

using namespace meshview;

int main(int argc, char** argv) {
    Viewer viewer;
    viewer.draw_axes = true;
    viewer.camera.dist_to_center = 5.0f;

#ifdef MESHVIEW_IMGUI
    ImGui::FileBrowser fileDialog;
    fileDialog.SetTitle("file browser");
    fileDialog.SetTypeFilters({".pcd"});

    viewer.on_gui = [&]() -> bool {
        ImGui::SetNextWindowSize(ImVec2(200, 100));
        if(ImGui::Begin("point cloud dialog")) {
            if(ImGui::Button("load")) {
                fileDialog.Open();
            }
        }
        ImGui::End();

        fileDialog.Display();
        if(fileDialog.HasSelected())
        {
            std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
            fileDialog.ClearSelected();
        }
        return false;  // True to update all meshes and camera
    };
#else
    std::cout
        << "meshview was built without Dear ImGUI, no GUI will be available\n";
#endif
    viewer.show();
}