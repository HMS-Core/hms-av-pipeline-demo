# HUAWEI AV Pipeline Kit Sample

## Table of Contents
 * [Introduction](#introduction)
 * [Getting Started](#getting-started)
 * [Supported Environments](#supported-environments)
 * [License](#license)
## Introduction
AV Pipeline Kit is a framework for creating media applications. It parses a configuration file and connects multiple plug-ins according to the orchestration relationship in the configuration file to form a pipeline to implement specific media services (such as playback, recording, and editing). Each plug-in is responsible for completing a specific task, for example, demuxing, decoding, and filtering.
Pipelines that can be used in playback scenarios have been preconfigured in the AV Pipeline Kit. (e.g., video playback, video overcommitment, sound event detection) and encapsulates the API into a Java interface for developers to use. In addition, developers can directly invoke a single plug-in through C++ interfaces. If preconfigured plug-ins or pipelines do not meet requirements, developers can customize plug-ins or pipelines.

## Getting Started
1. Check whether your Android Studio development environment is ready. 
2. Open "cpp" or "java" in Android studio, compile and run it on your Android device.

## Supported Environments
Huawei mobile phone (EMUI 10.0 or later or HarmonyOS 2.0)

## License
The sample of AVPipeline Kit has obtained the [Apache 2.0 license.](http://www.apache.org/licenses/LICENSE-2.0).