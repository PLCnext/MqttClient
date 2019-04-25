//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#pragma once
#include "IMqttClientService.hpp"

namespace PxceTcs { namespace MqttClient { namespace Services
{

class MqttClientServiceImpl : public IMqttClientService
{
public: // construction/destruction
    /// <summary>Constructs an <see cref="DemoService" /> instance.</summary>
    MqttClientServiceImpl(void);
    /// <summary>Destructs this instance and frees all resouces.</summary>
    virtual ~MqttClientServiceImpl(void);

public: // IMqttClientService operations
    int32   Connect(int32 clientId, const ConnectOptions& opts)override;
    int32   CreateClient(const RscString<512>& serverURI, const RscString<512>& clientId)override;
    int32   DestroyClient(int32 clientId)override;
    int32   Disconnect(int32 clientId, int32 timeoutMS)override;
    int32   GetTimeout(int32 clientId)override;
    boolean IsConnected(int32 clientId)override;
    int32   Publish(int32 clientId, const RscString<512>& topic, RscVariant<512> payload, uint32 length, int32 qos, boolean retained)override;
    int32   Reconnect(int32 clientId)override;
    int32   SetTimeout(int32 clientId, int32 timeoutMS)override;
    int32   Subscribe(int32 clientId, const RscString<512>& topicFilter)override;
    int32   TryConsumeMessage(int32 clientId, Message& msg)override;
    int32   Unsubscribe(int32 clientId, const RscString<512>& topicFilter)override;

private: // deleted methods (for non-copyable classes)
    MqttClientServiceImpl(const MqttClientServiceImpl& arg) = delete;
    MqttClientServiceImpl& operator=(const MqttClientServiceImpl& arg) = delete;
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class MqttClientServiceImpl
inline MqttClientServiceImpl::MqttClientServiceImpl(void)
{
}

inline MqttClientServiceImpl::~MqttClientServiceImpl(void)
{
}

}}} // end of namespace PxceTcs::MqttClient::Services
