#include "./AppComponent.hpp"
#include "./controller/AppController.cpp"

#include "DotEnv.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

void run() {
    AppComponent components;

    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    router->addController(std::make_shared<AppController>());

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionProvider>, connectionProvider);

    oatpp::network::Server server(connectionProvider, connectionHandler);
    
    OATPP_LOGi("simple-api", "Server running on port {}", connectionProvider->getProperty("port").toString());

    server.run();
}

int main(int argc, const char* argv[]) {
    loadDotEnv(".env");

    oatpp::Environment::init();

    run();

    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::Environment::getObjectsCreated() << "\n\n";

    oatpp::Environment::destroy();

    return 0;
}