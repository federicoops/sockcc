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



#include "../include/sockpp/ClientSocket.h"

namespace sockpp
{
    ClientSocket::ClientSocket(const std::string address,const std::string port)
    {
        // Prepare socket hints structure
        struct addrinfo hints, *serverInfo, *addrPtr;
        
        std::memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        int rv = getaddrinfo(address.c_str(), port.c_str(), &hints, &serverInfo);
        if(rv != 0)
            throw std::runtime_error("Could not connect to "+address+" "+port);

        for(addrPtr = serverInfo; addrPtr != nullptr; addrPtr = addrPtr->ai_next) {
            auto fd = socket(addrPtr->ai_family, addrPtr->ai_socktype, addrPtr->ai_protocol);
            if(fd == -1) continue;
            auto res = connect(fd, addrPtr->ai_addr, addrPtr->ai_addrlen);
            if(res == -1) continue;

            this->ss = new SocketStream{fd};
            // Connnection succeded, exiting
            break;
        }

        // Cleanup
        freeaddrinfo(serverInfo);

        // Reached end of list, no suitable addr found
        // Should throw
        if(addrPtr == nullptr)
            throw std::runtime_error("Could not connect to "+address+" "+port);
            return;

        // Invariant reached: client is in OK state
    }

}