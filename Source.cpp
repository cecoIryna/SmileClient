#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client, (sockaddr*)&server, sizeof(server));

    int x = 10, y = 10;
    char key;

    cout << "Use arrow keys to move smiley. Press ESC to exit." << endl;

    while (true) {
        key = _getch();
        if (key == 27) break;

        if (key == -32 || key == 0) {
            key = _getch();
            switch (key) {
            case 72: y = max(0, y - 1); break;
            case 80: y++; break;            
            case 75: x = max(0, x - 1); break;
            case 77: x++; break;              
            }

            int coords[2] = { x, y };
            send(client, (char*)coords, sizeof(coords), 0);
        }
    }

    closesocket(client);
    WSACleanup();
    return 0;
}
