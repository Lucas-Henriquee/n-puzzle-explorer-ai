#ifdef MODE_SERVER
    #include "../include/server_app.hpp"
#endif

#ifdef MODE_CLI
    #include "../include/cli_app.hpp"
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    #ifdef MODE_SERVER
        cout << "Iniciando o servidor...\n";
                return runServerApp();

    #elif MODE_CLI
        cout << "Iniciando a aplicação CLI...\n";
                return runCliApp(argc, argv);
    #else
        return 1;
    #endif
}