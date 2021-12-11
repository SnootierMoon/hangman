#include "main.hpp"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        return usage(argv[0]);
    } else {
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

int usage(char* argv0) 
{
    cout << "Usage: \"" << argv0 << " [server|client]\"" << endl;
    return 1;
}

string get_input(string prompt)
{
    string msg;

    cout << prompt << " > ";

    getline(cin, msg);

    if (cin.fail())
    {
        cout << endl;
        exit(0);
    }

    return msg;
}

