#ifndef _UPINFO_H_
#define _UPINFO_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

//#define DEBUG   // 调试用宏定义

// 获取当前天气信息类
class UpInfo {
  public:
    UpInfo(String userMid);

    bool update();          // 更新信息  
    
    long getPlay();         // 获得视频播放数量
    long getRead();         // 获得专栏阅读数量
    long getLikes();        // 获得获赞数量   
    String getServerCode(); // 获取服务器响应状态码
    
  private:  
    void _parseFansInfo(WiFiClient client);      // 解析哔哩哔哩API信息
    
    const char* _host = "api.bilibili.com";     // 服务器地址 
    const int _port = 80;                       // 服务器端口
    String _mid; 
    
    String _status_response; // 服务器响应状态行
    String _response_code;   // 服务器响应状态码  

    long _data_archive_view;   
    long _data_article_view;
    long _data_likes; 
};

#endif
