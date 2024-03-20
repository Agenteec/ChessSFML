#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <SFML/Network/IpAddress.hpp>
using namespace std;
static const char* uTC(const char8_t* str)
{
	return reinterpret_cast<const char*> (str);
}
struct KeyBind
{
	string KeyName;
	sf::Keyboard::Key key;
};
class CChessSettings
{
public:
	float scale;
	int cellSize;
	int gamemode;
	int timeControl;
	int increment;
	bool playerColor;
	CChessSettings() :scale(1), cellSize(50), gamemode(0), timeControl(600), increment(0), playerColor(0){}
};
class CNetworkSettings
{
public:
	unsigned short port;
	sf::IpAddress ip;
	CNetworkSettings():port(25565),ip(sf::IpAddress::getLocalAddress()) {}
};
class CVideoSettings
{
public:
	CVideoSettings() :FrameRateLimit(60), WinW(1024), WinH(720), FullScreen(false), Vsynk(false), brightness(1){};
	CVideoSettings(int FrameRateLimit, float WinW, float WinH, bool FullScreen, bool Vsynk, float brightness) :FrameRateLimit(FrameRateLimit), WinW(WinW), WinH(WinH), FullScreen(FullScreen), Vsynk(Vsynk), brightness(brightness){};
	/// <summary>
	/// Лимит кадров в секунду
	/// </summary>
	int FrameRateLimit;
	/// <summary>
	/// Размеры окна
	/// </summary>
	float WinW;
	float WinH;
	/// <summary>
	/// Флаг полноэкранного режима
	/// </summary>
	bool FullScreen;
	/// <summary>
	/// Флаг вертикальной синхронизации
	/// </summary>
	bool Vsynk;
	/// <summary>
	/// Яркость
	/// </summary>
	float brightness;

};
class CVolumeSettings
{
public:
	CVolumeSettings() :ambientVolume(1), musicVolume(1) {};
	CVolumeSettings(float ambientVolume, float musicVolume) :ambientVolume(ambientVolume), musicVolume(musicVolume) {};
	/// <summary>
	/// Настройки громкости окружения
	/// </summary>
	float ambientVolume;
	/// <summary>
	/// Громкость музыки
	/// </summary>
	float musicVolume;
};
class CControlSettings
{
public:
	CControlSettings():Attack(sf::Keyboard::X),Jump(sf::Keyboard::Space),UP(sf::Keyboard::W),Down(sf::Keyboard::S),Left(sf::Keyboard::A),Right(sf::Keyboard::D),Chat(sf::Keyboard::T),Score(sf::Keyboard::Tab),Menu(sf::Keyboard::Escape){};
	//CControlSettings() {};
	//CControlSettings(int ambientVolume, int musicVolume) {};
	/// <summary>
	/// Кнопка атаки
	/// </summary>
	sf::Keyboard::Key Attack;
	/// <summary>
	/// Кнопка прыжка
	/// </summary>
	sf::Keyboard::Key Jump;
	/// <summary>
	/// Кнопка вверх
	/// </summary>
	sf::Keyboard::Key UP;
	/// <summary>
	/// Кнопка вниз
	/// </summary>
	sf::Keyboard::Key Down;
	/// <summary>
	/// Кнопка влево
	/// </summary>
	sf::Keyboard::Key Left;
	/// <summary>
	/// Кнопка вправо
	/// </summary>
	sf::Keyboard::Key Right;
	/// <summary>
	/// Кнопка чата
	/// </summary>
	sf::Keyboard::Key Chat;
	/// <summary>
	/// Кнопка счёт/ список игроков
	/// </summary>
	sf::Keyboard::Key Score;
	/// <summary>
	/// Кнопка выйти в меню
	/// </summary>
	sf::Keyboard::Key Menu;
};
class CSettings
{
	public:
		CChessSettings chess;
		CVideoSettings video;
		CVolumeSettings volume;
		CControlSettings controls;
		CNetworkSettings network;
		
		bool SetSettings(sf::RenderWindow* window)
		{
			#pragma region Video settings
			window->setFramerateLimit(video.FrameRateLimit);
			window->setSize(sf::Vector2u(video.WinW,video.WinH));
			window->setVerticalSyncEnabled(video.Vsynk);
			#pragma endregion
			return false;
		}


};

