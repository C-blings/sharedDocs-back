#include "DatabaseFabric.hpp"

namespace database{
    std::shared_ptr<PGDatabase> DatabaseFabric::database_ = std::make_shared<PGDatabase>("shareDocs");
}