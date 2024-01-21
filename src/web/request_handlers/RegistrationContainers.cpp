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

        std::vector<database::postgresql::Store> parameters = {
                request.GetParameters().at("userName")
        };

        bool result;

        try{
            auto row_result = database_->HandleQuery("SELECT * FROM users WHERE login=$1", parameters);
            result = !row_result.empty();
        }catch (std::exception& e){
            return HttpResponse(400, "Error", headers);
        }

        formats::json::JsonValue body;
        body.AddValue("result", result ? "true" : "false");

        return HttpResponse(200, "OK", headers, body.AsString());
    }

    RegistrationContainers::RegistrationContainers() {
        Container container;
        container.AddValue({HandlerMatcher(Method::POST, "\\/add-user"), AddUser});
        container.AddValue({HandlerMatcher(Method::GET, "\\/check-if-user-exists\\?userName=.*"), CheckIfUserExists});
        SetContainer(container);
    }
}
