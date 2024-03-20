#include <iostream>
#include <thread>
#include <SFML/Network.hpp>
static std::string PacketMove = "-";
class NClient
{
public:
    bool debug;
    NClient(const sf::IpAddress serverAddress, unsigned short serverPort) :
        m_socket(),
        debug(1),
        m_serverAddress(serverAddress),
        m_serverPort(serverPort),
        m_running(true),
        m_thread(&NClient::receiveMessages, this)//Передаём в поток функцию приёма сообщений
    {
        if (m_socket.connect(serverAddress, serverPort) != sf::Socket::Done)//Если подключение не состоялось
        {
            if(debug)
            std::cerr << "Failed to connect to server at " << serverAddress << ":" << serverPort << std::endl;
            m_running = false;
        }
        else
        {
            if (debug)
            std::cout << "Connected to server at " << serverAddress << ":" << serverPort << std::endl;
        }
    }

    ~NClient()
    {
        disconnect();
    }

    void sendMessage(const std::string& message)
    {
        sf::Packet packet;
        packet << message;
        if (m_socket.send(packet) != sf::Socket::Done)
        {
            if (debug)
            std::cerr << "Failed to send message to server" << std::endl;
        }
        else
        {
            if (debug)
            std::cout << "Sent message to server: " << message << std::endl;
        }
    }

    void disconnect()
    {
        if (m_running)
        {
            m_running = false;
            m_thread.join();
            m_socket.disconnect();
            if (debug)
            std::cout << "Disconnected from server" << std::endl;
        }
    }

private:
    void receiveMessages()
    {
        while (m_running)
        {
            sf::Packet packet;
            if (m_socket.receive(packet) == sf::Socket::Done)
            {
                std::string message;
                packet >> message;
                if (debug)
                std::cout << "Received message from server: " << message << std::endl;
                PacketMove = message;
            }
        }
    }

private:
    sf::TcpSocket m_socket;
    sf::IpAddress m_serverAddress;
    unsigned short m_serverPort;
    bool m_running;
    std::thread m_thread;
};

