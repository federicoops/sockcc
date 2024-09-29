// /*
// emptyNN
// Copyright (C) 2024 Federico Rossi
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


#include "sockpp/ServerSocket.h"

namespace sockpp {

    ServerSocket::ServerSocket(std::string address,std::string port) {
        struct addrinfo hints, *serverInfo, *addrPtr;
        std::memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        auto rv = getaddrinfo(nullptr, port.c_str(), &hints, &serverInfo);

        for(addrPtr = serverInfo; addrPtr!= nullptr; addrPtr = addrPtr->ai_next) {
            socketFD = socket(addrPtr->ai_family, addrPtr->ai_socktype, addrPtr->ai_protocol);
            if(socketFD == -1)
                continue;
            int opt = 1;
            auto res = setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
            if(res == -1)
                throw std::runtime_error("Could not create server socket");
            res = bind(socketFD, addrPtr->ai_addr, addrPtr->ai_addrlen);
            if(res == -1)
                continue;
            
            // ServerSocket now binded
            break;
        }

        freeaddrinfo(serverInfo);
        if(addrPtr == nullptr)
            throw std::runtime_error("Could not bind server socket");

        // Now listen
        auto res = listen(socketFD, backlog);
        if(res == -1) 
            throw std::runtime_error("Could not listen on server socket");
    }


    void ServerSocket::serverLoop(std::function<bool(SocketStream&)> acceptCB) {
        bool condition = false;
        struct sockaddr_storage peerAddress;
        socklen_t addressSocketLength;
        while(!condition) {
            auto fd = accept(socketFD, (struct sockaddr*)&peerAddress, &addressSocketLength);
            SocketStream  ss{fd};
            condition = acceptCB(ss);
        }
    }


} // sockpp