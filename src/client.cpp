#include "main.hpp"

static void client_phase1();
static void client_phase2();

static IPaddress addr;
static TCPsocket socket;
static SDLNet_SocketSet socket_set;

/** Run the client
 *
 * @returns status code to be returned from main
 */
int client_run()
{
    sdl_init();

    client_phase1();
    client_phase2();

    return 0;
}

/** Client phase 1 
 *
 * This function polls the player for a username and server IP, and then
 * attempts to connect to that server.
 */
void client_phase1()
{
    // Ask player for username
    string username = get_input("Enter your username");

    // Ensure that the username is only one word
    stringstream username_stream;
    username_stream.str(username);
    username_stream >> username;

    cout << "Username: \"" << username << "\"" << endl;

    // Ask player for server IP
    string host_addr = get_input("Enter the server's address");
    bool started = false;
    if (SDLNet_ResolveHost(&addr, host_addr.c_str(), PORT) == -1)
    {
        cout << endl;
        cout << "Failed to resolve address." << endl;
        string host_addr = get_input("Enter the server's address");
    }

    // Attempt to connect to IP
    socket = SDLNet_TCP_Open(&addr);
    if (!socket)
    {
        cout << "Failed to connect to server." << endl;
        exit(1);
    }

    // Create a socket set for polling the socket
    socket_set = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(socket_set, socket);

    // The first message is the client's username
    sdl_net_write(socket, username);
    cout << "Waiting for response from server." << endl;

    // The server should respond with "Accept" or "Reject"
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

    // When the game starts, the server sends "Start"
    // When a new player joins, the server sends "Conn {username}"
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

/** Client phase 2
 *
 * This function sends locally drawn lines to the server, and draws lines
 * received from the server.
 */
void client_phase2() 
{
    bool done = false;
    int thickness = 20;

    sdl_init_window();

    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                SDL_MouseMotionEvent motion = event.motion;
                bool is_motion = motion.xrel || motion.yrel;
                bool left_mouse_down = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK;
                if (is_motion && left_mouse_down)
                {
                    stringstream stream;

                    stream << motion.x << " " << motion.y << " " 
                        << (motion.x - motion.xrel) << " " << (motion.y - motion.yrel) << " "
                        << thickness;

                    sdl_net_write(socket, stream.str());
                }
            }
            else if (event.type == SDL_MOUSEWHEEL)
            {
                thickness += event.wheel.y;
                thickness = std::min(std::max(thickness, 1), 30);
            }
        }

        if (SDLNet_CheckSockets(socket_set, 0) && SDLNet_SocketReady(socket))
        {
            int x1, y1, x2, y2, thick;

            stringstream stream;
            stream.str(sdl_net_read(socket));

            stream >> x1 >> y1 >> x2 >> y2 >> thick;

            thickLineRGBA(
                    renderer,
                    x1, y1,
                    x2, y2,
                    thick * 2,
                    0, 0, 0, 255
                    );
            filledCircleRGBA(
                    renderer,
                    x1, y1,
                    thick,
                    0, 0, 0, 255
                    );
            filledCircleRGBA(
                    renderer,
                    x2, y2,
                    thick,
                    0, 0, 0, 255
                    );
        }

        sdl_update();
    }
}


