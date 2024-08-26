#include "token.h"
#include "utils.h"

dumilang::TokenGroup::TokenGroup(fs::path path)
{
    id = appId(this);
    _path = path;
    _success = false;
}

bool dumilang::TokenGroup::isTokenized()
{
    return _success;
}

bool dumilang::Tokenizer::tokenize()
{
    bool success = true;
    for(auto& grp: _groups){
        if(!grp.isTokenized()){
            success &= _genTokens(grp);
        }
    }

    return success;
}

bool dumilang::Tokenizer::tokenize(fs::path path)
{
    if(!addPath(path)){
        return false;
    }

    return _genTokens(_groups[_groups.size()-1]);
}

bool dumilang::Tokenizer::addPath(fs::path path)
{
    for(auto&grp:_groups){
        if(grp._path == path){return false;}
    }

    _groups.push_back(TokenGroup(path));
    return true;
}

void dumilang::Tokenizer::addDir(fs::path path, const char* ext)
{
    auto files = dcutil::listFiles(path, ext, true);
    for(auto& file : files){
        addPath(file);
    }
}
