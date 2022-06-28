#include "ErrorHandler.h"
#include "Scanner.h"

void run(std::string&& buffer)
{
    Scanner scanner(std::move(buffer));
    std::vector<Token> tokens = scanner.ScanTokens();
    for (auto token : tokens) {
        std::cout << token << std::endl;
    }
}

static void runFile(const char* filename)
{
    if (std::ifstream is { filename, std::ios::binary }) {
        is.seekg(0, is.end);
        const size_t length = is.tellg();
        is.seekg(0, is.beg);

        char* buffer = new char[length + 1];

        is.read(buffer, length);

        const size_t pos = is.tellg();
        buffer[pos] = '\0';

        is.close();
        run(buffer);

        if (s_hadError)
            exit(65);
    }
}

static void runPrompt()
{
    while (true) {
        std::cout << "> ";

        std::string line;
        std::getline(std::cin, line);

        if (line.empty())
            break;

        run(line.c_str());
        s_hadError = false;
    }
}

int main(int argc, char* argv[])
{
    if (argc > 2) {
        std::cout << "Usage: jali [script]" << std::endl;
        system("pause");
        exit(64);
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }

    system("pause");
    return 0;
}
