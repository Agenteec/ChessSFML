#pragma once
#include "RenderMenu.h"
#include "CSettings.h"
#include "ChessBoard.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <sstream>
#include <iomanip>


struct MoveFrTo
{
    int piecef;
    int pieceto;
    sf::Vector2i from;
    sf::Vector2i to;
    MoveFrTo(sf::Vector2i from, sf::Vector2i to, int piecef, int pieceto) :from(from), to(to), piecef(piecef), pieceto(pieceto) {}
};
struct MoveWB
{
    MoveFrTo White;
    MoveFrTo Black;
    MoveWB(MoveFrTo White, MoveFrTo Black) :White(White), Black(Black) {}

};
class OnGameUI
{
    
public:
    static float& WinW;
    static float& WinH;

    OnGameUI(){}
    string MoveToStr(MoveFrTo move)
    {
       
        if (move.piecef == EMPTYPiece)
            return "-";
        std::string s = "";
        if(move.piecef == WKing)
        {
            if (move.to.y - move.from.y == 2)
            {
                return "0-0";
            }
            if (move.to.y - move.from.y <= -2)
            {
                return "0-0-0";
            }
        }
        if (move.piecef == BKing)
        {
            if (move.to.y - move.from.y == 2)
            {
                return "O-O";
            }
            if (move.to.y - move.from.y <= -2)
            {
                return "O-O-O";
            }
        }
       
        s += char(move.from.y + 'A');
        s += char(move.from.x +'1');
        
        s += '-';
        s += char(move.to.y + 'A');
        s += char(move.to.x +'1');
        
        return s;
    }
    void draw(int HBoard,vector <MoveWB> moves)
    {
        ImGui::SetNextWindowSize(ImVec2(WinW / 5.1, WinH / 4));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.5f);
        ImGui::Begin("Chess Game", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos("Chess Game", ImVec2(ImVec2(WinW+WinW/3, WinH/4)));
        // Отображаем шахматные ходы
        
        for (size_t i = 0; i < moves.size(); i++)
        {
            
            if (ImGui::Button(MoveToStr(moves[i].White).c_str()))
            {
                
                std::cout << " Ход \n";
            }
            ImGui::SameLine();
            if(moves[i].Black.piecef!=EMPTYPiece)
            if (ImGui::Button(MoveToStr(moves[i].Black).c_str()))
            {
                
                std::cout << " Ход \n";
            }
            ImGui::Columns();
        }
        // Заканчиваем окно ImGui
        ImGui::End();
    }
    void RenderChessMovesWindow(int HBoard, vector <MoveWB> moves,bool& back, bool& NetMoveback, bool& MyMoveBack,int& rotation, string& message)
    {
        ImGui::SetNextWindowSize(ImVec2(WinW / 2.5, WinH / 3.5));
        ImGui::SetNextWindowPos(ImVec2(WinW / 0.75, WinH / 4.555));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.5f);
        ImGui::Begin("Chess Game", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        // Кнопки для сдачи, ничьей и отмены хода
        ImGui::BeginGroup();

        //ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 200, 10)); // Установка положения курсора внутри группы
            if (MyMoveBack)
            {
                
                if (ImGui::Button(uTC(u8"Отменить отмену хода")))
                {
                    message = ("bd");
                    back = false;
                    MyMoveBack = false;
                    NetMoveback = false;
                }
            }
            else if (NetMoveback)
            {
                
                ImGui::Text(uTC(u8"Противник хочет отменить последний ход"));
                ImGui::Spacing();
                if (ImGui::Button(uTC(u8"Отменить отмену хода")))
                {
                    back = false;
                    MyMoveBack = false;
                    NetMoveback = false;
                    message = ("bd");
                }
                ImGui::SameLine();
                if (ImGui::Button(uTC(u8"Ок")))
                {
                    back = true;
                    MyMoveBack = true;
                    NetMoveback = true;
                    message = ("ba");
                }
            }
            else
            {
                /*ImGui::SetCursorPos(ImVec2(0, 30));*/
                if (ImGui::Button(uTC(u8"Сдаться")))
                {
                    message = ("ml");
                }

                ImGui::SameLine();
                if (ImGui::Button(uTC(u8"Ничья")))
                {
                    message = ("md");
                }

                ImGui::SameLine();
                if (ImGui::Button(uTC(u8"Отменить ход")))
                {
                    message = ("b");
                    back = true;
                    MyMoveBack = true;
                }
            }
            ImGui::Spacing();
            if (ImGui::Button(uTC(u8"Повернуть доску")))
            {
                rotation++;
                if (rotation >=5)
                {
                    rotation = 1;
                }

            }
        
        
        

        ImGui::EndGroup();
        // Колонка ходов белых
        ImGui::Text(uTC(u8"Ходы белых/чёрных"));
        ImGui::Separator();
        ImGui::Columns(2, "moves_columns", true);

        for (auto& move : moves)
        {
            if (ImGui::Button(MoveToStr(move.White).c_str()))
            {
                // Обработка нажатия на ход белых
            }
            ImGui::NextColumn();
            if (ImGui::Button(MoveToStr(move.Black).c_str()))
            {
                // Обработка нажатия на ход чёрных
            }
            ImGui::NextColumn();
        }

        ImGui::Columns(1);
        
        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 50); // Установка положения курсора по горизонтали перед рисованием текста


        //↺

        ImGui::End();
        
    }
    void WinDraw(int i,bool& b)
    {
        ImGui::SetNextWindowSize(ImVec2(WinW / 5, WinH /6));

        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.5f);
        switch (i)
        {case 0:
            ImGui::Begin(uTC(u8"Ничья!"), &b);
            break;
        case 1:
            ImGui::Begin(uTC(u8"Белые победили!"), &b);
            break;
        case 2:
            ImGui::Begin(uTC(u8"Чёрные победили!"), &b);
            break;
        default:
            break;
        }
        if (ImGui::Button(uTC(u8"Ок")))
        {
            b = false;
        }
        ImGui::End();

    }
    void drawChessClock(sf::RenderWindow* window) {
        static bool isPaused = true;
        static bool isBlackTurn = false;
        static int whiteTime = 60*100;
        static int blackTime = 60;
        static sf::Clock ClockT;

        //ImGui::SFML::Update(*window, ClockT.restart());
        ClockT.restart();
        ImGui::Begin("Chess Clock");

        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << whiteTime / 60 << ":"
            << std::setw(2) << std::setfill('0') << whiteTime % 60;
        std::string whiteTimeString = ss.str();

        ss.str("");
        ss << std::setw(2) << std::setfill('0') << blackTime / 60 << ":"
            << std::setw(2) << std::setfill('0') << blackTime % 60;
        std::string blackTimeString = ss.str();

        if (!isPaused) {
            sf::Time timeElapsed = ClockT.restart();
            if (isBlackTurn) {
                blackTime -= timeElapsed.asSeconds();
                if (blackTime <= 0) {
                    blackTime = 0;
                    isPaused = true;
                }
            }
            else {
                whiteTime -= timeElapsed.asSeconds();
                if (whiteTime <= 0) {
                    whiteTime = 0;
                    isPaused = true;
                }
            }
        }

        if (ImGui::Button(isPaused ? "Start" : "Pause")) {
            isPaused = !isPaused;
        }

        if (ImGui::Button("Reset")) {
            whiteTime = 60;
            blackTime = 60;
            isPaused = true;
            isBlackTurn = false;
        }

        ImGui::Text(isBlackTurn ? "Black's turn" : "White's turn");

        ImGui::Text("White: %s", whiteTimeString.c_str());
        ImGui::Text("Black: %s", blackTimeString.c_str());

        if (!isPaused) {
            ImGui::Text("Time remaining: %d", isBlackTurn ? blackTime : whiteTime);
        }

        ImGui::End();
    }

};

