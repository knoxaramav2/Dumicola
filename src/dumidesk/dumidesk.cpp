#include "dumicore.hpp"
#include "logger.hpp"
#include <cstdio>

class Base {
public:
    const char* name;
    Base():name("BASE"){};
    Base(const char* _name):name(_name){};
    virtual void sayHello() const = 0;
    virtual ~Base() = default; // Ensure proper cleanup of derived objects
};

class Derived : public Base {
public:
    Derived():Base("DERIVED"){}
    void sayHello() const override {
        printf("Derived init...");
    }
};

int main(){

    InitDumiCore
    
    dumicore::DumiCore::registerServices([](serviceman::ServiceManager& sm){
        //sm.registerTransient<Base, Derived>();
        sm.registerTransient<dumisdk::ILogger, DesktopLogger>();
        // sm.registerTransient<Base, Derived>();
        // auto b = sm.resolveTransient<Base>();
        // if(b) 
        //     b->sayHello();
    });

    auto logger = GetLogger();
    logger->log("!!!");
    logger->log_debug("DEBUG");
    logger->log_info("INFO");
    logger->log_warn("WARNING");
    logger->log_error("ERROR");

    auto status = dumicore::DumiCore::checkStatus();

    // const char* statMsg = status == 0 ? "OK" : "ERR";
    // printf("CORE STATE: %s\n", statMsg);

    Shutdown

    return status != 0;
}