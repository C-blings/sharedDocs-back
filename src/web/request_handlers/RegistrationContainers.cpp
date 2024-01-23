#define FMT_HEADER_ONLY

#include "RegistrationContainers.hpp"
#include <formats/json/Json.hpp>

namespace web_layout{
    std::shared_ptr<database::PGDatabase>
            RegistrationContainers::database_ = database::DatabaseFabric::GetDatabase();

    HttpResponse RegistrationContainers::AddUser(const HttpRequest& request){
        std::unordered_map<std::string, std::string> headers = {
                {"Access-Control-Allow-Origin", "*"}
        };

        std::string body = request.GetBody();
        formats::json::JsonValue json(body);

        std::vector<database::postgresql::Store> parameters = {
                json.GetValue<std::string>("login"),
                json.GetValue<std::string>("email"),
                json.GetValue<std::string>("password")
        };

        try{
            database_->HandleQuery("INSERT INTO users (login, email, password) VALUES ($1, $2, $3)", parameters);
        }catch (std::exception& e){
            return HttpResponse(400, "Error", headers);
        }

        return HttpResponse(200, "OK", headers);
    }

    HttpResponse RegistrationContainers::CheckIfUserExists(const web_layout::HttpRequest &request) {
        std::unordered_map<std::string, std::string> headers = {
                {"Access-Control-Allow-Origin", "*"}
        };
        auto parameters = request.GetParameters();
        std::string login = parameters.at("login");
        std::string email =  parameters.at("email");

        bool result;

        try{
            auto row_result =
                    database_->HandleQuery("SELECT * FROM users WHERE login=$1 OR email=$2", {login, email});
            result = !row_result.empty();
        }catch (std::exception& e){
            return HttpResponse(400, "Error", headers);
        }

        formats::json::JsonValue response_body;
        response_body.AddValue("result", result);

        return HttpResponse(200, "OK", headers, response_body.AsString());
    }

    RegistrationContainers::RegistrationContainers() {
        Container container;
        container.AddValue({HandlerMatcher(Method::POST, "\\/add-user"), AddUser});
        container.AddValue({HandlerMatcher(Method::GET, R"(\/check-if-user-exists\?login=.*\;email=.*)"), CheckIfUserExists});
        SetContainer(container);
    }
}
