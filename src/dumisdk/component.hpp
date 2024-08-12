#pragma once

#include "component_interface.hpp"

#pragma region DC_Basic

struct DCBase: IDCBase{

};

struct DCTemplateBase: DCBase{

};

struct DCObjectBase: DCBase, IDCObject{

};

#pragma endregion

#pragma DC_Nodes

struct DCIOBase: DCBase, IDCIONodeDefinition{

};

struct DCViewBase: DCIOBase, IDCViewDefinition{

};

struct DCView: DCViewBase, IDCView{

};

struct DCInputBase: DCIOBase, IDCInputDefinition{

};

struct DCInput: DCInputBase, IDCInput{

};

struct DCInputTemplate: 
    DCInputBase, IDCTemplate<IDCInput>, IDCInputTemplate{

};

struct DCOutputBase: DCIOBase, IDCOutputDefinition{

};

struct DCOutput: DCOutputBase, IDCOutput{

};

struct DCOutputTemplate:
    DCOutputBase, IDCTemplate<IDCOutput>, IDCOutputTemplate{

};

#pragma endregion

#pragma region DC_Component

template<
    typename TInput, typename TOutput,
    typename TView, typename TField>
struct DCComponentBase: DCBase, IDCComponentDefition<TInput, TOutput, TView, TField>{

};

template<typename T>
struct DCComponentTemplate:
    DCComponentBase<IDCInputTemplate, IDCOutputTemplate, IDCViewTemplate, IDCFieldTemplate>,
    IDCComponentTemplate<T>{

};

struct DCComponent: 
    DCComponentBase<IDCInput, IDCOutput, IDCView, IDCField>,
    IDCComponent{

};

#pragma endregion

#pragma region DC_Monitor

template<typename T>
struct DCMonitorTemplate: DCComponentTemplate<IDCMonitor>,
    IDCMonitorTemplate{

};

struct DCMonitor: DCComponent, IDCMonitor{

};

#pragma endregion

#pragma region Provider

template<typename T>
struct DCProviderTemplate: DCComponentTemplate<IDCProvider>,
    IDCProviderTemplate{

};

struct DCProvider: DCComponent, IDCProvider{

};

#pragma endregion

#pragma region DC_Aux

struct DCFieldBase: DCBase, IDCFieldDefinition{

};

struct DCFieldTemplate: DCFieldBase, IDCTemplate<IDCField>, IDCFieldTemplate{

};

struct DCField: DCFieldBase, IDCField{

};


struct DCConfigFieldBase: DCBase, IDCConfigFieldDefintiion{

};

struct DCConfigFieldTemplate: DCConfigFieldBase, IDCTemplate<IDCConfigField>, IDCConfigFieldTemplate{

};

struct DCConfigField: DCConfigFieldBase, IDCConfigField{

};

#pragma endregion

