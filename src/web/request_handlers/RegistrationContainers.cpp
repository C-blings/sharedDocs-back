#include "RegistrationContainers.hpp"

#include <formats/json/Json.hpp>
#include <iostream>

namespace web_layout{

    HttpResponse RegistrationContainers::AddUser(const HttpRequest& request){
        std::string body = request.GetBody();
        formats::json::JsonValue json(body);
        std::unordered_map<std::string, std::string> headers = {
                {"Access-Control-Allow-Origin", "*"}
        };
        std::cout << "JSON: " << json.GetValue<std::string>("name") << '\n';
        return HttpResponse(200, "OK", headers);
    }

    RegistrationContainers::RegistrationContainers() {
        Container container;
        container.AddValue({HandlerMatcher(Method::POST, std::regex("/add-user")), AddUser});
        SetContainer(container);
    }
}
