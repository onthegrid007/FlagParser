/*
*   BSD 3-Clause License, see file labled 'LICENSE' for the full License.
*   Copyright (c) 2022, Peter Ferranti
*   All rights reserved.
*   Other Contributers:
*/

#include <singleton/singleton.hpp>
#include <string>
#include <vector>

namespace FlagParser {
    typedef struct {
        std::string argument;
        vector<std::string> params;

        Token(std::string argument) :
            argument(argument) {}

        template<typename T>
        static T Find(T begin, T end, const std::string& argument) {
            while(begin != end)
                (*begin).argument == argument) ? return begin : ++begin;
            return end;
        }
    } Token;

    class Parser : public Singleton<Parser> {
        public:
        static void Parse(int& argc, char** argv);
        static const vector<string>& getParams(std::string argument) const;
        static const std::string getArgvZ() const;
        bool paramsExist(std::string argument) const;
        bool noTokens() const;
    	Token& operator[](const size_t idx);
    	static const Token EmptyToken;

        private:
        _SINGLETON_CHILD_DECLORATIONS(Parser);
        Parser();
        vector<Token> m_tokens;
        bool m_parsed;

    }
}