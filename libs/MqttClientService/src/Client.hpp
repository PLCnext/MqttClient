//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#pragma once
#include <unordered_map>
#include "mqtt/client.h"

namespace PxceTcs { namespace Mqtt
{

class Client
{
public: // typedefs
   typedef std::uint16_t client_id_t;

public: // construction/destruction
    Client();
    virtual ~Client() = default;

public: // operations
    void Connect(Client::client_id_t clientId);
    void Connect(Client::client_id_t clientId, mqtt::connect_options opts);
    client_id_t CreateClient(const std::string serverURI, const std::string clientId);
    void DestroyClient(Client::client_id_t clientId);
    void Disconnect(client_id_t client_id);
    void Disconnect(client_id_t client_id, int timeoutMS);
    bool IsConnected(Client::client_id_t clientId);
    void Publish(client_id_t client_id, mqtt::string_ref top, const void * payload, std::size_t n, int qos, bool retained);
    void Reconnect(Client::client_id_t clientId);
    void Subscribe(Client::client_id_t clientId, const std::string & topicFilter);
    bool TryConsumeMessage(Client::client_id_t clientId, mqtt::const_message_ptr * msg);
    void UnSubscribe(Client::client_id_t clientId, const std::string & topicFilter);

private: // methods

private: // fields
    std::unordered_map<client_id_t, mqtt::client_ptr> clients;  // The container for MQTT client objects
};

}} // end of namespace PxceTcs.Mqtt
