CXX := g++
CXXFLAGS := -std=c++17

all: bin/server_start bin/client_start

SERVER_I := -Iinclude/Server
CLIENT_I := -Iinclude/Client


SERVER_SRCS := src/Server/Server.cpp src/main/server_start.cpp
CLIENT_SRCS := src/Client/Client.cpp src/main/client_start.cpp

bin/server_start: $(SERVER_SRCS)
	$(CXX) $(CXXFLAGS) $(SERVER_SRCS) -o bin/server_start $(SERVER_I)
	ln -srf bin/server_start server_start

bin/client_start: $(CLIENT_SRCS)
	$(CXX) $(CXXFLAGS) $(CLIENT_SRCS) -o bin/client_start $(CLIENT_I)
	ln -srf bin/client_start client_start
	
clean:
	rm -f client_start server_start bin/*