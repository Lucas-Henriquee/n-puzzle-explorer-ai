#include "../include/defines.hpp"
#include "../include/server_app.hpp"
#include "crow/mustache.h"
#include "crow/app.h"
#include "../include/router.hpp"

bool endsWith(const string &str, const string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int runServerApp()
{
    crow::SimpleApp app;

    crow::mustache::set_base("frontend");

    // Página principal (index.html)
    CROW_ROUTE(app, "/")([]
                         {
        ifstream file("frontend/index.html");
        if (!file) return crow::response(404, "Arquivo index.html não encontrado.");
        stringstream buffer;
        buffer << file.rdbuf();
        return crow::response{buffer.str()}; });

    // Servir arquivos estáticos como JS e CSS
    CROW_ROUTE(app, "/<string>/<string>")
    ([](const string &dir, const string &file)
     {
        string path = "frontend/" + dir + "/" + file;
        ifstream in(path, ios::binary);
        if (!in)
            return crow::response(404, "Arquivo não encontrado: " + path);
        
        ostringstream contents;
        contents << in.rdbuf();
        auto resp = crow::response(contents.str());

        // Define o Content-Type correto
        if (endsWith(path, ".js")) resp.set_header("Content-Type", "application/javascript");
        else if (endsWith(path, ".css")) resp.set_header("Content-Type", "text/css");
        else if (endsWith(path, ".html")) resp.set_header("Content-Type", "text/html");


        return resp; });

    // Rota da API
    define_routes(app);

    cout << "Servidor escutando na porta 18080...\n";
    app.port(18080).multithreaded().run();

    return 0;
}
