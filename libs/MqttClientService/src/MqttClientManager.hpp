//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Commons/Logging.h"
#include "Arp/System/Rsc/Services/RscString.hxx"
#include "Arp/System/Rsc/Services/RscVariant.hxx"
#include "services/Message.hpp"
#include "services/ConnectOptions.hpp"
#include "Client.hpp"

namespace PxceTcs { namespace MqttClient
{

using namespace Arp;
using namespace Arp::System::Rsc::Services;
using namespace Services;

class MqttClientManager : public Singleton<MqttClientManager>
, private Loggable<MqttClientManager>
{
public: // typedefs

public: // construction/destruction
    /// <summary>Constructs an <see cref="MqttClientManager" /> instance.</summary>
    MqttClientManager(void) = default;
    /// <summary>Copy constructor.</summary>
    MqttClientManager(const MqttClientManager& arg) = default;
    /// <summary>Assignment operator.</summary>
    MqttClientManager& operator=(const MqttClientManager& arg) = default;
    /// <summary>Destructs this instance and frees all resources.</summary>
    ~MqttClientManager(void) = default;

public: // operators

public: // static operations

public: // setter/getter operations

public: // operations
//    int32   Connect(int32 clientId);
    int32   Connect(int32 clientId, const ConnectOptions& opts);
    int32   CreateClient(const RscString<512>& serverURI, const RscString<512>& clientId);
    int32   DestroyClient(int32 clientId);
//    int32   Disconnect(int32 clientId)override;
    int32   Disconnect(int32 clientId, int32 timeoutMS);
    int32   GetTimeout(int32 clientId);
    boolean IsConnected(int32 clientId);
    int32   Publish(int32 clientId, const RscString<512>& topic, RscVariant<512> payload, uint32 length, int32 qos, boolean retained);
    int32   Reconnect(int32 clientId);
    int32   SetTimeout(int32 clientId, int32 timeoutMS);
    int32   Subscribe(int32 clientId, const RscString<512>& topicFilter);
    int32   TryConsumeMessage(int32 clientId, Message& msg);
    int32   Unsubscribe(int32 clientId, const RscString<512>& topicFilter);

protected: // operations

private: // static methods

private: // methods
    void   HandleException();

private: // fields
    std::unique_ptr<Mqtt::Client> client = std::make_unique<Mqtt::Client>();

private: // static fields

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class MqttClientManager

}} // end of namespace PxceTcs.MqttClient
