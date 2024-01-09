/*
*   BSD 3-Clause License, see file labled 'LICENSE' for the full License.
*   Copyright (c) 2023, Peter Ferranti
*   All rights reserved.
*/
#include <string>
#include <vector>
#include <algorithm>

namespace FlagParser {
    typedef struct Token {
        std::string flag;
        std::vector<std::string> params;

        Token(std::string flag) :
            flag(flag) {}
    } Token;
    
    class Parser {
        public:
        inline static const Token EmptyToken{""};
        Parser(int& argc, char** argv) {
            if(!argc) return;
            m_tokens.emplace_back(argv[0]);
            for(int i{1}; i < argc; i++) {
                std::string str{argv[i]};
                std::for_each(str.begin(), str.end(), [](char& c){ c = tolower(c); });
                if(str.substr(0, 2) == "--") {
                    m_tokens.emplace_back(str.substr(2, str.length()));
                }
                else if(m_tokens.size() > 1) {
                    m_tokens.back().params.emplace_back(str);
                }
            }
        }
        
        const bool hasFlag(const std::string flag) const {
            for(auto itt{m_tokens.begin()}; itt != m_tokens.end(); itt++)
                if((*itt).flag == flag) return true;
            return false;
        }
        
        const std::vector<std::string>& getFlagParams(const std::string flag) const {
            for(auto itt{m_tokens.begin()}; itt != m_tokens.end(); itt++)
                if((*itt).flag == flag) return (*itt).params;
            return EmptyToken.params;
        }
        
        const std::string getFirstFlag() const {
            if(m_tokens.size() > 0)
                return m_tokens[0].flag;
            return EmptyToken.flag;
        }
        
    	const Token& operator[](const size_t idx) const {
            if(m_tokens.size() > 0 && m_tokens.size() > idx)
                return m_tokens[idx];
            return EmptyToken;
        }
        
        private:
        std::vector<Token> m_tokens;
    };
}