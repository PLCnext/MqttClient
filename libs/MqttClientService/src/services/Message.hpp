//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Rsc/Services/IRscSerializable.hpp"
#include "Arp/System/Rsc/Services/RscReader.hpp"
#include "Arp/System/Rsc/Services/RscString.hxx"
#include "Arp/System/Rsc/Services/RscVariant.hxx"
#include "Arp/System/Rsc/Services/RscWriter.hpp"

// DO NOT MODIFY THIS FILE, THIS FILE IS AUTOGENERATED

namespace PxceTcs { namespace MqttClient { namespace Services
{

using namespace Arp;
using namespace Arp::System::Rsc::Services;

/// <summary>
/// An MQTT message holds everything required for an MQTT PUBLISH message.
/// This holds the message payload, topic string, and all the additional meta-data for an MQTT message.
/// </summary>
struct Message : public IRscSerializable
{
    /// <summary>
    /// The message topic.
    /// </summary>
    RscString<512>  topic;

    /// <summary>
    /// The message payload, truncated to 512 bytes if necessary.
    /// </summary>
    RscVariant<512> payload;

    /// <summary>
    /// The number of bytes in the payload.
    /// </summary>
    int32           len = 0;

    /// <summary>
    /// The quality of service for the message.
    /// </summary>
    int32           qos = 0;

    /// <summary>
    /// Whether this message might be a duplicate of one which has already been received.
    /// </summary>
    boolean         duplicate = false;

    /// <summary>
    /// Whether the message should be retained by the broker.
    /// </summary>
    boolean         retained = false;

    void Serialize(RscWriter& writer)const override
    {
        writer.Write(this->topic);
        writer.Write(this->payload);
        writer.Write(this->len);
        writer.Write(this->qos);
        writer.Write(this->duplicate);
        writer.Write(this->retained);
    }

    void Deserialize(RscReader& reader)override
    {
        reader.Read(this->topic);
        reader.Read(this->payload);
        reader.Read(this->len);
        reader.Read(this->qos);
        reader.Read(this->duplicate);
        reader.Read(this->retained);
    }

    static size_t GetFieldCount(void)
    {
        return 6;
    }
};

}}} // end of namespace PxceTcs::MqttClient::Services
