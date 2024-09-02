#pragma once

#include "dtypes.h"
#include "defs.h"
#include "dumiexcept.h"
#include "environment.h"

#include <memory>
#include <exception>

#pragma region IDC_Basic

namespace dumisdk {

	class IDCLibrary;
	class DCComponentDefinition; class ComponentInfo;

#pragma region Basic
	class DCDefinition {
	protected:
		DCDefinition(DCDefinition& definition);
		DCDefinition(HASHID id, HASHID parentId);
		DCDefinition();
	public:
		virtual ~DCDefinition() = default;
		const HASHID id;
		const HASHID parentId;
	};

	class DCImplementation : extend DCDefinition {
	protected:
		DCImplementation(HASHID id, HASHID parentId);
		DCImplementation();
	public:
		virtual ~DCImplementation() = default;
		virtual void update() = 0;
	};

	template<typename T>
	class DCInterface : extend DCDefinition {
		static_assert(std::is_base_of<DCImplementation, T>::value, "T must extend DCImplementation");
	protected:
		DCInterface(HASHID id, HASHID parentId) : DCDefinition(id, parentId) {}
	public:
		virtual ~DCInterface() = default;
		virtual T* create() = 0;
	};

#pragma endregion

#pragma region fields

	class DCFieldDefinition : extend DCDefinition {
	protected:
	public:
	};

	//template<typename T>
	class DCFieldImplementation : extend DCImplementation, extend DCFieldDefinition {
	protected:
		//DCType<T> _value;
	public:
		//virtual void set(DCType<T>& value){
		//	
		//}
		//virtual DCType<T>& get(){
		//	return _value;
		//}
	};

	template<typename T>
	class DCFieldTemplate : extend DCInterface<T>, extend DCFieldDefinition {
	static_assert(std::is_base_of<DCFieldImplementation, T>::value, "T must extend DCFieldImplementation");
	protected:
	using DCInterface<T>::DCInterface;
	using DCFieldDefinition::DCFieldDefinition;
	public:
	DCFieldTemplate(){

	}
	virtual ~DCFieldTemplate() = default;
	};

#pragma region ConfigField


#pragma endregion

#pragma endregion

#pragma region Component
	class DCComponentDefinition : extend DCDefinition {
	protected:
		DCComponentDefinition(HASHID id, HASHID parentId,
			DCFieldDefinition* fields
			);
		DCComponentDefinition();
	public:
		virtual ~DCComponentDefinition() = default;
		const DCFieldDefinition* fields;
	};

	template<typename T>
	class DCComponentTemplate;

	class DCComponentImplementation : extend DCImplementation, extend DCComponentDefinition {
	protected:
		using DCImplementation::DCImplementation;
		using DCComponentDefinition::DCComponentDefinition;
		DCComponentImplementation();
	public:
		DCComponentImplementation(DCComponentDefinition& definition);
		virtual ~DCComponentImplementation() = default;
	};

	struct ComponentInfo {
		const char* name;
		const char* description;
		APPSID libraryId;
		ComponentInfo(const char* name, const char* description, APPSID libraryId);

	};

	template<typename T>
	class DCComponentTemplate : extend DCInterface<T>, extend DCComponentDefinition, public ComponentInfo {
		static_assert(std::is_base_of<DCComponentImplementation, T>::value, "T must extend DCComponentImplementation");
	protected:
		using DCInterface<T>::DCInterface;
		using DCComponentDefinition::DCComponentDefinition;
	public:
		DCComponentTemplate(const DCFieldTemplate<DCFieldImplementation>* fields):
			fields(fields)
		{
		
		}
		virtual ~DCComponentTemplate() = default;
		
		const DCFieldTemplate<DCFieldImplementation>* fields; 
	};

#pragma endregion

#pragma region DC_LIBRARY

	struct LibraryInfo {
		const char* name;
		const char* version;
		const char* author;
		const char* repository;
		const char* description;
		const APPSID libraryId;
	public:
		LibraryInfo(const char* name, const char* version, const char* author,
			const char* repository, const char* description, APPSID libraryId);
	};

	class IDCLibrary : public LibraryInfo {
	public:

	protected:
		IDCLibrary(const char* name, const char* version, const char* author,
			const char* repository, const char* description);
		virtual const std::vector<ComponentInfo> manifest() = 0;
		virtual const DCComponentImplementation* create(const char* name) = 0;
		virtual const DCComponentImplementation* create(HASHID id) = 0;
		virtual bool registerTemplate(std::shared_ptr<DCComponentTemplate<DCComponentImplementation>>
			componentTemplate) = 0;

		optmap<HASHID, std::shared_ptr<DCComponentTemplate<DCComponentImplementation>>> _templates;
	public:
		virtual ~IDCLibrary() = default;
	};

#pragma endregion

}

#define DUMIEXPORT EXPORT dumisdk::IDCLibrary* 
#define DUMIIMPORT IMPORT dumisdk::IDCLibrary*
