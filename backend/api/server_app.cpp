#include "../include/server_app.hpp"
#include "crow/app.h"
#include "../include/router.hpp"
#include "../include/defines.hpp"

int runServerApp(int argc, char *argv[])
{
    crow::SimpleApp app;

    // Configura suas rotas da API
    CROW_ROUTE(app, "/")([]()
                         { return "Servidor Crow funcionando!"; });

    define_routes(app);

    cout << "Servidor escutando na porta 18080..." << endl;
    app.port(18080).multithreaded().run();

    return 0;
}