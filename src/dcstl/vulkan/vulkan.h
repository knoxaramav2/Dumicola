#pragma once

#include "component.h"

typedef std::function<void()> _updateFnc;

#ifdef VULKAN_EXPORT
#define VULKAN_API DUMIEXPORT
#else
#define VULKAN_API DUMIIMPORT
#endif

class VulkanBaseDefinition : extend dumisdk::DCComponentDefinition {
protected:
	using DCComponentDefinition::DCComponentDefinition;
	VulkanBaseDefinition(VulkanBaseDefinition& def);
public:
};

class VulkanBaseComponent :
	extend VulkanBaseDefinition, extend dumisdk::DCComponentImplementation {
	_updateFnc _update;
protected:
public:
	VulkanBaseComponent(VulkanBaseDefinition& def, _updateFnc update);
	void update() override;
};

class VulkanBaseTemplate : extend VulkanBaseDefinition, extend dumisdk::DCComponentTemplate<VulkanBaseComponent> {

	_updateFnc _update;

protected:
public:

	VulkanBaseComponent* create() override;
};

class VulkanLibrary : extend dumisdk::IDCLibrary {

public:
	VulkanLibrary();
	const std::vector<dumisdk::ComponentInfo> manifest() override;
	const dumisdk::DCComponentImplementation* create(const char* name) override;
	const dumisdk::DCComponentImplementation* create(HASHID id) override;
	bool registerTemplate(std::shared_ptr<dumisdk::DCComponentTemplate<dumisdk::DCComponentImplementation>> componentTemplate) override;

};

extern "C" {
	__declspec (dllexport) dumisdk::IDCLibrary* LoadLibrary();
}


