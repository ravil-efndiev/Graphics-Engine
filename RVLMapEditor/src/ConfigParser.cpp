#include "ConfigParser.hpp"
#include <Core/Utils/Files.hpp>
#include <regex>
#include <optional>

namespace Rvl
{
    static std::unordered_map<TypeName, TokenType> TypeList = 
    {
        {TypeName::Assign,  { TypeName::Assign, R"(^\=)"}},
        {TypeName::NewLine, { TypeName::NewLine, R"(^\n)"}},
        {TypeName::LeftBracket, { TypeName::NewLine, R"(^\[)"}},
        {TypeName::RightBracket, { TypeName::NewLine, R"(^\])"}},
        {TypeName::Number,  { TypeName::Number, R"(^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+))"}},
        {TypeName::String,  { TypeName::String, R"(^\'([^\']*)\')"}},
        {TypeName::Name,    { TypeName::Name, R"(^[_|A-Z|a-z]+[_|A-Z|a-z|0-9]+)"}},
        {TypeName::Space,   { TypeName::Space, R"(^\s+)"}},
    };

    ConfigParser::ConfigParser(const std::string& path)
    {
        _path = path;   
        _data = Utils::GetTextFromFile(_path);
        Parse();
    }

    ConfigParser::~ConfigParser() {}

    void ConfigParser::Parse()
    {
        while (_tokenPosition < _data.size())
        {
            NextToken();
        }

        ParseTokens();
    }

    void ConfigParser::NextToken()
    {
        for (auto& type : TypeList)
        {
            auto regexp = std::regex(type.second.Regex);
            auto currentString = _data.substr(_tokenPosition);

            std::smatch result;

            if (std::regex_search(currentString, result, regexp)) 
            {
                _tokenPosition += result.str().size();
                if (type.first != TypeName::Space)
                {
                    Token token (type.second, result.str());
                    _tokens.push_back(token);
                }
                return;
            }
        }
        throw Error("invalid token", RVL_CLIENT_ERROR);
    }


    template <class... Types>
    std::optional<Token> ConfigParser::Find(const Types&... types)
    {
        std::vector<TokenType> params = { { types... } };
        if (_parserPosition < _tokens.size())
        {
            Token currentToken = _tokens[_parserPosition];
            if (std::find_if(params.begin(), params.end(), [currentToken](const TokenType& type){return type.Name == currentToken.Type.Name;}) != params.end())
            {
                _parserPosition++;
                return currentToken;
            }
        }
        return std::nullopt;
    }

    template <class... Types>
    Token ConfigParser::Require(const Types& ...types)
    {
        auto token = Find(types...);

        if (token == std::nullopt)
           throw Error("Parser => required token not found", RVL_CLIENT_ERROR);

        return *token;
    }

    void ConfigParser::ParseTokens()
    {
        while (_parserPosition < _tokens.size())
        {
            Token name = Require(TypeList[TypeName::Name], TypeList[TypeName::NewLine]);

            if (name.Type.Name == TypeName::NewLine)
                continue;

            Token assign = Require(TypeList[TypeName::Assign]);

            auto lBracket = Find(TypeList[TypeName::LeftBracket]);

            if (lBracket)
            {
                std::vector<Token> values;
                while (!Find(TypeList[TypeName::RightBracket]))
                {
                    if (_parserPosition >= _tokens.size())
                        throw Error("array has no right closing bracket", RVL_CLIENT_ERROR);

                    values.push_back(Require(TypeList[TypeName::Number], TypeList[TypeName::String]));
                }
                _arrays.push_back(std::make_pair(name, values));
            }
            else
            {
                Token value = Require(TypeList[TypeName::Number], TypeList[TypeName::String]);

                _values.push_back(std::make_pair(name, value));
            }   
        }
    }

    std::string ConfigParser::GetString(const std::string& name)
    {
        auto it = std::find_if(_values.begin(), _values.end(), [name](auto token)
        {
            return name == token.first.Text;
        });

        if (it == _values.end()) return "";

        if (it->second.Type.Name != TypeName::String)
            throw Error("type of value is not string", RVL_CLIENT_ERROR);

        std::string str = it->second.Text;
        str.pop_back();
        str.erase(0, 1);

        return str;
    }

    double ConfigParser::GetNumber(const std::string& name)
    {
        auto it = std::find_if(_values.begin(), _values.end(), [name](auto token)
        {
            return name == token.first.Text;
        });

        if (it == _values.end()) return 0.0;

        if (it->second.Type.Name != TypeName::Number)
            throw Error("type of value is not number", RVL_CLIENT_ERROR);

        return std::stod(it->second.Text);
    }

    std::vector<std::string> ConfigParser::GetStringArray(const std::string& name)
    {
        auto it = std::find_if(_arrays.begin(), _arrays.end(), [name](auto token)
        {
            return name == token.first.Text;
        });

        if (it == _arrays.end()) return {};

        std::vector<std::string> values;

        for (auto& token : it->second)
        {
            if (token.Type.Name != TypeName::String)
                throw Error("type of value in array is not string", RVL_CLIENT_ERROR);

            std::string str = token.Text;
            str.pop_back();
            str.erase(0, 1);

            values.push_back(str);
        }

        return values;
    }

    std::vector<double> ConfigParser::GetNumberArray(const std::string& name)
    {
        auto it = std::find_if(_arrays.begin(), _arrays.end(), [name](auto token)
        {
            return name == token.first.Text;
        });

        if (it == _arrays.end()) return {};

        std::vector<double> values;

        for (auto& token : it->second)
        {
            if (token.Type.Name != TypeName::Number)
                throw Error("type of value in array is not number", RVL_CLIENT_ERROR);

            values.push_back(std::stod(token.Text));
        }

        return values;
    }
    
    std::unordered_map<std::string, std::vector<std::string>> ConfigParser::GetStringArrays()
    {
        std::unordered_map<std::string, std::vector<std::string>> arrs;

        for (auto& arr : _arrays)
        {
            arrs.emplace(arr.first.Text, GetStringArray(arr.first.Text));
        }

        return arrs;
    }

    void ConfigParser::AddStringArray(const std::string& name, const std::initializer_list<std::string>& strings)
    {
        std::vector<Token> vec;
        for (auto& str : strings)
        {
            vec.push_back(Token(TypeList[TypeName::String], std::string("'") + str + "'"));
        }

        _arrays.push_back(std::make_pair(Token(TypeList[TypeName::Name], name), vec));
    }
    
    void ConfigParser::Delete(const std::string& name)
    {
        auto vit = std::remove_if(_values.begin(), _values.end(), [name](auto tkn) {return tkn.first.Text == name;} );
        auto ait = std::remove_if(_arrays.begin(), _arrays.end(), [name](auto tkn) {return tkn.first.Text == name;} );
        
        if (vit != _values.end()) _values.erase(vit);
        if (ait != _arrays.end()) _arrays.erase(ait);
    }
    
    void ConfigParser::Save()
    {
        std::string text;
        for (auto& val : _values)
        {
            text += val.first.Text + " = " + val.second.Text + "\n";
        }

        for (auto& arr : _arrays)
        {
            std::string line;
            for (auto& el : arr.second)
            {
                line += el.Text + " ";
            }
            text += arr.first.Text + " = [" + line + "]\n";
        }

        Utils::SaveTextToFile(_path.c_str(), text);

        Parse();
    }
}

