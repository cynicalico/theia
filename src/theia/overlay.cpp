#include "theia/overlay.hpp"
#include "theia/dear.hpp"

void theia::draw_overlay() {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    Dear::Begin("##FPS", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize) &&
        [] { Dear::Text("{:.2f} fps", ImGui::GetIO().Framerate); };

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x, 0), ImGuiCond_Always, ImVec2(1, 0));
    Dear::Begin("##Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize) &&
        [] { Dear::TabBar("tabs") && [] { Hermes::instance().publish<OverlayTabEvent>(); }; };
}
