#include "vulkan.h"


VulkanLibrary::VulkanLibrary():dumisdk::IDCLibrary(
    "Vulkan", "0.0.1", "KnoxaramaV2", "https://github.com/knoxaramav2/Dumicola.git", 
    "STL Dumicola logic component library" 
)
{
    //auto _lgAndTmpl = std::make_shared<>("STL AND", "Logical AND");

    //registerTemplate(_lgAndTmpl);

}

const std::vector<dumisdk::ComponentInfo> VulkanLibrary::manifest()
{
    return std::vector<dumisdk::ComponentInfo>();
}

const dumisdk::DCComponentImplementation* VulkanLibrary::create(const char* name)
{
    return nullptr;
}

const dumisdk::DCComponentImplementation* VulkanLibrary::create(HASHID id)
{
    return nullptr;
}

bool VulkanLibrary::registerTemplate(dumisdk::DCComponentTemplate<dumisdk::DCComponentImplementation>& componentTemplate)
{
    return false;
}

VulkanBaseDefinition::VulkanBaseDefinition(VulkanBaseDefinition &def): 
    DCDefinition(def) {}

VulkanBaseComponent::VulkanBaseComponent(VulkanBaseDefinition &def, _updateFnc update):
    VulkanBaseDefinition(def) { _update = update; }

void VulkanBaseComponent::update() { _update(); }

VulkanBaseComponent* VulkanBaseTemplate::create()
{
    return nullptr;
}

dumisdk::IDCLibrary* LoadLibrary()
{
    return new VulkanLibrary();;
}
