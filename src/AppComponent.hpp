#ifndef AppComponent_hpp
#define AppComponent_hpp

#include "oatpp/Types.hpp"
#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include <cstdlib>
#include <string>

class AppComponent {
    public:

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
        const char* hostEnv = std::getenv("SERVER_HOST");
        oatpp::String host = hostEnv ? static_cast<oatpp::String>(hostEnv) : "0.0.0.0";
        const char* portEnv = std::getenv("SERVER_PORT");
        oatpp::UInt16 port = portEnv ? static_cast<oatpp::UInt16>(std::stoi(portEnv)) : static_cast<oatpp::UInt16>(8000);
        
        return oatpp::network::tcp::server::ConnectionProvider::createShared({host, port, oatpp::network::Address::IP_4});
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMapper)([] {
        auto json = std::make_shared<oatpp::json::ObjectMapper>();
        json->serializerConfig().json.useBeautifier = true;

        auto mappers = std::make_shared<oatpp::web::mime::ContentMappers>();
        mappers->putMapper(json);

        return mappers; 
    }());
};
#endif