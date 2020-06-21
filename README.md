# ESP8266-哔哩哔哩  / ESP8266-BiliBili


## 基本介绍

本库用于ESP8266开发板通过哔哩哔哩网站API获取以下信息：

1. 粉丝信息 （UP有多少个粉丝数量、UP关注了多少个B站UP主的数量、UP的黑名单数量）
2. UP信息（UP的全部视频播放数、UP的全部专栏文章阅读数、UP的全部作品获赞数）
3. 视频播放信息（视频播放量、弹幕数量、收藏数量、投币量、分享次数、点赞次数）

假如您想要制作一款类似我们太极创客团队[小凯](https://gitee.com/xiaoxiaokai)开发的哔哩哔哩网络天气时钟小电视](https://gitee.com/taijichuangke/bilibili_weather_clock)，就可以利用这款ESP8266库。

## 关于本库

本库为太极创客团队制作的免费视频教程《零基础入门学用物联网 》中一部分。该教程系统的向您讲述ESP8266的物联网应用相关的软件和硬件知识。如果您希望观看教程视频，可前往以下视频平台观看。

哔哩哔哩：https://www.bilibili.com/video/BV1L7411c7jw

YouTube: https://www.youtube.com/playlist?list=PL8mx3Pk-gVLI2GwuxuqR_T5WDKeAPRkzj

ESP8266-哔哩哔哩库仅仅是我们团队所开发的诸多免费开源项目中的一个。我们坚持免费开源是为了让更多的朋友可以体会开源项目和开源协作的魅力，让我们开发的项目更富活力。假如您喜欢我们的项目，请为本项目打上一颗小星星，或者把我们推荐给更多热爱科技的朋友们。谢谢！您的鼓励是我们前进最大的动力！

## 使用前准备工作

1. 使用本库前请预先注册好哔哩哔哩网站账号。
2. 本程序使用Arduino编程语言。如您使用Arduino IDE开发，请预先在Arduino IDE中安装好ESP8266扩展程序，如需了解详细安装方法，请参考太极创客团队制作的[《零基础入门学用物联网 - 基础知识篇》3-1-2 为ESP8266-NodeMCU搭建Arduino IDE开发环境](http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/nodemcu-arduino-ide/)。
3. 本程序使用ArduinoJson库
   请预先在Arduino IDE中安装[ArduinoJson库](www.arduinojson.org)。 如果您想了解该库的具体使用方法，请参考太极创客团队制作的免费视频教程《[零基础入门学用物联网](http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/)》

## 使用方法

### 获取粉丝信息

1 您可以参考 **example** 目录中的fans_info 示例程序了解具体使用方法

2 首先通过FansInfo建立对象

  ```C++
  FansInfo fansInfo("BiliBili用户ID");
  ```
以上语句中括号里的参数为字符串类型。参数内容是被查询UP的用户ID。有关如何获取用户ID的操作方法，可参考以下链接：

http://www.taichi-maker.com/homepage/iot-development/iot-platform/esp8266-bilibili-api/

3 使用`update`函数对粉丝信息进行更新（此函数返回值为`bool`型。在ESP8266成功连接哔哩哔哩API服务器并且服务器返回响应状态码为`200`时，此函数将会返回真，否则会返回假。

4 使用下列函数获取具体UP主的粉丝信息 

| 函数说明                                      | 函数示例                   |
| --------------------------------------------- | -------------------------- |
| UP有多少个粉丝数量(返回值类型：long)          | `fansInfo.getFansNumber()` |
| UP关注了多少个B站UP主的数量 (返回值类型：int) | `fansInfo.getFollowing()`  |
| UP的黑名单数量 (返回值类型：int)              | `fansInfo.getBlack()`      |

5 使用`getServerCode`函数可获取服务器响应状态码。
当用户向服务器发送的请求存在问题时，服务器会通过响应状态码告知用户问题的具体原因。您可以通过该响应状态码判断具体问题原因。该函数返回值为int型。

```C++
   fansInfo.getServerCode()
```
### 获取用户信息

1 您可以参考 **example** 目录中的up_info 示例程序了解具体使用方法

2 首先通过UpInfo建立对象

  ```C++
  UpInfo upInfo("哔哩哔哩用户ID"); 
  ```
以上语句中括号里的参数为字符串类型。参数内容是被查询UP的用户ID。有关如何获取用户ID的操作方法，可参考以下链接：

http://www.taichi-maker.com/homepage/iot-development/iot-platform/esp8266-bilibili-api/

3 使用`update`函数对用户信息进行更新（此函数返回值为`bool`型。在ESP8266成功连接哔哩哔哩API服务器并且服务器返回响应状态码为`200`时，此函数将会返回真，否则会返回假。）

4 使用下列函数获取UP主信息 

| 函数说明                                       | 函数示例           |
| ---------------------------------------------- | ------------------ |
| 获取UP的全部视频播放次数(返回值类型：long)     | `upInfo.getPlay()` |
| 获取UP的全部专栏文章阅读次数(返回值类型：long) | `upInfo.getRead()` |
| 获取UP的全部作品获赞总数 (返回值类型：long)    |                    |

5 使用`getServerCode`函数可获取服务器响应状态码。
当用户向服务器发送的请求存在问题时，服务器会通过响应状态码告知用户问题的具体原因。您可以通过该响应状态码判断具体问题原因。该函数返回值为int型。

```C++
   upInfo.getServerCode()
```
### 获取视频信息

1 您可以参考 **example** 目录中的video_info 示例程序了解具体使用方法

2 首先通过VideoInfo建立对象

  ```C++
  VideoInfo videoInfo("视频BV号"); 
  ```
以上语句中括号里的参数为字符串类型。参数内容是被查询的视频BV号。有关如何获取视频BV号的操作方法，可参考以下链接：

http://www.taichi-maker.com/homepage/iot-development/iot-platform/esp8266-bilibili-api/

3 使用`update`函数对视频信息进行更新（此函数返回值为`bool`型。在ESP8266成功连接哔哩哔哩API服务器并且服务器返回响应状态码为`200`时，此函数将会返回真，否则会返回假。）

4 使用下列函数获取视频信息 

| 函数说明                     | 函数示例                  |
| ---------------------------- | ------------------------- |
| 视频播放量(返回值类型：long) | `videoInfo.getPlay()`     |
| 弹幕数量(返回值类型：long)   | `videoInfo.getDanmu()`    |
| 评论数量 (返回值类型：long)  | `videoInfo.getReply()`    |
| 收藏数量(返回值类型：long)   | `videoInfo.getFavorite()` |
| 投币量(返回值类型：long)     | `videoInfo.getCoin()`     |
| 分享次数(返回值类型：long)   | `videoInfo.getShare()`    |
| 点赞次数(返回值类型：long)   | `videoInfo.getLikes()`    |
|                              |                           |

5 使用`getServerCode`函数可获取服务器响应状态码。
当用户向服务器发送的请求存在问题时，服务器会通过响应状态码告知用户问题的具体原因。您可以通过该响应状态码判断具体问题原因。该函数返回值为int型。

```C++
   videoInfo.getServerCode()
```
--------
## 太极创客团队信息

太极创客官网地址：http://www.taichi-maker.com/

太极创客哔哩哔哩主页：https://space.bilibili.com/103589285

太极创客YouTube：https://www.youtube.com/channel/UC8EkxMr5gGnrb9adVgR-UJw

太极创客GitHub：https://github.com/taichi-maker

太极创客码云：https://gitee.com/taijichuangke

## ESP8266-BiliBili库项目开发人员
CYNO朔	https://github.com/Cyno-Shuo

-----------------------------

## ESP8266-BiliBili

Use ESP8266 to get User and  Video information from BiliBili Website.

About Taichi-Maker Team
--------

Taichi-Maker Official Website：http://www.taichi-maker.com/

Taichi-Maker BiliBili：https://space.bilibili.com/103589285

Taichi-Maker YouTube Chanel：https://www.youtube.com/channel/UC8EkxMr5gGnrb9adVgR-UJw

Taichi-Maker GitHub：https://github.com/taichi-maker

Taichi-Maker Gitee：https://gitee.com/taijichuangke