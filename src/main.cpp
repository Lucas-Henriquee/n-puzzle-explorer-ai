#ifdef MODE_CLI
    #include "../include/cli_app.hpp"
#endif

#ifdef MODE_SERVER
    #include "../include/server_app.hpp"
#endif

int main(int argc, char *argv[])
{
    #ifdef MODE_CLI
        return runCliApp(argc, argv);
    #elif MODE_SERVER
        return runServerApp(argc, argv);
    #else
        return 1;
    #endif
}