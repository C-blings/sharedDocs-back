#include <web/helpers/HandlerMatcher.hpp>
#include <web/request_handlers/RequestHandlersContainerBase.hpp>
#include <web/tcp_server/TCPServer.hpp>
#include <web/request_handlers/BasicContainer.hpp>
#include <web/request_handlers/CORSContainers.hpp>
#include <logging/Logger.hpp>

<<<<<<< HEAD
int main() {
=======
#include "src/web/request_handlers/BasicContainer.hpp"
#include "src/web/request_handlers/CORSContainers.hpp"

#include "src/database/Database.hpp"
#include "src/database/postgresql/PGConnection.hpp"
#include "src/database/postgresql/PGController.hpp"

int main(){
>>>>>>> 2a1300154042054268781c11227867e0572b8b37
    std::vector<web_layout::RequestHandlersContainerBase> requests_containers = {
web_layout::CORSContainer(),web_layout::BasicContainer(),
   };

    database::Database<database::postgresql::PGConnection, database::postgresql::PGController, database::postgresql::Store> db("shareDocs");
    db.HandleQuery({}, {});

    web_layout::Container full_container;

    for (const web_layout::RequestHandlersContainerBase& container_base : requests_containers){
        full_container.AddValues(container_base.GetContainer());
    }

    web_layout::RouterBase router(full_container);
    Logger(Debug).Print("Server restart");
    web_layout::TCPServer server("127.0.0.1", 80);
    std::shared_ptr<web_layout::WebServer> handler = std::make_shared<web_layout::WebServer>(router);

    server.StartListen(handler);
    return 0; 
}