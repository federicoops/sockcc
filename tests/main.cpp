// /*
// sockpp
// Copyright (C) 2025 Federico Rossi
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// *


#include <iostream>
#include <chrono>
#include <sockpp/sockpp.h>
#include <sockpp/SocketStream.h>
#include <sockpp/ClientSocket.h>
#include <sockpp/ServerSocket.h>

#include <thread>

void serverThreadBody() {
    sockpp::ServerSocket ss{"127.0.0.1", "4242"};
    int a = 2;
    ss.serverLoop([a](sockpp::SocketStream& ss) -> bool {
        auto buf = std::vector<char>(3);
        ss << buf;
        ss << a; 
        return true;
    });
}

auto main() -> int{
    std::jthread jt(serverThreadBody);
    using namespace std::chrono_literals;

    int retries = 10;
    int a;

    // Just wait for the server to spin up
    std::this_thread::sleep_for(1000ms);

    sockpp::ClientSocket s{"127.0.0.1", "4242"};
    std::vector<char> buf(3);
    *(s.stream()) >> buf;
    *(s.stream()) >> a;

    return 0;
}
