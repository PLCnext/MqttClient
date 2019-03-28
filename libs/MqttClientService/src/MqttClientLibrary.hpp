//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Core/AppDomain.hpp"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Core/Library.h"
#include "Arp/System/Acf/LibraryBase.hpp"

namespace PxceTcs { namespace MqttClient
{

using namespace Arp::System::Acf;

class MqttClientLibrary : public LibraryBase, public Arp::Singleton<MqttClientLibrary>
{
public: // typedefs
    typedef Singleton<MqttClientLibrary> SingletonBase;

public: // construction/destruction
    MqttClientLibrary(Arp::AppDomain& appDomain);
    virtual ~MqttClientLibrary() = default;

public: // static operations (called through reflection)
    static void Main(Arp::AppDomain& appDomain);

private: // deleted methods
    MqttClientLibrary(const MqttClientLibrary& arg) = delete;
    MqttClientLibrary& operator= (const MqttClientLibrary& arg) = delete;
};

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(Arp::AppDomain& appDomain);

///////////////////////////////////////////////////////////////////////////////
// inline methods of class MqttClientLibrary

}} // end of namespace PxceTcs.MqttClient
