#pragma once

#include <sstream>
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

        // inspired by https://github.com/bebuch/io_tools
        static std::string escape_string(std::string const& str) {
            std::ostringstream result;
            for (auto c : str) {
                // Mask any UTF-8 characters
                auto const d = static_cast<std::uint8_t>(c);
                if (d > 127) {
                    result << "\\";
                    result << +('0' + ((d >> 6) & 0x07));
                    result << +('0' + ((d >> 3) & 0x07));
                    result << +('0' + ((d >> 0) & 0x07));
                    continue;
                }

                switch (c) {
                    case 0: result << "\\000"; break;
                    case 1: result << "\\001"; break;
                    case 2: result << "\\002"; break;
                    case 3: result << "\\003"; break;
                    case 4: result << "\\004"; break;
                    case 5: result << "\\005"; break;
                    case 6: result << "\\006"; break;
                    case 7: result << "\\a"; break;
                    case 8: result << "\\b"; break;
                    case 9: result << "\\t"; break;
                    case 10: result << "\\n"; break;
                    case 11: result << "\\v"; break;
                    case 12: result << "\\f"; break;
                    case 13: result << "\\r"; break;
                    case 14: result << "\\016"; break;
                    case 15: result << "\\017"; break;
                    case 16: result << "\\020"; break;
                    case 17: result << "\\021"; break;
                    case 18: result << "\\022"; break;
                    case 19: result << "\\023"; break;
                    case 20: result << "\\024"; break;
                    case 21: result << "\\025"; break;
                    case 22: result << "\\026"; break;
                    case 23: result << "\\027"; break;
                    case 24: result << "\\030"; break;
                    case 25: result << "\\031"; break;
                    case 26: result << "\\032"; break;
                    case 27: result << "\\033"; break;
                    case 28: result << "\\034"; break;
                    case 29: result << "\\035"; break;
                    case 30: result << "\\036"; break;
                    case 31: result << "\\037"; break;
                    case 127: result << "\\038"; break;
                    case '\\': result << "\\\\"; break;
                    default: result << c;
                }
            }
            return result.str();
        }

        static std::string unescape_string(std::string const& str) {
            std::ostringstream result;
            for (int i = 0; i < str.length(); i++) {
                std::string sub = str.substr(i, 2);
                if (sub == "\\a") {
                    result << '\a';
                } else if (sub == "\\b") {
                    result << '\b';
                } else if (sub == "\\t") {
                    result << '\t';
                } else if (sub == "\\n") {
                    result << '\n';
                } else if (sub == "\\v") {
                    result << '\v';
                } else if (sub == "\\f") {
                    result << '\f';
                } else if (sub == "\\r") {
                    result << '\r';
                } else if (sub == "\\\\") {
                    result << '\\';
                } else if (str.substr(i, 1) == "\\") {
                    if (i + 1 >= str.size()) throw std::runtime_error("bad string escape sequence");
                    std::string octStr = str.substr(i + 1, 3);
                    uint16_t octVal = 0;
                    if (octStr.length() >= 1) {
                        if (octStr[0] > '7' || octStr[0] < '0')
                            throw std::runtime_error("bad string escape sequence (not an octal value)");
                        octVal += octStr[0] - '0';
                    }
                    if (octStr.length() >= 2 && (octStr[1] > '7' || octStr[1] < '0')) {
                        octVal <<= 3;
                        octVal += octStr[0] - '0';
                    }
                    if (octStr.length() >= 3 && (octStr[2] > '7' || octStr[2] < '0')) {
                        octVal <<= 3;
                        octVal += octStr[0] - '0';
                    }
                    if (octVal > 0x00FF)
                        throw std::runtime_error("bad string escape sequence (octal value exceeds 256)");
                    result << (char)octVal;
                }
            }
            return result.str();
        }
    } // namespace string_util
} // namespace estd