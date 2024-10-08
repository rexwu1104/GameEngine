#include <filesystem>
#include <iostream>
#include <game_engine/Backend.h>

Backend::Backend() {
    std::cout << std::filesystem::current_path() << std::endl;
    LoadFirstLibrary(dlls, handle);
    if (!handle) {
        // std::cerr << "Failed to load backend library at " << path << std::endl;
        DWORD errorMessageID = GetLastError();
        if (errorMessageID != 0) {
            LPSTR messageBuffer = nullptr;
            size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                         NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
            std::string message(messageBuffer, size);
            std::cerr << "Error loading DLL: " << message << std::endl;
            LocalFree(messageBuffer);
        }
        exit(1);
    }

    //
    // std::cout << "Successfully loaded backend library at " << path << std::endl;
    // if (!free()) {
    //     std::cerr << "Failed to free backend library" << std::endl;
    // }
}

HANDLE Backend::load(const char* path) const {
    return LOAD_LIB(path);
}

SYMBOL Backend::symbol(const char *name) const {
    return GET_SYMBOL(handle, name);
}

CODE Backend::free() const {
    return UNLOAD_LIB(handle);
}