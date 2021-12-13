#include "main.hpp"

int main(int argc, char** argv)
{
    // The following code checks if there is exactly 1 argument (not including
    // the program name).  Then, it runs `server_run` if the argument is
    // "server", and `client_run` if the argument is "client". Otherwise, it
    // prints the valid usage.

    if (argc != 2)
    {
        return usage(argv[0]);
    } 
    else
    {
        string opt = argv[1];

        if (opt == "server")
        {
            return server_run();
        }
        else if (opt == "client")
        {
            return client_run();
        }
        else
        {
            cout << "Invalid option \"" << opt << "\"" << endl;
            return usage(argv[0]);
        }
    }

}

/** Print valid usage information
 *
 * @param argv0 the value of argv[0], the name of the executable
 *
 * @returns status code to be returned from main
 */
int usage(char* argv0) 
{
    cout << "Usage: \"" << argv0 << " [server|client]\"" << endl;
    return 1;
}

/** Get a line of input
 *
 * @param prompt a same-line prompt to give the user
 *
 * @return user-input response
 */
string get_input(string prompt)
{
    string msg;

    cout << prompt << " > ";

    getline(cin, msg);

    // Exit the program if input fails (allows Ctrl-D to force close)
    if (cin.fail())
    {
        cout << endl;
        exit(0);
    }

    return msg;
}

