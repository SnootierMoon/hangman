#include "main.hpp"

static void client_phase1();

static IPaddress addr;
static TCPsocket socket;

int client_run()
{
    sdl_init();

    client_phase1();

    return 0;
}

void client_phase1()
{
    string username = get_input("Enter your username");
    stringstream(username) >> username;
    cout << "Username: \"" << username << "\"" << endl;

    string host_addr = get_input("Enter the server's address");
    bool started = false;


    if (SDLNet_ResolveHost(&addr, host_addr.c_str(), PORT) == -1)
    {
        cout << endl;
        cout << "Failed to resolve address." << endl;
        string host_addr = get_input("Enter the server's address");
    }

    socket = SDLNet_TCP_Open(&addr);

    if (!socket)
    {
        cout << "Failed to connect to server." << endl;
        exit(1);
    }

    sdl_net_write(socket, username);

    cout << "Waiting for response from server." << endl;

    string response = sdl_net_read(socket);

    if (response == "Reject")
    {
        cout << "You got rejected by the server." << endl;
        exit(1);
    }
    else if (response != "Accept")
    {
        cout << "Invalid packet from server." << endl;
        exit(1);
    }

    cout << endl;
    cout << "You got accepted by the server." << endl;

    while (!started)
    {
        string word;
        stringstream msg(sdl_net_read(socket));
        msg >> word;
        if (word == "Conn")
        {
            string username;
            msg >> username;

            cout << "New player: \"" << username << "\"." << endl;
        }
        else if (word == "Start")
        {
            started = true;
        }
    }
}
