//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#include "MqttClientManager.hpp"

namespace PxceTcs { namespace MqttClient
{
using namespace PxceTcs::Mqtt;

int32 MqttClientManager::Connect(int32 clientId, const ConnectOptions& opts)
{
    int32 result = 0;

    try
    {
        // Specify connection options, including will and ssl options.
        mqtt::connect_options mqtt_opts;
        mqtt_opts.set_keep_alive_interval(opts.keepAliveInterval);
        mqtt_opts.set_connect_timeout(opts.connectTimeout);
        if (strlen(opts.userName.CStr()) > 0)
            mqtt_opts.set_user_name(opts.userName.CStr());
        if (strlen(opts.password.CStr()) > 0)
            mqtt_opts.set_password(opts.password.CStr());
        mqtt_opts.set_max_inflight(opts.maxInflight);
        mqtt_opts.set_max_inflight(opts.maxInflight);
        mqtt_opts.set_clean_session(opts.isCleanSession);
        // TODO: Implement server list
        mqtt_opts.set_mqtt_version(opts.mqttVersion);
        mqtt_opts.set_automatic_reconnect(opts.minRetryInterval, opts.maxRetryInterval);
        mqtt_opts.set_automatic_reconnect(opts.automaticReconnect);

        mqtt::will_options mqtt_will_opts;
        if (strlen(opts.willOptions.topic.CStr()) > 0)
            mqtt_will_opts.set_topic(opts.willOptions.topic.CStr());
        if (strlen(opts.willOptions.payload.CStr()) > 0)
            mqtt_will_opts.set_payload((std::string)opts.willOptions.payload.CStr());
        mqtt_will_opts.set_qos(opts.willOptions.qos);
        mqtt_will_opts.set_retained(opts.willOptions.retained);
        mqtt_opts.set_will(mqtt_will_opts);

        mqtt::ssl_options mqtt_ssl_opts;
        if (strlen(opts.sslOptions.trustStore.CStr()) > 0)
            mqtt_ssl_opts.set_trust_store(opts.sslOptions.trustStore.CStr());
        if (strlen(opts.sslOptions.keyStore.CStr()) > 0)
            mqtt_ssl_opts.set_key_store(opts.sslOptions.keyStore.CStr());
        if (strlen(opts.sslOptions.privateKey.CStr()) > 0)
            mqtt_ssl_opts.set_private_key(opts.sslOptions.privateKey.CStr());
        if (strlen(opts.sslOptions.privateKeyPassword.CStr()) > 0)
            mqtt_ssl_opts.set_private_key_password(opts.sslOptions.privateKeyPassword.CStr());
        if (strlen(opts.sslOptions.enabledCipherSuites.CStr()) > 0)
            mqtt_ssl_opts.set_enabled_cipher_suites(opts.sslOptions.enabledCipherSuites.CStr());
        mqtt_ssl_opts.set_enable_server_cert_auth(opts.sslOptions.enableServerCertAuth);
        mqtt_opts.set_ssl(mqtt_ssl_opts);

        this->log.Info("Connecting to MQTT server");
        this->client->Connect((Client::client_id_t)clientId, mqtt_opts);
        this->log.Info("Connected");
    }
    catch(...)
    {
        this->log.Error("Exception in operation: Connect({0}, ConnectOptions)", clientId);
        HandleException();
        result = -1;
    }
    return result;
}

int32 MqttClientManager::CreateClient(const RscString<512>& serverURI, const RscString<512>& clientId)
{
    int32 result = 0;

    try
    {
        result = (int32)this->client->CreateClient(serverURI.ToString(), clientId.ToString());
    }
    catch(...)
    {
        this->log.Error("Exception in operation: CreateClient({0}, {1})", serverURI, clientId);
        HandleException();
        result = -1;
    }
    return result;
}

int32 MqttClientManager::DestroyClient(int32 clientId)
{
    int32 result = 0;

    try
    {
        this->client->DestroyClient((Client::client_id_t)clientId);
    }
    catch(...)
    {
        this->log.Error("Exception in operation: DestroyClient({0})", clientId);
        HandleException();
        result = -1;
    }
    return result;
}

int32 MqttClientManager::Disconnect(int32 clientId, int32 timeoutMS)
{
    int32 result = 0;

    try
    {
        this->client->Disconnect((Client::client_id_t)clientId, timeoutMS);
    }
    catch(...)
    {
        this->log.Error("Exception in operation: Disconnect({0}, {1})", clientId, timeoutMS);
        HandleException();
        result = -1;
    }
    return result;
}

int32 MqttClientManager::GetTimeout(int32 clientId)
{
    int32 result = 0;

    try
    {
        result = this->client->GetTimeout((Client::client_id_t)clientId);
    }
    catch(...)
    {
        this->log.Error("Exception in operation: GetTimeout({0})", clientId);
        HandleException();
        result = -1;
    }
    return result;
}

boolean MqttClientManager::IsConnected(int32 clientId)
{
    boolean result = false;

    try
    {
        result = this->client->IsConnected((Client::client_id_t)clientId);
    }
    catch(...)
    {
        this->log.Error("Exception in operation: IsConnected({0})", clientId);
        HandleException();
        result = false;
    }
    return result;
}

int32 MqttClientManager::Publish(int32 clientId, const RscString<512>& topic, RscVariant<512> payload, uint32 length, int32 qos, boolean retained)
{
    int32 result = 0;

    // Declare MQTT variables
    const char * mqtt_topic = topic.CStr();
    const byte * mqtt_payload = payload.GetDataAddress();

    try
    {
        this->client->Publish((Client::client_id_t)clientId, mqtt_topic, mqtt_payload, length, qos, retained);
    }
    catch(...)
    {
        this->log.Error("Exception in operation: Publish({0}, {1}, RscVariant, {2}, {3}, {4})", clientId, topic, length, qos, retained);
        HandleException();
        result = -1;
    }
    return result;
}

int32 MqttClientManager::Reconnect(int32 clientId)
{
    int32 result = 0;

    try
    {
        this->client->Reconnect((Client::client_id_t)clientId);
    }
    catch(...)
    {
        this->log.Error("Exception in operation: Reconnect({0})", clientId);
        HandleException();
        result = -1;
    }
    return result;
}

int32 MqttClientManager::SetTimeout(int32 clientId, int32 timeoutMS)
{
    int32 result = 0;

    try
    {
        this->client->SetTimeout((Client::client_id_t)clientId, timeoutMS);
    }
    catch(...)
    {
        this->log.Error("Exception in operation: SetTimeout({0}, {1})", clientId, timeoutMS);
        HandleException();
        result = -1;
    }
    return result;
}

int32 MqttClientManager::Subscribe(int32 clientId, const RscString<512>& topicFilter)
{
    int32 result = 0;

    try
    {
        this->client->Subscribe((Client::client_id_t)clientId, topicFilter.CStr());
    }
    catch(...)
    {
        this->log.Error("Exception in operation: Subscribe({0})", clientId, topicFilter);
        HandleException();
        result = -1;
    }
    return result;
}

int32 MqttClientManager::TryConsumeMessage(int32 clientId, Message& msg)
{
    int32 result = -1;

    mqtt::const_message_ptr mqtt_msg = nullptr;
    bool got_message;

    try
    {
        this->log.Info("** About to call client->TryConsumeMessage");
        got_message = this->client->TryConsumeMessage((Client::client_id_t)clientId, &mqtt_msg);
        if (got_message)
        {
            this->log.Info("** Got message.");
            this->log.Info("** Is mqtt_msg null? {0}", (mqtt_msg==nullptr) );
            this->log.Info("** Getting topic");
            this->log.Info("** mqtt_msg->get_topic() = {0}", mqtt_msg->get_topic());
            this->log.Info("** About to cast topic to RscString");
            // TODO: CHECK FOR NULL POINTER?
            // Copy the mqtt topic
            msg.topic = RscString<512>(mqtt_msg->get_topic());

            this->log.Info("** About to copy payload");
            // Copy the mqtt payload
            const mqtt::binary mqtt_payload = mqtt_msg->get_payload();
            this->log.Info("** Payload size = {0}", mqtt_payload.size());
            msg.payload = RscVariant<512>();
            msg.payload.SetType(RscType::Stream);
            memcpy(msg.payload.GetDataAddress(), mqtt_msg->get_payload_ref().data(), mqtt_payload.size());

            // Copy the remaining message information
            msg.len = mqtt_payload.size();
            msg.qos = mqtt_msg->get_qos();
            msg.duplicate = mqtt_msg->is_duplicate();
            msg.retained = mqtt_msg->is_retained();

            result = 1;  // Got a message
        }
        else
        {
            this->log.Info("** No message");
            result = 0;  // No message
        }

    }
    catch(...)
    {
        this->log.Error("Exception in operation: TryConsumeMessage({0}, Message &)", clientId);
        HandleException();
        result = -1;  // Error
    }
    return result;
}

int32 MqttClientManager::Unsubscribe(int32 clientId, const RscString<512>& topicFilter)
{
    int32 result = 0;

    try
    {
        this->client->UnSubscribe((Client::client_id_t)clientId, topicFilter.CStr());
    }
    catch(...)
    {
        this->log.Error("Exception in operation: UnSubscribe({0})", clientId, topicFilter);
        HandleException();
        result = -1;
    }
    return result;
}

// Standard exception handler for all operations
void MqttClientManager::HandleException()
{
    try
    {
        throw;
    }
    catch(const std::out_of_range& e)
    {
        this->log.Error("{0} out of range. Cannot find a client with this ID.", e.what());
    }
    catch(const mqtt::exception& e)
    {
        this->log.Error("{0}", e.what());
    }
    catch(const std::exception& e)
    {
        this->log.Error("{0}", e.what());
    }
    catch(...)
    {
    }
}

}} // end of namespace PxceTcs.MqttClient
