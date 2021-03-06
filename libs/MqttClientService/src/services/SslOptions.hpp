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
#include "Arp/System/Rsc/Services/RscWriter.hpp"

// DO NOT MODIFY THIS FILE, THIS FILE IS AUTOGENERATED

namespace PxceTcs { namespace MqttClient { namespace Services
{

using namespace Arp;
using namespace Arp::System::Rsc::Services;

/// <summary>
/// Holds the set of SSL options for connection.
/// </summary>
struct SslOptions : public IRscSerializable
{
    /// <summary>
    /// The filename containing the public digital certificates trusted by the client.
    /// </summary>
    RscString<512> trustStore;

    /// <summary>
    /// The filename containing the public certificate chain of the client.
    /// </summary>
    RscString<512> keyStore;

    /// <summary>
    /// The filename containing the client's private key.
    /// </summary>
    RscString<512> privateKey;

    /// <summary>
    /// The password to load the client's privateKey (if encrypted).
    /// </summary>
    RscString<512> privateKeyPassword;

    /// <summary>
    /// The list of cipher suites that the client will present to the server during the SSL handshake.
    /// </summary>
    RscString<512> enabledCipherSuites;

    /// <summary>
    /// Enable verification of the server certificate.
    /// </summary>
    boolean        enableServerCertAuth = false;

    void Serialize(RscWriter& writer)const override
    {
        writer.Write(this->trustStore);
        writer.Write(this->keyStore);
        writer.Write(this->privateKey);
        writer.Write(this->privateKeyPassword);
        writer.Write(this->enabledCipherSuites);
        writer.Write(this->enableServerCertAuth);
    }

    void Deserialize(RscReader& reader)override
    {
        reader.Read(this->trustStore);
        reader.Read(this->keyStore);
        reader.Read(this->privateKey);
        reader.Read(this->privateKeyPassword);
        reader.Read(this->enabledCipherSuites);
        reader.Read(this->enableServerCertAuth);
    }

    static size_t GetFieldCount(void)
    {
        return 6;
    }
};

}}} // end of namespace PxceTcs::MqttClient::Services
