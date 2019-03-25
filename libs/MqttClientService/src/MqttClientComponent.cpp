//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#include "MqttClientComponent.hpp"
#include "Arp/System/Rsc/ServiceManager.hpp"
#include "services/IMqttClientService.hpp"
#include "services/MqttClientServiceFactory.hpp"
#include "MqttClientManager.hpp"
#include "MQTTClient.h"  // Needed only for initialisation.

namespace PxceTcs { namespace MqttClient
{

void MqttClientComponent::Initialize()
{
    // subscribe events from the event system (Nm) here

    // Initialise the underlying MQTT libraries.
    // Without this, other SSL/TLS connections (e.g. Proficloud) will not work correctly.
    MQTTAsync_init_options inits = MQTTAsync_init_options_initializer;
    MQTTAsync_global_init(&inits);

    MQTTClient_init_options initsClient = MQTTClient_init_options_initializer;
    MQTTClient_global_init(&initsClient);

    // Create the MQTT Client Manager singleton
    MqttClientManager::CreateInstance();
}

void MqttClientComponent::PublishServices()
{
    this->log.Info("Publishing MQTT Client service");
    // publish the services of this component here
    using namespace Arp::System::Rsc;
    using namespace MqttClient::Services;
    ServiceManager::PublishService<IMqttClientService, MqttClientServiceFactory>("PxceTcs");
    this->log.Info("Published MQTT Client service");
}

void MqttClientComponent::Dispose()
{
    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()

    MqttClientManager::DisposeInstance();
}

}} // end of namespace PxceTcs.MqttClient
