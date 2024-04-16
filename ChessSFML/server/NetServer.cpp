#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <thread>

const unsigned short PORT = 25565;

void handleClient(sf::TcpSocket* client, std::vector<sf::TcpSocket*>& clients) {
    while (true) {
        sf::Packet packet;
        if (client->receive(packet) == sf::Socket::Done) {
            std::string message;
            packet >> message;
            std::cout << "Received message from client " << client->getRemoteAddress() << ": " << message << std::endl;

            // Пересылка сообщения другим клиентам
            for (sf::TcpSocket* otherClient : clients) {
                if (otherClient != client) {
                    sf::Packet copyPacket = packet;
                    if (otherClient->send(copyPacket) != sf::Socket::Done) {
                        std::cerr << "Failed to relay message to a client" << std::endl;
                    }
                }
            }
        }
        else {
            std::cout << "Client disconnected: " << client->getRemoteAddress() << std::endl;
            delete client;
            clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
            return;
        }
    }
}

int main() {
    sf::TcpListener listener;
    if (listener.listen(PORT) != sf::Socket::Done) {
        std::cerr << "Failed to bind port " << PORT << std::endl;
        return 1;
    }

    std::cout << "Server is listening to port " << PORT << ", waiting for connections..." << std::endl;

    std::vector<sf::TcpSocket*> clients;

    // Поток для прослушивания новых подключений
    std::thread acceptThread([&]() {
        while (true) {
            sf::TcpSocket* client = new sf::TcpSocket;
            if (listener.accept(*client) == sf::Socket::Done) {
                clients.push_back(client);
                std::cout << "New client connected: " << client->getRemoteAddress() << std::endl;

                // Создаем новый поток для обработки сообщений от клиента
                std::thread clientThread(handleClient, client, std::ref(clients));
                clientThread.detach(); // Отделяем поток, чтобы он мог работать независимо
            }
            else {
                delete client;
                std::cout << "Connection failed" << std::endl;
            }
        }
        });
    acceptThread.join();

    return 0;
}
