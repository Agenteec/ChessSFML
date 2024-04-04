#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_console/imgui_console.h>
#include <windows.h>
#include "RenderMenu.h"
#include "CSettings.h"
#include "RenderClassicChess.h"


int main()
{
    //float Scale = 1.5f;

    Starter();
    #pragma region Время/Версия билда
    // получаем текущую дату и время
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);
    std::stringstream* ss = new stringstream;
    // форматируем дату в нужном формате
    *ss << "Alpha V(1.8.1)  ";
    *ss << std::put_time(&tm, "%d.%m.%Y") << std::endl;
    RenderMenu::VersionBuildStr = ss->str();
    delete ss;

#pragma endregion
	#pragma region Настройка конслоси Windows
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	setlocale(LC_ALL, "Russian");
	#pragma endregion
	#pragma region Создание окна SFML
    sf::RenderWindow* window;
    if (!RenderMenu::CGlobalSettings.video.FullScreen)
    {
        window = new sf::RenderWindow(sf::VideoMode(RenderMenu::CGlobalSettings.video.WinW, RenderMenu::CGlobalSettings.video.WinH), "Chess counterattack", sf::Style::Close);
    }
    else
    {
        window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Chess counterattack", sf::Style::Fullscreen);
        RenderMenu::CGlobalSettings.video.WinW = sf::VideoMode::getDesktopMode().width;
        RenderMenu::CGlobalSettings.video.WinH = sf::VideoMode::getDesktopMode().height;
    }
    sf::Image icon;
    if (!icon.loadFromFile("source\\images\\icon.png"))
    {
        // Ошибка загрузки файла
    }
    // Изменение иконки окна
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window->setFramerateLimit(RenderMenu::CGlobalSettings.video.FrameRateLimit);

    // Инициализация imgui
    ImGui::SFML::Init(*window);

    // Загрузка шрифта для imgui
   // Load font
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("source\\Fonts\\impact.ttf", 20.f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

    // Update font texture
    ImGui::SFML::UpdateFontTexture();

    // Настройка стилей для imgui
    ImGui::StyleColorsDark();
    ImGui::GetStyle().WindowBorderSize = 0.f;

    // Загрузка текстур для фона
    sf::Texture texture;
    texture.loadFromFile("source\\images\\background.png");
    sf::Sprite background(texture);
    scaleImage(background, texture.getSize().x, texture.getSize().y);
    ImGui::StyleColorsDark(); // устанавливаем стиль

    ImGuiStyle& style = ImGui::GetStyle(); // получаем текущий стиль

    // изменяем цвет фона кнопок
    style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

    // изменяем цвет текста на кнопке
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    // изменяем отступ вокруг кнопки
    style.FramePadding = ImVec2(10.0f, 5.0f);

    // изменяем выравнивание текста на кнопке
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	#pragma endregion
    #pragma region Загрузка шахматных спрайтов
    
    ChessBoard CB;
    #pragma endregion

    


    #pragma region SFMLFont
    sf::Font font;
    if (!font.loadFromFile("source\\Fonts\\arial.ttf"))
    {
        std::cout << "Unable to load font!\n";
        return EXIT_FAILURE;
    }
    #pragma endregion
    #pragma region FPSText
    sf::Clock clock;
    sf::Text fpsText("0", font, 17);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition(RenderMenu::CGlobalSettings.video.WinW - 100, 5);
    #pragma endregion
    
    int r = 0, g = 0, b = 0;
    const int cellSize = 50;
    bool conection = false;
    RenderMenu::CGlobalSettings.chess.scale = 1.5;
    RenderClassicChess ChessRender;
    ChessRender.Rotate(2);
    RenderClassicChess* NetGame = nullptr;
    bool isTimeSet = false;
    //ImGuiConsole console;
	#pragma region Цикл отрисовки
        // Основной цикл
        while (window->isOpen())
        {
            
            // Обработка событий окна
            sf::Event event;
            while (window->pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed)
                    window->close();
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Tilde)
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        {
                            RenderMenu::showConsole = RenderMenu::showConsole ? 0 : 1;
                        }

                    }
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        if (RenderMenu::OnGameGUI|| RenderMenu::OnNetGameGUI)
                        {
                            RenderMenu::showRenderMenu = RenderMenu::showRenderMenu == 0 ? 1 : 0;
                        }
                        
                    }
                }
                if (RenderMenu::OnGameGUI)
                {
                    ChessRender.Mover(event, window);
                }
                if (RenderMenu::OnNetGameGUI&& NetGame!=nullptr)
                {

                    NetGame->Mover(event, window);
                }
               
               
            }
            
            // Начало отрисовки imgui
            //cout << (RenderMenu::CGlobalSettings.video.FrameRateLimit == 0 ? 120 : RenderMenu::CGlobalSettings.video.FrameRateLimit)<<endl;
            //ImGui::SFML::Update(*window, sf::seconds(1.f /(RenderMenu::CGlobalSettings.video.FrameRateLimit==0?120: RenderMenu::CGlobalSettings.video.FrameRateLimit)));
            ImGui::SFML::Update(*window, sf::seconds(1.f / 60.f));
            if (RenderMenu::showRenderMenu)
            {
                RenderMenu::ShovMenu(window);
            }
            
            #pragma region FPS
            float deltaTime = clock.restart().asSeconds();

            // Вычисляем текущее FPS
            float fps = 1.0f / deltaTime;

            // Обновляем текст с текущим FPS
            
            fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
            #pragma endregion
            if (RenderMenu::Play)
            {
                RenderMenu::Play = false;
                ChessRender.play();
            }
            if (RenderMenu::is_server_waiting)
            {

            }
            // Завершение отрисовки imgui
            window->clear();
            window->draw(background);

            if (RenderMenu::OnNetGameGUI)
            {
                if (NetGame==nullptr)
                {
                    if (RenderMenu::ServerOrClient)
                    {
                        NetGame = new RenderClassicChess(1,0);
                        NetGame->Rotate(2);
                    }
                    else
                    {
                        NetGame = new RenderClassicChess(2, 0);
                        NetGame->Rotate(3);
                    }
                    
                }
                
                NetGame->Draw(window, deltaTime);
            }
           
            if (RenderMenu::OnGameGUI)
            {
                if (!isTimeSet)
                {
                    isTimeSet = !isTimeSet;
                    ChessRender.resetTime();
                }
                ChessRender.Draw(window, deltaTime);
            }
            ImGui::SFML::Render(*window);
            
            window->draw(fpsText);
            window->display();
        }

        
        
	
	#pragma endregion
        // Очистка ресурсов imgui
        ImGui::SFML::Shutdown();
        delete window;
        SaveSettings();
	return 0;
}





//Настройки
//// Установка фиксированного размера окна
            //window.setSize(sf::Vector2u(1024, 720));

            //// Отключение масштабирования содержимого окна
            //sf::View view(sf::FloatRect(0, 0, 1024, 720));
            //window.setView(view);