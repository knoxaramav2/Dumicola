#pragma once

#include "component_interface.hpp"

// #pragma region DC_Basic

// struct DCBase: public virtual IDCBase{
//     virtual ~DCBase() = default;
// };

// struct DCTemplateBase: public virtual DCBase{
//     virtual ~DCTemplateBase() = default;
// };

// struct DCObjectBase: public virtual DCBase, public virtual IDCObject{
//     virtual ~DCObjectBase() = default;
// };

// #pragma endregion

// #pragma DC_Nodes

// struct DCIOBase: public virtual DCBase, public virtual IDCIONodeDefinition{
//     virtual ~DCIOBase() = default;
// };

// struct DCViewBase: public virtual DCIOBase, public virtual IDCViewDefinition{
//     virtual ~DCViewBase() = default;
// };

// struct DCView: public virtual DCViewBase, public virtual IDCView{
//     virtual ~DCView() = default;
// };

// struct DCInputBase: public virtual DCIOBase, public virtual IDCInputDefinition{
//     virtual ~DCInputBase() = default;
// };

// struct DCInput: public virtual DCInputBase, public virtual IDCInput{
//     virtual ~DCInput() = default;
// };

// struct DCInputTemplate: 
//     public virtual DCInputBase, public virtual IDCTemplate<IDCInput>, public virtual IDCInputTemplate{
//     virtual ~DCInputTemplate() = default;
// };

// struct DCOutputBase: public virtual DCIOBase, public virtual IDCOutputDefinition{
//     virtual ~DCOutputBase() = default;
// };

// struct DCOutput: public virtual DCOutputBase, public virtual IDCOutput{
//     virtual ~DCOutput() = default;
// };

// struct DCOutputTemplate:
//     public virtual DCOutputBase, public virtual IDCTemplate<IDCOutput>, public virtual IDCOutputTemplate{
//     virtual ~DCOutputTemplate() = default;
// };

// #pragma endregion

// #pragma region DC_Component

// template<
//     typename TInput, typename TOutput,
//     typename TView, typename TField>
// struct DCComponentBase: public virtual DCBase, public virtual IDCComponentDefinition<TInput, TOutput, TView, TField>{
//     virtual ~DCComponentBase() = default;
// };

// template<typename T>
// struct DCComponentTemplate:
//     public virtual DCComponentBase<IDCInputTemplate, IDCOutputTemplate, IDCViewTemplate, IDCFieldTemplate>,
//     public virtual IDCComponentTemplate<T>{
//     virtual ~DCComponentTemplate() = default;
// };

// struct DCComponent: 
//     public virtual DCComponentBase<IDCInput, IDCOutput, IDCView, IDCField>,
//     public virtual IDCComponent{
//     virtual ~DCComponent() = default;
// };

// #pragma endregion

// #pragma region DC_Monitor

// template<typename T>
// struct DCMonitorTemplate: public virtual DCComponentTemplate<IDCMonitor>,
//     public virtual IDCMonitorTemplate{
//     virtual ~DCMonitorTemplate() = default;
// };

// struct DCMonitor: public virtual DCComponent, public virtual IDCMonitor{
//     virtual ~DCMonitor() = default;
// };

// #pragma endregion

// #pragma region Provider

// template<typename T>
// struct DCProviderTemplate: public virtual DCComponentTemplate<IDCProvider>,
//     public virtual IDCProviderTemplate{
//     virtual ~DCProviderTemplate() = default;
// };

// struct DCProvider: public virtual DCComponent, public virtual IDCProvider{
//     virtual ~DCProvider() = default;
// };

// #pragma endregion

// #pragma region DC_Aux

// struct DCFieldBase: public virtual DCBase, public virtual IDCFieldDefinition{
//     virtual ~DCFieldBase() = default;
// };

// struct DCFieldTemplate: public virtual DCFieldBase, virtual IDCTemplate<IDCField>, public virtual IDCFieldTemplate{
//     virtual ~DCFieldTemplate() = default;
// };

// struct DCField: public virtual DCFieldBase, public virtual IDCField{
//     virtual ~DCField() = default;
// };


// struct DCConfigFieldBase: public virtual DCBase, public virtual IDCConfigFieldDefintiion{
//     virtual ~DCConfigFieldBase() = default;
// };

// struct DCConfigFieldTemplate: public virtual DCConfigFieldBase, virtual IDCTemplate<IDCConfigField>, public virtual IDCConfigFieldTemplate{
//     virtual ~DCConfigFieldTemplate() = default;
// };

// struct DCConfigField: public virtual DCConfigFieldBase, public virtual IDCConfigField{
//     virtual ~DCConfigField() = default;
// };

// #pragma endregion
