#!/bin/bash
#//
#// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
#// Licensed under the MIT. See LICENSE file in the project root for full license information.
#// SPDX-License-Identifier: MIT
#//
while getopts t:a:n: option
do
case "${option}"
in
t) TOOLCHAIN=${OPTARG};;
a) ARPVERSION=${OPTARG};;
n) TARGETNAME=${OPTARG};;
esac
done

echo "Build Paho Mqtt C"
./build-paho.mqtt.c.sh -t "${TOOLCHAIN}" -a "${ARPVERSION}" -n "${TARGETNAME}"

echo "Build Paho Mqtt Cpp"
./build-paho.mqtt.cpp.sh -t "${TOOLCHAIN}" -a "${ARPVERSION}" -n "${TARGETNAME}"

echo "Build MqttClient"
./build-component.sh -t "${TOOLCHAIN}" -a "${ARPVERSION}" -n "${TARGETNAME}"
