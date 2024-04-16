#pragma once


#include <imgui.h>
#include "SFtoS.h"
#include "CSettings.h"
#include "OnGameUI.h"
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include <SFML/Graphics.hpp>
#include <imgui_console/imgui_console.h>
#include <cstdlib>
#include <fstream>
#include <DBController.h>

void Starter();
void SaveSettings();
void StartServer();
void scaleImage(sf::Sprite& sprite, int desiredWidth, int desiredHeight);
class RenderMenu
{
public:
    static bool showRenderMenu;


    ///����������� � ��������� �����
    static int gameMode; // ������ ���������� ������ ����
    static float moveTime; // ���������� ������ �� ���
    static int addTimeIndex; // ������ ���������� ������� ��� ����������
    static DBController db;


    static bool isControlTime;
    static bool withRating;
    static const char* gameModes[];
    static const char* addTimes[];
    static const float moveTimes[];

    ///����������� � ��������� �����\\\

    static bool OnGameGUI;
    static bool OnNetGameGUI;
    static bool Play;
    static bool showRule;

    static bool is_server_waiting;

    static bool showConsole;
    static bool showProfile;
    static bool showSettings;
    static bool showLocalGame;
    static bool showNetworkGame;
    static bool showNetworkGameCreator;
    static int userId;
    
    static bool ServerOrClient;
    //static RenderClassicChess* netGame;
    static bool ShowGraphicsSettings;
    //static bool showControlsSettings;
    //static bool showSoundSettings;

    static float deltaTime;
    static float lastFrameTime;
    static int fps;

    static bool showReloadDialog;
    static ImGuiConsole console;

    static CSettings tempSettings;

    static CSettings CGlobalSettings;

    static string VersionBuildStr;
    
    static void restart_program();
    static void ReloaderDialog();
    
    static void OpenURL(const std::string& url) {
        // ��������� ������� ��� �������� ������ � ��������
        std::string command = "start " + url; // � Linux ������ ������������ xdg-open, � Windows ����� ������������ start
        // ��������� ������� � ��������� ������
        system(command.c_str());
    }

    static void ShowRule()
    {
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.8f);
        if (showRule)
        {
            ImGui::Begin(uTC(u8"�������"), &showRule);

            ImGui::Text(uTC(u8"������� ����:"));
            ImGui::Text(uTC(u8"1. ���� ����: ����� ���� � ������� �������� ��� � ���������, ����� ������ ������ �� ������� ��������� ��� ������� ������� � �� ����� ����������� �������� �������."));
            ImGui::Text(uTC(u8"2. ������ � �� ����:"));
            ImGui::Text(uTC(u8" ������: ����� ������ �� ����� �������� ����."));
            ImGui::Text(uTC(u8" ����� : ����� ������ �� �����������, ��������� � ���������."));
            ImGui::Text(uTC(u8" ����� : ��������� ������ �� ����������� � ���������."));
            ImGui::Text(uTC(u8" ���� : ��������� ������ �� ���������."));
            ImGui::Text(uTC(u8" ���� : ����� ������ � � ��� ���� � ����� ����������� � ���� ��������������� ���."));
            ImGui::Text(uTC(u8" ����� : ����� ������ �� ���� ����, �� � ��������� ������� ����� ������� ��� ����.���� ������ �� ��������� �� ���� ����.."));
            ImGui::Text(uTC(u8"3. ���������: ����������� ���, ��� ������� ������ � ����� ������������ ������������. �� ����� ���� �������� ������ � ������, ���� �� ������, �� ����� �� ������� ���, � ����� ���� ��� ������ �����."));
            ImGui::Text(uTC(u8"4. ������ �� �������: ����������� ����� ��������� ����� ���������, ������� ��������� �� ��� ���� �� ��������� �������. ����� ���������� ����� ����� �� ��� ����� ��� ��������� ������ �� ���� ����."));
            ImGui::Text(uTC(u8"5. ����������� �����: ���� ����� ��������� ���������� ���� �����, ��� ������ ���� �������� �� ������, �� ����� ������."));
            ImGui::Text(uTC(u8"6. ���: ��������, ����� � ������ ��� ����������� ������� ���, �� ��� ������ �� ��������� ��� �����. ��� ����������� ������."));
            ImGui::Text(uTC(u8"7. ���: ��������, ����� ������ ��������� ��� ������ ������ � �� ����� ����������� �������� �������."));

            if (ImGui::Button(uTC(u8"����������� ������")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/gK5JfSwK");
            }
            ImGui::SameLine();
            if (ImGui::Button(uTC(u8"�������� ������� ������")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/CnvGZGnf");
            }
            ImGui::SameLine();

            if (ImGui::Button(uTC(u8"����� �����������")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/jjXjIEgi");
            }
            if (ImGui::Button(uTC(u8"����� ������ �����")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/pBeyrqxN");
            }
            ImGui::SameLine();

            if (ImGui::Button(uTC(u8"������� ������")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/2kPECrhW");
            }
            ImGui::SameLine();

        }

        // ����� ������ ����

        if (ImGui::Button(uTC(u8"������")))
        {
            showRule = 0;
        }

        // ���������� ���� ImGui

        ImGui::End();

    }

    static void ShowProfile()
    {
        ImGui::Begin(uTC(u8"���������� ���������"), &showProfile);
        if (db.users.empty())
        {
            ImGui::Text(uTC(u8"������������ �� ������, �������� ������������"));
        }
        else
        {
            for (const auto& user : db.users) {
                if (userId == user.id)
                {
                    
                    ImGui::Text("%s", user.name.c_str());
                }
               
            }
        }

        static char nameBuffer[64];
        ImGui::InputText(uTC(u8"��� ������������"), nameBuffer, IM_ARRAYSIZE(nameBuffer));
        if (ImGui::Button(uTC(u8"��������"))) {
            db.createUser(nameBuffer);
            memset(nameBuffer, 0, sizeof(nameBuffer));
        }

        ImGui::Text(uTC(u8"������ �������������:"));
        if (ImGui::BeginTable("##table1", 3)) {
            ImGui::TableSetupColumn(uTC(u8"���"));
            ImGui::TableSetupColumn(uTC(u8"ID"));
            ImGui::TableSetupColumn("");
            ImGui::TableHeadersRow();

            for (const auto& user : db.users) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", user.name.c_str());
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%d", user.id);
                ImGui::TableSetColumnIndex(2);
                if (ImGui::Button((uTC(u8"�������##") + std::to_string(user.id)).c_str())) {
                    db.deleteUser(user.id);
                }
                ImGui::SameLine();
                if (ImGui::Button((uTC(u8"�������##") + std::to_string(user.id)).c_str())) {
                    userId = user.id;
                }

            }

            ImGui::EndTable();
        }

        ImGui::End();
    }

    
    static void ShowControlSettings()
    {
        if (ImGui::CollapsingHeader(uTC(u8"����������")))
        {
            #pragma region ������
            ImGui::Text((uTC(u8"������")));
            ImGui::SameLine();
            ImGui::PushID("Jump");

            if (ImGui::Button(SFtoS::toString(tempSettings.controls.Jump).c_str()))
            {
                ImGui::OpenPopup("JumpKeyPopup");
            }
            if (ImGui::BeginPopup("JumpKeyPopup"))
            {
                for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
                {
                    if (ImGui::Selectable(SFtoS::toString(static_cast<sf::Keyboard::Key>(i)).c_str()))
                    {
                        tempSettings.controls.Jump = static_cast<sf::Keyboard::Key>(i);
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::EndPopup();
            }
            ImGui::PopID();
            #pragma endregion

            

            ImGui::Text(uTC(u8"�����"));
            ImGui::SameLine();
            ImGui::PushID(uTC(u8"Shoot"));
            if (ImGui::Button(SFtoS::toString(tempSettings.controls.Attack).c_str()))
            {
                ImGui::OpenPopup(uTC(u8"ShootKeyPopup"));
            }
            if (ImGui::BeginPopup(uTC(u8"ShootKeyPopup")))
            {
                for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
                {
                    if (ImGui::Selectable(SFtoS::toString(static_cast<sf::Keyboard::Key>(i)).c_str()))
                    {
                        tempSettings.controls.Attack = static_cast<sf::Keyboard::Key>(i);
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::EndPopup();
            }
            ImGui::PopID();
        }
    }

    static void showGraphicsSettings()
    {
        ImGui::Text(uTC(u8"��������� �������"));
        ImGui::SliderFloat(uTC(u8"�������"), &tempSettings.video.brightness, 0.0f, 1.0f);
        ImGui::Text(uTC(u8"������ ����"));
        ImGui::SameLine();
        ImGui::PushID("WinSize");

        std::string s;
        s = "";
        s += std::to_string((int)tempSettings.video.WinW) + "x" + std::to_string((int)tempSettings.video.WinH);
        if (ImGui::Button(s.c_str()))
        {
            ImGui::OpenPopup("WindowSize");
        }
        if (ImGui::BeginPopup("WindowSize"))
        {
            if (ImGui::Selectable("Adaptive"))
            {

                tempSettings.video.WinH = sf::VideoMode::getDesktopMode().height;
                tempSettings.video.WinW = sf::VideoMode::getDesktopMode().width;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("1920x1080"))
            {
                tempSettings.video.WinH = 1080;
                tempSettings.video.WinW = 1920;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("1366x768"))
            {
                tempSettings.video.WinW = 1366;
                tempSettings.video.WinH = 768;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("1280x720"))
            {
                tempSettings.video.WinW = 1280;
                tempSettings.video.WinH = 720;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("1024x768"))
            {
                tempSettings.video.WinW = 1024;
                tempSettings.video.WinH = 768;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("800x600"))
            {
                tempSettings.video.WinW = 800;
                tempSettings.video.WinH = 600;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("640x480"))
            {
                tempSettings.video.WinW = 640;
                tempSettings.video.WinH = 480;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::PopID();
        ImGui::Checkbox("Vsynk", &tempSettings.video.Vsynk);
        ImGui::Checkbox(uTC(u8"������ �����"), &tempSettings.video.FullScreen);
        ImGui::Text("FrameRateLimit");
        ImGui::SameLine();
        ImGui::PushID("FrameRateLimit");
        s = "";
        s += std::to_string((int)tempSettings.video.FrameRateLimit);
        if (ImGui::Button(s.c_str()))
        {
            ImGui::OpenPopup("FrameRateLimit");
        }
        if (ImGui::BeginPopup("FrameRateLimit"))
        {

            if (ImGui::Selectable("30"))
            {
                tempSettings.video.FrameRateLimit = 30;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("60"))
            {
                tempSettings.video.FrameRateLimit = 60;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("120"))
            {
                tempSettings.video.FrameRateLimit = 120;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("Off limit"))
            {
                tempSettings.video.FrameRateLimit = 0;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::PopID();

    }

    static void ShowLocalGame()
    {
        ImGui::Begin(uTC(u8"�������� ��������� ����"),&showLocalGame);

        // ����� ������ ����

        ImGui::Text(uTC(u8"������� �����:"));
        ImGui::ListBox("##gamemode", &RenderMenu::gameMode, gameModes, 1, 4);

        // ����� �������� �������
        if (RenderMenu::gameMode != 7)
        {
            ImGui::Checkbox(uTC(u8"�������� �������"), &isControlTime);
            if (isControlTime)
            {
                ImGui::Text(uTC(u8"�������� �������:"));
                ImGui::SliderFloat(uTC(u8"����� �� ������"), &moveTime, 30.0f, 3600.0f, "%.0f sec");
                ImGui::Combo(uTC(u8"���������� ������ �� ���"), &addTimeIndex, addTimes, 6);
            }
            ImGui::Checkbox(uTC(u8"����������� ������"), &withRating);
            // ������ "������" � "������"
        }
        

        if (ImGui::Button(uTC(u8"������")))
        {
            showRenderMenu = false;
            showLocalGame = false;

            OnGameGUI = true;

            printf("Starting game...\n");
        }

        ImGui::SameLine();

        if (ImGui::Button(uTC(u8"������")))
        {
            showLocalGame = 0;
        }

        // ���������� ���� ImGui

        ImGui::End();

    }

    static void ShowNetworkGame()
    {
        ImGui::Begin(uTC(u8"�������� ������� ����"), &showNetworkGameCreator);

        // ����� ������ ����

        ImGui::Text(uTC(u8"������� �����:"));
        ImGui::ListBox("##gamemode", &RenderMenu::gameMode, gameModes, 1, 4);

        // ����� �������� �������

        if (RenderMenu::gameMode != 7)
        {
            ImGui::Checkbox(uTC(u8"�������� �������"), &isControlTime);
            if (isControlTime)
            {
                ImGui::Text(uTC(u8"�������� �������:"));
                ImGui::SliderFloat(uTC(u8"����� �� ������"), &moveTime, 30.0f, 3600.0f, "%.0f sec");
                ImGui::Combo(uTC(u8"���������� ������ �� ���"), &addTimeIndex, addTimes, 6);
            }
            //ImGui::Checkbox(uTC(u8"����������� ������"), &withRating);
            // ������ "������" � "������"
        }


        if (ImGui::Button(uTC(u8"������")))
        {
            StartServer();
            is_server_waiting = true;
            showRenderMenu = false;
            showLocalGame = false;
            showNetworkGameCreator = false;
            showNetworkGame = false;
            OnNetGameGUI = true;
            ServerOrClient = true;
            printf("Starting game...\n");
        }

        ImGui::SameLine();

        if (ImGui::Button(uTC(u8"������")))
        {
            showNetworkGameCreator = 0;
        }


        ImGui::End();

    }

    static void NetworkMenu()
    {
        ImGui::Begin(uTC(u8"������� ����"),&showNetworkGame);

        ImGui::Text(uTC(u8"����������� � �������"));
        static char serverAddress[64] = "127.0.0.1"; // IP-����� �������
        ImGui::InputText(uTC(u8"����� �������"), serverAddress, 64);

        if (ImGui::Button(uTC(u8"������������"))) {
            cout << serverAddress << endl;
            CGlobalSettings.network.ip = serverAddress;
            ServerOrClient = false;
            is_server_waiting = false;
            showRenderMenu = false;
            showLocalGame = false;
            showNetworkGameCreator = false;
            showNetworkGame = false;
            OnNetGameGUI = true;
            
            printf("Starting game...\n");
        }

        ImGui::Separator();


        //ImGui::Text(uTC(u8"������ ��������� ���"));
        //static std::vector<std::string> games;// = GetAvailableGames(); // ��������� ������ ��������� ���
        //games.push_back("127.0.0.1");
        //static int selectedGame = 0; // ������ ��������� ����
        //static bool gameListChanged = true; // ���� ��������� ������ ���
        //if (ImGui::BeginListBox(uTC(u8"##������ ���"), ImVec2(-1, 100))) {
        //    for (int i = 0; i < games.size(); i++) {
        //        bool isSelected = (selectedGame == i);
        //        if (ImGui::Selectable(games[i].c_str(), isSelected)) {
        //            selectedGame = i;
        //        }
        //        if (isSelected) {
        //            ImGui::SetItemDefaultFocus();
        //        }
        //    }
        //    ImGui::EndListBox();
        //}

        //if (ImGui::Button(uTC(u8"�������� ������ ���"))) {
        //    // ��������� ������� �� ������ "�������� ������ ���"
        //    //games = GetAvailableGames();
        //    gameListChanged = true;
        //}

        ImGui::Separator();

        if (ImGui::Button(uTC(u8"������� ����� ����"))) {
            showNetworkGameCreator = true;
        }

        //if (ImGui::Button(uTC(u8"�������������� � ��������� ����"))) {
        //    // ��������� ������� �� ������ "�������������� � ��������� ����"
        //    if (selectedGame >= 0 && selectedGame < games.size()) {
        //        //JoinGame(games[selectedGame]);
        //    }
        //}

        ImGui::End();
    }

    static void SerwerWait()
    {
            ImGui::Begin(uTC(u8"Waiting for opponent"), &is_server_waiting, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
            ImGui::Text(uTC(u8"����������, ��������� ���� � ��� �� ����������� �������..."));
            if (ImGui::Button(uTC(u8"������")))
            {
                //is_cancelled = true;
            }
            ImGui::End();
        
    }

    static void ImGuiFunctionDebug() {
        // ������� ����������� ���������� ��� ������������ ������� � FPS


        // ��������� ����� ��������� � ���������� ���������� �����
        const float current_time = ImGui::GetTime();
        deltaTime = current_time - lastFrameTime;
        lastFrameTime = current_time;
        fps = 1.0f / deltaTime;

        // ���������� �������� FPS
        ImGui::Begin(uTC(u8"Debug"), nullptr);
        ImGui::Text("FPS: %d", fps);
        ImGui::End();
    }


	static int ShovMenu(sf::RenderWindow* window)
	{
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.8f);
        if (showSettings)
        {
            ImGui::SetNextWindowSize(ImVec2(800, 400), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
            ImGui::Begin(uTC(u8"���������"), &showSettings);

            if (ImGui::Button(uTC(u8"�������")))
            {
                ShowGraphicsSettings = true;
                //showControlsSettings = false;
                //showSoundSettings = false;
            }
            /*ImGui::SameLine();
            if (ImGui::Button(uTC(u8"����������")))
            {
                ShowGraphicsSettings = false;
                showControlsSettings = true;
                showSoundSettings = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(uTC(u8"����")))
            {
                ShowGraphicsSettings = false;
                showControlsSettings = false;
                showSoundSettings = true;
            }*/

            if (ShowGraphicsSettings)
            {
                showGraphicsSettings();
            }
            //else if (showControlsSettings)
            //{
            //    ImGui::Text(uTC(u8"��������� ����������"));
            //    ShowControlSettings();
            //}
            //else if (showSoundSettings)
            //{
            //    ImGui::Text(uTC(u8"��������� �����"));
            //    ImGui::SliderFloat(uTC(u8"��������� ���������"), &tempSettings.volume.ambientVolume, 0.0f, 1.0f);
            //    ImGui::SliderFloat(uTC(u8"��������� ������"), &tempSettings.volume.musicVolume, 0.0f, 1.0f);
            //}

            ImGui::Separator();

            ImGui::SetCursorPos(ImVec2(ImGui::GetWindowContentRegionMax().x - 300, ImGui::GetWindowContentRegionMax().y - 50));

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 0)); 
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); 
            if (ImGui::Button(uTC(u8"��"), ImVec2(80, 0))) {

                showSettings = false;
                if (tempSettings.SetSettings(window) || tempSettings.video.FullScreen != CGlobalSettings.video.FullScreen)
                {
                    showReloadDialog = true;
                }
                CGlobalSettings = tempSettings;
            }
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();

            ImGui::SameLine();
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 0));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.3f, 0.3f, 1.0f));
            if (ImGui::Button(uTC(u8"������"), ImVec2(80, 0))) {

                tempSettings = CGlobalSettings;
                showSettings = false;
            }
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();


            ImGui::SameLine();
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 0));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.8f, 1.0f));
            if (ImGui::Button(uTC(u8"���������"), ImVec2(100, 0))) {
                // ��������, ����������� ��� ������� �� ������
                if (tempSettings.SetSettings(window)|| tempSettings.video.FullScreen != CGlobalSettings.video.FullScreen)
                {
                    showReloadDialog = true;
                }
                CGlobalSettings = tempSettings;

            }
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();
            ImGui::End();
        }
        if (showConsole)
        {
            console.Draw(&showConsole);
            ImGuiFunctionDebug();
        }
        if (showReloadDialog)
        {
            ReloaderDialog();
        }
        if (showLocalGame)
        {
            ShowLocalGame();
        }
        if (showNetworkGame)
        {
            NetworkMenu();
        }
        if (showNetworkGameCreator)
        {
            ShowNetworkGame();
        }
        if (is_server_waiting)
        {
            SerwerWait();
        }
        if (showRule)
        {
            ShowRule();
        }
        if (showProfile)
        {
            ShowProfile();
        }
        // �������� �������� ���� imgui
        ImGui::SetNextWindowSizeConstraints(ImVec2(RenderMenu::CGlobalSettings.video.WinW, RenderMenu::CGlobalSettings.video.WinH), ImVec2(FLT_MAX, FLT_MAX));
        ImGui::SetNextWindowSize(ImVec2(RenderMenu::CGlobalSettings.video.WinW, RenderMenu::CGlobalSettings.video.WinH), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.25f);
        ImGui::Begin(VersionBuildStr.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

        // ��������� ������
        ImGui::Dummy(ImVec2(10.0f, RenderMenu::CGlobalSettings.video.WinH / 2));
        if (OnGameGUI)
            if (ImGui::Button(uTC(u8"��������� ����"), ImVec2(200.f, 50.f)))
            {
                
                OnGameGUI = false;
            }
        if (!OnGameGUI)
        if (ImGui::Button(uTC(u8"��������� ����"), ImVec2(200.f, 50.f)))
        {
            
            showLocalGame = true;
        }
        ImGui::Spacing();
        if (!OnGameGUI)
        if (ImGui::Button(uTC(u8"������� ����"), ImVec2(200.f, 50.f)))
        {
            showNetworkGame = true;
        }
        if (!OnGameGUI)
        if (ImGui::Button(uTC(u8"�������"), ImVec2(200.f, 50.f)))
        {
            showProfile = true;
        }
        //ImGui::Spacing();
        //if (!OnGameGUI)
        //if (ImGui::Button(uTC(u8"��������� ����"), ImVec2(200.f, 50.f)))
        //{
        //    
        //}
        ImGui::Spacing();
        if (ImGui::Button(uTC(u8"���������"), ImVec2(200.f, 50.f)))
        {
            showSettings = true;
        }
        ImGui::Spacing();
        if (ImGui::Button(uTC(u8"�������"), ImVec2(200.f, 50.f)))
        {
            showRule = true;
        }
        ImGui::Spacing();
        if (ImGui::Button(uTC(u8"�����"), ImVec2(200.f, 50.f)))
        {
            window->close();
        }

        // �������� �������� ���� imgui
        ImGui::End();
        return 0;
	}
    

};

