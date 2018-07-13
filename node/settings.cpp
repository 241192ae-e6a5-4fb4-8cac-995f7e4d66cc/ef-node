#include <iostream>

#include <boost/program_options.hpp>


#include "settings.hpp"


namespace po = boost::program_options;


TNodeSettings::TNodeSettings(int argc, char **argv) {
    po::options_description desc("Command line options");

    desc.add_options()
        ("help,h",
         "show this help")

        ("port,p",
         po::value<uint16_t>(&Port)->default_value(8090),
         "port to listen on")

        ("private-key",
         po::value<std::string>(&MyPrivateKeyPath),
         "private key to sign messages")

        ("public-key",
         po::value<std::string>(&OtherPublicKeyPath),
         "public key to verify messages")

        ("remote-addr",
         po::value<std::string>(&RemoteAddress),
         "remote node address")

        ("remote-port",
         po::value<uint16_t>(&RemotePort),
         "remote node port")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        std::exit(0);
    }
}
