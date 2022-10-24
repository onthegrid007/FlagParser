/*
*   BSD 3-Clause License, see file labled 'LICENSE' for the full License.
*   Copyright (c) 2022, Peter Ferranti
*   All rights reserved.
*   Other Contributers:
*/

#include <string>
#include <vector>

namespace FlagParser {
    typedef struct {
        std::string argument;
        std::vector<std::string> params;

        Token(std::string argument) :
            argument(argument) {}

        template<typename T>
        static T Find(T begin, T end, const std::string& argument) {
            while(begin != end)
                (*begin).argument == argument) ? return begin : ++begin;
            return end;
        }
    } Token;

    class Parser{
        public:
        Parser(int& argc, char** argv);
        const std::vector<string>& getParams(std::string argument) const;
        const std::string getArgvZ() const;
        bool paramsExist(std::string argument) const;
        bool noTokens() const;
    	Token& operator[](const size_t idx);
    	static const Token EmptyToken;

        private:
        std::vector<Token> m_tokens;
        bool m_parsed;
    };
}