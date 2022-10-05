#include "params_parser.h"
#include "parser_exceptions.h"

// unrecognized character escape sequence ('/' and ' ')
#pragma warning(push)
#pragma warning(disable : 4129)

using namespace std;

map<string, string> ParseParams(const string& params)
{
    map<string, string> result;
    // Checks if escape sequence is passed. If so, move the iterator to the required character, ignoring the escape character (backslash)
    auto checkAndMoveIteratorToEscapeSeq = [](const auto& endIt, auto& it) {
        if (*it == '\\') {
            auto nextIt = std::next(it);
            if (nextIt != endIt && (*nextIt == '\\' || *nextIt == '\/' || *nextIt == '\"' || *nextIt == '\ ')) {
                it = nextIt;
            }
        }
    };

    for (auto it = params.begin(); it != params.end();) {
        if (*it == '/') {
            // 1. Parse param
            auto beginParamIt = ++it;
            // Validate if param is presented
            if (beginParamIt == params.end() || *beginParamIt == ' ') {
                auto pos = std::distance(params.begin(), beginParamIt);
                throw MissingParameterNameException(params, ParamsChunk{ static_cast<size_t>(pos - 1), static_cast<size_t>(pos) });
            }
            while (it != params.end() && *it != ' ' && *it != '\t') {
                ++it;
            }
            auto endParamIt = it;

            // 2. Parse value of param (if available)
            std::string value;
            if (it != params.end()) {
                // Skip spaces and tabs
                while (it != params.end() && (*it == ' ' || *it == '\t')) {
                    ++it;
                }

                // Check if a value of param is not next param
                if (it != params.end() && *it != '/') {
                    // Value of param in quotation marks
                    if (*it == '\"') {
                        auto beginPos = std::distance(params.begin(), it);
                        ++it;
                        while (it != params.end() && *it != '\"') {
                            checkAndMoveIteratorToEscapeSeq(params.end(), it);
                            value += *it;
                            ++it;
                        }
                        // Validate missing quotes
                        if (it == params.end()) {
                            auto endPos = std::distance(params.begin(), it);
                            throw MissingQuotesException(params, ParamsChunk{ static_cast<size_t>(beginPos), static_cast<size_t>(endPos) });
                        }
                        else {
                            auto nextIt = std::next(it);
                            if (nextIt != params.end() && *nextIt != ' ' && *nextIt != '\t') {
                                auto endPos = std::distance(params.begin(), nextIt);
                                throw MissingQuotesException(params, ParamsChunk{ static_cast<size_t>(beginPos), static_cast<size_t>(endPos) });
                            }
                        }
                    }
                    else {
                        while (it != params.end() && *it != ' ' && *it != '\t') {
                            checkAndMoveIteratorToEscapeSeq(params.end(), it);
                            value += *it;
                            ++it;
                        }
                    }

                    // After parse value in quotation marks string iterator can point to a quote, skip it
                    if (it != params.end() && *it == '\"') {
                        ++it;
                    }
                }
            }

            auto emplaced = result.emplace(string{ beginParamIt, endParamIt }, std::move(value));
            // Validate if param already exist
            if (!emplaced.second) {
                auto beginPos = std::distance(params.begin(), --beginParamIt);
                auto endPos = std::distance(params.begin(), endParamIt);
                throw SpecifiedTwiceParameterException(params, ParamsChunk{ static_cast<size_t>(beginPos), static_cast<size_t>(endPos) });
            }
        }
        else if (*it == ' ' || *it == '\t') {
            ++it;
        }
        else {
            auto beginPos = std::distance(params.begin(), it);
            // Value in quotation marks
            if (*it == '\"') {
                ++it;
                while (it != params.end() && *it != '\"') {
                    ++it;
                }
                // After parse value in quotation marks string iterator can point to a quote, skip it
                if (it != params.end() && *it == '\"') {
                    ++it;
                }
            }
            else {
                while (it != params.end() && *it != ' ' && *it != '\t') {
                    ++it;
                }
            }
            auto endPos = std::distance(params.begin(), it);
            throw UnexpectedValueException(params, ParamsChunk{ static_cast<size_t>(beginPos), static_cast<size_t>(endPos) });
        }
    }

    return result;
}

#pragma warning(pop) 
