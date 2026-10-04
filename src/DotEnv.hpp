#ifndef DOTENV_HPP
#define DOTENV_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

// Trims leading and trailing whitespace from a string
inline std::string trimEnvStr(const std::string& str) {
    const auto first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    const auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Parses a .env file and sets the variables into the system environment
inline void loadDotEnv(const std::string& filepath = ".env") {
    std::ifstream file(filepath);
    // Fallback: If running inside build/, try looking one directory up
    if (!file.is_open()) {
        file.open("../" + filepath);
    }
    
    if (!file.is_open()) {
        return; // If .env doesn't exist, silently failover to default system env
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string trimmed = trimEnvStr(line);

        // Ignore empty lines and comment lines starting with '#'
        if (trimmed.empty() || trimmed[0] == '#') {
            continue;
        }

        auto pos = trimmed.find('=');
        if (pos != std::string::npos) {
            std::string key = trimEnvStr(trimmed.substr(0, pos));
            std::string value = trimEnvStr(trimmed.substr(pos + 1));

            // Strip surrounding quotes if present (e.g., KEY="value")
            if (value.length() >= 2 && 
            ((value.front() == '"' && value.back() == '"') || 
                (value.front() == '\'' && value.back() == '\''))) {
                value = value.substr(1, value.length() - 2);
            }

            // Inject into system environment variables (Cross-platform)
#ifdef _WIN32
            _putenv_s(key.c_str(), value.c_str());
#else
            setenv(key.c_str(), value.c_str(), 1); // 1 = overwrite if existing
#endif
        }
    }
}

#endif