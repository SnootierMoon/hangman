#include "main.hpp"

struct Client
{
    string name;
    TCPsocket socket;
    int score;
};

static string input;
static vector<Client> clients;
static IPaddress addr;
static TCPsocket socket;
static SDLNet_SocketSet socket_set;

static void server_phase1();
static void server_phase2();

/** Run the server
 *
 * @returns status code to be returned from main
 */
int server_run()
{
    sdl_init();

    server_phase1();
    server_phase2();

    return 0;
}

/** Server phase 1
 *
 * This functions creates the server socket, establishes connections with
 * client sockets, and then informs them when a game is ready.
 */
void server_phase1()
{
    // Create an IPaddress that allows all incoming connections on the port
    SDLNet_ResolveHost(&addr, NULL, PORT);

    // Create a socket bound to the server's IPaddress
    socket = SDLNet_TCP_Open(&addr);

    // Create a socket set to poll sockets for new data
    socket_set = SDLNet_AllocSocketSet(8);

    // Continuously check for new connections, and handle them as they come
    while (clients.size() < 8)
    {
        // Ask host if they want to continue to the game
        cout << (clients.size()) << "/8 players connected." << endl;
        input = get_input("Enter 'c' to continue, or anything else to poll connections");
        cout << endl;

        if (input == "c" || input == "C")
        {
            break;
        }

        Client client;

        // Handle a new connection
        while ((clients.size() < 8) && (client.socket = SDLNet_TCP_Accept(socket)))
        {
            // First message received is the player's username
            client.name = sdl_net_read(client.socket);

            cout << "Got connection from \"" << client.name << "\"." << endl;
            input = get_input("Enter 'y' to accept, or anything else to reject");

            if (input == "y" || input == "Y")
            {
                // Respond with "Accept" if the host accepts them
                sdl_net_write(client.socket, "Accept");

                // Tell the new player about the current players
                for (int i = 0; i < clients.size(); i++)
                {
                    sdl_net_write(client.socket, "Conn " + clients[i].name);
                }

                // Add the new player to the list
                clients.push_back(client);

                // Inform all clients about the new connection.
                for (int i = 0; i < clients.size(); i++)
                {
                    sdl_net_write(clients[i].socket, "Conn " + client.name);
                }

                // Add them to the socket set
                SDLNet_TCP_AddSocket(socket_set, client.socket);
                cout << "Accepted connection." << endl;
            }
            else
            {
                // Respond with "Reject" if the host denies them
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

/** Server phase 2
 *
 * This function runs the game. It simply relays the messages between clients.
 */
void server_phase2()
{
    bool done = false;
    while (!done) 
    {
        SDL_Event event;
        // Check if the server is closed
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
        }

        // Iterate through clients
        SDLNet_CheckSockets(socket_set, 0);
        for (int i = 0; i < clients.size(); i++)
        {
            // Check if the client has new data
            if (SDLNet_SocketReady(clients[i].socket)) 
            {
                // Read the data
                string msg = sdl_net_read(clients[i].socket);

                // If the client disconnected ...
                if (msg == "") 
                {
                    // Close the connection with the client
                    SDLNet_TCP_DelSocket(socket_set, clients[i].socket);
                    SDLNet_TCP_Close(clients[i].socket);
                    clients.erase(clients.begin() + i);
                    i--;
                } 
                else
                {
                    // Otherwise, broadcast the message to all clients
                    for (int j = 0; j < clients.size(); j++) 
                    {
                        sdl_net_write(clients[j].socket, msg);
                    }
                }
            }
        }
    }
}
