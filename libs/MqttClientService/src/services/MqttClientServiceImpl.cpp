//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#include "MqttClientServiceImpl.hpp"
#include "MqttClientManager.hpp"

namespace PxceTcs { namespace MqttClient { namespace Services
{

// int32 MqttClientServiceImpl::Connect(int32 clientId)
// {
//     int32 result = 0;
//     // Service method implementation
//     result = MqttClientManager::GetInstance().Connect(clientId);
//     return result;
// }

int32 MqttClientServiceImpl::Connect(int32 clientId, const ConnectOptions& opts)
{
    int32 result = 0;
    // Service method implementation
    result = MqttClientManager::GetInstance().Connect(clientId, opts);
    return result;
}

int32 MqttClientServiceImpl::CreateClient(const RscString<512>& serverURI, const RscString<512>& clientId)
{
    int32 result = 0;
    // Service method implementation
    result = MqttClientManager::GetInstance().CreateClient(serverURI, clientId);
    return result;
}

int32 MqttClientServiceImpl::DestroyClient(int32 clientId)
{
    int32 result = 0;
    // Service method implementation
    result = MqttClientManager::GetInstance().DestroyClient(clientId);
    return result;
}

// int32 MqttClientServiceImpl::Disconnect(int32 clientId)
// {
//     int32 result = 0;
//     // Service method implementation
//     result = MqttClientManager::GetInstance().Disconnect(clientId);
//     return result;
// }

int32 MqttClientServiceImpl::Disconnect(int32 clientId, int32 timeoutMS)
{
    int32 result = 0;
    // Service method implementation
    result = MqttClientManager::GetInstance().Disconnect(clientId, timeoutMS);
    return result;
}

boolean MqttClientServiceImpl::IsConnected(int32 clientId)
{
    boolean result = false;
    // Service method implementation
    result = MqttClientManager::GetInstance().IsConnected(clientId);
    return result;
}

int32 MqttClientServiceImpl::Publish(int32 clientId, const RscString<512>& topic, RscVariant<512> payload, uint32 length, int32 qos, boolean retained)
{
    int32 result = 0;
    // Service method implementation
    result = MqttClientManager::GetInstance().Publish(clientId, topic, payload, length, qos, retained);
    return result;
}

int32 MqttClientServiceImpl::Reconnect(int32 clientId)
{
    int32 result = 0;
    // Service method implementation
    result = MqttClientManager::GetInstance().Reconnect(clientId);
    return result;
}

int32 MqttClientServiceImpl::Subscribe(int32 clientId, const RscString<512>& topicFilter)
{
    int32 result = 0;
    // Service method implementation
    result = MqttClientManager::GetInstance().Subscribe(clientId, topicFilter);
    return result;
}

int32 MqttClientServiceImpl::TryConsumeMessage(int32 clientId, Message& msg)
{
    int32 result = 0;
    // Service method implementation
    result = MqttClientManager::GetInstance().TryConsumeMessage(clientId, msg);
    return result;
}

int32 MqttClientServiceImpl::Unsubscribe(int32 clientId, const RscString<512>& topicFilter)
{
    int32 result = 0;
    // Service method implementation
    result = MqttClientManager::GetInstance().Unsubscribe(clientId, topicFilter);
    return result;
}

}}} // end of namespace PxceTcs::MqttClient::Services
