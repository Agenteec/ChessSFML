#pragma once
#include "ChessBoard.h"
#include "RenderMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "NClient.h"
#include <cmath>
#include "NetParser.h"
struct LastMove
{
    int piece;
    sf::Vector2i from;
    sf::Vector2i to;
    LastMove(sf::Vector2i from, sf::Vector2i to,int piece) :from(from), to(to),piece(piece) {}
};
class RenderClassicChess
{
public:
    /// <summary>
    /// Спрайты фигур
    /// </summary>
    std::vector<SpritePiece>* SpritePieces;
    /// <summary>
    /// Текстуры фигур
    /// </summary>
    sf::Texture* ChessPicesTexture;
    /// <summary>
    /// Игровая доска
    /// </summary>
    ChessBoard Board;
    
    #pragma region Chess text
    sf::Text ChessText;
    sf::Font font;
    sf::Text Superiority;

    #pragma endregion
    int superiority;
    /// <summary>
    /// Поворот доски
    /// </summary>
    int Rotation;
    /// <summary>
    /// Осуществилось ли подключение
    /// </summary>
    bool conection;
    /// <summary>
    /// Последний ход (для взятия на проходе)
    /// </summary>
    LastMove lastmove;
    /// <summary>
    /// Игровое меню
    /// </summary>
    OnGameUI gameUI;
    /// <summary>
    /// Ход полученый от сервера
    /// </summary>
    string netMove;
    /// <summary>
    /// Совершается ли ход
    /// </summary>
    bool isMove;
    /// <summary>
    /// Индекс выбранной фигуры
    /// </summary>
    int n;
    /// <summary>
    /// Изменение координат перемещаемого объекта
    /// </summary>
    float dx, dy;
    /// <summary>
    /// Старая и новая позиция
    /// </summary>
    sf::Vector2f oldPos, newPos;
    sf::Vector2f offset;
    /// <summary>
    /// Позиция объекта для перемещения
    /// </summary>
    sf::Vector2i pos;
    /// <summary>
    /// Указатель на клиент(для подключения к серверу)
    /// </summary>
    NClient* nc;
    sf::SoundBuffer MoveSoundBuffer;
    /// <summary>
    /// Звук хода
    /// </summary>
    sf::Sound MoveSound;
    sf::SoundBuffer CaptureSoundBuffer;
    /// <summary>
    /// Звук взятия
    /// </summary>
    sf::Sound CaptureeSound;
    /// <summary>
    /// Наш последний ход для передачи серверу
    /// </summary>
    string myMove;
    /// <summary>
    /// Чей ход Белые/Чёрные
    /// </summary>
    bool WorB;


    /// <summary>
    /// Окно Победы/Ничьи
    /// </summary>
    bool WinWindow;
    bool WinWindowC;

    
    /// <summary>
    /// Шах белым
    /// </summary>
    bool WCheck;
    /// <summary>
    /// Шах чёрным
    /// </summary>
    bool BCheck;
    /// <summary>
    /// Мат белым
    /// </summary>
    bool WMate;
    /// <summary>
    /// Мат чёрным
    /// </summary>
    bool BMate;
    /// <summary>
    /// Ничья
    /// </summary>
    bool WBDraw;
    /// <summary>
    /// Просмотр предыдущих ходов
    /// </summary>
    bool IsHistory;
    /// <summary>
    /// Режим сетевой игры
    /// </summary>
    int OnNetworkGame;
    std::vector<MoveWB> Moves;
    std::vector<sf::Vector2i>* moves;
    /// <summary>
    /// Отмена хода
    /// </summary>
    bool Back;
    /// <summary>
    /// Запрос на отмену хода
    /// </summary>
    bool NetBack;

    bool MyNetBack;

    string MyPacket;
    /// <summary>
    /// В кого превращается пешка
    /// </summary>
    int TransPawn;
    /// <summary>
    /// Контроль времени
    /// </summary>
    float wTime, bTime;

    sf::Vector2i CordRotater(int x,int y)
    {
        int temp;
        int xx = x;
        int yy = y;
        switch (Rotation)
        {
        case 1:
            break;
        case 2:
            temp = xx;
            xx = Board.YMax - yy - 1;
            yy = temp;
            break;
        case 3:
            temp = yy;
            yy = Board.XMax - xx - 1;
            xx = temp;
            break;
        case 4:

            yy = Board.YMax - yy - 1;
            xx = Board.XMax - xx - 1;
            break;
        default:
            break;
        }
        return sf::Vector2i(xx, yy);
    }
    sf::Vector2i UnCordRotater(int x, int y)
    {
        int temp;
        int xx = x;
        int yy = y;
        switch (Rotation)
        {
        case 4:
            yy = Board.YMax - yy - 1;
            xx = Board.XMax - xx - 1;
            break;
        case 3:
            temp = xx;
            xx = Board.YMax - yy - 1;
            yy = temp;
            break;
        case 2:
            temp = yy;
            yy = Board.XMax - xx - 1;
            xx = temp;
            break;
        case 1:

           
            break;
        default:
            break;
        }
        return sf::Vector2i(xx, yy);
    }
    RenderClassicChess() :Board(ChessBoard()), Rotation(1), offset(sf::Vector2f(25 * RenderMenu::CGlobalSettings.chess.scale, 25 * RenderMenu::CGlobalSettings.chess.scale)), isMove(0), n(-1), dx(0), dy(0), WorB(1) ,lastmove(LastMove(sf::Vector2i(), sf::Vector2i(),12)),WCheck(false),WMate(false),BMate(false),BCheck(false),moves(nullptr),WBDraw(false),OnNetworkGame(0),conection(0),netMove("-"),myMove("-"), WinWindow(0), WinWindowC(0),nc(nullptr),Back(false),IsHistory(false),NetBack(false),MyNetBack(false),MyPacket(""),TransPawn(0), superiority(0){

        
        MoveSoundBuffer.loadFromFile("source/Sounds/Move.wav");
        CaptureSoundBuffer.loadFromFile("source/Sounds/Сapture.wav");
        MoveSound.setBuffer(MoveSoundBuffer);
        CaptureeSound.setBuffer(CaptureSoundBuffer);

        Rotation = 4;
        

        if (!font.loadFromFile("source/Fonts/arial.ttf"))
        {
            std::cout << "Unable to load font!\n";
        }
        Superiority.setFont(font);
        Superiority.setFillColor(sf::Color(0,0,0));
        Superiority.setCharacterSize(30 * RenderMenu::CGlobalSettings.chess.scale * 0.7);

        ChessText.setFont(font);
        ChessText.setCharacterSize(14 * RenderMenu::CGlobalSettings.chess.scale * 0.7);
        //ChessText.setScale(RenderMenu::CGlobalSettings.chess.scale, RenderMenu::CGlobalSettings.chess.scale);
        ChessPicesTexture = new sf::Texture[EMPTYPiece];

        ChessText.scale(RenderMenu::CGlobalSettings.chess.scale, RenderMenu::CGlobalSettings.chess.scale);

        ChessPicesTexture[WPawn].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(WPawn) + ".png");

        ChessPicesTexture[WKnight].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(WKnight) + ".png");

        ChessPicesTexture[WBishop].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(WBishop) + ".png");

        ChessPicesTexture[WRook].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(WRook) + ".png");

        ChessPicesTexture[WQueen].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(WQueen) + ".png");

        ChessPicesTexture[WKing].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(WKing) + ".png");

        ChessPicesTexture[BPawn].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(BPawn) + ".png");

        ChessPicesTexture[BKnight].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(BKnight) + ".png");

        ChessPicesTexture[BBishop].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(BBishop) + ".png");

        ChessPicesTexture[BRook].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(BRook) + ".png");

        ChessPicesTexture[BQueen].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(BQueen) + ".png");

        ChessPicesTexture[BKing].loadFromFile("source/images/ChessPiece/500png/" + ChessPieceStr(BKing) + ".png");
        SpritePieces = new std::vector<SpritePiece>;
        for (int i = 0; i < Board.XMax; ++i)
        {
            for (int j = 0; j < Board.YMax; ++j)
            {
                if (Board.board[i][j] != 12)
                {
                    sf::Sprite temp;
                    temp.setScale(0.1 * RenderMenu::CGlobalSettings.chess.scale, 0.1 * RenderMenu::CGlobalSettings.chess.scale);
                    temp.setTexture(ChessPicesTexture[Board.board[i][j]]);
                    temp.setPosition(j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                    SpritePieces->push_back(SpritePiece(temp, sf::Vector2i(i, j), (int)Board.board[i][j]));
                }
            }
        }

    }

    RenderClassicChess(int OnNetworkGame,int gamemode):RenderClassicChess::RenderClassicChess(){
        this->OnNetworkGame = OnNetworkGame;
        wTime = (RenderMenu::moveTime);
        bTime = (RenderMenu::moveTime);

    }
    void resetTime()
    {
        wTime = (RenderMenu::moveTime);
        bTime = (RenderMenu::moveTime);
    }
    void Mover(sf::Event event, sf::RenderWindow* window)
    {

        pos = sf::Mouse::getPosition(*window) - sf::Vector2i(offset);
        /////drag and drop///////
        if (event.type == sf::Event::MouseButtonPressed)
            if (event.key.code == sf::Mouse::Left)
            {
                if (moves != nullptr)
                {
                    isMove = true;
                    ReleasedMove(window);
                    delete moves;
                    moves = nullptr;
                    n = -1;
                }
                
                for (int i = 0; i < SpritePieces->size(); i++)
                    if (SpritePieces[0][i].Piece.getGlobalBounds().contains(pos.x + 25 * RenderMenu::CGlobalSettings.chess.scale, pos.y + 25 * RenderMenu::CGlobalSettings.chess.scale))
                    {
                        isMove = true; n = i;
                        dx = pos.x - SpritePieces[0][i].Piece.getPosition().x;
                        dy = pos.y - SpritePieces[0][i].Piece.getPosition().y;
                        oldPos = SpritePieces[0][i].Piece.getPosition();
                    }
            }
                

        if (event.type == sf::Event::MouseButtonReleased)
            if (event.key.code == sf::Mouse::Left)
            {
                ReleasedMove(window);
            }
    
    } 
    void ReleasedMove(sf::RenderWindow* window)
    {
        cout << n << endl;
        if (isMove && n != -1)
        {
            isMove = false;
            int min = 50;
            int xx = -1;
            int yy = -1;
            float xp = RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale;
            float yp = RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale;
            for (int i = 0; i < Board.XMax; ++i)
            {

                for (int j = 0; j < Board.YMax; ++j)
                {
                    //cout << i << " " << j << endl;
                    float temp = sqrt(pow((i * xp + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale - pos.x), 2) + pow((j * yp + RenderMenu::CGlobalSettings.video.WinH / 10 - pos.y), 2));
                    //cout << temp << endl;
                    if (temp < min)
                    {

                        min = temp;
                        xx = i;
                        yy = j;
                    }
                }
            }
            int xe = xx;
            int temp;
            int x = xx;
            int y = yy;
            cout << ChessPieceStr(SpritePieces[0][n].Type) << " " << SpritePieces[0][n].Pos.x << "/" << SpritePieces[0][n].Pos.y << endl;
            switch (Rotation)
            {
            case 1:
                break;
            case 2:
                temp = xx;
                xx = Board.YMax - yy - 1;
                yy = temp;
                break;
            case 3:
                temp = yy;
                yy = Board.XMax - xx - 1;
                xx = temp;
                break;
            case 4:

                yy = Board.YMax - yy - 1;
                xx = Board.XMax - xx - 1;
                break;
            default:
                break;
            }
            //std::cout << "(" << SpritePieces[0][n].Pos.x << ", " << SpritePieces[0][n].Pos.y << ")" << "--> (" << xx << ", " << yy << ") - 1" << std::endl;'
            //Проверка, не взял ли игорёк фигуру противника

            if (((SpritePieces[0][n].Type >= 0 && SpritePieces[0][n].Type <= 5) && (!WorB || OnNetworkGame == 2)) || ((SpritePieces[0][n].Type >= 6 && SpritePieces[0][n].Type <= 11) && (WorB || OnNetworkGame == 1)))
            {
                SpritePieces[0][n].Piece.setPosition(oldPos);
            }
            //xe - x error
            else if (xe != -1 && !(xx == SpritePieces[0][n].Pos.x && yy == SpritePieces[0][n].Pos.y) && TransPawn != -1)
            {
                int result = isValidMove(std::pair(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y), std::pair(xx, yy));
                if (0 < result)
                {

                    if (result != 7)
                    {
                        newPos = sf::Vector2f(x * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, y * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                        SpritePieces[0][n].Piece.setPosition(newPos);

                    }
                    //Если ход белых
                    if (WorB && (OnNetworkGame == 0 || OnNetworkGame == 1))
                    {

                        int del = -1;
                        //Если рокировка
                        #pragma region Рокировка
                        if (result == 7)
                        {

                            Moves.push_back(MoveWB(MoveFrTo(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), SpritePieces[0][n].Type, Board.board[xx][yy]), MoveFrTo(sf::Vector2i(-1, -1), sf::Vector2i(-1, -1), EMPTYPiece, EMPTYPiece)));
                            //Moves[Moves.size() - 1].Black = MoveFrTo(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), SpritePieces[0][n].Type, Board.board[xx][yy]);
                            lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);
                            if (SpritePieces[0][n].Pos.y - yy < 0)
                            {
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 3] = EMPTYPiece;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 1] = WRook;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 2] = WKing;
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == sf::Vector2i(0, Board.YMax - 1))
                                    {
                                        SpritePieces[0][i].Pos = sf::Vector2i(0, Board.YMax - 1 - 2);
                                        //cout << "000" << endl;
                                        posSetter(i);
                                        break;
                                    }
                                }
                                SpritePieces[0][n].Pos = sf::Vector2i(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y + 2);
                                posSetter(n);


                            }
                            else
                            {
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 4] = EMPTYPiece;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 1] = WRook;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 2] = WKing;
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == sf::Vector2i(0, 0))
                                    {
                                        SpritePieces[0][i].Pos = sf::Vector2i(0, 3);
                                        //cout << "00" << endl;
                                        posSetter(i);
                                        break;
                                    }
                                }
                                SpritePieces[0][n].Pos = sf::Vector2i(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y - 2);
                                posSetter(n);
                            }
                            MoveSound.play();
                            //lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);

                        }
                        #pragma endregion


                        else
                        {


                            if (result == 5)
                            {
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == lastmove.to) {
                                        del = i;
                                        break;
                                    }
                                }
                                Board.board[lastmove.to.x][lastmove.to.y] = EMPTYPiece;
                            }
                            Moves.push_back(MoveWB(MoveFrTo(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), SpritePieces[0][n].Type, Board.board[xx][yy]), MoveFrTo(sf::Vector2i(-1, -1), sf::Vector2i(-1, -1), EMPTYPiece, EMPTYPiece)));
                            lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                            if (result != 5)
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy)) {
                                        del = i;
                                        break;
                                    }
                                }
                            SpritePieces[0][n].Pos = sf::Vector2i(xx, yy);

                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                            //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                            if (result == 2 || result == 4)
                            {
                                sf::Sprite sp[4];
                                for (int i = 0; i < 4; i++)
                                {
                                    sp[i].setScale(0.1 * RenderMenu::CGlobalSettings.chess.scale, 0.1 * RenderMenu::CGlobalSettings.chess.scale);
                                    sp[i].setTexture(ChessPicesTexture[i + 1]);
                                    sp[i].setPosition(UnCordRotater(SpritePieces[0][n].Pos.x + 1, SpritePieces[0][n].Pos.y - 2 + i).x * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, UnCordRotater(SpritePieces[0][n].Pos.x + 1, SpritePieces[0][n].Pos.y - 2 + i).y * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                                }TransPawn = 0;
                                while (TransPawn == 0)
                                {

                                    sf::Event e;
                                    while (window->pollEvent(e))
                                    {
                                        if (e.type == sf::Event::MouseButtonPressed)
                                            if (e.key.code == sf::Mouse::Left)
                                            {
                                                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
                                                for (int i = 0; i < 4; i++)
                                                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sp[i].getGlobalBounds().contains(mousePos))
                                                    {
                                                        TransPawn = i + 1;
                                                    }
                                            }

                                    }
                                    for (int i = 0; i < 4; i++)
                                    {
                                        window->draw(sp[i]);
                                    }

                                    window->display();
                                }

                                SpritePieces[0][n].Piece.setTexture(ChessPicesTexture[TransPawn]);
                                SpritePieces[0][n].Type = TransPawn;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                                //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                            }
                            if (del != -1)
                            {
                                SpritePieces[0].erase(SpritePieces[0].begin() + del);
                                if (n >= 1)
                                {
                                    if (SpritePieces->size() - 1 < n)
                                    {
                                        for (size_t i = 0; i < SpritePieces->size(); i++)
                                        {
                                            if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy))
                                            {
                                                n = i;
                                            }
                                        }
                                    }
                                    CaptureeSound.play();
                                }
                            }
                            else
                            {
                                MoveSound.play();
                            }
                        }

                        //
                        //Проверка на шах
                        for (int i = 0; i < Board.XMax; i++)
                        {
                            for (int j = 0; j < Board.YMax; j++)
                            {
                                if (!BCheck && Board.board[i][j] == BKing)
                                {
                                    if (isValidMoveKing(std::pair(i, j), std::pair(i, j)) == 0)
                                    {
                                        BCheck = true;
                                        i = 0;
                                        j = 0;
                                    }
                                }
                                if (BCheck)
                                {
                                    //проверка на мат
                                    delete moves;
                                    moves = new vector<sf::Vector2i>;
                                    for (i = 0; i < Board.XMax; i++)
                                    {
                                        for (j = 0; j < Board.YMax; j++)
                                        {
                                            if (Board.board[i][j] > 5 && Board.board[i][j] < 12)
                                            {
                                                isValidMove(std::pair(i, j), std::pair(i, j), -1, moves, 1);
                                                for (int k = 0; k < moves->size(); k++)
                                                {
                                                    if (isValidMove(std::pair(i, j), std::pair(moves[0][k].x, moves[0][k].y)) == 0) {
                                                        moves[0].erase(moves[0].begin() + k);
                                                        k--;
                                                    }
                                                }
                                                if (moves->size() > 0)
                                                {
                                                    i = Board.XMax;
                                                    j = Board.YMax;
                                                    break;


                                                }
                                            }
                                        }
                                    }
                                    if (moves->size() == 0)
                                    {

                                        BMate = 1;

                                    }
                                    else
                                    {
                                        i = Board.XMax;
                                        j = Board.YMax;
                                        break;

                                    }


                                }
                            }
                        }
                        //Проверка на пат

                        if (!BCheck && !BMate)
                        {
                            int i;
                            int j;
                            delete moves;
                            moves = new vector<sf::Vector2i>;
                            for (i = 0; i < Board.XMax; i++)
                            {
                                for (j = 0; j < Board.YMax; j++)
                                {
                                    if (Board.board[i][j] > 5 && Board.board[i][j] < 12)
                                    {
                                        isValidMove(std::pair(i, j), std::pair(i, j), -1, moves, 1);
                                        for (int k = 0; k < moves->size(); k++)
                                        {
                                            if (isValidMove(std::pair(i, j), std::pair(moves[0][k].x, moves[0][k].y)) == 0) {
                                                moves[0].erase(moves[0].begin() + k);
                                                k--;
                                            }
                                        }

                                        if (moves->size() > 0)
                                        {

                                            i = Board.XMax;
                                            j = Board.YMax;
                                            break;


                                        }
                                    }
                                }
                            }
                            if (moves->size() == 0)
                            {

                                WBDraw = 1;

                            }

                        }
                        WCheck = 0;
                        if (BMate)
                        {
                            cout << "White win\n";
                        }
                        if (WBDraw && !BMate)
                        {
                            cout << "Draw\n";
                        }

                        delete moves;
                        moves = nullptr;
                        SendMove(lastmove.from.x, lastmove.from.y, xx, yy);
                        WorB = 0;
                    }
                    else if (OnNetworkGame == 0 || OnNetworkGame == 2)
                    {

                        #pragma region Рокировка
                        if (result == 7)
                        {

                            Moves[Moves.size() - 1].Black = MoveFrTo(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), SpritePieces[0][n].Type, Board.board[xx][yy]);
                            lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);
                            if (SpritePieces[0][n].Pos.y - yy < 0)
                            {
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 3] = EMPTYPiece;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 1] = BRook;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 2] = BKing;
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == sf::Vector2i(Board.XMax - 1, Board.YMax - 1))
                                    {
                                        SpritePieces[0][i].Pos = sf::Vector2i(Board.XMax - 1, Board.YMax - 1 - 2);
                                        //cout << "000" << endl;
                                        posSetter(i);
                                        break;
                                    }
                                }
                                SpritePieces[0][n].Pos = sf::Vector2i(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y + 2);
                                posSetter(n);


                            }
                            else
                            {
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 4] = EMPTYPiece;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 1] = BRook;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 2] = BKing;
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == sf::Vector2i(Board.XMax - 1, 0))
                                    {
                                        SpritePieces[0][i].Pos = sf::Vector2i(Board.XMax - 1, 3);
                                        //cout << "00" << endl;
                                        posSetter(i);
                                        break;
                                    }
                                }
                                SpritePieces[0][n].Pos = sf::Vector2i(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y - 2);
                                posSetter(n);
                            }
                            MoveSound.play();



                        }
                        #pragma endregion
                        else
                        {
                            int del = -1;
                            if (result == 5)
                            {
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == lastmove.to) {
                                        del = i;
                                        break;
                                    }
                                }
                                Board.board[lastmove.to.x][lastmove.to.y] = EMPTYPiece;
                            }
                            lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);
                            Moves[Moves.size() - 1].Black.from = SpritePieces[0][n].Pos;
                            Moves[Moves.size() - 1].Black.to = sf::Vector2i(xx, yy);
                            Moves[Moves.size() - 1].Black.piecef = SpritePieces[0][n].Type;
                            Moves[Moves.size() - 1].Black.pieceto = Board.board[xx][yy];
                            if (result == 2 || result == 4)
                            {
                                sf::Sprite sp[4];
                                for (int i = 0; i < 4; i++)
                                {
                                    sp[i].setScale(0.1 * RenderMenu::CGlobalSettings.chess.scale, 0.1 * RenderMenu::CGlobalSettings.chess.scale);
                                    sp[i].setTexture(ChessPicesTexture[i + BKnight]);
                                    sp[i].setPosition(UnCordRotater(SpritePieces[0][n].Pos.x - 1, SpritePieces[0][n].Pos.y - 2 + i).x * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, UnCordRotater(SpritePieces[0][n].Pos.x - 1, SpritePieces[0][n].Pos.y - 2 + i).y * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                                }TransPawn = 0;
                                while (TransPawn == 0)
                                {

                                    sf::Event e;
                                    while (window->pollEvent(e))
                                    {
                                        if (e.type == sf::Event::MouseButtonPressed)
                                            if (e.key.code == sf::Mouse::Left)
                                            {
                                                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
                                                for (int i = 0; i < 4; i++)
                                                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sp[i].getGlobalBounds().contains(mousePos))
                                                    {
                                                        TransPawn = i + 1;
                                                    }
                                            }

                                    }
                                    for (int i = 0; i < 4; i++)
                                    {
                                        window->draw(sp[i]);
                                    }

                                    window->display();
                                }

                                SpritePieces[0][n].Piece.setTexture(ChessPicesTexture[BKnight + TransPawn - 1]);
                                SpritePieces[0][n].Type = BKnight + TransPawn - 1;
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                                //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

                            }


                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                            if (result != 5)
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy)) {
                                        del = i;
                                        break;
                                    }
                                }
                            SpritePieces[0][n].Pos = sf::Vector2i(xx, yy);

                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;

                            //cout << ChessPieceStr(SpritePieces[0][n].Type) << endl;

                            if (del != -1)
                            {
                                SpritePieces[0].erase(SpritePieces[0].begin() + del);
                                if (n >= 1)
                                {
                                    if (SpritePieces->size() - 1 < n)
                                    {
                                        for (size_t i = 0; i < SpritePieces->size(); i++)
                                        {
                                            if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy))
                                            {
                                                n = i;
                                            }
                                        }
                                    }
                                    CaptureeSound.play();
                                }

                            }
                            else
                            {
                                MoveSound.play();
                            }

                        }

                        //Проверка на шах
                        for (int i = 0; i < Board.XMax; i++)
                        {
                            for (int j = 0; j < Board.YMax; j++)
                            {
                                if (!BCheck && Board.board[i][j] == WKing)
                                {
                                    if (isValidMoveKing(std::pair(i, j), std::pair(i, j)) == 0)
                                    {
                                        WCheck = true;
                                        i = 0;
                                        j = 0;
                                    }
                                }
                                if (WCheck)
                                {
                                    //проверка на мат
                                    delete moves;
                                    moves = new vector<sf::Vector2i>;
                                    for (i = 0; i < Board.XMax; i++)
                                    {
                                        for (j = 0; j < Board.YMax; j++)
                                        {
                                            if (Board.board[i][j] >= 0 && Board.board[i][j] < 6)
                                            {
                                                isValidMove(std::pair(i, j), std::pair(i, j), -1, moves, 1);
                                                for (int k = 0; k < moves->size(); k++)
                                                {
                                                    if (isValidMove(std::pair(i, j), std::pair(moves[0][k].x, moves[0][k].y)) == 0) {
                                                        moves[0].erase(moves[0].begin() + k);
                                                        k--;
                                                    }
                                                }
                                                if (moves->size() > 0)
                                                {

                                                   
                                                    i = Board.XMax;
                                                    j = Board.YMax;
                                                    break;

                                                }
                                            }
                                        }
                                    }
                                    if (moves->size() == 0)
                                    {

                                        WMate = 1;

                                    }
                                    else
                                    {
                                        
                                        i = Board.XMax;
                                        j = Board.YMax;
                                        break;
                                    }


                                }
                            }

                        }
                        //проверка на пат
                        if (!WCheck && !WMate)
                        {
                            int i, j;
                            delete moves;
                            moves = new vector<sf::Vector2i>;
                            for (i = 0; i < Board.XMax; i++)
                            {
                                for (j = 0; j < Board.YMax; j++)
                                {
                                    if (Board.board[i][j] >= 0 && Board.board[i][j] < 6)
                                    {
                                        isValidMove(std::pair(i, j), std::pair(i, j), -1, moves, 1);
                                        for (int k = 0; k < moves->size(); k++)
                                        {
                                            if (isValidMove(std::pair(i, j), std::pair(moves[0][k].x, moves[0][k].y)) == 0) {
                                                moves[0].erase(moves[0].begin() + k);
                                                k--;
                                            }
                                        }
                                        if (moves->size() > 0)
                                        {
                                            i = Board.XMax;
                                            j = Board.YMax;
                                            break;


                                        }
                                    }
                                }
                            }
                            if (moves->size() == 0)
                            {

                                WBDraw = 1;

                            }

                        }
                        if (WMate)
                        {
                            cout << "Black win\n";
                        }
                        if (WBDraw && !BMate)
                        {
                            cout << "Draw\n";
                        }
                        BCheck = 0;
                        SendMove(lastmove.from.x, lastmove.from.y, xx, yy);
                        WorB = 1;
                        delete moves;
                        moves = nullptr;
                    }
                    else
                    {
                        SpritePieces[0][n].Piece.setPosition(oldPos);
                    }


                }
                else
                    SpritePieces[0][n].Piece.setPosition(oldPos);
            }
            else if (xx == SpritePieces[0][n].Pos.x && yy == SpritePieces[0][n].Pos.y)
            {
                if (moves == nullptr)
                {
                    delete moves;
                    moves = new vector<sf::Vector2i>;
                }

                isValidMove(std::pair(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y), std::pair(xx, yy), -1, moves, 1);
                /*printf("------------------------------------------------\n");
                cout << "Размер: " << moves->size()<<endl;
                printf("------------------------------------------------\n");*/
                for (int i = 0; i < moves->size(); i++)
                {
                    if (isValidMove(std::pair(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y), std::pair(moves[0][i].x, moves[0][i].y)) == 0) {
                        moves[0].erase(moves[0].begin() + i);
                        i--;
                    }

                }

                /*printf("------------------------------------------------\n");
                cout << "Размер: " << moves->size() << endl;
                printf("------------------------------------------------\n");*/
                SpritePieces[0][n].Piece.setPosition(oldPos);
                return;
            }
            else
            {
                SpritePieces[0][n].Piece.setPosition(oldPos);
            }
            n = -1;
            
            SetSuperiority();
           
        }
    }
    void SetSuperiority()
    {
        int bs = 0;
        int ws = 0;
        for (int i = 0; i < Board.XMax; i++)
        {
            for (int j = 0; j < Board.YMax; j++)
            {
                if (Board.board[i][j] != EMPTYPiece)
                {
                    switch (Board.board[i][j])
                    {
                    case WPawn:
                        ws++;
                        break;
                    case WKnight:
                    case WBishop:
                        ws += 3;
                        break;
                    case WRook:
                        ws += 5;
                        break;
                    case WQueen:
                        ws += 9;
                        break;
                    case BPawn:
                        bs++;
                        break;
                    case BKnight:
                    case BBishop:
                        bs += 3;
                        break;
                    case BRook:
                        bs += 5;
                        break;
                    case BQueen:
                        bs += 9;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        superiority = ws - bs;
    }
    void MoveBack()
    {
        if (Moves.size() == 0)
        {
            Back = false;
            return;
        }
        if (Moves[Moves.size()-1].Black.piecef != EMPTYPiece)
        {
            bool isRook = 1;
            bool CaptureePawn = 0;
            bool untrans = false;
            //Если король
            if (Moves[Moves.size() - 1].Black.piecef == BKing)
            {
                //Сделал ближнюю рокировку
                if (Moves[Moves.size() - 1].Black.to.y - Moves[Moves.size() - 1].Black.from.y >= 2)
                {
                    //Находим ладью
                    for (size_t i = 0; i < SpritePieces->size(); i++)
                    {
                        //Вертаем обратно
                        if (SpritePieces[0][i].Pos.x == (Board.XMax - 1) && SpritePieces[0][i].Pos.y == (Board.YMax - 3))
                        {
                            //cout << "ok\n";
                            Board.board[Board.XMax - 1][Board.YMax - 3] = EMPTYPiece;
                            Board.board[Board.XMax - 1][Board.YMax - 1] = BRook;
                            SpritePieces[0][i].Pos = sf::Vector2i(Board.XMax - 1,Board.YMax - 1);
                            posSetter(i);
                            isRook = 0;
                            break;
                        }
                    }
                    for (size_t i = 0; i < SpritePieces->size(); i++)
                    {
                        if (SpritePieces[0][i].Pos.y == Board.YMax - 2 && SpritePieces[0][i].Pos.x == Board.XMax - 1)
                        {
                            Board.board[Board.XMax - 1][Board.YMax - 2] = EMPTYPiece;
                            Board.board[Board.XMax - 1][Board.YMax - 4] = BKing;
                            SpritePieces[0][i].Pos = Moves[Moves.size() - 1].Black.from;
                            posSetter(i);
                            break;
                        }
                    }
                }
                //Сделал дальнюю рокировку
                else if (Moves[Moves.size() - 1].Black.to.y - Moves[Moves.size() - 1].Black.from.y <= -2)
                {
                    for (size_t i = 0; i < SpritePieces->size(); i++)
                    {
                        //Вертаем обратно
                        if (SpritePieces[0][i].Pos.x == (Board.XMax - 1)&& SpritePieces[0][i].Pos.y == 3)
                        {
                            Board.board[Board.XMax - 1][3] = EMPTYPiece;
                            Board.board[Board.XMax - 1][0] = BRook;
                            SpritePieces[0][i].Pos = sf::Vector2i(Board.XMax - 1, 0);
                            posSetter(i);
                            isRook = 0;
                            break;
                        }
                    }
                    for (size_t i = 0; i < SpritePieces->size(); i++)
                    {
                        if (SpritePieces[0][i].Pos.y == Board.YMax - 6 && SpritePieces[0][i].Pos.x == Board.XMax - 1)
                        {
                            Board.board[Board.XMax - 1][Board.YMax - 6] = EMPTYPiece;
                            Board.board[Board.XMax - 1][Board.YMax - 4] = BKing;
                            SpritePieces[0][i].Pos = Moves[Moves.size() - 1].Black.from;
                            posSetter(i);
                            break;
                        }
                    }

                }
            }
            //Если пешка
           
            if (Moves[Moves.size() - 1].Black.piecef == BPawn)
            {
                //Совершила удар
                if ((Moves[Moves.size() - 1].Black.to.y- Moves[Moves.size() - 1].Black.from.y) !=0)
                {
                    //Взятие на проходе
                    if (Moves[Moves.size() - 1].Black.pieceto == EMPTYPiece)
                    {
                        CaptureePawn = 1;
                    }

                }
                //Совершила превращение
                if (Moves[Moves.size() - 1].Black.to.x == 0)
                {
                    untrans = true;
                }

            }
            if (isRook)
            {
                Board.board[Moves[Moves.size() - 1].Black.from.x][Moves[Moves.size() - 1].Black.from.y] = Moves[Moves.size() - 1].Black.piecef;
                Board.board[Moves[Moves.size() - 1].Black.to.x][Moves[Moves.size() - 1].Black.to.y] = Moves[Moves.size() - 1].Black.pieceto;
                for (size_t i = 0; i < SpritePieces->size(); i++)
                {
                    if (SpritePieces[0][i].Pos == Moves[Moves.size() - 1].Black.to)
                    {
                        SpritePieces[0][i].Pos = Moves[Moves.size() - 1].Black.from;
                        if (untrans)
                        {

                            SpritePieces[0][i].Piece.setTexture(ChessPicesTexture[BPawn]);
                            SpritePieces[0][i].Type = BPawn;
                            Board.board[Moves[Moves.size() - 1].Black.from.x][Moves[Moves.size() - 1].Black.from.y] = BPawn;
                        }
                        posSetter(i);
                        break;
                    }
                }
                if ((Moves[Moves.size() - 1].Black.pieceto != EMPTYPiece)&&!CaptureePawn)
                {
                    sf::Sprite temp;
                    temp.setTexture(ChessPicesTexture[Moves[Moves.size() - 1].Black.pieceto]);
                    temp.setScale(0.1 * RenderMenu::CGlobalSettings.chess.scale, 0.1 * RenderMenu::CGlobalSettings.chess.scale);
                    SpritePieces[0].push_back(SpritePiece(temp, Moves[Moves.size() - 1].Black.to, Moves[Moves.size() - 1].Black.pieceto));
                    posSetter(SpritePieces->size() - 1);
                    Board.board[SpritePieces[0][SpritePieces->size() - 1].Pos.x][SpritePieces[0][SpritePieces->size() - 1].Pos.y] = SpritePieces[0][SpritePieces->size() - 1].Type;
                }
                if (CaptureePawn)
                {
                    sf::Sprite temp;
                    temp.setTexture(ChessPicesTexture[WPawn]);
                    temp.setScale(0.1 * RenderMenu::CGlobalSettings.chess.scale, 0.1 * RenderMenu::CGlobalSettings.chess.scale);
                    SpritePieces[0].push_back(SpritePiece(temp, sf::Vector2i(Moves[Moves.size() - 1].Black.to.x+1, Moves[Moves.size() - 1].Black.to.y), WPawn));
                    posSetter(SpritePieces->size() - 1);
                }
            }
            DelBMove();
            WorB = 0;
        }
        else
        {
            bool isRook = 1;
            bool CaptureePawn = 0;
            bool untrans = false;
            //Если король
            if (Moves[Moves.size() - 1].White.piecef == WKing)
            {
                //Сделал ближнюю рокировку
                if (Moves[Moves.size() - 1].White.to.y - Moves[Moves.size() - 1].White.from.y >= 2)
                {
                    //Находим ладью
                    for (size_t i = 0; i < SpritePieces->size(); i++)
                    {
                        //Вертаем обратно
                        if (SpritePieces[0][i].Pos.x == 0 && SpritePieces[0][i].Pos.y == (Board.YMax - 3))
                        {
                            Board.board[0][Board.YMax - 3] = EMPTYPiece;
                            Board.board[0][Board.YMax - 1] = WRook;
                            SpritePieces[0][i].Pos = sf::Vector2i(0, Board.YMax - 1);
                            posSetter(i);
                            isRook = 0;
                            break;
                        }
                    }
                    for (size_t i = 0; i < SpritePieces->size(); i++)
                    {
                        if (SpritePieces[0][i].Pos.y == Board.YMax - 2 && SpritePieces[0][i].Pos.x == 0)
                        {
                            Board.board[0][Board.YMax - 2] = EMPTYPiece;
                            Board.board[0][Board.YMax - 4] = WKing;
                            SpritePieces[0][i].Pos = Moves[Moves.size() - 1].White.from;
                            posSetter(i);
                            break;
                        }
                    }
                }
                //Сделал дальнюю рокировку
                else if (Moves[Moves.size() - 1].White.to.y - Moves[Moves.size() - 1].White.from.y <= -2)
                {
                    for (size_t i = 0; i < SpritePieces->size(); i++)
                    {
                        //Вертаем обратно
                        if (SpritePieces[0][i].Pos.x == 0 && SpritePieces[0][i].Pos.y == 3)
                        {
                            Board.board[0][3] = EMPTYPiece;
                            Board.board[0][0] = WRook;
                            SpritePieces[0][i].Pos = sf::Vector2i(0, 0);
                            posSetter(i);
                            isRook = 0;
                            break;
                        }
                    }
                    for (size_t i = 0; i < SpritePieces->size(); i++)
                    {
                        if (SpritePieces[0][i].Pos.y == Board.YMax - 6 && SpritePieces[0][i].Pos.x == 0)
                        {
                            Board.board[0][Board.YMax - 6] = EMPTYPiece;
                            Board.board[0][Board.YMax - 4] = WKing;
                            SpritePieces[0][i].Pos = Moves[Moves.size() - 1].White.from;
                            posSetter(i);
                            break;
                        }
                    }

                }
            }
            //Если пешка
            if (Moves[Moves.size() - 1].White.piecef == WPawn)
            {
                //Совершила удар
                if ((Moves[Moves.size() - 1].White.to.y - Moves[Moves.size() - 1].White.from.y) != 0)
                {
                    //Взятие на проходе
                    if (Moves[Moves.size() - 1].White.pieceto == EMPTYPiece)
                    {
                        CaptureePawn = 1;
                    }

                }
                //Совершила превращение
                if (Moves[Moves.size() - 1].White.to.x == Board.XMax-1)
                {
                    untrans = true;
                }
            }
            if (isRook)
            {
                Board.board[Moves[Moves.size() - 1].White.from.x][Moves[Moves.size() - 1].White.from.y] = Moves[Moves.size() - 1].White.piecef;
                Board.board[Moves[Moves.size() - 1].White.to.x][Moves[Moves.size() - 1].White.to.y] = Moves[Moves.size() - 1].White.pieceto;
                for (size_t i = 0; i < SpritePieces->size(); i++)
                {
                    if (SpritePieces[0][i].Pos == Moves[Moves.size() - 1].White.to)
                    {
                        SpritePieces[0][i].Pos = Moves[Moves.size() - 1].White.from;
                        if (untrans)
                        {

                            SpritePieces[0][i].Piece.setTexture(ChessPicesTexture[WPawn]);
                            SpritePieces[0][i].Type = WPawn;
                            Board.board[Moves[Moves.size() - 1].White.from.x][Moves[Moves.size() - 1].White.from.y] = WPawn;
                        }
                        posSetter(i);
                        break;
                    }
                }
                if (Moves[Moves.size() - 1].White.pieceto != EMPTYPiece&&!CaptureePawn)
                {
                    sf::Sprite temp;
                    temp.setTexture(ChessPicesTexture[Moves[Moves.size() - 1].White.pieceto]);
                    temp.setScale(0.1 * RenderMenu::CGlobalSettings.chess.scale, 0.1 * RenderMenu::CGlobalSettings.chess.scale);
                    SpritePieces[0].push_back(SpritePiece(temp, Moves[Moves.size() - 1].White.to, Moves[Moves.size() - 1].White.pieceto));
                    posSetter(SpritePieces->size() - 1);
                }
                if (CaptureePawn)
                {
                    sf::Sprite temp;
                    temp.setTexture(ChessPicesTexture[BPawn]);
                    temp.setScale(0.1 * RenderMenu::CGlobalSettings.chess.scale, 0.1 * RenderMenu::CGlobalSettings.chess.scale);
                    SpritePieces[0].push_back(SpritePiece(temp, sf::Vector2i(Moves[Moves.size() - 1].White.to.x - 1, Moves[Moves.size() - 1].White.to.y), BPawn));
                    posSetter(SpritePieces->size() - 1);
                }
            }
            
            Moves.pop_back();
            WorB = 1;
        }
        Back = false;
        SetSuperiority();
    }
    void DelBMove()
    {
        ///***///
        Moves[Moves.size() - 1].Black.piecef = EMPTYPiece;
        Moves[Moves.size() - 1].Black.pieceto = EMPTYPiece;
        Moves[Moves.size() - 1].Black.from = sf::Vector2i(-1, -1);
        Moves[Moves.size() - 1].Black.to = sf::Vector2i(-1, -1);
        ///***///
    }
    void Mover(int fx,int fy,int xx,int yy,int trans = 0)
    {
        for (size_t i = 0; i < SpritePieces->size(); i++)
        {
            if (SpritePieces[0][i].Pos == sf::Vector2i(fx,fy))
            {
                n = i;
                break;
            }
        }
        cout << "Deb\n";
        if (((SpritePieces[0][n].Type >= 0 && SpritePieces[0][n].Type <= 5) && !WorB) || ((SpritePieces[0][n].Type >= 6 && SpritePieces[0][n].Type <= 11) && WorB))
        {
            SpritePieces[0][n].Piece.setPosition(oldPos);
        }
        //xe - x error
        else if (!(xx == SpritePieces[0][n].Pos.x && yy == SpritePieces[0][n].Pos.y))
        {
            int result = isValidMove(std::pair(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y), std::pair(xx, yy));
            if (0 < result)
            {
                if (result != 7)
                {
                    int x = UnCordRotater(xx, yy).x;
                    int y = UnCordRotater(xx, yy).y;
                    newPos = sf::Vector2f(x * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, y * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                    SpritePieces[0][n].Piece.setPosition(newPos);

                }
                //Если ход белых
                if (WorB)
                {
                    int del = -1;
                    //Если рокировка
                    #pragma region Рокировка
                    if (result == 7)
                    {

                        Moves.push_back(MoveWB(MoveFrTo(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), SpritePieces[0][n].Type, Board.board[xx][yy]), MoveFrTo(sf::Vector2i(-1, -1), sf::Vector2i(-1, -1), EMPTYPiece,EMPTYPiece)));
                        lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);
                        if (SpritePieces[0][n].Pos.y - yy < 0)
                        {
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 3] = EMPTYPiece;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 1] = WRook;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 2] = WKing;
                            for (size_t i = 0; i < SpritePieces->size(); i++)
                            {
                                if (SpritePieces[0][i].Pos == sf::Vector2i(0, Board.YMax - 1))
                                {
                                    SpritePieces[0][i].Pos = sf::Vector2i(0, Board.YMax - 1 - 2);
                                    //cout << "000" << endl;
                                    posSetter(i);
                                    break;
                                }
                            }
                            SpritePieces[0][n].Pos = sf::Vector2i(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y + 2);
                            posSetter(n);


                        }
                        else
                        {
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 4] = EMPTYPiece;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 1] = WRook;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 2] = WKing;
                            for (size_t i = 0; i < SpritePieces->size(); i++)
                            {
                                if (SpritePieces[0][i].Pos == sf::Vector2i(0, 0))
                                {
                                    SpritePieces[0][i].Pos = sf::Vector2i(0, 3);
                                    posSetter(i);
                                    break;
                                }
                            }
                            SpritePieces[0][n].Pos = sf::Vector2i(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y - 2);
                            posSetter(n);
                        }
                        MoveSound.play();


                    }
#pragma endregion


                    else
                    {


                        if (result == 5)
                        {
                            for (size_t i = 0; i < SpritePieces->size(); i++)
                            {
                                if (SpritePieces[0][i].Pos == lastmove.to) {
                                    del = i;
                                    break;
                                }
                            }
                            Board.board[lastmove.to.x][lastmove.to.y] = EMPTYPiece;
                        }
                        Moves.push_back(MoveWB(MoveFrTo(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), SpritePieces[0][n].Type, Board.board[xx][yy]), MoveFrTo(sf::Vector2i(-1, -1), sf::Vector2i(-1, -1), EMPTYPiece,EMPTYPiece)));
                        lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);
                        Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                        if (result != 5)
                            for (size_t i = 0; i < SpritePieces->size(); i++)
                            {
                                if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy)) {
                                    del = i;
                                    break;
                                }
                            }
                        SpritePieces[0][n].Pos = sf::Vector2i(xx, yy);

                        Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;

                        if (result == 2 || result == 4)
                        {
                            SpritePieces[0][n].Piece.setTexture(ChessPicesTexture[trans]);
                            SpritePieces[0][n].Type = trans;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                        }
                        if (del != -1)
                        {
                            SpritePieces[0].erase(SpritePieces[0].begin() + del);
                            if (n >= 1)
                            {
                                if (SpritePieces->size() - 1 < n)
                                {
                                    for (size_t i = 0; i < SpritePieces->size(); i++)
                                    {
                                        if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy))
                                        {
                                            n = i;
                                        }
                                    }
                                }
                                CaptureeSound.play();
                            }
                        }
                        else
                        {
                            MoveSound.play();
                        }
                    }
                    WorB = 0;
                    //
                    //Проверка на шах
                    for (int i = 0; i < Board.XMax; i++)
                    {
                        for (int j = 0; j < Board.YMax; j++)
                        {
                            if (!BCheck && Board.board[i][j] == BKing)
                            {
                                if (isValidMoveKing(std::pair(i, j), std::pair(i, j)) == 0)
                                {
                                    BCheck = true;
                                    i = 0;
                                    j = 0;
                                }
                            }
                            if (BCheck)
                            {
                                //проверка на мат
                                delete moves;
                                moves = new vector<sf::Vector2i>;
                                for (i = 0; i < Board.XMax; i++)
                                {
                                    for (j = 0; j < Board.YMax; j++)
                                    {
                                        if (Board.board[i][j] > 5 && Board.board[i][j] < 12)
                                        {
                                            isValidMove(std::pair(i, j), std::pair(i, j), -1, moves, 1);
                                            for (int k = 0; k < moves->size(); k++)
                                            {
                                                if (isValidMove(std::pair(i, j), std::pair(moves[0][k].x, moves[0][k].y)) == 0) {
                                                    moves[0].erase(moves[0].begin() + k);
                                                    k--;
                                                }
                                            }
                                            if (moves->size() > 0)
                                            {
                                                i = Board.XMax;
                                                j = Board.YMax;
                                                break;
                                               

                                            }
                                        }
                                    }
                                }
                                if (moves->size() == 0)
                                {

                                    BMate = 1;

                                }
                                else
                                {
                                    i = Board.XMax;
                                    j = Board.YMax;
                                    break;
                                    
                                }


                            }
                        }
                    }
                    //Проверка на пат

                    if (!BCheck)
                    {
                        int i;
                        int j;
                        //проверка на мат
                        delete moves;
                        moves = new vector<sf::Vector2i>;
                        for (i = 0; i < Board.XMax; i++)
                        {
                            for (j = 0; j < Board.YMax; j++)
                            {
                                if (Board.board[i][j] > 5 && Board.board[i][j] < 12)
                                {
                                    isValidMove(std::pair(i, j), std::pair(i, j), -1, moves, 1);
                                    for (int k = 0; k < moves->size(); k++)
                                    {
                                        if (isValidMove(std::pair(i, j), std::pair(moves[0][k].x, moves[0][k].y)) == 0) {
                                            moves[0].erase(moves[0].begin() + k);
                                            k--;
                                        }
                                    }
                                    if (moves->size() > 0)
                                    {
                                        i = Board.XMax;
                                        j = Board.YMax;
                                        break;
                                        

                                    }
                                }
                            }
                        }
                        if (moves->size() == 0)
                        {

                            WBDraw = 1;

                        }

                    }
                    WCheck = 0;
                    if (BMate)
                    {
                        cout << "White win\n";
                    }
                    if (WBDraw && !BMate)
                    {
                        cout << "Draw\n";
                    }

                    delete moves;
                    moves = nullptr;
                }
                else
                {
                #pragma region Рокировка
                    if (result == 7)
                    {

                        Moves[Moves.size() - 1].Black = MoveFrTo(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), SpritePieces[0][n].Type, Board.board[xx][yy]);
                        lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);
                        if (SpritePieces[0][n].Pos.y - yy < 0)
                        {
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 3] = EMPTYPiece;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 1] = BRook;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y + 2] = BKing;
                            for (size_t i = 0; i < SpritePieces->size(); i++)
                            {
                                if (SpritePieces[0][i].Pos == sf::Vector2i(Board.XMax - 1, Board.YMax - 1))
                                {
                                    SpritePieces[0][i].Pos = sf::Vector2i(Board.XMax - 1, Board.YMax - 1 - 2);
                                    //cout << "000" << endl;
                                    posSetter(i);
                                    break;
                                }
                            }
                            SpritePieces[0][n].Pos = sf::Vector2i(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y + 2);
                            posSetter(n);


                        }
                        else
                        {
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 4] = EMPTYPiece;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 1] = BRook;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y - 2] = BKing;
                            for (size_t i = 0; i < SpritePieces->size(); i++)
                            {
                                if (SpritePieces[0][i].Pos == sf::Vector2i(Board.XMax - 1, 0))
                                {
                                    SpritePieces[0][i].Pos = sf::Vector2i(Board.XMax - 1, 3);
                                    //cout << "00" << endl;
                                    posSetter(i);
                                    break;
                                }
                            }
                            SpritePieces[0][n].Pos = sf::Vector2i(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y - 2);
                            posSetter(n);
                        }
                        MoveSound.play();



                    }
#pragma endregion
                    else
                    {
                        int del = -1;
                        if (result == 5)
                        {
                            for (size_t i = 0; i < SpritePieces->size(); i++)
                            {
                                if (SpritePieces[0][i].Pos == lastmove.to) {
                                    del = i;
                                    break;
                                }
                            }
                            Board.board[lastmove.to.x][lastmove.to.y] = EMPTYPiece;
                        }
                        lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);


                        Moves[Moves.size() - 1].Black.from = SpritePieces[0][n].Pos;
                        Moves[Moves.size() - 1].Black.to = sf::Vector2i(xx, yy);
                        Moves[Moves.size() - 1].Black.piecef = SpritePieces[0][n].Type;
                        Moves[Moves.size() - 1].Black.pieceto = Board.board[xx][yy];
                        Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                        if (result != 5)
                            for (size_t i = 0; i < SpritePieces->size(); i++)
                            {
                                if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy)) {
                                    del = i;
                                    break;
                                }
                            }
                        SpritePieces[0][n].Pos = sf::Vector2i(xx, yy);

                        Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                        if (result == 2|| result == 4)
                        {
                            SpritePieces[0][n].Piece.setTexture(ChessPicesTexture[BKnight + trans-1]);
                            SpritePieces[0][n].Type = BKnight + trans - 1;
                            Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                        }
                        //cout << ChessPieceStr(SpritePieces[0][n].Type) << endl;

                        if (del != -1)
                        {
                            SpritePieces[0].erase(SpritePieces[0].begin() + del);
                            if (n >= 1)
                            {
                                if (SpritePieces->size() - 1 < n)
                                {
                                    for (size_t i = 0; i < SpritePieces->size(); i++)
                                    {
                                        if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy))
                                        {
                                            n = i;
                                        }
                                    }
                                }
                                CaptureeSound.play();
                            }

                        }
                        else
                        {
                            MoveSound.play();
                        }
                    }

                    //Проверка на шах
                    for (int i = 0; i < Board.XMax; i++)
                    {
                        for (int j = 0; j < Board.YMax; j++)
                        {
                            if (!BCheck && Board.board[i][j] == WKing)
                            {
                                if (isValidMoveKing(std::pair(i, j), std::pair(i, j)) == 0)
                                {
                                    WCheck = true;
                                    i = 0;
                                    j = 0;
                                }
                            }
                            if (WCheck)
                            {
                                //проверка на мат
                                delete moves;
                                moves = new vector<sf::Vector2i>;
                                for (i = 0; i < Board.XMax; i++)
                                {
                                    for (j = 0; j < Board.YMax; j++)
                                    {
                                        if (Board.board[i][j] >= 0 && Board.board[i][j] < 6)
                                        {
                                            isValidMove(std::pair(i, j), std::pair(i, j), -1, moves, 1);
                                            for (int k = 0; k < moves->size(); k++)
                                            {
                                                if (isValidMove(std::pair(i, j), std::pair(moves[0][k].x, moves[0][k].y)) == 0) {
                                                    moves[0].erase(moves[0].begin() + k);
                                                    k--;
                                                }
                                            }
                                            if (moves->size() > 0)
                                            {
                                                i = Board.XMax;
                                                j = Board.YMax;
                                                break;
                                                

                                            }
                                        }
                                    }
                                }
                                if (moves->size() == 0)
                                {

                                    WMate = 1;

                                }
                                else
                                {
                                    i = Board.XMax;
                                    j = Board.YMax;
                                    break;
                                    
                                }


                            }
                        }

                    }
                    //проверка на пат
                    if (!WCheck)
                    {
                        int i, j;
                        delete moves;
                        moves = new vector<sf::Vector2i>;
                        for (i = 0; i < Board.XMax; i++)
                        {
                            for (j = 0; j < Board.YMax; j++)
                            {
                                if (Board.board[i][j] >= 0 && Board.board[i][j] < 6)
                                {
                                    isValidMove(std::pair(i, j), std::pair(i, j), -1, moves, 1);
                                    for (int k = 0; k < moves->size(); k++)
                                    {
                                        if (isValidMove(std::pair(i, j), std::pair(moves[0][k].x, moves[0][k].y)) == 0) {
                                            moves[0].erase(moves[0].begin() + k);
                                            k--;
                                        }
                                    }
                                    if (moves->size() > 0)
                                    {
                                        i = Board.XMax;
                                        j = Board.YMax;
                                        break;
                                        

                                    }
                                }
                            }
                        }
                        if (moves->size() == 0)
                        {

                            WBDraw = 1;

                        }

                    }
                    if (WMate)
                    {
                        cout << "Black win\n";
                    }
                    if (WBDraw && !BMate)
                    {
                        cout << "Draw\n";
                    }
                    BCheck = 0;
                    WorB = 1;
                    delete moves;
                    moves = nullptr;
                }
            }
        }
        SetSuperiority();
    }
    void Restart()
    {
        Board = ChessBoard();
        delete SpritePieces;
        SpritePieces = new std::vector<SpritePiece>;
        for (int i = 0; i < Board.XMax; ++i)
        {
            for (int j = 0; j < Board.YMax; ++j)
            {
                if (Board.board[i][j] != 12)
                {
                    sf::Sprite temp;
                    temp.setScale(0.1 * RenderMenu::CGlobalSettings.chess.scale, 0.1 * RenderMenu::CGlobalSettings.chess.scale);
                    temp.setTexture(ChessPicesTexture[Board.board[i][j]]);
                    temp.setPosition(j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                    SpritePieces->push_back(SpritePiece(temp, sf::Vector2i(i, j), (int)Board.board[i][j]));
                }
            }
        }
    }
    //void Network()
    //{
    //    if (OnNetworkGame == 1)
    //    {
    //        if (nc == nullptr)
    //        {
    //            nc = new NetClient(RenderMenu::CGlobalSettings.network.ip, RenderMenu::CGlobalSettings.network.port);
    //            sf::Packet paket;
    //            paket << "-";
    //            nc->sendPacket(paket);
    //        }
    //        else
    //        {
    //            /*if (!conection)
    //            {
    //                conection = nc->Connector(RenderMenu::CGlobalSettings.network.ip, RenderMenu::CGlobalSettings.network.port);
    //                conection = true;
    //            }*/
    //            
    //            //str = nc->Receiver();
    //            if (PacketMove!=netMove)
    //            {
    //                if (PacketMove[0] != '-')
    //                {
    //                    if (netMove != PacketMove)
    //                    {
    //                        Mover((PacketMove[0] - '0'), (PacketMove[1] - '0'), (PacketMove[2] - '0'), (PacketMove[3] - '0'));
    //                        netMove = PacketMove;
    //                    }
    //                }
    //            }
    //           
    //            //nc->SendMessenge(myMove);
    //        }
    //    }
    //    if (OnNetworkGame == 2)
    //    {
    //        if (nc == nullptr)
    //        {
    //            nc = new NetClient(RenderMenu::CGlobalSettings.network.ip, RenderMenu::CGlobalSettings.network.port);
    //            //nc->SendMessenge("-");
    //        }
    //        else
    //        {
    //           /* if (!conection)
    //            {
    //                conection = nc->Connector(RenderMenu::CGlobalSettings.network.ip, RenderMenu::CGlobalSettings.network.port);
    //                conection = true;
    //            }*/
    //            
    //            if (PacketMove != netMove)
    //            {
    //                if (PacketMove[0] != '-')
    //                {
    //                    if (netMove != PacketMove)
    //                    {
    //                        Mover((PacketMove[0] - '0'), (PacketMove[1] - '0'), (PacketMove[2] - '0'), (PacketMove[3] - '0'));
    //                        netMove = PacketMove;
    //                    }
    //                }
    //            }
    //                sf::Packet paket;
    //                paket << "-";
    //                nc->sendPacket(paket);
    //                //nc->SendMessenge(myMove);
    //                    
    //                
    //            
    //        }
    //    }
    //    
    //}
    void Network()
    {
        if (OnNetworkGame == 1)
        {
            if (nc == nullptr)
            {
                nc = new NClient(RenderMenu::CGlobalSettings.network.ip, RenderMenu::CGlobalSettings.network.port);
                nc->sendMessage("Hi server, i'm home client!");
                /*
                * Этот клиент управляет сервером
                * Он отсылает начальные настройки
                */
                nc->sendMessage(NetParser::NetSettings(RenderMenu::CGlobalSettings.chess.gamemode, RenderMenu::CGlobalSettings.chess.timeControl, RenderMenu::CGlobalSettings.chess.increment, RenderMenu::CGlobalSettings.chess.playerColor));
                
            }
            else
            {
                NetParcer();
            }
        }
        if (OnNetworkGame == 2)
        {
            if (nc == nullptr)
            {
                nc = new NClient(RenderMenu::CGlobalSettings.network.ip, RenderMenu::CGlobalSettings.network.port);
                nc->sendMessage("Hi server, i'm guest client!");
            }
            else
            {
                NetParcer();
            }
        }

    }
    void NetParcer()
    {
        if (PacketMove != netMove)
        {
            if (PacketMove == "Hi server, i'm guest client!")
            {
                RenderMenu::is_server_waiting = false;
            }
            if (PacketMove[0] != '-')
            {
                if (netMove != PacketMove)
                {
                    if (PacketMove[0] == 'm')
                    {
                        if (n != -1)
                        {
                            SpritePieces[0][n].Piece.setPosition(oldPos);
                            isMove = 0;
                        }
                        
                            Back = false;
                            NetBack = false;
                            MyNetBack = false;
                            for (int i = 1; i < PacketMove.size(); i++)
                            {
                                if (!isalnum(PacketMove[i]))
                                {
                                    goto outOfChar;
                                }
                            }
                            if (PacketMove.length()<6)
                            {
                                Mover((PacketMove[1] - '0'), (PacketMove[2] - '0'), (PacketMove[3] - '0'), (PacketMove[4] - '0'));
                            }
                            else
                            {
                                Mover((PacketMove[1] - '0'), (PacketMove[2] - '0'), (PacketMove[3] - '0'), (PacketMove[4] - '0'), (PacketMove[5] - '0'));
                            }
                            outOfChar:
                            netMove = PacketMove;
                    }
                    else if (PacketMove[0] == 'b')
                    {
                        if (PacketMove.length() < 2)
                        {
                            Back = true;
                            NetBack = true;
                        }

                        else if (PacketMove[1] == 'a')
                        {
                            Back = true;
                            NetBack = true;

                        }
                        else if (PacketMove[1] == 'd')
                        {
                            Back = false;
                            NetBack = false;
                            MyNetBack = false;

                        }
                        netMove = PacketMove;

                    }
                    else if (PacketMove[0] == 'l')
                    {
                        netMove = PacketMove;
                    }
                    else if (PacketMove[0] == 'd')
                    {
                        netMove = PacketMove;
                    }

                }
            }
            else
            {
                PacketMove = "-";
            }
        }
    
    }
    void SendMove(int fx,int fy,int xx,int yy)
    {
        string m;
        m += 'm';
        m += fx + '0';
        m += fy + '0';
        m += xx + '0';
        m += yy + '0';
        if (TransPawn >0)
        {
            m += TransPawn + '0';
            TransPawn = -1;
        }
        myMove = m;
        if (OnNetworkGame == 1&&WorB)
        {
            nc->sendMessage(m);
            MyPacket = myMove;
        }if (OnNetworkGame == 2 && !WorB)
        {
            nc->sendMessage(m);
            MyPacket = myMove;
        }
    }
    void Draw(sf::RenderWindow* window, float deltaTime)
    {
        if ((Back&&OnNetworkGame ==0)||((Back&&NetBack)&&MyNetBack))
        {
            if (OnNetworkGame > 0)
            {
                myMove = "empty";
                nc->sendMessage("-");
            }
            MoveBack();
            NetBack = false;
            MyNetBack = false;
            n = -1;
        }
        if (OnNetworkGame>0)
        {
            Network();

        }
        string msg = "-";
        int dr = Rotation;
        gameUI.RenderChessMovesWindow(Board.YMax,Moves,Back,NetBack,MyNetBack,Rotation, msg);
        if (dr != Rotation)
        {
            Rotate(Rotation);
        }
        if (msg != "-"&& OnNetworkGame>0)
        {
            nc->sendMessage(msg);
        }
        if (RenderMenu::isControlTime)
        {
            gameUI.drawChessClock(window, RenderMenu::addTimeIndex,wTime,bTime, deltaTime, !WorB);
        }

        if ((WMate||WBDraw||BMate)&&!WinWindowC)
        {
            WinWindow = 1;
            WinWindowC = 1;

        }
        if (WinWindow)
        {
            if (WBDraw && !(WMate|| BMate))
            {
                gameUI.WinDraw(0,WinWindow);
            }
            else if (WMate)
            {
                gameUI.WinDraw(2, WinWindow);
            }
            else if ( BMate)
            {
                gameUI.WinDraw(1, WinWindow);
            }

        }
        if (n!=-1)
        {
            if (isMove) SpritePieces[0][n].Piece.setPosition(pos.x - dx, pos.y - dy);
        }
        if (TransPawn!=0)
        {
            TransPawn = 0;
        }
        Superiority.setPosition(Board.XMax * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale +RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale+20, RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
        Superiority.setString(std::to_string(superiority));
        window->draw(Superiority);
        //Рамка
        sf::RectangleShape Bsquare(sf::Vector2f(RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale * Board.XMax+16, RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale * Board.YMax+16));
        Bsquare.setPosition(0 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale-8, 0 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10-8);
        Bsquare.setFillColor(sf::Color(31, 33, 33));
        window->draw(Bsquare);
        //Рамка
        //Отрисовка фигур, клеток доски, подсветки ходов и т.д.
        for (int i = 0; i < Board.XMax; ++i)
        {
            for (int j = 0; j < Board.YMax; ++j)
            {
                

                sf::RectangleShape square(sf::Vector2f(RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale));
                square.setPosition(i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                // Чередование цветов клеток
                if (Rotation == 2 || Rotation == 3)
                {
                    if ((i + j) % 2 == 0)
                    {ChessText.setFillColor(sf::Color(255, 206, 158));// Бежевый
                        
                        square.setFillColor(sf::Color(255, 206, 158)); // Бежевый
                    }
                    else
                    {
                        ChessText.setFillColor(sf::Color(209, 139, 71));// Коричневый
                        square.setFillColor(sf::Color(209, 139, 71)); // Коричневый

                    }
                }
                else
                {
                    if ((i + j) % 2 != 0)
                    {
                        ChessText.setFillColor(sf::Color(255, 206, 158));// Бежевый
                        square.setFillColor(sf::Color(255, 206, 158)); // Бежевый
                    }
                    else
                    {ChessText.setFillColor(sf::Color(209, 139, 71));// Коричневый
                        
                        square.setFillColor(sf::Color(209, 139, 71)); // Коричневый

                    }
                }
                if (BCheck)
                {
                    if( Board.board[CordRotater(i,j).x][CordRotater(i, j).y]==BKing)square.setFillColor(sf::Color(235, 64, 52));
                }
                if (WCheck)
                {
                    if (Board.board[CordRotater(i, j).x][CordRotater(i, j).y] == WKing)square.setFillColor(sf::Color(235, 64, 52));
                }
                window->draw(square);
                if (moves != nullptr)
                {
                    for (int k = 0; k < moves->size(); k++)
                    {
                        if (UnCordRotater(moves[0][k].x, moves[0][k].y).x == i && UnCordRotater(moves[0][k].x, moves[0][k].y).y == j)
                        {
                            sf::CircleShape circle((RenderMenu::CGlobalSettings.chess.cellSize / 8) * RenderMenu::CGlobalSettings.chess.scale);
                            //circle.setPosition(i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale+ (RenderMenu::CGlobalSettings.chess.cellSize / 2.5) * RenderMenu::CGlobalSettings.chess.scale- RenderMenu::CGlobalSettings.chess.scale, j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10+ (RenderMenu::CGlobalSettings.chess.cellSize / 2.5) * RenderMenu::CGlobalSettings.chess.scale - RenderMenu::CGlobalSettings.chess.scale);
                            circle.setPosition(square.getPosition().x+(RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale) / 2- (RenderMenu::CGlobalSettings.chess.cellSize / 8)* RenderMenu::CGlobalSettings.chess.scale, square.getPosition().y+ (RenderMenu::CGlobalSettings.chess.cellSize* RenderMenu::CGlobalSettings.chess.scale) /2- (RenderMenu::CGlobalSettings.chess.cellSize / 8)* RenderMenu::CGlobalSettings.chess.scale);
                            circle.setFillColor(sf::Color(62, 163, 59, 125));
                            window->draw(circle);
                        }
                    }
                }
                if (n != -1)
                {


                    if (UnCordRotater(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y) == sf::Vector2i(i, j))
                    {
                        sf::RectangleShape squareg(sf::Vector2f(RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale));
                        squareg.setPosition(i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                        squareg.setFillColor(sf::Color(62, 163, 59, 125));
                        window->draw(squareg);
                    }
                }
                
                    #pragma region Исправить
                //            switch (Rotation)
                //{
               
                //            case 1:
                //                if ((Board.YMax - 1 - j == 0) || (Board.XMax - 1 - i == 0))
                //                {
                //                    ChessText.setPosition((Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    if (j == Board.YMax - 1)
                //                    {
                //                        ChessText.setString(std::to_string((i + 1)));
                //                        ChessText.setPosition((Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                        window->draw(ChessText);
                //                    }
                //                    if ((i == Board.YMax - 1) && j != Board.YMax - 1)
                //                    {
                //                        ChessText.setString(std::string(1, 'A' + Board.YMax - 1 - j));
                //                        ChessText.setPosition((Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                        window->draw(ChessText);
                //                    }
                //                }
                //                break;
                //            case 3:
                //                if ((j == 0) || (i == 0))
                //                {
                //                    ChessText.setPosition(j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    window->draw(ChessText);
                //                }


                //                break;
                //            case 4:
                //                if ((j == 0) || (i == 0))
                //                {
                //                    ChessText.setPosition(i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    window->draw(ChessText);
                //                }
                //                break;
                //            case 2:
                //                if (j == Board.YMax - 1)
                //                {
                //                    ChessText.setString(std::to_string((Board.XMax - i)));
                //                    ChessText.setPosition((Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.YMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    window->draw(ChessText);
                //                }
                //                if ((i == Board.XMax - 1) && j != Board.YMax - 1)
                //                {
                //                    ChessText.setString((char)(Board.YMax - 1 - j + 'A'));
                //                    ChessText.setPosition((Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.YMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    window->draw(ChessText);
                //                }

                //                break;
                //            default:
                //                break;
                //            }
                            ////исправить
                            //            case 1:

                        //if (j==0)
                        //{
                        //    ChessText.setString(std::to_string(i+1));
                        //    ChessText.setPosition((Board.XMax-2 -CordRotater(i, j).x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax-1 -CordRotater(i, j).y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                        //    window->draw(ChessText);
                        //}
                        //if (i ==0)
                        //{
                        //    char c[2] = { ('A' + j),'\0'};
                        //    ChessText.setString(std::string(c));
                        //    ChessText.setPosition((Board.XMax -1- CordRotater(i, j).x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax  - CordRotater(i, j).y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                        //    window->draw(ChessText);
                        //}
                                

                        #pragma endregion
                
            }
        }
        
        //gameUI.ChessClock();

        for (SpritePiece value : *SpritePieces)
        {
            window->draw(value.Piece);
        }
        if(n!=-1)
        window->draw(SpritePieces[0][n].Piece);
    }
    void Rotate(int Rotation)
    {
        if (Rotation > 0 && Rotation < 5)
            this->Rotation = Rotation;
        else
            this->Rotation = 1;
        for (int i =0;i< SpritePieces->size();i++)
        {
            switch (Rotation)
            {
            case 4:
                SpritePieces[0][i].Piece.setPosition((Board.XMax - 1 - SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                break;
            case 3:
                SpritePieces[0][i].Piece.setPosition((Board.XMax -1 - SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                break;
            case 2:
                
                SpritePieces[0][i].Piece.setPosition((SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                break;
            case 1:
                SpritePieces[0][i].Piece.setPosition((SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                break;
            }
        }
    }
    void posSetter(int i)
    {
        switch (this->Rotation)
        {
        case 4:
            SpritePieces[0][i].Piece.setPosition((Board.XMax - 1 - SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
            break;
        case 3:
            SpritePieces[0][i].Piece.setPosition((Board.XMax - 1 - SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
            break;
        case 2:

            SpritePieces[0][i].Piece.setPosition((SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
            break;
        case 1:
            SpritePieces[0][i].Piece.setPosition((SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
            break;
        }
    }
    /*
    * 0 - Ход недоступен
    * 1 - Можно сделать ход либо ударить
    * 2 - Превращение пешки при ходе на 1 клетку вперёд
    * 3 - Ход пешки на 2 клетки
    * 4 - Бой пешки с превращением
    * 5 - Взятие на проходе
    * 6 - Ход пешки на 1 клетку
    * 7 - Рокировка
    */
    int isValidMove(std::pair<int, int> from, std::pair<int, int> to,int king = 0, std::vector<sf::Vector2i>* moves = nullptr,bool ff = false)
    {
        short piece = Board.board[from.first][from.second];
        short piece2 = Board.board[to.first][to.second];
        /*cout << ChessPieceStr(piece) << " (" << from.first << ", " << from.second << ")\n";
        cout << ChessPieceStr(piece2) << " (" << to.first << ", " << to.second << ")\n";*/
        if (king > 0)
        {
            return (isValidMoveHorse(from, to,king)|| isValidMoveHeavy(from, to,king)|| isValidMoveDiag(from, to, king));
        }
        //Огонь по своим
        if ((((piece>=0&&piece<=5)&& (piece2 >= 0 && piece2 <= 5))|| ((piece >= 6 && piece <= 11) && (piece2 >= 6 && piece2 <= 11)))&&!ff)
        {
            //Если рокировка
            if (!((piece == WKing && piece2 == WRook) || (piece == BKing && piece2 == BRook)))
            {
                return false;
            }
            
        }
        switch (piece)
        {
            ///Белая пешка
        case WPawn:
            return isValidMovePawn(from, to, king, moves);
            break;
        case BPawn:
            return isValidMovePawn(from, to, king, moves);
            break;
            case WBishop:
                return isValidMoveDiag(from, to, king, moves);
                break;
            case BBishop:
                return isValidMoveDiag(from, to, king, moves);
                break;
            case WKnight:
                return isValidMoveHorse(from, to,king,moves);
                break;
            case BKnight:
                return isValidMoveHorse(from, to,king,moves);
                break;
            case WQueen:
                return (isValidMoveHeavy(from, to, king, moves)|| isValidMoveDiag(from, to, king, moves));
                break;
            case BQueen:
                return (isValidMoveHeavy(from, to, king, moves)|| isValidMoveDiag(from, to, king, moves));
                break;
            case WRook:
                return isValidMoveHeavy(from, to, king, moves);
                break;
            case BRook:
                return isValidMoveHeavy(from, to, king, moves);
                break;
            case WKing:
                return isValidMoveKing(from, to,king,moves);
                break;
            case BKing:
                return isValidMoveKing(from, to, king, moves);
                break;
        default:
            break;
        }
     

        return false; 
    }
    int isValidMoveHeavy(std::pair<int, int> from, std::pair<int, int> to, int king = 0, std::vector<sf::Vector2i>* moves = nullptr)
    {
        //moves = new std::vector<sf::Vector2i>;
        //Проверка на короля
        short tto = Board.board[to.first][to.second];
        if (king == 0)
        {
            if (!CheckKing(from, to))
            {
                return 0;
            }
        }
        bool mn = false;
        if (moves == nullptr)
        {
            moves = new std::vector<sf::Vector2i>;
            mn = true;
        }
        
        bool p = false;
        //  ↓
        for (int i = from.first - 1; i >= 0; i--)
        {

            if (Board.board[i][from.second] != EMPTYPiece)
            {
                if (i != to.first || from.second != to.second)
                {
                    p = true;
                    if (king == 1)
                    {
                        if (Board.board[i][from.second]==BQueen|| Board.board[i][from.second]==BRook)
                        {
                            return true;
                        }
                        break;
                    }
                    if (king == 2)
                    {
                        if (Board.board[i][from.second] == WQueen || Board.board[i][from.second] == WRook)
                        {
                            return true;
                        }
                        break;
                    }
                    
                }
                if (king == -1)
                {
                    moves->push_back(sf::Vector2i(i, from.second));
                    break;
                }

            }
            if (king == -1)
            {
                moves->push_back(sf::Vector2i(i, from.second));
            }
            if (!p && (i == to.first && from.second == to.second)&&king==0)
            {
                return true;
            }
        }
        p = false;
        // ↑
        for (int i = from.first + 1; i < Board.XMax; i++)
        {

            if (Board.board[i][from.second] != EMPTYPiece)
            {
                if ((i != to.first || from.second != to.second))
                {
                    p = true;
                    if (king == 1)
                    {
                        if (Board.board[i][from.second] == BQueen || Board.board[i][from.second] == BRook)
                        {
                            return true;
                        }
                        break;
                    }
                    if (king == 2)
                    {
                        if (Board.board[i][from.second] == WQueen || Board.board[i][from.second] == WRook)
                        {
                            return true;
                        }
                        break;
                    }
                }
                    
                if (king == -1)
                {
                    moves->push_back(sf::Vector2i(i, from.second));
                    break;
                }

            }
            if (king == -1)
            {
                moves->push_back(sf::Vector2i(i, from.second));
            }
            if (!p && (i == to.first && from.second == to.second) && king == 0)
            {
                return true;
            }
        }
        p = false;
        // ->
        for (int i = from.second + 1; i < Board.YMax; i++)
        {

            if (Board.board[from.first][i] != EMPTYPiece)
            {
                if ((from.first != to.first || i != to.second))
                {
                    p = true;
                    if (king == 1)
                    {
                        if (Board.board[from.first][i] == BQueen || Board.board[from.first][i] == BRook)
                        {
                            return true;
                        }
                        break;
                    }
                    if (king == 2)
                    {
                        if (Board.board[from.first][i] == WQueen || Board.board[from.first][i] == WRook)
                        {
                            return true;
                        }
                        break;
                    }
                }
                   
                if (king == -1)
                {
                    moves->push_back(sf::Vector2i(from.first, i));
                    break;
                }

            }
            if (king == -1)
            {
                moves->push_back(sf::Vector2i(from.first, i));
            }
            if (!p && (from.first == to.first && i == to.second) && king == 0)
            {
                return true;
            }
        }
        p = false;
        // <-
        for (int i = from.second - 1; i >= 0; i--)
        {

            if (Board.board[from.first][i] != EMPTYPiece)
            {
                if ((from.first != to.first || i != to.second))
                {
                    p = true;
                    if (king == 1)
                    {
                        if (Board.board[from.first][i] == BQueen || Board.board[from.first][i] == BRook)
                        {
                            return true;
                        }
                        break;
                    }
                    if (king == 2)
                    {
                        if (Board.board[from.first][i] == WQueen || Board.board[from.first][i] == WRook)
                        {
                            return true;
                        }
                        break;
                    }
                }
                if (king == -1)
                {
                    moves->push_back(sf::Vector2i(from.first, i));
                    break;
                }

            }
            if (king == -1)
            {
                moves->push_back(sf::Vector2i(from.first, i));
            }
            if (!p && (from.first == to.first && i == to.second) && king == 0)
            {
                return true;
            }
        }
        return false;
    }
    int isValidMoveDiag(std::pair<int, int> from, std::pair<int, int> to,int king = 0, std::vector<sf::Vector2i>* moves = nullptr)
    {
        //Проверка на короля
        short tto = Board.board[to.first][to.second];
        if (king == 0)
        {
            if (!CheckKing(from, to))
            {
                return 0;
            }
        }
        bool mn = false;
        if (moves == nullptr)
        {
            moves = new std::vector<sf::Vector2i>;
            mn = true;
        }
        bool p = false;
        //  ↙
        for (int i = from.first - 1, j = from.second-1; i >= 0&&j>=0; i--,j--)
        {

            if (Board.board[i][j] != EMPTYPiece)
            {

                if (i != to.first || j != to.second)
                {
                    p = true;
                    if (king == 1)
                    {
                        if (Board.board[i][j] == BQueen || Board.board[i][j] == BBishop)
                        {
                            return true;
                        }
                        break;
                    }
                    if (king == 2)
                    {
                        if (Board.board[i][j] == WQueen || Board.board[i][j] == WBishop)
                        {
                            return true;
                        }
                        break;
                    }
                    
                }
                if (king == -1)
                {
                    moves->push_back(sf::Vector2i(i, j));
                    break;
                }
                    
            }
            if (king == -1)
            {
                moves->push_back(sf::Vector2i(i, j));
            }
            if (!p && (i == to.first && j == to.second) && king == 0)
            {
                return true;
            }
        }
        p = false;
        // ↗
        for (int i = from.first + 1,  j = from.second + 1; i < Board.XMax && j < Board.XMax; i++, j++)
        {

            if (Board.board[i][j] != EMPTYPiece)
            {
                if (i != to.first || j != to.second)
                {
                    p = true;
                    if (king == 1)
                    {
                        if (Board.board[i][j] == BQueen || Board.board[i][j] == BBishop)
                        {
                            return true;
                        }
                        break;
                    }
                    if (king == 2)
                    {
                        if (Board.board[i][j] == WQueen || Board.board[i][j] == WBishop)
                        {
                            return true;
                        }
                        break;
                    }
                }
                if (king == -1)
                {
                    moves->push_back(sf::Vector2i(i, j));
                    break;
                }

            }
            if (king == -1)
            {
                moves->push_back(sf::Vector2i(i, j));
            }
            if (!p && (i == to.first && j == to.second) && king == 0)
            {
                return true;
            }
        }
        
        p = false;
        // ↘
        for (int i = from.first - 1,  j = from.second + 1; i >= 0 && j < Board.YMax; i--, j++)
        {

            if (Board.board[i][j] != EMPTYPiece)
            {
                if (i != to.first || j != to.second)
                {
                    p = true;
                    if (king == 1)
                    {
                        if (Board.board[i][j] == BQueen || Board.board[i][j] == BBishop)
                        {
                            return true;
                        }
                        break;
                    }
                    if (king == 2)
                    {
                        if (Board.board[i][j] == WQueen || Board.board[i][j] == WBishop)
                        {
                            return true;
                        }
                        break;
                    }
                    

                }
                if (king == -1)
                {
                    moves->push_back(sf::Vector2i(i, j));
                    break;
                }
                
            }
            if (king == -1)
            {
                moves->push_back(sf::Vector2i(i, j));
            }
            if (!p && (i == to.first && j == to.second) && king == 0)
            {
                return true;
            }
        }
        p = false;
        // ↖
        for (int i = from.first + 1,  j = from.second - 1; i < Board.XMax && j >= 0; i++, j--)
        {

            if (Board.board[i][j] != EMPTYPiece)
            {
                if (i != to.first || j != to.second)
                {
                    p = true;
                    if (king == 1)
                    {
                        if (Board.board[i][j] == BQueen || Board.board[i][j] == BBishop)
                        {
                            return true;
                        }
                        break;
                    }
                    if (king == 2)
                    {
                        if (Board.board[i][j] == WQueen || Board.board[i][j] == WBishop)
                        {
                            return true;
                        }
                        break;
                    }
                }
                if (king == -1)
                {
                    moves->push_back(sf::Vector2i(i, j));
                    break;
                }

            }
            if (king == -1)
            {
                moves->push_back(sf::Vector2i(i, j));
            }
            if (!p && (i == to.first && j == to.second) && king == 0)
            {
                return true;
            }
        }
        return false;
    }
    int isValidMoveHorse(std::pair<int, int> from, std::pair<int, int> to,int king = 0, std::vector<sf::Vector2i>* moves = nullptr)
    {
        short tto = Board.board[to.first][to.second];
        if (king == 0)
        {
            if (!CheckKing(from, to))
            {
                return 0;
            }
        }
        bool mn = false;
        if (moves == nullptr)
        {
            moves = new std::vector<sf::Vector2i>;
            mn = true;
        }
        
        if (from.first+2<Board.XMax&&from.second+1< Board.YMax)
        {
            moves->push_back(sf::Vector2i(from.first + 2, from.second + 1));
        }
        if (from.first + 1 < Board.XMax && from.second + 2 < Board.YMax)
        {
            moves->push_back(sf::Vector2i(from.first + 1, from.second + 2));
        }
        if (from.first - 1 >= 0 && from.second + 2 < Board.YMax)
        {
            moves->push_back(sf::Vector2i(from.first - 1, from.second + 2));
        }
        if (from.first - 2 >= 0 && from.second + 1 < Board.YMax)
        {
            moves->push_back(sf::Vector2i(from.first - 2, from.second + 1));
        }
        if (from.first - 2 >= 0 && from.second - 1 >= 0)
        {
            moves->push_back(sf::Vector2i(from.first - 2, from.second - 1));
        }
        if (from.first - 1 >= 0 && from.second - 2 >= 0)
        {
            moves->push_back(sf::Vector2i(from.first - 1, from.second - 2));
        }
        if (from.first + 1 < Board.XMax && from.second - 2 >= 0)
        {
            moves->push_back(sf::Vector2i(from.first + 1, from.second - 2));
        }
        if (from.first + 2 < Board.XMax && from.second - 1 >= 0)
        {
            moves->push_back(sf::Vector2i(from.first + 2, from.second - 1));
        }
        if (king == 0)
        {
            for (size_t i = 0; i < moves->size(); i++)
            {
                if ((moves[0][i].x == to.first) && (moves[0][i].y == to.second))
                {
                    if(mn)
                    delete moves;
                    return true;
                }
            }
        }
        else if(king == 1)
        {
            for (size_t i = 0; i < moves->size(); i++)
            {
                if (Board.board[moves[0][i].x][moves[0][i].y]==BKnight)
                {
                    if (mn)
                    delete moves;
                    return true;
                }
            }
        }
        else if (king == 2)
        {
            for (size_t i = 0; i < moves->size(); i++)
            {
                if (Board.board[moves[0][i].x][moves[0][i].y] == WKnight)
                {
                    if (mn)
                    delete moves;
                    return true;
                }
            }
        }

        return false;
    }
    int isValidMoveKing(std::pair<int, int> from, std::pair<int, int> to,int king = 0, std::vector<sf::Vector2i>* moves = nullptr)
    {
        short piece = Board.board[from.first][from.second];
        short tto = Board.board[to.first][to.second];
        bool mn = false;
        if (moves == nullptr)
        {
            moves = new std::vector<sf::Vector2i>;
            mn = true;
        }
        if (king == -1)
        {
            int i = from.first;
            int j = from.second;
            if ((i + 1 < Board.XMax) &&(j + 1 < Board.YMax))
            {
                moves->push_back(sf::Vector2i(i + 1, j + 1));
            }
            if ((j + 1) < Board.YMax)
            {
                moves->push_back(sf::Vector2i(i, j + 1));
            }
            if (i - 1 >= 0 && j + 1 < Board.YMax)
            {
                moves->push_back(sf::Vector2i(i - 1, j + 1));
            }
            if ((i - 1 )>= 0)
            {
                moves->push_back(sf::Vector2i(i - 1, j));
            }
            if ((i - 1 >= 0 )&&( (j - 1) >= 0))
            {
                moves->push_back(sf::Vector2i(i - 1, j - 1));
            }
            if (j - 1 >= 0)
            {
                moves->push_back(sf::Vector2i(i, j - 1));
            }
            if ((i + 1 < Board.XMax )&& (j - 1 >= 0))
            {
                moves->push_back(sf::Vector2i(i + 1, j - 1));
            }
            if (i + 1 < Board.XMax)
            {
                moves->push_back(sf::Vector2i(i + 1, j));
            }
            if (j + 2 < Board.YMax-1)
            {
                moves->push_back(sf::Vector2i(i, j+2));
            }
            if (j-3>0)
            {
                moves->push_back(sf::Vector2i(i, j-2));
            }
            return 0;
        }
        if ((((from.first-to.first<=1) && (from.first - to.first) >=-1))&& ((from.second - to.second <= 1) && (from.second - to.second) >= -1))
        {
           
            if (piece == WKing)
            {
                //Если огонь по своим
                if (Board.board[to.first][to.second] < 6 && Board.board[to.first][to.second] != WKing)
                {
                    return false;
                }
                //Есть ли пешки рядом
                if (to.first + 1 < Board.XMax && to.second + 1 < Board.YMax)
                {
                    if (Board.board[to.first + 1][to.second + 1] == BPawn)
                    {
                        return false;
                    }
                }
                if (to.first + 1 < Board.XMax && to.second - 1 >= 0)
                {
                    if (Board.board[to.first + 1][to.second - 1] == BPawn)
                    {
                        return false;
                    }
                }

                //Временная перестановка
                Board.board[from.first][from.second] = EMPTYPiece;
                Board.board[to.first][to.second] = piece;
                
                //Если рядом король
                for (int i = 0; i < Board.XMax; i++)
                {
                    for (int j = 0; j < Board.YMax; j++)
                        if (Board.board[i][j] == BKing)
                        {
                            if (i + 1 < Board.XMax && j + 1 < Board.YMax)//++
                            {
                                if (Board.board[i + 1][j + 1] == WKing)
                                {
                                    
                                    Board.board[to.first][to.second] = tto;
                                    Board.board[from.first][from.second] = WKing;
                                    return false;
                                }
                            }
                            if (j + 1 < Board.YMax)//0+
                            {
                                if (Board.board[i][j + 1] == WKing)
                                {
                                   
                                    Board.board[to.first][to.second] = tto;
                                    Board.board[from.first][from.second] = WKing;
                                    return false;
                                }
                            }
                            if (i - 1 >= 0 && j + 1 < Board.YMax)//-+
                            {
                                if (Board.board[i - 1][j + 1] == WKing)
                                {
                                    
                                    Board.board[to.first][to.second] = tto;
                                    Board.board[from.first][from.second] = WKing;
                                    return false;
                                }
                            }
                            if (i - 1 >= 0)//-0
                            {
                                if (Board.board[i - 1][j] == WKing)
                                {
                                    
                                    Board.board[to.first][to.second] = tto;
                                    Board.board[from.first][from.second] = WKing;
                                    return false;
                                }
                            }
                            if (i - 1 >= 0 && j - 1 >= 0)//--
                            {
                                if (Board.board[i - 1][j - 1] == WKing)
                                {
                                    
                                    Board.board[to.first][to.second] = tto;
                                    Board.board[from.first][from.second] = WKing;
                                    return false;
                                }
                            }
                            if (j - 1 >= 0)//0-
                            {
                                if (Board.board[i][j - 1] == WKing)
                                {
                                    
                                    Board.board[to.first][to.second] = tto;
                                    Board.board[from.first][from.second] = WKing;
                                    return false;
                                }
                            }
                            if (i + 1 < Board.XMax && j - 1 >= 0)//+-
                            {
                                if (Board.board[i + 1][j - 1] == WKing)
                                {
                                    
                                    Board.board[to.first][to.second] = tto;
                                    Board.board[from.first][from.second] = WKing;
                                    return false;
                                }
                            }
                            if (i + 1 < Board.XMax)//+0
                            {
                                if (Board.board[i + 1][j] == WKing)
                                {
                                    
                                    Board.board[to.first][to.second] = tto;
                                    Board.board[from.first][from.second] = WKing;
                                    return false;
                                }
                            }
                            i = Board.XMax;
                            break;
                            
                        }
                }

                int result = isValidMove(to, to, 1);
                if (result != 0)
                {
                    
                    
                    Board.board[to.first][to.second] = tto;
                    Board.board[from.first][from.second] = piece;
                    return false;
                }
            }
            if (piece == BKing)
            {
                //Если огонь по своим
                if (Board.board[to.first][to.second] >= 6 && Board.board[to.first][to.second] < 12 && Board.board[to.first][to.second] != BKing)
                {
                    return false;
                }
                //Есть ли пешки рядом
                if (to.first - 1 >= 0 && to.second + 1 < Board.YMax)
                {
                    if (Board.board[to.first - 1][to.second + 1] == WPawn)
                    {
                        return false;
                    }
                }
                if (to.first - 1 >= 0 && to.second - 1 >= 0)
                {
                    if (Board.board[to.first - 1][to.second - 1] == WPawn)
                    {
                        return false;
                    }
                }
                Board.board[from.first][from.second] = EMPTYPiece;
                Board.board[to.first][to.second] = BKing;
                //Если рядом король
                for (int i = 0; i < Board.XMax; i++)
                {
                    for (int j = 0; j < Board.YMax; j++)
                        if (Board.board[i][j] == WKing)
                        {
                            if ((i + 1 < Board.XMax) &&(j + 1 < Board.YMax))//++
                            {
                                if (Board.board[i + 1][j + 1] == BKing)
                                {
                                    Board.board[from.first][from.second] = BKing;
                                    Board.board[to.first][to.second] = tto;
                                    return false;
                                }
                                    
                            }
                            if ((j + 1) < Board.YMax)//0+
                            {
                                if (Board.board[i][j + 1] == BKing)
                                {
                                    Board.board[from.first][from.second] = BKing;
                                    Board.board[to.first][to.second] = tto;
                                    return false;
                                }
                            }
                            if (i - 1 >= 0 && j + 1 < Board.YMax)//-+
                            {
                                
                                if (Board.board[i - 1][j + 1] == BKing)
                                {
                                    Board.board[from.first][from.second] = BKing;
                                    Board.board[to.first][to.second] = tto;
                                    return false;
                                }
                            }
                            if ((i - 1 )>= 0)//-0
                            {
                                if (Board.board[i - 1][j] == BKing)
                                {
                                    Board.board[from.first][from.second] = BKing;
                                    Board.board[to.first][to.second] = tto;
                                    return false;
                                }
                            }
                            if ((i - 1 >= 0 )&&( (j - 1) >= 0))//--
                            {
                                if (Board.board[i - 1][j - 1] == BKing)
                                {
                                    Board.board[from.first][from.second] = BKing;
                                    Board.board[to.first][to.second] = tto;
                                    return false;
                                }
                            }
                            if (j - 1 >= 0)//0-
                            {
                                if (Board.board[i][j - 1] == BKing)
                                {
                                    Board.board[from.first][from.second] = BKing;
                                    Board.board[to.first][to.second] = tto;
                                    return false;
                                }
                            }
                            if ((i + 1 < Board.XMax )&& (j - 1 >= 0))//+-
                            {
                                if (Board.board[i + 1][j - 1] == BKing)
                                {
                                    Board.board[from.first][from.second] = BKing;
                                    Board.board[to.first][to.second] = tto;
                                    return false;
                                }
                            }
                            if (i + 1 < Board.XMax)//+0
                            {
                                if (Board.board[i + 1][j] == BKing)
                                {
                                    Board.board[from.first][from.second] = BKing;
                                    Board.board[to.first][to.second] = tto;
                                    return false;
                                }
                            }

                            i = Board.XMax;
                            break;
                        }
                }
               
                int result = isValidMove(to, to,2);
                if (result != 0)
                {
                    Board.board[to.first][to.second] = tto;
                    Board.board[from.first][from.second] = BKing;
                    return false;
                }
            }
            Board.board[to.first][to.second] = tto;
            Board.board[from.first][from.second] = piece;
            return true;
        }
        else if(from.first - to.first == 0&&!(BCheck||WCheck))
        {
            //Рокировка
            if (piece == WKing)
            {
                for (int i = 0; i < Moves.size(); i++)
                {
                    if (Moves[i].White.piecef == piece)
                    {
                        return false;
                    }                  
                }
                //Куда делать рокировку 
                // -->
                if (from.second - to.second < 0)
                {
                    //если ладья ходила и/или убита
                    for (int i = 0; i < Moves.size(); i++)
                    {
                        if (Moves[i].White.from == sf::Vector2i(0,Board.YMax-1) || Moves[i].Black.to == sf::Vector2i(0, Board.YMax - 1))
                        {
                            return false;
                        }
                    }
                    if (Board.board[0][Board.YMax - 2] == EMPTYPiece && Board.board[0][Board.YMax - 3] == EMPTYPiece)
                    {

                        if (isValidMoveKing(from,std::pair(from.first,from.second+1)))
                        {
                            Board.board[from.first][from.second] = EMPTYPiece;
                            Board.board[from.first][from.second + 1] = WKing;
                            if (isValidMoveKing(std::pair(from.first, from.second + 1), std::pair(from.first, from.second + 2)))
                            {
                                Board.board[from.first][from.second + 1] = EMPTYPiece;
                                Board.board[from.first][from.second] = WKing;
                                return 7;
                            }
                            else
                            {
                                Board.board[from.first][from.second + 1] = EMPTYPiece;
                                Board.board[from.first][from.second] = WKing;
                                return false;
                            }
                        }
                    }
                }
                // <--
                else
                {
                    //если ладья ходила и/или убита
                    for (int i = 0; i < Moves.size(); i++)
                    {
                        if (Moves[i].White.from == sf::Vector2i(0, 0) || Moves[i].Black.to == sf::Vector2i(0, 0))
                        {
                            return false;
                        }
                    }
                    if (Board.board[0][1] == EMPTYPiece && Board.board[0][2] == EMPTYPiece&& Board.board[0][3] == EMPTYPiece)
                    {

                        if (isValidMoveKing(from, std::pair(from.first, from.second - 1)))
                        {
                            Board.board[from.first][from.second] = EMPTYPiece;
                            Board.board[from.first][from.second - 1] = WKing;
                            if (isValidMoveKing(std::pair(from.first, from.second - 1), std::pair(from.first, from.second - 2)))
                            {
                                Board.board[from.first][from.second - 1] = EMPTYPiece;
                                Board.board[from.first][from.second] = WKing;
                                return 7;
                            }
                            else
                            {
                                Board.board[from.first][from.second - 1] = EMPTYPiece;
                                Board.board[from.first][from.second] = WKing;
                                return false;
                            }
                        }
                    }

                }
            }
            else if (piece == BKing)
            {
                for (int i = 0; i < Moves.size(); i++)
                {
                    if (Moves[i].Black.piecef == piece)
                    {
                        return false;
                    }
                }
                //Куда делать рокировку 
                // -->
                if (from.second - to.second < 0)
                {
                    //если ладья ходила и/или убита
                    for (int i = 0; i < Moves.size(); i++)
                    {
                        if (Moves[i].White.from == sf::Vector2i(Board.XMax - 1, Board.YMax - 1) || Moves[i].Black.to == sf::Vector2i(Board.XMax - 1, Board.YMax - 1))
                        {
                            return false;
                        }
                    }
                    if (Board.board[Board.XMax - 1][Board.YMax - 2] == EMPTYPiece && Board.board[Board.XMax - 1][Board.YMax - 3] == EMPTYPiece)
                    {
                        if (isValidMoveKing(from, std::pair(from.first, from.second + 1)))
                        {
                            Board.board[from.first][from.second] = EMPTYPiece;
                            Board.board[from.first][from.second + 1] = BKing;
                            if (isValidMoveKing(std::pair(from.first, from.second + 1), std::pair(from.first, from.second + 2)))
                            {
                                Board.board[from.first][from.second + 1] = EMPTYPiece;
                                Board.board[from.first][from.second] = BKing;
                                return 7;
                            }
                            else
                            {
                                Board.board[from.first][from.second + 1] = EMPTYPiece;
                                Board.board[from.first][from.second] = BKing;
                                return false;
                            }
                        }
                    }
                }
                // <--
                else
                {
                    
                    //если ладья ходила и/или убита
                    for (int i = 0; i < Moves.size(); i++)
                    {
                        if (Moves[i].White.from == sf::Vector2i(Board.XMax-1, 0) || Moves[i].Black.to == sf::Vector2i(Board.XMax - 1, 0))
                        {
                            return false;
                        }
                    }
                    if (Board.board[Board.XMax-1][1]==EMPTYPiece&& Board.board[Board.XMax - 1][2]==EMPTYPiece&& Board.board[Board.XMax - 1][3] == EMPTYPiece)
                    {
                        
                        if (isValidMoveKing(from, std::pair(from.first, from.second - 1)))
                        {
                            
                            Board.board[from.first][from.second] = EMPTYPiece;
                            Board.board[from.first][from.second - 1] = BKing;
                            if (isValidMoveKing(std::pair(from.first, from.second - 1), std::pair(from.first, from.second - 2)))
                            {
                                Board.board[from.first][from.second - 1] = EMPTYPiece;
                                Board.board[from.first][from.second] = BKing;
                                return 7;
                            }
                            else
                            {
                                Board.board[from.first][from.second - 1] = EMPTYPiece;
                                Board.board[from.first][from.second] = BKing;
                                return false;
                            }
                        }
                    }

                }
            }
            
        }
        Board.board[to.first][to.second] = tto;
        Board.board[from.first][from.second] = piece;
        return false;
    }
    int isValidMovePawn(std::pair<int, int> from, std::pair<int, int> to,int king = 0, std::vector<sf::Vector2i>* moves = nullptr)
    {
        bool mn = false;
        if (moves == nullptr)
        {
            moves = new std::vector<sf::Vector2i>;
            mn = true;
        }
        short piece = Board.board[from.first][from.second];
        short piece2 = Board.board[to.first][to.second];
        short tto = Board.board[to.first][to.second];
        if (king == 0)
        {
            if (!CheckKing(from,to))
            {
                return 0;
            }
        }
        switch (piece)
        {
        case WPawn:
            if (king == -1)
            {
                if (from.first + 1<Board.XMax)
                {
                    if (from.first + 2 < Board.XMax)
                    {
                        moves->push_back(sf::Vector2i(from.first + 2, from.second));
                    }
                    moves->push_back(sf::Vector2i(from.first + 1, from.second));
                    if (from.second + 1 < Board.YMax)
                    {
                        moves->push_back(sf::Vector2i(from.first + 1, from.second + 1));
                    }
                    if (from.second - 1 >= 0)
                    {
                        moves->push_back(sf::Vector2i(from.first + 1, from.second - 1));
                    }
                }
                
            }
            if (from.first == 1)
            {
                if ((to.first - from.first) == 2 && from.second - to.second == 0)
                {
                    //Если 2 клетки пусты, можно идти
                    if (piece2 == EMPTYPiece && Board.board[to.first - 1][to.second] == EMPTYPiece)
                    {
                        return 3;
                    }
                    
                }

            }
            if ((to.first - from.first) == 1 && (from.second - to.second) <= 1 && (from.second - to.second) >= -1)
            {

                if (from.second - to.second != 0 && (piece2 != EMPTYPiece))
                {
                    if (to.first == (Board.XMax - 1))
                    {

                        return 4;//Бой с превращением
                    }
                    return true;//Бой пешки
                }

                /*Взятие на проходе*/
                if (lastmove.piece == BPawn)
                {
                    if ((lastmove.from.x - lastmove.to.x) == 2)
                    {
                        if (to.first< lastmove.from.x && to.first > lastmove.to.x)
                        {
                            if (to.second == lastmove.to.y)
                            {
                                return 5;//Взятие на проходе
                            }
                        }
                    }
                }

                if (from.second - to.second == 0 && piece2 == 12)
                {
                    if (to.first == (Board.XMax - 1))
                    {
                        return 2;//Превращение
                    }
                    return 6;//Ход на 1 клетку
                }


            }
            break;
        case BPawn:
            if (king == -1)
            {
                if (from.first - 2>=0)
                {
                    moves->push_back(sf::Vector2i(from.first - 2, from.second));
                }
                if (from.first - 1 >= 0)
                {
                    moves->push_back(sf::Vector2i(from.first - 1, from.second));
                    if (from.second - 1 >= 0)
                    {
                        moves->push_back(sf::Vector2i(from.first - 1, from.second - 1));
                    }
                    if (from.second + 1 < Board.YMax)
                    {
                        moves->push_back(sf::Vector2i(from.first - 1, from.second + 1));
                    }
                    
                }
            }
            if ((Board.XMax - 1 - from.first) == 1)
            {
                if ((to.first - from.first) == -2 && from.second - to.second == 0)
                {
                    //Если 2 клетки пусты, можно идти
                    if (piece2 == EMPTYPiece && Board.board[to.first + 1][to.second] == EMPTYPiece)
                    {
                        return 3;
                    }

                }

            }
            if ((to.first - from.first) == -1 && (from.second - to.second) <= 1 && (from.second - to.second) >= -1)
            {
                if (from.second - to.second != 0 && (piece2 != EMPTYPiece))
                {
                    if (to.first == 0)
                    {
                        return 4;
                    }
                    return true;
                }
                /*Взятие на проходе*/
                if (lastmove.piece == WPawn)
                {
                    if ((lastmove.to.x - lastmove.from.x) == 2)
                    {
                        if (to.first > lastmove.from.x && to.first < lastmove.to.x)
                        {
                            if (to.second == lastmove.to.y)
                            {
                                return 5;
                            }
                        }
                    }
                }
                if (from.second - to.second == 0 && piece2 == 12)
                {
                    if (to.first == 0)
                    {
                        return 2;
                    }
                    return 6;
                }


            }
        }
        return 0;
    }
    int CheckKing(std::pair<int, int> from, std::pair<int, int> to){
        short tto = Board.board[to.first][to.second];


        if (Board.board[from.first][from.second] < 5)
        {
            Board.board[to.first][to.second] = Board.board[from.first][from.second];
            Board.board[from.first][from.second] = EMPTYPiece;
            for (size_t i = 0; i < Board.XMax; i++)
            {
                for (size_t j = 0; j < Board.YMax; j++)
                    if (Board.board[i][j] == WKing)
                    {
                        if (!isValidMoveKing(std::pair(i, j), std::pair(i, j)))
                        {
                            Board.board[from.first][from.second] = Board.board[to.first][to.second];
                            Board.board[to.first][to.second] = tto;
                            return 0;
                        }
                        else
                        {
                            Board.board[from.first][from.second] = Board.board[to.first][to.second];
                            Board.board[to.first][to.second] = tto;
                            i = Board.XMax;
                            break;

                        }

                    }
            }

        }
        if (Board.board[from.first][from.second] > 5)
        {
            Board.board[to.first][to.second] = Board.board[from.first][from.second];
            Board.board[from.first][from.second] = EMPTYPiece;
            for (size_t i = 0; i < Board.XMax; i++)
            {
                for (size_t j = 0; j < Board.YMax; j++)
                    if (Board.board[i][j] == BKing)
                    {
                        if (!isValidMoveKing(std::pair(i, j), std::pair(i, j)))
                        {
                            Board.board[from.first][from.second] = Board.board[to.first][to.second];
                            Board.board[to.first][to.second] = tto;
                            return 0;
                        }
                        else
                        {
                            Board.board[from.first][from.second] = Board.board[to.first][to.second];
                            Board.board[to.first][to.second] = tto;
                            i = Board.XMax;
                            break;

                        }

                    }
            }

        }
        return 1;
    }
    void play()
    {
        for (size_t i = 0; i < Moves.size(); i++)
        {
            cout << "#" << i << endl;
            cout << "White: from (" << Moves[i].White.from.x << ", " << Moves[i].White.from.y << ")to (" << Moves[i].White.to.x << ", " << Moves[i].White.to.y << ")\n";
            cout << "Black: from (" << Moves[i].Black.from.x << ", " << Moves[i].Black.from.y << ")to (" << Moves[i].Black.to.x << ", " << Moves[i].Black.to.y << ")\n";

        }
    }
    ~RenderClassicChess()
    {
       delete[] ChessPicesTexture;
       delete moves;
       delete SpritePieces;
       delete nc;
    }
};

