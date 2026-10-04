#include "./AppComponent.hpp"
#include "./controller/AppController.hpp"

#include "DotEnv.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

void run() {
    AppComponent components;

    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    router->addController(std::make_shared<AppController>());

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider);

    oatpp::network::Server server(serverConnectionProvider, connectionHandler);
    
    OATPP_LOGi("simple-api", "Server running on port {}", serverConnectionProvider->getProperty("port").toString());

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