#include <MainGenerator.hpp>

int main(){
    codegen::MainGenerator::GenerateMain("configs/server_config.json", "main.cpp");
    return 0;
}