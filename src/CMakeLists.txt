add_library(sockpp SHARED ClientSocket.cpp ServerSocket.cpp SocketStream.cpp)
target_include_directories(sockpp PUBLIC ../include)