# 华为多媒体管线服务示例代码

中文 | [English](README.md)

## 目录

 * [简介](#简介)
 * [快速上手](#快速上手)
 * [支持的设备](#支持的设备)
 * [技术支持](#技术支持)
 * [许可证](#许可证)
## 简介
多媒体管线服务（AV Pipeline Kit，简称AV Pipeline）是一个用于创建媒体应用的框架，负责解析配置文件并将多个插件按照配置文件中的编排关系连接组成一个Pipeline，实现特定的媒体业务（例如播放、录制、编辑等）。其中，每个插件负责完成特定的任务，例如解封装、解码、滤波等。
AV Pipeline Kit已预置可应用在播放场景的Pipeline（例如视频播放、视频超分、声音事件检测），并对外封装成了Java接口供开发者使用。同时，也支持开发者通过C++接口直接调用单个插件。若预置插件或预置Pipeline不满足使用要求，开发者可以自定义插件、自定义Pipeline。

## 快速上手
1. 检查您的Android studio开发环境是否已准备好。
2. 在Android studio中打开"cpp"目录或"java"目录，编译并运行在您的安卓设备上。

## 支持的设备
安卓手机（安卓9.0及以上版本）

## 技术支持
如果您对HMS Core还处于评估阶段，可在[Reddit社区](https://www.reddit.com/r/HuaweiDevelopers/)获取关于HMS Core的最新讯息，并与其他开发者交流见解。

如果您对使用HMS示例代码有疑问，请尝试：
- 开发过程遇到问题上[Stack Overflow](https://stackoverflow.com/questions/tagged/huawei-mobile-services?tab=Votes)，在`huawei-mobile-services`标签下提问，有华为研发专家在线一对一解决您的问题。
- 到[华为开发者论坛](https://developer.huawei.com/consumer/cn/forum/blockdisplay?fid=18?ha_source=hms1) HMS Core板块与其他开发者进行交流。

如果您在尝试示例代码中遇到问题，请向仓库提交[issue](https://github.com/HMS-Core/hms-av-pipeline-demo/issues)，也欢迎您提交[Pull Request](https://github.com/HMS-Core/hms-av-pipeline-demo/pulls)。

## 许可证

该示例代码已获取了[Apache 2.0许可证](http://www.apache.org/licenses/LICENSE-2.0)。

