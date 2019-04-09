#!/bin/bash
#//
#// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
#// Licensed under the MIT. See LICENSE file in the project root for full license information.
#// SPDX-License-Identifier: MIT
#//
while getopts h: option
do
case "${option}"
in
h) HARDWARE+=${OPTARG};;
esac
done
# Get the directory of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
# Get all available targets

OLD=$IFS
IFS=$'\n\t'
Targets=($( plcncli get targets | grep -oPe [[:alpha:]]+[[:digit:]]+[[:alpha:]]?[[:punct:]][0-9]+[.][0-9]+.?.?.?.?.?.?.?.?[[:punct:]].?[0-9]+[.][0-9]+[.][0-9]+[.][0-9]+.?.?[[:punct:]]))
echo -e ${Targets[@]}

# Extract Hardware and Release and Firmware Version

Hardware=($(echo -e ${Targets[@]} | grep -oPe [[:alpha:]]+[[:digit:]]+[[:alpha:]]?))
IFS=$OLD

Release=($(echo -e ${Targets[@]} | grep -oPe [^.,][0-9]+[.][0-9]+[.]?[0-9]?[[:blank:]][L]?[T]?[S]?[[:blank:]]?))

IFS=$'\n\t'
Version=($(echo -e ${Targets[@]} | grep -oPe  [0-9]+[.][0-9]+[.][0-9]+[.][0-9]+))

ARPVERSION=($(echo -e ${Targets[@]} | grep -oPe [^.,][0-9]+[.][0-9]+[.]?[0-9]?[[:blank:]][L]?[T]?[S]?[[:blank:]]?[[:punct:]].?[0-9]+[.][0-9]+[.][0-9]+[.][0-9]+[[:blank:]]?[[:blank:]]?[[:punct:]]))
IFS=$OLD

echo -e "H:\n${Hardware[@]} \n R:\n ${Release[@]} \n V:\n ${Version[@]} \nA:\n ${ARPVERSION[@]} \n"

var=${#Hardware[@]}
## Extract SDK paths and match to Targets

Toolchains=($(plcncli get sdks | grep -oPe [[:blank:]]?[/][[:alnum:][:blank:][:punct:]]*[[:blank:]]?))
echo -e "Toolchain: \n ${Toolchains[@]} \n "

rm -r "${DIR}/../build"

# Build for each Version of Specified HARDWARE
var=${#Hardware[@]}
for ((i=0; i<var; i++ ));
do
echo -e "T: ${Toolchains[$i]} \n V:${ARPVERSION[$i]} \n HW:${Hardware[$i]} \n "
echo "Build MqttClient"
$DIR/build-all.sh  -t "${Toolchains[$i]}" -a "${ARPVERSION[$i]}" -n "${Hardware[$i]}"

done
