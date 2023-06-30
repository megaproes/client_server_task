# Readme File for Git Repository

This repository contains a simple client-server application written in C++. The application allows clients to connect to a server and exchange messages.

## Project Structure

The project directory structure is as follows:

```
.
├── bin
├── include
│   ├── Client
│   │   └── Client.h
│   └── Server
│       └── Server.h
├── Makefile
└── src
    ├── Client
    │   └── Client.cpp
    ├── main
    │   ├── client_start.cpp
    │   └── server_start.cpp
    └── Server
        └── Server.cpp
```

- The `bin` directory will contain the compiled binary files.
- The `include` directory contains the header files for the client and server classes.
- The `src` directory contains the source code files.
- The `Makefile` is used to compile the source code and generate the executables.

## Compilation and Execution

To compile the source code and generate the executables, run the following command:

```
make all
```

This command will compile the client and server source files and generate the `client_start` and `server_start` executables in the `bin` directory.

To run the server, execute the following command:

```
./bin/server_start
```

To run the client, execute the following command:

```
./bin/client_start <SERVER_IP> <PORT>
```

Replace `<SERVER_IP>` with the IP address of the server and `<PORT>` with the port number on which the server is listening.

## Usage

Once the server and client are running, you can interact with the application by entering messages in the client terminal. The client will send the messages to the server, and the server will process and respond accordingly. The available commands are:

- `disconnect`: Disconnects the client from the server.

## Signal Handling

The server and client applications handle the `SIGINT` signal (generated by pressing `Ctrl+C`) to gracefully disconnect from the server. When the `SIGINT` signal is received, the client application will send a `disconnect` message to the server and terminate.

## Cleaning Up

To clean up the generated files, run the following command:

```
make clean
```

This command will remove the `bin` directory and the `server_start` and `client_start` symlinks.

## Dependencies

The application has the following dependencies:

- `arpa/inet.h`: Header file for networking operations.
- `iostream`: Input/output stream library.
- `fstream`: File stream library.
- `unistd.h`: Header file for POSIX API.
- `cstring`: C string manipulation functions.
- `thread`: Header file for multithreading support.
- `mutex`: Header file for mutual exclusion synchronization primitives.
- `string`: String class and operations.
- `stdexcept`: Standard exception classes.

Ensure that the required dependencies are available in your C++ development environment.

## Contributing

Contributions to this project are welcome. If you encounter any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use and modify the code according to the terms of the license.