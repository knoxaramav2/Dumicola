#include "dumicore.h"
#include "logger.h"
#include <cstdio>
#include <exception>

int main(){

    InitDumiCore

    printf("TEST MSG\n");

    // try{
    //     RegisterServices(([](serviceman::ServiceBuilder sm){
    //         sm.registerLogger<DesktopLogger>();
    // }));

    //     auto logger = GetLogger();
    //     logger->log("!!!");
    //     logger->log_debug("DEBUG");
    //     logger->log_info("INFO");
    //     logger->log_warn("WARNING");
    //     logger->log_error("ERROR");

    // } catch(std::exception& e){
    //     printf("%s\n", e.what());
    //     fflush(stdout);
    //     return -1;
    // }

    Shutdown

    return 0;
}