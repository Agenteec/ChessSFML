#pragma region ChessBoard
//if (RenderMenu::OnGameGUI)
//{
//
//    for (int i = 0; i < CB.XMax; i++)
//    {
//        for (int j = 0; j < CB.YMax; j++)
//        {
//            if (CB.board[i][j] != 12)
//            {
//                switch (rotater)
//                {
//                case 4:
//                    ChessPicesSprite[CB.board[i][j]].setPosition((CB.XMax - 1 - i) * cellSize * Scale + RenderMenu::CGlobalSettings.video.WinW / 2 - CB.XMax / 2 * cellSize * Scale, (CB.YMax - 1 - j) * cellSize * Scale + RenderMenu::CGlobalSettings.video.WinH / 10);
//                    break;
//                case 3:
//                    ChessPicesSprite[CB.board[i][j]].setPosition(j * cellSize * Scale + RenderMenu::CGlobalSettings.video.WinW / 2 - CB.XMax / 2 * cellSize * Scale, i * cellSize * Scale + RenderMenu::CGlobalSettings.video.WinH / 10);
//                    break;
//                case 2:
//                    ChessPicesSprite[CB.board[i][j]].setPosition(i * cellSize * Scale + RenderMenu::CGlobalSettings.video.WinW / 2 - CB.XMax / 2 * cellSize * Scale, j * cellSize * Scale + RenderMenu::CGlobalSettings.video.WinH / 10);
//                    break;
//                case 1:
//                    ChessPicesSprite[CB.board[i][j]].setPosition((CB.YMax - 1 - j) * cellSize * Scale + RenderMenu::CGlobalSettings.video.WinW / 2 - CB.XMax / 2 * cellSize * Scale, (CB.XMax - 1 - i) * cellSize * Scale + RenderMenu::CGlobalSettings.video.WinH / 10);
//                #pragma region Move
//                    {
//                        while (window->pollEvent(event))
//                        {
//                            sf::Vector2f piecePosition;
//                            sf::Vector2f mousePosition;
//                            std::cout << "+++\n";
//                            // Добавляем обработку событий мыши
//                            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//                            {
//                                // Определяем координаты мыши при нажатии на фигуру
//                                mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
//                                r++;
//                                g++;
//                                b++;
//                                if (r >= 255)
//                                {
//                                    r = 0;
//                                    g = 0;
//                                    b = 0;
//                                }
//                                // Находим фигуру, на которую нажал пользователь
//                                for (int i = 0; i < CB.XMax; i++)
//                                {
//                                    for (int j = 0; j < CB.YMax; j++)
//                                    {
//                                        if (CB.board[i][j] != 12)
//                                        {
//                                            // Получаем позицию фигуры на доске
//                                            sf::Vector2f piecePosition = ChessPicesSprite[CB.board[i][j]].getPosition();

//                                            // Проверяем, находится ли мышь внутри фигуры
//                                            if (mousePosition.x >= piecePosition.x && mousePosition.x <= piecePosition.x + cellSize * Scale &&
//                                                mousePosition.y >= piecePosition.y && mousePosition.y <= piecePosition.y + cellSize * Scale)
//                                            {
//                                                // Сохраняем позицию фигуры и выходим из цикла
//                                                piecePosition = ChessPicesSprite[CB.board[i][j]].getPosition();
//                                                ChessPicesSprite->setColor(sf::Color(r, g, b));
//                                                break;
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
//                            {
//                                // Определяем координаты мыши при отпускании фигуры
//                                mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
//                            }
//                        }
//                    }
//                    #pragma endregion

//                    break;
//                default:
//                    break;
//                }
//                
//                //window->draw(ChessPicesSprite[CB.board[i][j]]);
//            }
//               
//        }
//    }
//    
//}
//ImGui::Begin("Rotator");
//if (ImGui::Button(u8"Rotate", ImVec2(200.f, 50.f)))
//{
//    if (rotater<4)
//    {
//        rotater++;
//    }
//    else
//    {
//        rotater = 1;
//    }
//}
//ImGui::End();

#pragma endregion
#pragma region SVG
    //sfc::SVGImage img;

    ///* Don't show debug lines */
    //img.setMode(sfc::DrawMode::NORMAL);
    //
    ///* Load SVG image from file */
    //img.loadFromFile("source\\images\\ChessPieceSVG\\blackRook.svg");
    //img.scale(10);
    ///* Rasterize image */
    //img.rasterize(5).saveToFile("rasterized.png");

    ///* Move it by [10, 10] to make it more visible */
    //img.move({ 10, 10 });


#pragma endregion
/*sf::Vector2f p = SpritePieces[0][n].Piece.getPosition() + sf::Vector2f((50) / 2, (50) / 2);
                newPos = sf::Vector2f((50) * int(p.x / (50)), (50) * int(p.y / (50)));*/

                /*str = toChessNote(oldPos) + toChessNote(newPos);
                move(str);
                std::cout << str << std::endl;*/




                //std::cout << "(" << SpritePieces[0][n].Pos.x << ", " << SpritePieces[0][n].Pos.y << ")" << "--> (" << Board.YMax - yy - 1 << ", " << xx << ") - 2" << std::endl;//2
                                    //std::cout << "(" << SpritePieces[0][n].Pos.x << ", " << SpritePieces[0][n].Pos.y << ")" << "--> (" << yy << ", " << Board.XMax - 1- xx  << ") - 3" << std::endl;//3
                                    //std::cout << "(" << SpritePieces[0][n].Pos.x << ", " << SpritePieces[0][n].Pos.y << ")" << "--> (" << Board.XMax - xx - 1 << ", " << Board.YMax - 1 - yy << ") - 4" << std::endl;//4
                                    //float xp = RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale;
                                    //float yp = RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale;
                                    //for (int i = 0; i < Board.XMax; ++i)
                                    //{

                                    //    for (int j = 0; j < Board.YMax; ++j)
                                    //    {
                                    //        //cout << i << " " << j << endl;
                                    //        float temp = sqrt(pow((i * xp + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale - pos.x), 2) + pow((j * yp + RenderMenu::CGlobalSettings.video.WinH / 10 - pos.y), 2));
                                    //        //cout << temp << endl;
                                    //        if (temp < min)
                                    //        {

                                    //            min = temp;
                                    //            x = i;
                                    //            y = j;
                                    //        }
                                    //    }
                                    //}
                                    //cout << endl;
                                    //cout <<  << "/" <<  << endl;
                                    //newPos = sf::Vector2f((25 * RenderMenu::CGlobalSettings.chess.scale) * int(p.x / (25 * RenderMenu::CGlobalSettings.chess.scale)), (25 * RenderMenu::CGlobalSettings.chess.scale) * int(p.y / (25 * RenderMenu::CGlobalSettings.chess.scale)));
                                    //if (x != -1)
#pragma region Бинарный поиск расстояния
/*std::vector<int> xCoords;
for (int i = 0; i < Board.XMax-1; ++i)
{
    xCoords.push_back(i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale);
}
std::sort(xCoords.begin(), xCoords.end());

std::vector<int> yCoords;
for (int j = 0; j < Board.YMax-1; ++j)
{
    yCoords.push_back(j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
}
std::sort(yCoords.begin(), yCoords.end());

int xx = std::distance(xCoords.begin(), std::lower_bound(xCoords.begin(), xCoords.end(), pos.x));
if (xx > 0 && pos.x - xCoords[xx - 1] < xCoords[xx] - pos.x)
{
    xx--;
}

int yy = std::distance(yCoords.begin(), std::lower_bound(yCoords.begin(), yCoords.end(), pos.y));
if (yy > 0 && pos.y - yCoords[yy - 1] < yCoords[yy] - pos.y)
{
    yy--;
}

    break;*/
    //}
#pragma endregion