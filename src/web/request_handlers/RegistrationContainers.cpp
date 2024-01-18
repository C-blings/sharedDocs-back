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
            database_->HandleQuery("INSERT INTO users (nickname, email, password) VALUES ($1, $2, $3)", parameters);
        }catch (std::exception& e){
            return HttpResponse(400, "Error", headers);
        }

        return HttpResponse(200, "OK", headers);
    }

    RegistrationContainers::RegistrationContainers() {
        Container container;
        container.AddValue({HandlerMatcher(Method::POST, std::regex("/add-user")), AddUser});
        SetContainer(container);
    }
}
