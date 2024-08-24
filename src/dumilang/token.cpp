#include "token.h"
#include "utils.h"

TokenGroup::TokenGroup(fs::path path)
{
    id = appId(this);
    _path = path;
    _success = false;
}

bool TokenGroup::isTokenized()
{
    return _success;
}

bool Tokenizer::tokenize()
{
    bool success = true;
    for(auto& grp: _groups){
        if(!grp.isTokenized()){
            success &= _genTokens(grp);
        }
    }

    return success;
}

bool Tokenizer::tokenize(fs::path path)
{
    if(!addPath(path)){
        return false;
    }

    return _genTokens(_groups[_groups.size()-1]);
}

bool Tokenizer::addPath(fs::path path)
{
    for(auto&grp:_groups){
        if(grp._path == path){return false;}
    }

    _groups.push_back(TokenGroup(path));
    return true;
}

void Tokenizer::addDir(fs::path path, const char* ext)
{
    auto files = dcutil::listFiles(path, ext, true);
    for(auto& file : files){
        addPath(file);
    }
}
