#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

enum FileSize {
    SMALL = 512 * 1024 * 1024,   // 512 MB
    MEDIUM = 1 * 1024 * 1024 * 1024,  // 1 GB
    LARGE = 2LL * 1024 * 1024 * 1024   // 2 GB
};

FileSize getFileSize(const std::string& size) {
    if (size == "SMALL") return SMALL;
    if (size == "MEDIUM") return MEDIUM;
    if (size == "LARGE") return LARGE;
    throw std::invalid_argument("Invalido.");
}

void generateFile(const std::string& filePath, FileSize size) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error." << std::endl;
        return;
    }

    std::srand(static_cast<unsigned>(std::time(0)));

    size_t numIntegers = size / sizeof(int);
    for (size_t i = 0; i < numIntegers; ++i) {
        int randomNumber = std::rand();
        file.write(reinterpret_cast<const char*>(&randomNumber), sizeof(randomNumber));
    }

    file.close();
}

int main(int argc, char* argv[]) {
    std::cout << "Numbero de argumentos: " << argc << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument[" << i << "]: " << argv[i] << std::endl;
    }

    if (argc < 5) {
        std::cerr << "Uso: " << argv[0] << " --generate --size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        return 1;
    }

    std::string command(argv[1]);

    if (command == "--generate") {
        if (argc != 5) {
            std::cerr << "Uso: " << argv[0] << " --generate --size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
            return 1;
        }

        std::string sizeArg(argv[3]);
        std::string outputPath(argv[4]);

        try {
            FileSize fileSize = getFileSize(sizeArg);
            generateFile(outputPath, fileSize);
            std::cout << "Archivo generado." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Error: " << command << std::endl;
        return 1;
    }

    return 0;
}
