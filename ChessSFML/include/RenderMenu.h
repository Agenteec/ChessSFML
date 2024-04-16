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


    ///Переместить в отдельный класс
    static int gameMode; // Индекс выбранного режима игры
    static float moveTime; // Количество секунд на ход
    static int addTimeIndex; // Индекс выбранного времени для добавления
    static DBController db;


    static bool isControlTime;
    static bool withRating;
    static const char* gameModes[];
    static const char* addTimes[];
    static const float moveTimes[];

    ///Переместить в отдельный класс\\\

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
        // Формируем команду для открытия ссылки в браузере
        std::string command = "start " + url; // В Linux средах используется xdg-open, в Windows можно использовать start
        // Выполняем команду в командной строке
        system(command.c_str());
    }

    static void ShowRule()
    {
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.8f);
        if (showRule)
        {
            ImGui::Begin(uTC(u8"Правила"), &showRule);

            ImGui::Text(uTC(u8"Правила игры:"));
            ImGui::Text(uTC(u8"1. Цель игры: Целью игры в шахматы является мат – состояние, когда король любого из игроков находится под угрозой захвата и не имеет возможности избежать захвата."));
            ImGui::Text(uTC(u8"2. Фигуры и их ходы:"));
            ImGui::Text(uTC(u8" Король: Может ходить на любое соседнее поле."));
            ImGui::Text(uTC(u8" Ферзь : Может ходить по горизонтали, вертикали и диагонали."));
            ImGui::Text(uTC(u8" Ладья : Двигается только по горизонтали и вертикали."));
            ImGui::Text(uTC(u8" Слон : Двигается только по диагонали."));
            ImGui::Text(uTC(u8" Конь : Ходит буквой Г – два поля в одном направлении и одно перпендикулярно ему."));
            ImGui::Text(uTC(u8" Пешка : Ходит вперед на одно поле, но с начальной позиции может сделать два шага.Бьет фигуры по диагонали на одно поле.."));
            ImGui::Text(uTC(u8"3. Рокировка: Специальный ход, при котором король и ладья одновременно перемещаются. Он может быть выполнен только в случае, если ни король, ни ладья не сделали ход, и между ними нет других фигур."));
            ImGui::Text(uTC(u8"4. Взятие на проходе: Возможность пешки атаковать пешку соперника, которая двинулась на два поля из начальной позиции. Пешка противника может взять ее как будто она двигалась только на одно поле."));
            ImGui::Text(uTC(u8"5. Превращение пешки: Если пешка достигает последнего ряда доски, она должна быть заменена на фигуру, на выбор игрока."));
            ImGui::Text(uTC(u8"6. Пат: Ситуация, когда у игрока нет возможности сделать ход, но его король не находится под шахом. Это объявляется ничьей."));
            ImGui::Text(uTC(u8"7. Мат: Ситуация, когда король находится под прямой атакой и не имеет возможности избежать захвата."));

            if (ImGui::Button(uTC(u8"Итальянская партия")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/gK5JfSwK");
            }
            ImGui::SameLine();
            if (ImGui::Button(uTC(u8"Приятный Ферзевй Гамбит")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/CnvGZGnf");
            }
            ImGui::SameLine();

            if (ImGui::Button(uTC(u8"Дебют Сокольского")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/jjXjIEgi");
            }
            if (ImGui::Button(uTC(u8"Дебют четырёх коней")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/pBeyrqxN");
            }
            ImGui::SameLine();

            if (ImGui::Button(uTC(u8"Русская партия")))
            {
                OpenURL("https://lichess.org/study/QUXJ1WH3/2kPECrhW");
            }
            ImGui::SameLine();

        }

        // Выбор режима игры

        if (ImGui::Button(uTC(u8"Отмена")))
        {
            showRule = 0;
        }

        // Завершение окна ImGui

        ImGui::End();

    }

    static void ShowProfile()
    {
        ImGui::Begin(uTC(u8"Управление профилями"), &showProfile);
        if (db.users.empty())
        {
            ImGui::Text(uTC(u8"Пользователь не выбран, добавьте пользователя"));
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
        ImGui::InputText(uTC(u8"Имя пользователя"), nameBuffer, IM_ARRAYSIZE(nameBuffer));
        if (ImGui::Button(uTC(u8"Добавить"))) {
            db.createUser(nameBuffer);
            memset(nameBuffer, 0, sizeof(nameBuffer));
        }

        ImGui::Text(uTC(u8"Список пользователей:"));
        if (ImGui::BeginTable("##table1", 3)) {
            ImGui::TableSetupColumn(uTC(u8"Имя"));
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
                if (ImGui::Button((uTC(u8"Удалить##") + std::to_string(user.id)).c_str())) {
                    db.deleteUser(user.id);
                }
                ImGui::SameLine();
                if (ImGui::Button((uTC(u8"Выбрать##") + std::to_string(user.id)).c_str())) {
                    userId = user.id;
                }

            }

            ImGui::EndTable();
        }

        ImGui::End();
    }

    
    static void ShowControlSettings()
    {
        if (ImGui::CollapsingHeader(uTC(u8"Клавиатура")))
        {
            #pragma region Прыжок
            ImGui::Text((uTC(u8"Прыжок")));
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

            

            ImGui::Text(uTC(u8"Атака"));
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
        ImGui::Text(uTC(u8"Настройки графики"));
        ImGui::SliderFloat(uTC(u8"Яркость"), &tempSettings.video.brightness, 0.0f, 1.0f);
        ImGui::Text(uTC(u8"Размер окна"));
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
        ImGui::Checkbox(uTC(u8"Полный экран"), &tempSettings.video.FullScreen);
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
        ImGui::Begin(uTC(u8"Создание локальной игры"),&showLocalGame);

        // Выбор режима игры

        ImGui::Text(uTC(u8"Игровой режим:"));
        ImGui::ListBox("##gamemode", &RenderMenu::gameMode, gameModes, 1, 4);

        // Выбор контроля времени
        if (RenderMenu::gameMode != 7)
        {
            ImGui::Checkbox(uTC(u8"Контроль времени"), &isControlTime);
            if (isControlTime)
            {
                ImGui::Text(uTC(u8"Контроль времени:"));
                ImGui::SliderFloat(uTC(u8"Время на партию"), &moveTime, 30.0f, 3600.0f, "%.0f sec");
                ImGui::Combo(uTC(u8"Добавление секунд на ход"), &addTimeIndex, addTimes, 6);
            }
            ImGui::Checkbox(uTC(u8"Рейтинговая партия"), &withRating);
            // Кнопки "Запуск" и "Отмена"
        }
        

        if (ImGui::Button(uTC(u8"Запуск")))
        {
            showRenderMenu = false;
            showLocalGame = false;

            OnGameGUI = true;

            printf("Starting game...\n");
        }

        ImGui::SameLine();

        if (ImGui::Button(uTC(u8"Отмена")))
        {
            showLocalGame = 0;
        }

        // Завершение окна ImGui

        ImGui::End();

    }

    static void ShowNetworkGame()
    {
        ImGui::Begin(uTC(u8"Создание сетевой игры"), &showNetworkGameCreator);

        // Выбор режима игры

        ImGui::Text(uTC(u8"Игровой режим:"));
        ImGui::ListBox("##gamemode", &RenderMenu::gameMode, gameModes, 1, 4);

        // Выбор контроля времени

        if (RenderMenu::gameMode != 7)
        {
            ImGui::Checkbox(uTC(u8"Контроль времени"), &isControlTime);
            if (isControlTime)
            {
                ImGui::Text(uTC(u8"Контроль времени:"));
                ImGui::SliderFloat(uTC(u8"Время на партию"), &moveTime, 30.0f, 3600.0f, "%.0f sec");
                ImGui::Combo(uTC(u8"Добавление секунд на ход"), &addTimeIndex, addTimes, 6);
            }
            //ImGui::Checkbox(uTC(u8"Рейтинговая партия"), &withRating);
            // Кнопки "Запуск" и "Отмена"
        }


        if (ImGui::Button(uTC(u8"Запуск")))
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

        if (ImGui::Button(uTC(u8"Отмена")))
        {
            showNetworkGameCreator = 0;
        }


        ImGui::End();

    }

    static void NetworkMenu()
    {
        ImGui::Begin(uTC(u8"Сетевая игра"),&showNetworkGame);

        ImGui::Text(uTC(u8"Подключение к серверу"));
        static char serverAddress[64] = "127.0.0.1"; // IP-адрес сервера
        ImGui::InputText(uTC(u8"Адрес сервера"), serverAddress, 64);

        if (ImGui::Button(uTC(u8"Подключиться"))) {
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


        //ImGui::Text(uTC(u8"Список доступных игр"));
        //static std::vector<std::string> games;// = GetAvailableGames(); // Получение списка доступных игр
        //games.push_back("127.0.0.1");
        //static int selectedGame = 0; // Индекс выбранной игры
        //static bool gameListChanged = true; // Флаг изменения списка игр
        //if (ImGui::BeginListBox(uTC(u8"##Список игр"), ImVec2(-1, 100))) {
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

        //if (ImGui::Button(uTC(u8"Обновить список игр"))) {
        //    // Обработка нажатия на кнопку "Обновить список игр"
        //    //games = GetAvailableGames();
        //    gameListChanged = true;
        //}

        ImGui::Separator();

        if (ImGui::Button(uTC(u8"Создать новую игру"))) {
            showNetworkGameCreator = true;
        }

        //if (ImGui::Button(uTC(u8"Присоединиться к выбранной игре"))) {
        //    // Обработка нажатия на кнопку "Присоединиться к выбранной игре"
        //    if (selectedGame >= 0 && selectedGame < games.size()) {
        //        //JoinGame(games[selectedGame]);
        //    }
        //}

        ImGui::End();
    }

    static void SerwerWait()
    {
            ImGui::Begin(uTC(u8"Waiting for opponent"), &is_server_waiting, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
            ImGui::Text(uTC(u8"Пожалуйста, подождите пока к вам не подключится опонент..."));
            if (ImGui::Button(uTC(u8"Отмена")))
            {
                //is_cancelled = true;
            }
            ImGui::End();
        
    }

    static void ImGuiFunctionDebug() {
        // Создаем статические переменные для отслеживания времени и FPS


        // Обновляем время прошедшее с последнего обновления кадра
        const float current_time = ImGui::GetTime();
        deltaTime = current_time - lastFrameTime;
        lastFrameTime = current_time;
        fps = 1.0f / deltaTime;

        // Отображаем значение FPS
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
            ImGui::Begin(uTC(u8"Настройки"), &showSettings);

            if (ImGui::Button(uTC(u8"Графика")))
            {
                ShowGraphicsSettings = true;
                //showControlsSettings = false;
                //showSoundSettings = false;
            }
            /*ImGui::SameLine();
            if (ImGui::Button(uTC(u8"Управление")))
            {
                ShowGraphicsSettings = false;
                showControlsSettings = true;
                showSoundSettings = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(uTC(u8"Звук")))
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
            //    ImGui::Text(uTC(u8"Настройки управления"));
            //    ShowControlSettings();
            //}
            //else if (showSoundSettings)
            //{
            //    ImGui::Text(uTC(u8"Настройки звука"));
            //    ImGui::SliderFloat(uTC(u8"Громкость окружения"), &tempSettings.volume.ambientVolume, 0.0f, 1.0f);
            //    ImGui::SliderFloat(uTC(u8"Громкость музыки"), &tempSettings.volume.musicVolume, 0.0f, 1.0f);
            //}

            ImGui::Separator();

            ImGui::SetCursorPos(ImVec2(ImGui::GetWindowContentRegionMax().x - 300, ImGui::GetWindowContentRegionMax().y - 50));

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 0)); 
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); 
            if (ImGui::Button(uTC(u8"Ок"), ImVec2(80, 0))) {

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
            if (ImGui::Button(uTC(u8"Отмена"), ImVec2(80, 0))) {

                tempSettings = CGlobalSettings;
                showSettings = false;
            }
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();


            ImGui::SameLine();
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 0));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.8f, 1.0f));
            if (ImGui::Button(uTC(u8"Применить"), ImVec2(100, 0))) {
                // Действия, выполняемые при нажатии на кнопку
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
        // Создание главного окна imgui
        ImGui::SetNextWindowSizeConstraints(ImVec2(RenderMenu::CGlobalSettings.video.WinW, RenderMenu::CGlobalSettings.video.WinH), ImVec2(FLT_MAX, FLT_MAX));
        ImGui::SetNextWindowSize(ImVec2(RenderMenu::CGlobalSettings.video.WinW, RenderMenu::CGlobalSettings.video.WinH), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.25f);
        ImGui::Begin(VersionBuildStr.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

        // Отрисовка кнопок
        ImGui::Dummy(ImVec2(10.0f, RenderMenu::CGlobalSettings.video.WinH / 2));
        if (OnGameGUI)
            if (ImGui::Button(uTC(u8"Завершить игру"), ImVec2(200.f, 50.f)))
            {
                
                OnGameGUI = false;
            }
        if (!OnGameGUI)
        if (ImGui::Button(uTC(u8"Локальная игра"), ImVec2(200.f, 50.f)))
        {
            
            showLocalGame = true;
        }
        ImGui::Spacing();
        if (!OnGameGUI)
        if (ImGui::Button(uTC(u8"Сетевая игра"), ImVec2(200.f, 50.f)))
        {
            showNetworkGame = true;
        }
        if (!OnGameGUI)
        if (ImGui::Button(uTC(u8"Профили"), ImVec2(200.f, 50.f)))
        {
            showProfile = true;
        }
        //ImGui::Spacing();
        //if (!OnGameGUI)
        //if (ImGui::Button(uTC(u8"Загрузить игру"), ImVec2(200.f, 50.f)))
        //{
        //    
        //}
        ImGui::Spacing();
        if (ImGui::Button(uTC(u8"Настройки"), ImVec2(200.f, 50.f)))
        {
            showSettings = true;
        }
        ImGui::Spacing();
        if (ImGui::Button(uTC(u8"Справка"), ImVec2(200.f, 50.f)))
        {
            showRule = true;
        }
        ImGui::Spacing();
        if (ImGui::Button(uTC(u8"Выход"), ImVec2(200.f, 50.f)))
        {
            window->close();
        }

        // Закрытие главного окна imgui
        ImGui::End();
        return 0;
	}
    

};

