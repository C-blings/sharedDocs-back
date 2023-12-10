#pragma once

#include <vector>
#include <string>

namespace database{
    template<typename Connection, typename Store>
    class DatabaseController {
    public:
<<<<<<< HEAD
        virtual std::vector<std::vector<Store>> HandleQuery(Connection& connection,
                                       const std::string& query, const std::vector<Store>& parameters) = 0;
    };
}
=======
        virtual std::vector<Store> HandleQuery(Connection& connection,
                                       const std::string& query, const std::vector<Store>& parameters) = 0;
    };
}
>>>>>>> 2a1300154042054268781c11227867e0572b8b37
