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



#include "../include/sockpp/SocketStream.h"

namespace sockpp
{

    template<> SocketStream& SocketStream::operator<< <int const>(int const& buf) {
        auto sent = send(socketFD, &buf, sizeof(int), 0);
        std::cout << sent << std::endl;
        return *this;
    }

    template<> SocketStream& SocketStream::operator>> <int>(int & buf) {
        auto received = recv(socketFD, &buf, 4, 0);
        std::cout << received << std::endl;
        return *this;
    }
    
    
    template <> SocketStream& SocketStream::operator>> <std::vector<char>>(std::vector<char>& buf) {
        const unsigned int bufSize = buf.size();
        auto received = recv(socketFD, buf.data(), bufSize, 0);
        std::cout << received << std::endl;
        return *this;
    }

    template <>  SocketStream& SocketStream::operator<< <std::vector<char>>(std::vector<char>& buf) {
        const unsigned int bufSize = buf.size();
        auto sent = send(socketFD, buf.data(), bufSize, 0);
        std::cout << sent << std::endl;
        return *this;
    }
}