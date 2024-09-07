#include "dccompile.h"
#include "dumiexcept.h"
#include "dc_string.h"

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
    OP_BRCK,    //[
    CL_BRCK,    //]
    OP_BRCE,    //{
    CL_BRCE,    //}
    OP_PARN,    //(
    CL_PARN,    //)
    OP_ANGLE,   //<
    CL_ANGLE,   //>
    PROPERTY,   //::PROPERTY
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
            }
        } else {return false;}
    }
    return true;
}

inline DCLex detect0(std::string& term){

    if(term=="as"){return AS;}
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

// bool checkPrevEnc(std::string& cStack, char close){
//     char open;
//     switch (close)
//     {
//     case ')': open = '('; break;
//     case ']': open = '['; break;
//     case '}': open = '{'; break;
//     case '>': open = '<'; break;
//     default:
//         return false;
//     }
//     return cStack.size() > 0 && cStack[cStack.size()-1] == open;
// }

// size_t findNextUnescaped(std::string& text, size_t start, char c){
//     size_t idx;

//     do{
//         idx = text.find(c, start+1);
//         if(text[idx-1] != '\\') break;
//     } while (idx != text.npos);

//     return idx;
// }

// inline bool isWs(char c){
//     return c == ' '|| c == '\t' || c == '\r' || c == '\n';
// }

// inline bool isWs(std::string& text){
//     for(char c : text){
//         if(!isWs(c)) {return false;}
//     }
//     return true;
// }

// inline bool isTab(std::string& text, size_t& idx){
//     const int tabSize = 4;
//     if(idx+tabSize>=text.size()){return false;}
//     for(size_t i = 0; i < tabSize; ++i){
//         if (text[i+idx] != ' '){ return false; }
//     }
//     idx += tabSize-1;
//     return true;
// }

// inline size_t nextWs(std::string&text, size_t start){
//     for(size_t i=start+1; i < text.size(); ++i){
//         if(isWs(text[i])){
//             return i;
//         }
//     }
//     return text.npos;
// }

// inline int countNl(std::string& text, size_t idx){
//     char c = text[idx+1];
//     char nc = idx+2<text.size() ? text[idx] : 0;
//     return (c=='\r'||c=='\n')+(nc=='\r'||nc=='\n');
// }

// inline void appendToken(std::vector<Token>& stack, std::string& term, DCLex lex){
//     if (lex == NLINE && stack.size() && stack[stack.size()-1].lex != NLINE){
//         printf("< %s %s >\n", term.c_str(), DCLexToString(lex));
//         stack.push_back(Token{term, lex});
//     }
// }

// inline void appendToken(std::vector<Token>& stack, const char* term, DCLex lex){
//     static DCLex prev = END;
//     // if(lex==NLINE&&stack.size()&&stack[stack.size()-1].lex==NLINE){
//     //     prev = lex;
//     // }
//     if (!(prev == lex && lex == NLINE)){
//         printf("< %s %s >\n", term, DCLexToString(lex));
//         stack.push_back(Token{term, lex});
//     }
//     prev = lex;
// }

// void setToken(std::vector<Token>& stack, std::string& buff, size_t &pidx, size_t& cidx){
//     //printf("STK: %ld\t\t|%s\t|%ld >> %ld\n", stack.size(), buff.c_str(), pidx, cidx);

//     if(buff.size()==0){return;}
//     //stack.push_back(Token{buff, detect(buff)});
//     appendToken(stack, buff, detect(buff));
//     buff.clear();
//     pidx = cidx+1;
// }

// inline std::vector<Token> parseRaw(std::string &raw){
//     std::vector<Token> ret;
//     std::string bfr;
//     std::string cStack;
//     int line = 0;
//     size_t pidx = 0;

//     int oBrck=0, oBrc=0, oPrn=0;

//     for (size_t i=0; i < raw.size(); ++i){
//         char c = raw[i];
//         switch(c){
//             //WS
//             case ' ':{
//                 setToken(ret, bfr, pidx, i);
//                 const char* t = raw.c_str()+i;
//                 //printf("::>>%s\r\n", t);
//                 fflush(stdout);
//                 if(isTab(raw, i)){
//                     //ret.push_back(Token{"\t", TAB});
//                     appendToken(ret, "\t", TAB);
//                 }
//             }
//             break;
//             case '\t':
//             setToken(ret, bfr, pidx, i);
//             ++i;
//             //ret.push_back(Token{"\t", TAB});
//             appendToken(ret, "\t", TAB);
//             break;
//             //NL (note: scrub \r from results)
//             case '\n':
//                 ++line;
//                 setToken(ret, bfr, pidx, i);
//                 appendToken(ret, "", NLINE);
//             break;
//             //Comment
//             case '#':
//             setToken(ret, bfr, pidx, i);
//             {
//                 auto nl = raw.find('\n', i);
//                 if(nl==raw.npos) break;
//                 i = nl;
//                 appendToken(ret, "", NLINE);
//             }
//             break;
//             //Operators
//             case ':':
//                 if (raw[i+1] != ':'){
//                     throw dumisdk::dumiexception(
//                         dcutil::frmstr("Expected ':' (%s)::%d", bfr.c_str(), line).c_str());
//                 }
                
//                 bfr += "::";
//                 ++i;

//             break;
//             //Quotes
//             case '\'':
//             case '"':{
//             size_t next = findNextUnescaped(raw, i, c);
//             if (next == raw.npos){
//                 throw dumisdk::dumiexception(
//                     dcutil::frmstr("Unclosed single quote (%s)::%d", bfr.c_str(), line).c_str());
//             }
//             std::string substr = raw.substr(i+1, next-i-1);//substr longer than range provided
//             if(substr.find('\n')!=substr.npos){
//                 throw dumisdk::dumiexception(
//                     dcutil::frmstr("Newline before closing quote (%s)::%d", bfr.c_str(), line).c_str());
//             }
//             setToken(ret, bfr, pidx, i);
//             //ret.push_back(Token{substr, STRING});
//             appendToken(ret, substr, STRING);
//             i+=substr.size()+1;
//             pidx = i+1;
//             }
//             break;
//             //Closure
//             case '[': case ']':
//             case '(': case ')':
//             case '{': case '}':
//             case '<': case '>':
//             setToken(ret, bfr, pidx, i);
//             bfr = c;
//             setToken(ret, bfr, pidx, i);
//             break;
//             //Special
//             case '\\':
//                 if(i+1 < raw.size()){
//                     auto skpNl = countNl(raw, i);
//                     if(skpNl){
//                         i += skpNl;
//                     } else if (!isWs(raw[i+1])){
//                         bfr += raw[i+1];
//                     }
//                 }
//                 ++i;
//             break;
//             case '.':
//                 appendToken(ret, bfr, SYMBOL);
//                 appendToken(ret, ".", DOT);
//                 //ret.push_back(Token{bfr, SYMBOL});
//                 //ret.push_back(Token{".", DOT});
//             break;

//             default: bfr += c;
//         }
//     }

//     for(auto& item: ret){
//         printf("%s\t\t\t%d\n", item.text.c_str(), item.lex);
//     }

//     //ret.push_back(Token("", END));
//     appendToken(ret, "", END);
//     return ret;
// }

// void updateRawToken(){

// }

// void backInterpret(std::vector<Token>& target){
//     fflush(stdout);
//     int oBrace = 0, oBrack=0, oAngle=0, oParan=0;
//     for(size_t i = 0; i < target.size()-1; ++i){
//         auto lex = target[i].lex;
//         auto& next = target[i+1].lex;
//         switch(lex){
//             case PROPERTY:
//                 if(!isLiteral(next)){
//                     throw dumisdk::dumiexception(
//                     dcutil::frmstr("Expected value following %s, received %s.\n", 
//                     target[i].text.c_str(), target[i+1].text.c_str()).c_str());
//                 }
//                 break;
//             case DOT:
//                 if(next != RAW){
//                     throw dumisdk::dumiexception(
//                     dcutil::frmstr("Expected identifier, found %s.\n", 
//                     target[i].text.c_str(), DCLexToString(next)).c_str());
//                 }
//                 target[i+1].lex = SYMBOL;
//             case AS:
//                 if(next != RAW){
//                     throw dumisdk::dumiexception(
//                     dcutil::frmstr("Expected identifier, found %s.\n", 
//                     target[i].text.c_str(), DCLexToString(next)).c_str());
//                 }
//                 target[i+1].lex = ALIAS;
//                 break;
//             case OP_BRCE: ++oBrace; break;
//             case CL_BRCE:
//                 if(oBrace==0){throw dumisdk::dumiexception("Extraneous '}' found\n");}
//                 --oBrace;
//             break;
//             case OP_BRCK: ++oBrack; break;
//             case CL_BRCK:
//                 if(oBrack==0){throw dumisdk::dumiexception("Extraneous ']' found\n");}
//                 --oBrack;
//             break;
//             case OP_PARN: ++oParan; break;
//             case CL_PARN:
//                 if(oParan==0){throw dumisdk::dumiexception("Extraneous ')' found\n");}
//                 --oParan;
//             break;
//             case OP_ANGLE: ++oAngle; break;
//             case CL_ANGLE:
//                 if(oAngle==0){throw dumisdk::dumiexception("Extraneous '>' found\n");}
//                 --oAngle;
//             break;
//         }
//     }
// }

Token detect(std::vector<Token>& tokens, std::vector<std::string>::iterator it){
    const char* nrmStr = it->c_str();
    dcutil::toUpper(nrmStr);

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
        case ' ': if(it->c_str() == "    "){ lex = TAB;} break;
        default:{
            Token* prev = tokens.size() > 0 ? &tokens[tokens.size()-1] : nullptr; 
            std::string trm(nrmStr);
            if(isNumeric(trm, false)){ lex = INTEGER; }
            else if (isNumeric(trm, true)){ lex = DECIMAL; }
            else if (trm == "AS") { lex = AS; }

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

std::vector<Bytecode> compile(std::string &text)
{
    std::vector<Bytecode> ret;
    //std::vector<Token> rawStack = parseRaw(text); 
    //backInterpret(rawStack);

    // std::string rgstr(R"(g.*\()");
    //std::string rgstr(R"((::\w+)|(\w+)|([[](){}<>]]))|(?:#.*)");
    std::string rgstr(R"((::\w+)|(\w+)|([\[\]\{\}\(\)<>.,])|(\r\n|\n|\t| {4})|(".*")|('.*')|(?:#.*))");
    std::regex regx(rgstr.c_str());
    std::sregex_iterator iter(text.begin(), text.end(), regx);
    std::sregex_iterator end;
    int tkns = 0;

    std::vector<std::string> raw;
    
    while (iter != end){
        ++tkns;
        //printf("RAW: %s\n", iter->str().c_str());
        for (size_t i = 1; i < iter->size(); ++i){
            if ((*iter)[i].matched){
                printf("< %s >\n", (*iter)[i].str().c_str());
                raw.push_back(iter->str());
            } else {
                //printf("SKIP: %s\n", iter->str().c_str());
            }
        }
        ++iter;
    }

    std::vector<Token> tokens;
    for(auto it = raw.begin(); it != raw.end(); ++it){
        Token tk = detect(tokens, it);
        if(tk.lex != _PRS_SKIP_){
            tokens.push_back(tk);
        }
    }

    for(auto& t: tokens){
        printf("[%s]  [%d]\n", t.text.c_str(), t.lex);
    }

    return ret;
}
