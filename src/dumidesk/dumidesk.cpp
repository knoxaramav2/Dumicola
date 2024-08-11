#include "dumicore.hpp"
#include "logger.hpp"
#include <cstdio>
#include <exception>

int main(){

    InitDumiCore

    try{
        RegisterServices(([](serviceman::ServiceManager& sm){
        //sm.registerLogger<DesktopLogger>();
        sm.registerSingelton<dumisdk::ILogger, DesktopLogger>();
        
    }));
    } catch(std::exception& e){
        printf("%s\n", e.what());
        return -1;
    }
    
    auto logger = GetLogger();
    logger.log("!!!");
    logger.log_debug("DEBUG");
    logger.log_info("INFO");
    logger.log_warn("WARNING");
    logger.log_error("ERROR");

    // const char* statMsg = status == 0 ? "OK" : "ERR";
    // printf("CORE STATE: %s\n", statMsg);

    Shutdown

    return 0;
}