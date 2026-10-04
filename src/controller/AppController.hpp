#ifndef AppController_hpp
#define AppController_hpp

#include "../dto/MessageDTO.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class AppController : public oatpp::web::server::api::ApiController {
    public:
        AppController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers)) : oatpp::web::server::api::ApiController(apiContentMappers)
        {}
    
    public:
        ENDPOINT("GET", "/", root) {
            auto messageDto = MessageDto::createShared();

            messageDto->statusCode = 200;
            messageDto->message = "Hello";

            return createDtoResponse(Status::CODE_200, messageDto);
        }
};

#include OATPP_CODEGEN_END(ApiController)

#endif