#include "dccompile.h"
#include "dumiexcept.h"
#include "dc_string.h"

#include <iterator>
#include <regex>

enum DCLex{
    RAW,
    STRING,     //'...' or "..."
    INTEGER,    //123
    DECIMAL,    //1.23
    SYMBOL,     //abc
    DOT,        //a(.)b
    AS,         //A (as) B
    ALIAS,      //A as (B)
    LINK,       //Link <Node1> <Node2>
    OP_BRCK,    //[
    CL_BRCK,    //]
    OP_BRCE,    //{
    CL_BRCE,    //}
    OP_PARN,    //(
    CL_PARN,    //)
    OP_ANGLE,   //<
    CL_ANGLE,   //>
    PROPERTY,   //::PROPERTY
    COMMENT,    //#Comment
    COMMA,
    TAB,
    NLINE,          
    END,

    _PRS_SKIP_
};

const char* DCLexToString(DCLex lex){
    const char* ret;
    switch (lex)
    {
    case RAW: ret = "raw"; break;
    case STRING: ret = "string"; break;
    case INTEGER: ret = "integer"; break;
    case DECIMAL: ret = "decimal"; break;
    case SYMBOL: ret = "symbol"; break;
    case DOT: ret = "dot"; break;
    case AS: ret = "as"; break;
    case ALIAS: ret = "alias"; break;
    case LINK: ret = "link"; break;
    case OP_BRCK: ret = "["; break;
    case CL_BRCK: ret = "]"; break;
    case OP_BRCE: ret = "{"; break;
    case CL_BRCE: ret = "}"; break;
    case OP_PARN: ret = "("; break;
    case CL_PARN: ret = ")"; break;
    case OP_ANGLE: ret = "<"; break;
    case CL_ANGLE: ret = ">"; break;
    case PROPERTY: ret = "property"; break;
    case TAB: ret = "TAB"; break;
    case END: ret = "EOF"; break;
    case NLINE: ret = "NL"; break;
    case COMMENT: ret = "CMNT"; break;
    case _PRS_SKIP_: ret = "SKIP"; break;
    default:
        ret = "ERR_UNKNOWN";
    }

    return ret;
}

bool isLiteral(DCLex lex){
    return lex==STRING||lex==INTEGER||lex==DECIMAL||lex==OP_BRCK;
}

struct Token{
    std::string text;
    DCLex lex;
    Token(std::string text, DCLex lex): text(text), lex(lex){}
    Token(const char* text, DCLex lex): text(text), lex(lex){}
};

inline bool isNumeric(std::string& text, bool allowDecimal){
    bool deci = false;
    for(char c: text){
        if (c<'0'||c>9){
            if(c=='.'){
                if(deci){return false;}
                deci = true;
            } else {return false;}
        }
    }
    return true;
}

inline DCLex detect0(std::string& term){

    if(term=="AS"){return AS;}
    if(term=="LINK"){return LINK;}
    if(term.rfind("::", 0)==0){return PROPERTY;}
    if(isNumeric(term, false)){return INTEGER;}
    if(isNumeric(term, true)){return DECIMAL;}
    if(term.size()==1){
        switch (term[0])
        {
        case '[': return OP_BRCK; break;
        case ']': return CL_BRCK; break;
        case '{': return OP_BRCE; break;
        case '}': return CL_BRCE; break;
        case '(': return OP_PARN; break;
        case ')': return CL_PARN; break;
        case '<': return OP_ANGLE; break;
        case '>': return CL_ANGLE; break;
        }
    }

    return RAW;
}

Token detect(std::vector<Token>& tokens, std::string& text){
    const char* nrmStr = text.c_str();
    //dcutil::toUpper(nrmStr);

    printf("\t| %s ", nrmStr);
    fflush(stdout);

    char c = nrmStr[0];
    DCLex lex = SYMBOL;

    switch(c){
        case '"':
        case '\'': lex = STRING; break;
        case '[': lex = OP_BRCK; break;
        case ']': lex = CL_BRCK; break;
        case '(': lex = OP_PARN; break;
        case ')': lex = CL_PARN; break;
        case '{': lex = OP_BRCE; break;
        case '}': lex = CL_BRCE; break;
        case '<': lex = OP_ANGLE; break;
        case '>': lex = CL_ANGLE; break;
        case '.': lex = DOT; break;
        case ',': lex = COMMA; break;
        case '\t': lex = TAB; break;
        case '\r': case '\n': lex = NLINE; break;
        case ' ': if(strcmp(nrmStr, "    ")==0){ lex = TAB;} break;
        case '#': lex = COMMENT; break;
        default:{
            Token* prev = tokens.size() > 0 ? &tokens[tokens.size()-1] : nullptr; 
            std::string trm(nrmStr);
            if(isNumeric(trm, false)){ lex = INTEGER; }
            else if (isNumeric(trm, true)){ lex = DECIMAL; }
            else if (trm == "as") { lex = AS; }
            else if (trm == "link") { lex = LINK; }
            else{
                if(prev){
                    switch(prev->lex){
                        case AS: lex = ALIAS; break;
                    }
                } else {

                }
            }
        }
    }

    printf("\t\t\t | %s\n", nrmStr);

    std::string tstr(nrmStr);
    return Token(tstr, lex);
}

std::vector<Bytecode> compile(std::string& text)
{
    std::vector<Bytecode> ret;
    const char* rgstr(R"((::\w+)|(\w+)|([\[\]\{\}\(\)<>.,])|(\r\n|\n|\t| {4})|(".*")|('.*')|(?:#.*))");
    std::regex regx(rgstr);
    std::sregex_iterator start(text.begin(), text.end(), regx);
    std::sregex_iterator end;
    std::vector<std::string> raw;
    std::vector<Token> tokens;
    DCLex prvLex = DCLex::_PRS_SKIP_;
    for(auto it = start; it != end; ++it){
        auto lstr = it->str();
        
        Token tk = detect(tokens, lstr);
        if(tk.lex != _PRS_SKIP_ && tk.lex != COMMENT &&
            !(tk.lex == NLINE && prvLex == NLINE)){
            tokens.push_back(tk);
            prvLex = tk.lex;
        }
    }

    printf(">>>>>>>>>>>>>>>>>>>>>>>\n");

    for(auto& t: tokens){
        //if(t.lex == NLINE){ continue; }
        printf("[%s]  [%s]\n", t.text.c_str(), DCLexToString(t.lex));
    }

    return ret;
}
