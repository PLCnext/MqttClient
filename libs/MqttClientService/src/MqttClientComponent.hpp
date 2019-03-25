//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "MqttClientLibrary.hpp"
#include "Arp/System/Commons/Logging.h"

namespace PxceTcs { namespace MqttClient
{

using namespace Arp;
using namespace Arp::System::Acf;

//#component
class MqttClientComponent
: public ComponentBase
, private Loggable<MqttClientComponent>
{
public: // typedefs

public: // construction/destruction
    MqttClientComponent(IApplication& application, const String& name);
    virtual ~MqttClientComponent() = default;

public: // IComponent operations
    void Initialize() override;
    void PublishServices() override;
    void Dispose() override;

private: // methods
    MqttClientComponent(const MqttClientComponent& arg) = delete;
    MqttClientComponent& operator= (const MqttClientComponent& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields

public: /* Ports
           =====
           Ports are defined in the following way:
           //#port
           //#attributes(Input|Retain)
           //#name(NameOfPort)
           bool portField;

           The attributes comment define the port attributes and is optional.
           The name comment defines the name of the port and is optional. Default is the name of the field
        */
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class MqttClientComponent
inline MqttClientComponent::MqttClientComponent(IApplication& application, const String& name)
: ComponentBase(application, ::PxceTcs::MqttClient::MqttClientLibrary::GetInstance(), name, ComponentCategory::Custom, 100001, true)
{
}

inline IComponent::Ptr MqttClientComponent::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new MqttClientComponent(application, name));
}

}} // end of namespace PxceTcs.MqttClient
