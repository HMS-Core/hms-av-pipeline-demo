# AVPipeline  Kit

## Table of Contents
 * [Introduction](#introduction)
 * [Getting Started](#getting-started)
 * [Supported Environments](#supported-environments)
 * [License](#license)
## Introduction
AV Pipeline Kit is a framework for creating media applications. It parses a configuration file and connects multiple plug-ins according to the orchestration relationship in the configuration file to form a pipeline to implement specific media services (such as playback, recording, and editing). Each plug-in is responsible for completing a specific task, for example, demuxing, decoding, and filtering.
Pipelines that can be used in playback scenarios have been preconfigured in the AV Pipeline Kit. (e.g., video playback, video overcommitment, sound event detection) and encapsulates the API into a Java interface for developers to use. In addition, developers can directly invoke a single plug-in through C++ interfaces. If preconfigured plug-ins or pipelines do not meet requirements, developers can customize plug-ins or pipelines.
This sample code demonstrates how to directly invoke the sound event detection plug-in through the C++ interface.

## Getting Started
1. Check that your Android Studio development environment is ready. Open this sample code in Android studio, compile and run it on your Android device.
2. The sample code does not have a UI. You need to use the android logcat tool to capture run logs and search for avp-cppdemo to view the running result.

## Supported Environments
Huawei mobile phone (EMUI 10.0 or later or HarmonyOS 2.0)

## License
The sample of AVPipeline Kit has obtained the [Apache 2.0 license.](http://www.apache.org/licenses/LICENSE-2.0).