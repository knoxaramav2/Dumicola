#include "vulkan.h"


VulkanLibrary::VulkanLibrary():dumisdk::IDCLibrary(
    "Vulkan", "0.0.1", "KnoxaramaV2", "https://github.com/knoxaramav2/Dumicola.git", 
    "STL Dumicola logic component library" 
)
{
    //auto _lgAndTmpl = std::make_shared<>("STL AND", "Logical AND");

    //registerTemplate(_lgAndTmpl);

}

VulkanBaseDefinition::VulkanBaseDefinition(VulkanBaseDefinition &def): 
    DCDefinition(def) {}

VulkanBaseComponent::VulkanBaseComponent(VulkanBaseDefinition &def, _updateFnc update):
    VulkanBaseDefinition(def) { _update = update; }

void VulkanBaseComponent::update() { _update(); }

