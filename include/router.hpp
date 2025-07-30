#pragma once

#include "crow/app.h"
#include "../include/defines.hpp"

/// Define as rotas da aplicação web Crow.
void define_routes(crow::SimpleApp &app);

bool ends_with(const string &str, const string &suffix);
