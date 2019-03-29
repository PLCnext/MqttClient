# PLCnext Technology - MQTT Client Service

[![Feature Requests](https://img.shields.io/github/issues/PLCnext/MqttClient/feature-request.svg)](https://github.com/PLCnext/MqttClient/issues?q=is%3Aopen+is%3Aissue+label%3Afeature-request+sort%3Areactions-%2B1-desc)
[![Bugs](https://img.shields.io/github/issues/PLCnext/MqttClient/bug.svg)](https://github.com/PLCnext/MqttClient/issues?utf8=✓&q=is%3Aissue+is%3Aopen+label%3Abug)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Web](https://img.shields.io/badge/PLCnext-Website-blue.svg)](https://www.phoenixcontact.com/plcnext)
[![Community](https://img.shields.io/badge/PLCnext-Community-blue.svg)](https://www.plcnext-community.net)

| Date       | Version | Author       |
|------------|---------|--------------|
| 29.03.2019 | 0.0.1   | Martin Boers |


## Description

MQTT Client is a PLCnext Technology component that allows PLCnext Control applications to use MQTT Client functions through a Remote Service Call (RSC) interface.

## Contributing

Contributions to this project are welcome.

## Building from source

Building from source requires the PLCnext SDK for your target. It is strongly recommended that you use the PLCnext Command Line Interface (CLI) to install and manage PLCnext SDKs on your host. Assistance with this is available from the PLCnext Community.

An example of a build session is as follows:

```cmake
$ git clone https://github.com/PLCnext/MqttClient
$ cd MqttClient
$ cmake -G "Ninja" 
> -DCMAKE_TOOLCHAIN_FILE=/opt/pxc/sdk/AXCF2152/2019.3/toolchain.cmake
> -DBUILD_TESTING=OFF
> -DUSE_ARP_DEVICE=ON
> -DCMAKE_STAGING_PREFIX=/home/tcs-user/Documents/projects/MqttClient/bin/axcf2152
> -DCMAKE_INSTALL_PREFIX=/usr/local
> -DCMAKE_PREFIX_PATH=/home/tcs-user/Documents/projects/MqttClient/external/deploy/axcf2152
> -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
> -DARP_TOOLCHAIN_ROOT=/opt/pxc/sdk/AXCF2152/2019.3
> -DARP_DEVICE=AXCF2152 "-DARP_DEVICE_VERSION=2019.3 (19.3.0.18161)"
> -S . -B ./build/axcf2152-2019.3
$ cmake --build /home/tcs-user/Documents/projects/MqttClient/build/axcf2152-2019.3 --config Debug --target all -- -j 3
$ cmake --build /home/tcs-user/Documents/projects/MqttClient/build/axcf2152-2019.3 --config Debug --target install -- -j 3
```

## Installing

Copy the contents of `external/deploy/axcf2152` to `/usr/local` on the target.

Copy `libPxceTcs.Mqtt.Client.so` to `/usr/local/lib` on the target.

Copy `libs/MqttClient.acf.config` to `/opt/plcnext/projects/Default` on the target.

Reboot the target.

## Usage

Basic steps for using the MQTT Client RSC service in a PLCnext C++ component:

- Include `Arp/System/Rsc/ServiceManager.hpp` and `IMqttClientService.hpp`
- Declare a variable of type `PxceTcs::MqttClient::Services::IMqttClientService::Ptr`
- In the component's `SubscribeServices` method, call `ServiceManager::GetService<IMqttClientService>("PxceTcs")`, and assign the result to the pointer variable.
- Using the assigned pointer, call the `CreateClient` method to create an MQTT Client.

The complete set of available MQTT Client methods are documented ... (here).

The `CreateClient` method must always be called before any other MQTT operation. This method returns a unique ID that must be used in all other method calls. In this way, it is possible to create multiple MQTT Client instances.

The `DestroyClient` method should always be called when an MQTT client instance is no longer required, for example during component shutdown.

The MQTT Client service wraps parts of the open-source Paho MQTT C++ library (specifically, some methods of the Paho `client` class), so users the documentation for the Paho library will also be useful in understanding the behaviour of this service.

Client-side message persistence has not been implemented in this version.

## Example

One example of a PLCnext Component that uses the MQTT Client service is the [MQTT GDS Connector](https://github.com/plcnext/MqttGdsConnector) which, together with this project, was used to create the [MQTT Client Function Extension app](https://www.plcnextstore.com/#/) in the [PLCnext Store](https://www.plcnextstore.com/#/).

## Known issues
[![Bugs](https://img.shields.io/github/issues/PLCnext/MqttClient/bug.svg)](https://github.com/PLCnext/MqttClient/issues?utf8=✓&q=is%3Aissue+is%3Aopen+label%3Abug)

-----------
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
/ Licensed under the MIT. See LICENSE file in the project root for full license information.
-----------

This code requires:

1. [The Paho C++ library](https://github.com/eclipse/paho.mqtt.cpp) Copyright (c) 2013-2017 Frank Pagliughi.

   All rights reserved. This program and the accompanying materials are made available under the terms of the Eclipse Public License v1.0 which accompanies this distribution, and is available at http://www.eclipse.org/legal/epl-v10.html

1. [The Paho C library](https://github.com/eclipse/paho.mqtt.c) by Ian Craggs Copyright (c) 2013-2018, IBM Corp.

   All rights reserved. This program and the accompanying materials are made available under the terms of the Eclipse Public License v1.0 and Eclipse Distribution License v1.0 which accompany this distribution.

   The Eclipse Public License is available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse Distribution License is available at http://www.eclipse.org/org/documents/edl-v10.php.
