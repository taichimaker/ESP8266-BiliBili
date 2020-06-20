#ifndef _FANSINFO_H_
#define _FANSINFO_H_
 
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

//#define DEBUG   // 调试用宏定义

// 获取当前天气信息类
class FansInfo {
  public:
    FansInfo(String userMid);

    bool update();          // 更新信息  
    
    long getFansNumber();   // 获取粉丝数量
    int getFollowing();     // 获取关注数量
    int getBlack();         // 获取黑名单数量
    String getServerCode(); // 获取服务器响应状态码
    
  private:  
    void _parseFansInfo(WiFiClient client);      // 解析哔哩哔哩API信息
    
    const char* _host = "api.bilibili.com";     // 服务器地址 
    const int _port = 80;                       // 服务器端口
    String _mid; 
    
    String _status_response; // 服务器响应状态行
    String _response_code;   // 服务器响应状态码  

    int _data_following; // 关注数量
    int _data_black;     // 黑名单数量
    long _data_follower; // 粉丝数量   
};
#endif
