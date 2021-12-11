#include "main.hpp"

struct Client
{
    string name;
    TCPsocket socket;
};

static string input;
static vector<Client> clients;
static IPaddress addr;
static TCPsocket socket;
static SDLNet_SocketSet socket_set;

static void server_phase1();

int server_run()
{
    sdl_init();

    server_phase1();

    return 0;
}

void server_phase1()
{
    SDLNet_ResolveHost(&addr, NULL, PORT);

    socket = SDLNet_TCP_Open(&addr);

    socket_set = SDLNet_AllocSocketSet(9);
    SDLNet_TCP_AddSocket(socket_set, socket);

    while (clients.size() < 8)
    {
        cout << (clients.size()) << "/8 players connected." << endl;
        input = get_input("Enter 'c' to continue, or anything else to poll connections");
        cout << endl;

        if (input == "c" || input == "C")
        {
            if (clients.size() >= 2)
            {
                break;
            }
            else
            {
                cout << "You can't continue until more people join!" << endl;
            }
        }

        Client client;

        while ((clients.size() < 8) && (client.socket = SDLNet_TCP_Accept(socket)))
        {
            client.name = sdl_net_read(client.socket);

            cout << "Got connection from \"" << client.name << "\"." << endl;
            input = get_input("Enter 'y' to accept, or anything else to reject");

            if (input == "y" || input == "Y")
            {
                sdl_net_write(client.socket, "Accept");
                clients.push_back(client);

                for (int i = 0; i < clients.size(); i++)
                {
                    sdl_net_write(clients[i].socket, "Conn " + client.name);
                }

                SDLNet_TCP_AddSocket(socket_set, client.socket);
                cout << "Accepted connection." << endl;
            }
            else
            {
                sdl_net_write(client.socket, "Reject");

                SDLNet_TCP_Close(client.socket);
                cout << "Rejected connection." << endl;
            }
        }
    }

    for (int i = 0; i < clients.size(); i++)
    {
        sdl_net_write(clients[i].socket, "Start");
    }
}
