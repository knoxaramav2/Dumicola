#pragma once

#include "component.h"

typedef std::function<void()> _updateFnc;

class VulkanBaseDefinition: extend dumisdk::DCComponentDefinition{
    protected:
    using DCComponentDefinition::DCComponentDefinition;
    VulkanBaseDefinition(VulkanBaseDefinition& def);
    public:
};

class VulkanBaseComponent: 
    extend VulkanBaseDefinition, extend dumisdk::DCComponentImplementation{
    _updateFnc _update;
    protected:
    public:
    VulkanBaseComponent(VulkanBaseDefinition& def, _updateFnc update);
    void update() override;
};

class VulkanBaseTemplate: extend dumisdk::DCComponentDefinition, extend dumisdk::DCComponentTemplate<VulkanBaseComponent>{

    _updateFnc _update;

    protected:
    public:


};

class VulkanLibrary: extend dumisdk::IDCLibrary{

    public:
    VulkanLibrary();

};


