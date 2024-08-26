#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "defs.h"

namespace dumilang{

    namespace fs = std::filesystem; 
    
    enum Lexeme{
        
    };

    struct Token{
        Lexeme lexeme;
        const char* text;
    };

    class TokenGroup{
        APPSID id;
        fs::path _path;
        std::vector<Token> _tokens;
        protected:
        bool _success;
        public:
        TokenGroup(fs::path path);
        bool isTokenized();

        friend class Tokenizer;
    };

    class Tokenizer{

        bool _genTokens(TokenGroup& group);
        std::vector<TokenGroup> _groups;

        public:

        bool tokenize();
        bool tokenize(fs::path path);
        bool addPath(fs::path path);
        void addDir(fs::path path, const char* ext);

    };


}
