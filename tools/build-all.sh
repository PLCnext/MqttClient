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


# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

echo "Build Paho Mqtt C"
$DIR/build-paho.mqtt.c.sh -t "${TOOLCHAIN}" -a "${ARPVERSION}" -n "${TARGETNAME}"

echo "Build Paho Mqtt Cpp"
$DIR/build-paho.mqtt.cpp.sh -t "${TOOLCHAIN}" -a "${ARPVERSION}" -n "${TARGETNAME}"

echo "Build MqttClient"
$DIR/build-component.sh -t "${TOOLCHAIN}" -a "${ARPVERSION}" -n "${TARGETNAME}"
