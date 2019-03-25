//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#include "MqttClientLibrary.hpp"
#include "Arp/System/Core/CommonTypeName.hxx"
#include "MqttClientComponent.hpp"

namespace PxceTcs { namespace MqttClient
{

MqttClientLibrary::MqttClientLibrary(AppDomain& appDomain)
    : LibraryBase(appDomain, ARP_VERSION_CURRENT)
{
    this->componentFactory.AddFactoryMethod(CommonTypeName<::PxceTcs::MqttClient::MqttClientComponent>(), &::PxceTcs::MqttClient::MqttClientComponent::Create);
}

void MqttClientLibrary::Main(AppDomain& appDomain)
{
    SingletonBase::CreateInstance(appDomain);
}

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain)
{
    MqttClientLibrary::Main(appDomain);
    return  MqttClientLibrary::GetInstance();
}

}} // end of namespace PxceTcs.MqttClient
