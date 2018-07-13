#include "application.hpp"

using namespace NEvenFound::NNetwork;

int main(int argc, char **argv) {
    std::shared_ptr<TNodeApplication> App = std::make_shared<TNodeApplication>(argc, argv);
    return App->Run();
}
