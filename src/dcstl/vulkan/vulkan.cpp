#include "vulkan.h"


VulkanLibrary::VulkanLibrary() :dumisdk::IDCLibrary(
	"Vulkan", "0.0.1", "KnoxaramaV2", "https://github.com/knoxaramav2/Dumicola.git",
	"STL Dumicola logic component library"
)
{
	//auto _lgAndTmpl = std::make_shared<>("STL AND", "Logical AND");

	//registerTemplate(_lgAndTmpl);

}

const std::vector<dumisdk::ComponentInfo> VulkanLibrary::manifest()
{
	std::vector<dumisdk::ComponentInfo> ret;

	for(auto& cmp: _templates){
		ret.push_back(*cmp.second.get());
	}

	return ret;
}

const dumisdk::DCComponentImplementation* VulkanLibrary::create(const char* name)
{
	return create(hashId(name));
}

const dumisdk::DCComponentImplementation* VulkanLibrary::create(HASHID id)
{
	auto it = _templates.find(id);
	return it == _templates.end() ? nullptr:
		it->second->create();
}

bool VulkanLibrary::registerTemplate(std::shared_ptr<dumisdk::DCComponentTemplate<dumisdk::DCComponentImplementation>> componentTemplate)
{
    if (_templates.find(componentTemplate->id) != _templates.end()) {
        return false;
    }
    return _templates.emplace(componentTemplate->id, componentTemplate).second;
}


VulkanBaseDefinition::VulkanBaseDefinition(VulkanBaseDefinition& def) :
	DCDefinition(def) {}

VulkanBaseComponent::VulkanBaseComponent(VulkanBaseDefinition& def, _updateFnc update) :
	VulkanBaseDefinition(def) {
	_update = update;
}

void VulkanBaseComponent::update() { _update(); }

VulkanBaseComponent* VulkanBaseTemplate::create()
{
	return new VulkanBaseComponent(*this, _update);
}

dumisdk::IDCLibrary* LoadLibrary()
{
	return new VulkanLibrary();
}
