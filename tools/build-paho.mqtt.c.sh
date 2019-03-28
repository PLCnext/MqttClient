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
VERSION=$(echo $ARPVERSION | grep -oP [0-9]+\.[0-9]+\.[0-9]+\.[0-9]+)
echo "Version:${VERSION}"
# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

echo "Clone Paho mqtt C"
mkdir -p ${DIR}/../external
set +e
git clone -q https://github.com/eclipse/paho.mqtt.c.git "${DIR}/../external/paho.mqtt.c"
cd "${DIR}/../external/paho.mqtt.c"
git status || git init
git fetch --tags
git checkout v1.3.0
set -e


#cmake
echo CMAKE Configure
cmake \
-D CMAKE_BUILD_TYPE=Release \
-D BUILD_TESTING=OFF \
-D CMAKE_STAGING_PREFIX="${DIR}/../deploy/${TARGETNAME}_${VERSION}" \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D CMAKE_PREFIX_PATH="${DIR}/../deploy/${TARGETNAME}_${VERSION}" \
-D CMAKE_EXPORT_COMPILE_COMMANDS=ON \
-D BUILD_SHARED_LIBS=ON \
-D CMAKE_TOOLCHAIN_FILE="${TOOLCHAIN}/toolchain.cmake" \
-D ARP_TOOLCHAIN_ROOT="${TOOLCHAIN}" \
-D ARP_DEVICE="${TARGETNAME}" \
-D ARP_DEVICE_VERSION="${ARPVERSION}" \
-D PAHO_WITH_SSL=ON \
-D PAHO_BUILD_STATIC=FALSE \
-D PAHO_BUILD_DOCUMENTATION=OFF \
-D PAHO_BUILD_SAMPLES=OFF \
-D PAHO_BUILD_DEB_PACKAGE=OFF \
-D PAHO_ENABLE_TESTING=OFF \
-S "${DIR}/../external/paho.mqtt.c" \
-B "${DIR}/../build/external/paho.mqtt.c/${TARGETNAME}_${VERSION}"

echo "build"
cmake --build "${DIR}/../build/external/paho.mqtt.c/${TARGETNAME}_${VERSION}"
cmake --build "${DIR}/../build/external/paho.mqtt.c/${TARGETNAME}_${VERSION}" --target install
