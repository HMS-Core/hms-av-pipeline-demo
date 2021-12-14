# HMS Core AV Pipeline Kit Sample Code (C++)

English | [中文](README_ZH.md) 

## Contents

 * [Introduction](#Introduction)
 * [Quick Tutorial](#Quick-Tutorial)
 * [Supported Devices](#Supported-Devices)
 * [License](#License)
## Introduction
AV Pipeline Kit is a system for easier media app development. It contains a framework that parses plugin orchestration logic from each configuration file to create a pipeline with capabilities such as media playback, recording, or editing. Each plugin in a pipeline undertakes specific tasks, for example, demuxing, decoding, and filtering.
AV Pipeline Kit presets pipelines for scenarios like video playback, video super-resolution, and sound event detection, and it provides Java APIs for you to use these pipelines. You can also call a single preset plugin directly through C++ APIs. If you want to achieve more functions other than those provided by the preset plugins or pipelines, you can even customize some plugins or pipelines based on your own needs.
The sample code demonstrates how to directly call the sound event detection plugin through C++ APIs.

## Quick Tutorial
1. Install Android Studio on your computer. Open the sample code in Android Studio, compile the code, and run the demo app on an Android device.
2. Use Logcat to capture the log. Then, search by **avp-cppdemo** in the log to check the running result.

## Supported Devices
Huawei phones running EMUI 10.0 or later or HarmonyOS 2.0 or later

## License
The sample code is licensed under [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

