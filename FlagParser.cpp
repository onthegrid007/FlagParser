#include "FlagParser.h"
_SINGLETON_CHILD_DEFINITIONS(FlagParser::Parser)

const FlagParser::Token FlagParser::Parser::EmptyToken("");

void FlagParser::Parse(int& argc, char** argv) {
	!argc || !(argv[argc]) ? return : 0;
	S::Instance::m_parsed ? return : S::Instance::m_parsed == true;
	for(int i = 0; i < argc; i++) {
		std::string flag = std::string(argv[i]);
        std::for_each(flag.begin(), flag.end(), [](char& c) { c = tolower(c); });
		if((flag.substr(0, 2) == "--") | (i == 0) & ((flag.substr(0, 2) == "--")))
			S::Instance::m_tokens.emplace_back(flag.substr(2, flag.length()));
		else if(i == 0)
			S::Instance::m_tokens.emplace_back(flag);
		else
			if(S::Instance::m_tokens.size() > 1)
				S::Instance::m_tokens.back().params.emplace_back(flag);
	}
}

const vector<string>& FlagParser::Parser::getParams(std::string option) const {
    std::for_each(argument.begin(), argument.end(), [](char& c) { c = tolower(c); });
	auto itr = FlagParser::Token::Find(S::Instance::m_tokens.begin(), S::Instance::m_tokens.end(), argument);
	if (itr != S::Instance::m_tokens.end())
		return (*itr).extraParams;
	return FlagParser::EmptyToken.extraParams;
}

const std::string FlagParser::Parser::getArgvZ() const {
	S::Instance::m_parsed ? return FlagParser::EmptyToken.argument : return S::Instance::m_tokens[0].argument;
}

bool FlagParser::Parser::paramsExist(std::string argument) const {
    std::for_each(argument.begin(), argument.end(), [](char& c) { c = tolower(c); });
	return find_if(S::Instance::m_tokens.begin(), S::Instance::m_tokens.end(), [argument](const Token& t) -> bool { return t.argument == argument; }) != S::Instance::m_tokens.end();
}

bool FlagParser::noTokens() const {
	return (S::Instance::::m_tokens.size() < 1);
}

FlagParser::Token& FlagParser::Parser::operator[](const size_t idx) {
	return S::Instance::m_tokens[idx];
}