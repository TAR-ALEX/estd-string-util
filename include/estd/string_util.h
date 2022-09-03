#pragma once

#include <string>

namespace estd {
    namespace string_util {
        static std::string replace_all(std::string str, const std::string& from, const std::string& to) {
            size_t start_pos = 0;
            while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
                str.replace(start_pos, from.length(), to);
                start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
            }
            return str;
        }
        static std::string indent(std::string input, std::string indentation) {
            std::string output = "";
            for (size_t i = 0; i < input.length(); i++) {
                if (i == 0) { output += indentation; }
                output += input[i];
                if (input[i] == '\n' && i < input.length() - 1) { output += indentation; }
            }
            return output;
        }
    } // namespace string_util
} // namespace estd
