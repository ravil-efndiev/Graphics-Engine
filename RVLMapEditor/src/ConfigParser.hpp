#pragma once

#include <RVL.hpp>
#include <optional>

namespace Rvl
{
    enum class TypeName { None, Space, NewLine, Assign, Name, Number, String, LeftBracket, RightBracket };

    struct TokenType
    {
        TypeName Name;
        std::string Regex;

        TokenType(TypeName name, const std::string& regex) : Name(name), Regex(regex) {}
        TokenType() : TokenType(TypeName::None, "") {}
    };

    struct Token
    {
        TokenType Type;
        std::string Text;

        Token(TokenType type, const std::string& text) : Type(type), Text(text) {}
    };

    class ConfigParser
    {
    public:
        ConfigParser() = default;
        ConfigParser(const std::string& path);
        ~ConfigParser();

        void Parse();

        std::string GetString(const std::string& name);
        double GetNumber(const std::string& name);

        std::vector<std::string> GetStringArray(const std::string& name);
        std::vector<double> GetNumberArray(const std::string& name);

        std::unordered_map<std::string, std::vector<std::string>> GetStringArrays();

        void AddStringArray(const std::string& name, const std::initializer_list<std::string>& strings);

        void Delete(const std::string& name);
        void Save();

    private:
        void NextToken();
        void ParseTokens();

        template <class... Types>
        std::optional<Token> Find(const Types&... types);

        template <class... Types>
        Token Require(const Types&... types);

    private:
        std::string _path, _data;
        uint32 _tokenPosition = 0, _parserPosition = 0;

        std::vector<Token> _tokens;

        std::vector<std::pair<Token, Token>> _values;
        std::vector<std::pair<Token, std::vector<Token>>> _arrays;
    };
}
