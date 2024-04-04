#include "RenderMenu.h"

bool RenderMenu::showRenderMenu = true;
bool RenderMenu::showProfile = false;
bool RenderMenu::showConsole = false;
bool RenderMenu::showSettings = false;
bool RenderMenu::showLocalGame = false;
bool RenderMenu::showNetworkGame = false;
bool RenderMenu::showNetworkGameCreator = false;
bool RenderMenu::OnGameGUI = false;
bool RenderMenu::OnNetGameGUI = false;
bool RenderMenu::Play = false;
bool RenderMenu::ServerOrClient  = false;
bool RenderMenu::is_server_waiting = false;
bool RenderMenu::showRule = false;
///
int RenderMenu::gameMode;
float RenderMenu::moveTime = 60.0f; // Количество секунд на ход
int RenderMenu::addTimeIndex = 0; // Индекс выбранного времени для добавления
bool RenderMenu::isControlTime = true;
bool RenderMenu::withRating = false;

const char* RenderMenu::gameModes[] = { "Standard"};//"Standard", "Crazyhouse", "Chess960", "King of the Hill", "Three Check", "Antichess", "Racing Kings", "FFA(box2d)"
const char* RenderMenu::addTimes[] = { "+0 sec", "+1 sec", "+2 sec", "+3 sec", "+4 sec","+5 sec" };
const float RenderMenu::moveTimes[] = { 30.0f, 60.0f, 120.0f, 300.0f, 3600.0f };

//RenderClassicChess *RenderMenu::netGame = nullptr;

bool RenderMenu::ShowGraphicsSettings = true;
//bool RenderMenu::showControlsSettings = false;
//bool RenderMenu::showSoundSettings = false;
float RenderMenu::deltaTime = 0.0f;
float RenderMenu::lastFrameTime = 0.0f;
int RenderMenu::fps = 1;

DBController RenderMenu::db;
ImGuiConsole RenderMenu::console;
CSettings RenderMenu::tempSettings;
CSettings RenderMenu::CGlobalSettings;
string RenderMenu::VersionBuildStr;

bool RenderMenu::showReloadDialog = false;
struct KeySet
{
    string name;
    double* valueD = nullptr;
    int* valueI = nullptr;
    bool* valueB = nullptr;
    float* valueF = nullptr;
    sf::Keyboard::Key* valueK = nullptr;
    KeySet(string name, double* value) {
        this->name = name;
        this->valueD = value;
    }
    KeySet(string name, int* value) {
        this->name = name;
        this->valueI = value;
    }
    KeySet(string name, float* value) {
        this->name = name;
        this->valueF = value;
    }
    KeySet(string name, bool* value) {
        this->name = name;
        this->valueB = value;
    }
    KeySet(string name, sf::Keyboard::Key* value) {
        this->name = name;
        this->valueK = value;
    }
};
void Starter()
{
    vector<KeySet>* setteingstr = new vector<KeySet>;
    setteingstr->push_back(KeySet("brightness", &RenderMenu::CGlobalSettings.video.brightness));
    setteingstr->push_back(KeySet("FrameRateLimit", &RenderMenu::CGlobalSettings.video.FrameRateLimit));
    setteingstr->push_back(KeySet("FullScreen", &RenderMenu::CGlobalSettings.video.FullScreen));
    setteingstr->push_back(KeySet("Vsynk",&RenderMenu::CGlobalSettings.video.Vsynk));
    setteingstr->push_back(KeySet("WinW",&RenderMenu::CGlobalSettings.video.WinW));
    setteingstr->push_back(KeySet("WinH",&RenderMenu::CGlobalSettings.video.WinH));
    //setteingstr.push_back("brightness");
    
    std::ifstream file("source\\settings.txt"); // открыть файл для чтения
    std::string line;
    std::string key;
    double value;
    if (file.is_open()) { // проверить, успешно ли открыт файл
        while (file >> key >> value) { // читаем ключ и значение пока можем
            for (size_t i = 0; i < setteingstr->size(); i++)
            {
                if (setteingstr[0][i].name == key)
                {
                    if (setteingstr[0][i].valueB != nullptr)
                        *setteingstr[0][i].valueB = value;
                    else if (setteingstr[0][i].valueD != nullptr)
                        *setteingstr[0][i].valueD = value;
                    else if (setteingstr[0][i].valueF != nullptr)
                        *setteingstr[0][i].valueF = value;
                    else if (setteingstr[0][i].valueI != nullptr)
                        *setteingstr[0][i].valueI = value;
                    else if (setteingstr[0][i].valueK != nullptr)
                        *setteingstr[0][i].valueK = (sf::Keyboard::Key)value;
                    setteingstr->erase(setteingstr->begin() + i);
                    i--;
                }
            }
            std::cout << "Key: " << key << ", Value: " << value << std::endl;
        }
        file.close(); // закрыть файл
    }
    else {
        std::ofstream file("source\\settings.txt"); // открыть файл для записи

        if (file.is_open()) { // проверить, успешно ли открыт файл
            file << "brightness " << RenderMenu::CGlobalSettings.video.brightness << std::endl; // записать строку в файл
            file << "FrameRateLimit " << RenderMenu::CGlobalSettings.video.FrameRateLimit << std::endl; // записать строку в файл
            file << "FullScreen " << RenderMenu::CGlobalSettings.video.FullScreen << std::endl; // записать строку в файл
            file << "Vsynk " << RenderMenu::CGlobalSettings.video.Vsynk << std::endl; // записать строку в файл
            file << "WinW " << RenderMenu::CGlobalSettings.video.WinW << std::endl; // записать строку в файл
            file << "WinH " << RenderMenu::CGlobalSettings.video.WinH << std::endl; // записать строку в файл

            file.close(); // закрыть файл
        }
        else {
            std::cout << "Unable to open file" << std::endl;
        }


    }
    delete setteingstr;
    RenderMenu::tempSettings = RenderMenu::CGlobalSettings;
}
void SaveSettings()
{
    std::ofstream file("source\\settings.txt"); // открыть файл для записи

    if (file.is_open()) { // проверить, успешно ли открыт файл
        file << "brightness " << RenderMenu::CGlobalSettings.video.brightness << std::endl; // записать строку в файл
        file << "FrameRateLimit " << RenderMenu::CGlobalSettings.video.FrameRateLimit << std::endl; // записать строку в файл
        file << "FullScreen " << RenderMenu::CGlobalSettings.video.FullScreen << std::endl; // записать строку в файл
        file << "Vsynk " << RenderMenu::CGlobalSettings.video.Vsynk << std::endl; // записать строку в файл
        file << "WinW " << RenderMenu::CGlobalSettings.video.WinW << std::endl; // записать строку в файл
        file << "WinH " << RenderMenu::CGlobalSettings.video.WinH << std::endl; // записать строку в файл

        file.close(); // закрыть файл
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
}
void scaleImage(sf::Sprite& sprite, int desiredWidth, int desiredHeight)
{
    float scaleX = static_cast<float>(RenderMenu::CGlobalSettings.video.WinW) / static_cast<float>(desiredWidth);
    float scaleY = static_cast<float>(RenderMenu::CGlobalSettings.video.WinH) / static_cast<float>(desiredHeight);
    float scale = std::min(scaleX, scaleY);

    sprite.setScale(scaleX, scaleY);
}
//Только для Windows
void RenderMenu::restart_program()
{
    SaveSettings();
    // Вызываем командную строку и передаем ей команду для запуска программы заново

    std::system("start ChessCounterattack.exe");
    

    // Завершаем текущий процесс
    std::exit(0);
}
void RenderMenu::ReloaderDialog()
{
    ImGui::OpenPopup(uTC(u8"Перезагрузить приложение?"));
    
    // Confirmation
    if (ImGui::BeginPopupModal(uTC(u8"Перезагрузить приложение?"), &showReloadDialog, ImGuiWindowFlags_AlwaysAutoResize))
    {
        //std::cout << "Worked\n";
        ImGui::Text(uTC(u8"Для изменения некоторых параметров нужна перезагрузка,\n перезагрузить?\n\n"));
        ImGui::Separator();

        if (ImGui::Button(uTC(u8"Перезагрузить"), ImVec2(120, 0)))
        {
            showReloadDialog = false;
            restart_program();
            ImGui::CloseCurrentPopup();
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(uTC(u8"Нет"), ImVec2(120, 0)))
        {
            showReloadDialog = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
    /*
    ImGui::OpenPopup("Reload Dialog");
    if (ImGui::BeginPopupModal("Reload Dialog", &showReloadDialog, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Для изменения некоторых параметров нужна перезагрузка, перезагрузить?");
        ImGui::Separator();
        if (ImGui::Button("Да", ImVec2(120, 0))) {
            restart_program();
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Нет", ImVec2(120, 0))) {
            
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }*/
}
void StartServer()
{
    std::system("start ServerChessCounterattack.exe");
}





