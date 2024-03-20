#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <sstream>
static std::string PacketMove = "-";
class NetClient
{
public:
    NetClient(sf::IpAddress serverAddress, unsigned short serverPort)
    {
        // Connect to the server
        if (m_socket.connect(serverAddress, serverPort) != sf::Socket::Done)
        {
            std::cerr << "Failed to connect to server " << serverAddress << ":" << serverPort << std::endl;
            return;
        }

        std::cout << "Connected to server " << serverAddress << ":" << serverPort << std::endl;

        // Start the receiving thread
        m_receivingThread = std::thread([&]()
            {
                while (true)
                {
                    sf::Packet packet;
                    if (m_socket.receive(packet) != sf::Socket::Done)
                    {
                        // Server disconnected
                        std::cout << "Disconnected from server." << std::endl;
                        break;
                    }
                    std::stringstream ss;
                    ss << packet;
                    PacketMove = ss.str();
                    // Process the packet
                    // ...
                }
            });
    }

    ~NetClient()
    {
        // Disconnect from the server
        m_socket.disconnect();

        // Wait for the receiving thread to finish
        if (m_receivingThread.joinable())
        {
            m_receivingThread.join();
        }
    }

    void sendPacket(sf::Packet& packet)
    {
        m_socket.send(packet);
    }

private:
    sf::TcpSocket m_socket;
    std::thread m_receivingThread;
};
//#include <SFML/Network.hpp>
//#include "RenderMenu.h"
//#include <iostream>
//#include <string>
//class NetClient
//{
//    sf::UdpSocket socket;
//
//public:
//    NetClient()
//    {
//        socket.setBlocking(false);
//    }
//
//    std::string Receiver()
//    {
//        std::string message = "-";
//        sf::Packet response;
//        sf::IpAddress sender;
//        unsigned short port;
//        if (socket.receive(response, sender, port) == sf::Socket::Done)
//        {
//            
//            response >> message;
//            std::cout << "Received response from server: " << message << std::endl;
//        }
//        return message;
//    }
//
//    void SendMessenge(const std::string& message, sf::IpAddress IP = sf::IpAddress::getLocalAddress(), unsigned short port = 25565)
//    {
//        sf::Packet packet;
//        packet << message.c_str();
//        socket.send(packet, IP, port);
//        
//    }
//};
//
//class NetClient
//{
//    sf::TcpSocket socket;
//
//public:
//    NetClient()
//    {
//        //socket.setBlocking(false);
//    }
//
//    bool Connector(sf::IpAddress IP = sf::IpAddress::getLocalAddress(), unsigned short port = 25565)
//    {
//        std::cout << "попытка подключения" << std::endl;
//        sf::Socket::Status status = socket.connect(IP, port, sf::seconds(10));
//        if (status != sf::Socket::Done)
//        {
//            std::cout << "Ошибка подключения: " << status << std::endl;
//            return 0;
//        }
//        else
//        {
//            std::cout << "Успешное подключение " << status << std::endl;
//            return 1;
//        }
//    }
//
//    std::string Receiver()
//    {    
//            std::string message;
//
//            // Сокет готов к чтению
//            char buffer[2048];
//            std::size_t received;
//
//            // Читаем данные из сокета
//            sf::Socket::Status status = socket.receive(buffer, sizeof(buffer), received);
//            if (status == sf::Socket::Done)
//            {
//                // Данные получены успешно
//                std::cout << "Получены данные: " << buffer << std::endl;
//                message = buffer;
//            }
//            else if (status == sf::Socket::Disconnected)
//            {
//                // Соединение разорвано сервером
//                std::cout << "Соединение разорвано сервером" << std::endl;
//                message = "-1";
//            }
//            else
//            {
//                // Произошла ошибка
//                std::cout << "Ошибка чтения данных: " << status << std::endl;
//                message = "-";
//            }
//            return message;
//    }
//
//    void SendMessenge(const std::string& messenge)
//    {
//        socket.send(messenge.c_str(), messenge.size() + 1);
//    }
//};





























































//class NetClient {
//private:
//    sf::TcpSocket socket;
//
//public:
//    NetClient() {
//        socket.setBlocking(false);
//    }
//
//    bool Connector(sf::IpAddress ip,unsigned short port) {
//        if (socket.connect(ip, port, sf::seconds(10)) == sf::Socket::Done) {
//            socket.setBlocking(false);
//            return true;
//        }
//        return false;
//    }
//
//    void SendMessenge(const string move) {
//        std::string message = move;
//        socket.send(message.c_str(), message.size() + 1);
//    }
//    string Receiver() {
//        char buffer[1024];
//        std::size_t received;
//
//        sf::Socket::Status status = socket.receive(buffer, sizeof(buffer), received);
//        if (status == sf::Socket::Done) {
//            std::string message(buffer, received);
//            
//            return message;
//        }
//        // Обработка ошибок чтения данных из сокета
//        return "-"; // или бросить исключение
//    }
//};
//
