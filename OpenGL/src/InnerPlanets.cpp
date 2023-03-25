#include "InnerPlanets.h"
#include "simulation/CelestialBody.hpp"
#include "simulation/NBodyInterface.hpp"
#include "simulation/SymplecticEuler.hpp"
#include "simulation/PhysicsConstants.h"
#include "imgui.h"
#include <iostream>

namespace InnerPlanetsUI
{
    void Simulate(bool symplecticEuler, std::vector<std::shared_ptr<std::pair<std::string, bool>>> CelestialBodies, int Results_Rows, int Steps)
    {
        //Position data from JPL Horizons database dated: 01/01/2005
        std::shared_ptr<CelestialBody> Moon_ = std::make_shared<CelestialBody>(-27440663.8165208e3, 144729193.335639e3, 24808.236184314e3,
            -30.074128500212e3, -6.5095675566316e3, -0.057508367552749e3, PhysicsConstants::moonMass, PhysicsConstants::moonRadius);

        std::shared_ptr<CelestialBody> Earth_ = std::make_shared<CelestialBody>(-27067884.6257174e3, 144587718.527863e3, -1969.59490492195e3,
            -29.7609559402974e3, -5.58170729426966e3, 7.82453662445448e-1, PhysicsConstants::earthMass, PhysicsConstants::earthRadius);

        std::shared_ptr<CelestialBody> Sun_ = std::make_shared<CelestialBody>(0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, PhysicsConstants::sunMass, PhysicsConstants::sunRadius);

        std::shared_ptr<CelestialBody> Mercury_ = std::make_shared<CelestialBody>(-5.912134174085139e10, -1.122619296617797e10, 4.544945202497724e9,
            4.014526967381349e2, -4.597153609729074e4, -3.849231669600432e3, PhysicsConstants::mercuryMass, PhysicsConstants::mercuryRadius);

        std::shared_ptr<CelestialBody> Venus_ = std::make_shared<CelestialBody>(-7.094183693077585e10, -8.250232669178858e10, 2.956505086981911e9,
            2.819437134554216e4, -2.321446579433773e4, -2.076543268683134e3, PhysicsConstants::venusMass, PhysicsConstants::venusRadius);
        std::vector<std::shared_ptr<CelestialBody>> InnerPlanets(Results_Rows);
        int PlanetVector_counter = 0;
        if (CelestialBodies[0]->second)
        {
            InnerPlanets[PlanetVector_counter] = Moon_;
            PlanetVector_counter++;
        }
        if (CelestialBodies[1]->second)
        {
            InnerPlanets[PlanetVector_counter] = Earth_;
            PlanetVector_counter++;
        }
        if (CelestialBodies[2]->second)
        {
            InnerPlanets[PlanetVector_counter] = Sun_;
            PlanetVector_counter++;
        }
        if (CelestialBodies[3]->second)
        {
            InnerPlanets[PlanetVector_counter] = Mercury_;
            PlanetVector_counter++;
        }
        if (CelestialBodies[4]->second)
        {
            InnerPlanets[PlanetVector_counter] = Venus_;
        }

        std::unique_ptr<NBodyInterface> InnerPlanetInterface = std::make_unique<NBodyInterface>(InnerPlanets);

        std::unique_ptr<SymplecticEuler> InnerPlanetSolver = std::make_unique<SymplecticEuler>(*InnerPlanetInterface, 0, PhysicsConstants::earth_T0, PhysicsConstants::earth_T0 / Steps, "output_InnerPlanets.dat");
        InnerPlanetSolver->Solve();


        //std::vector<double> Output(3*Results_Rows);
        //return Output;
    }

//-----------------------------------------------------------------------------------------------------------------------------------------------
    void RenderUI(std::vector<std::shared_ptr<std::pair<std::string, bool>>>& CelestialBodies)
    {
        struct CustomConstraints
        {
        #define IM_MIN(A, B)            (((A) < (B)) ? (A) : (B))
        #define IM_MAX(A, B)            (((A) >= (B)) ? (A) : (B))
        #define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))
            // Helper functions to demonstrate programmatic constraints
            // FIXME: This doesn't take account of decoration size (e.g. title bar), library should make this easier.
            static void AspectRatio(ImGuiSizeCallbackData* data) { float aspect_ratio = *(float*)data->UserData; data->DesiredSize.x = IM_MAX(data->CurrentSize.x, data->CurrentSize.y); data->DesiredSize.y = (float)(int)(data->DesiredSize.x / aspect_ratio); }
            static void Square(ImGuiSizeCallbackData* data) { data->DesiredSize.x = data->DesiredSize.y = IM_MAX(data->CurrentSize.x, data->CurrentSize.y); }
            static void Step(ImGuiSizeCallbackData* data) { float step = *(float*)data->UserData; data->DesiredSize = ImVec2((int)(data->CurrentSize.x / step + 0.5f) * step, (int)(data->CurrentSize.y / step + 0.5f) * step); }
            // Make the UI compact because there are so many fields
            static void PushStyleCompact()
            {
                ImGuiStyle& style = ImGui::GetStyle();
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));
            }
            static void PopStyleCompact()
            {
                ImGui::PopStyleVar(2);
            }
            // Helper to display a little (?) mark which shows a tooltip when hovered.
            static void HelpMarker(const char* desc)
            {
                ImGui::TextDisabled("(?)");
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
                {
                    ImGui::BeginTooltip();
                    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                    ImGui::TextUnformatted(desc);
                    ImGui::PopTextWrapPos();
                    ImGui::EndTooltip();
                }
            }
        };
        //Styling
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 5.0f;
        style.FrameRounding = 2.0f;
        style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.75f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 0.50f);
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
        style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
        style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.01f, 0.50f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.00f, 0.01f, 0.50f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.00f, 0.01f, 0.50f);
        style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
        style.Colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.01f, 0.50f);
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.01f, 0.50f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.00f, 0.00f, 0.01f, 0.50f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.01f, 0.00f);          
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.00f, 0.01f, 0.00f);
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.00f, 0.01f, 0.00f);
        
        // Options
        static bool auto_resize = false;
        static int type = 0; // Aspect Ratio
        // Submit constraint
        float aspect_ratio = 18.0f / 11.0f;
        float fixed_step = 150.0f;
        if (type == 0) ImGui::SetNextWindowSizeConstraints(ImVec2(500, 280), ImVec2(500, 280));         // Between 100x100 and 500x500
        if (type == 1) ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
        if (type == 2) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0), ImVec2(-1, FLT_MAX));      // Vertical only
        if (type == 3) ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1), ImVec2(FLT_MAX, -1));      // Horizontal only
        if (type == 4) ImGui::SetNextWindowSizeConstraints(ImVec2(400, -1), ImVec2(500, -1));          // Width Between and 400 and 500
        if (type == 5) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::AspectRatio, (void*)&aspect_ratio);   // Aspect ratio
        if (type == 6) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);                              // Always Square
        if (type == 7) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Step, (void*)&fixed_step);            // Fixed Step
        // Submit window
        static int location = 0;
        ImGuiIO& io = ImGui::GetIO();

        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 work_size = viewport->WorkSize;
        ImVec2 window_pos, window_pos_pivot;
        window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);


        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
        if (ImGui::Begin("Planetary Orbits", nullptr))
        {
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Center", NULL, location == -2)) location = -2;
                if (ImGui::MenuItem("Top-left", NULL, location == 0)) location = 0;
                if (ImGui::MenuItem("Top-right", NULL, location == 1)) location = 1;
                if (ImGui::MenuItem("Bottom-left", NULL, location == 2)) location = 2;
                if (ImGui::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
                ImGui::EndPopup();
            }
        }
        ImGui::Text("Please choose which celestial bodies you want to include in the simulation");

        ImGui::Dummy(ImVec2(10.0f, 0.0f));

        //Bold font
        auto boldFont = io.Fonts->Fonts[0];

        //Main table
        enum ContentsType { CT_Text, CT_FillButton };
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        static bool display_headers = false;
        static int contents_type = CT_Text;
        CustomConstraints::PushStyleCompact();
        CustomConstraints::PopStyleCompact();
        if (ImGui::BeginTable("table1", 4, flags))
        {
            ImGui::PushFont(boldFont);
            ImGui::TableSetupColumn("Celestial Body");
            ImGui::TableSetupColumn("x");
            ImGui::TableSetupColumn("y");
            ImGui::TableSetupColumn("z");
            ImGui::TableHeadersRow();
            ImGui::PopFont();

            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Checkbox(CelestialBodies[row]->first.c_str(), &CelestialBodies[row]->second);
                if (row == 2)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("0.0");
                    ImGui::TableNextColumn();
                    ImGui::Text("0.0");
                    ImGui::TableNextColumn();
                    ImGui::Text("0.0");
                }
                else
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("x");
                    ImGui::TableNextColumn();
                    ImGui::Text("y %d");
                    ImGui::TableNextColumn();
                    ImGui::Text("z %d");
                }
            }

            ImGui::EndTable();
        }


        static bool clickedSim = false;;
        ImGui::Spacing();
        ImGui::PushFont(boldFont);
        //Ensuring more than 1 selected 
        int Results_Rows = 0;
        for (const auto& i : CelestialBodies)
        {
            Results_Rows += i->second;
        }
        if (Results_Rows <= 1)
        {
            ImGui::Text("Please choose more than 1 celestial body");
            clickedSim = false;
        }
        if (Results_Rows >= 2)
        {
            //Start sim and end sim 
            if (ImGui::SmallButton("Start simulation"))
            {
                clickedSim = true;
            }
            ImGui::SameLine();
            ImGui::SetCursorPosX(370); //moves stop button by 370 to the right
            if (ImGui::SmallButton("Stop simulation"))
            {
                clickedSim = false;
            }
            if (clickedSim)
            {
                ImGui::Text("Simulating...");
            }
        }
        ImGui::PopFont();
        //ImGui::ShowDemoWindow();

        ImGui::End();

        //Simulation


        //Results window
        //Sizing and position
        ImGui::SetNextWindowSizeConstraints(ImVec2(500, 280), ImVec2(500, 280));
        const int location_res = 2;
        const ImGuiViewport* viewport_res = ImGui::GetMainViewport();
        work_pos = viewport_res->WorkPos;
        work_size = viewport_res->WorkSize;
        window_pos, window_pos_pivot;
        window_pos.x = (location_res & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (location_res & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (location_res & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (location_res & 2) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

        if (clickedSim)
        {
            ImGui::Begin("Results");
            if (ImGui::BeginTable("table1", 4, flags))
            {
                ImGui::PushFont(boldFont);
                ImGui::TableSetupColumn("Celestial Body");
                ImGui::TableSetupColumn("x");
                ImGui::TableSetupColumn("y");
                ImGui::TableSetupColumn("z");
                ImGui::TableHeadersRow();
                ImGui::PopFont();

                for (int row = 0; row < 5; row++)
                {
                    if (CelestialBodies[row]->second)
                    {
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();
                        ImGui::Text(CelestialBodies[row]->first.c_str());
                        ImGui::TableNextColumn();
                        ImGui::Text("x");
                        ImGui::TableNextColumn();
                        ImGui::Text("y %d");
                        ImGui::TableNextColumn();
                        ImGui::Text("z %d");
                    }
                }
                ImGui::EndTable();
            }
            ImGui::End();
        }



        //Info window
        //Sizing and position
        ImGui::SetNextWindowSizeConstraints(ImVec2(270, 280), ImVec2(270, 280));
        const int location_info = 1;
        const ImGuiViewport* viewport_info = ImGui::GetMainViewport();
        work_pos = viewport_info->WorkPos;
        work_size = viewport_info->WorkSize;
        window_pos, window_pos_pivot;
        window_pos.x = (location_info & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
        window_pos.y = (location_info & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
        window_pos_pivot.x = (location_info & 1) ? 1.0f : 0.0f;
        window_pos_pivot.y = (location_info & 2) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

        ImGui::Begin("Information");
        ImGui::BeginGroup();
        ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
        ImGui::Separator();
        if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Description"))
            {
                ImGui::TextWrapped("This is a simple model of the N-Body problem with the 3 inner most planets and their orbits of the Sun, along with Earth's moon.");
                ImGui::TextWrapped("The N-Body problem is represented by a second order ODE IVP, and here solved by the symplectic Euler method.");
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Data"))
            {
                ImGui::TextWrapped("All inital position and velocity data is sourced from JPL Horizons, dated 01/01/2005.");
                ImGui::TextWrapped("The current time period for the simulation is the orbital period of the Earth, which is approximated as XXeXXs");
                ImGui::TextWrapped("The centre of the co-ordinate system is the initial position of the centre of the Sun, (0.0,0.0,0.0).");
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Future work"))
            {
                ImGui::TextWrapped("More features are in production. One of these is the graphical demonstration of the orbits of each celestial body via OpenGL. The velocities of each object, and a comaprison with tbe forward Euler method are also in the works.");
                ImGui::TextWrapped("Any feedback is appreciated.");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::EndChild();
        ImGui::EndGroup();

        ImGui::End();



    }
}