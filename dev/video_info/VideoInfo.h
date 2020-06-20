#ifndef _VIDEOINFO_H_
#define _VIDEOINFO_H_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

class VideoInfo{
public:
    VideoInfo(String userMid);

    bool update();        // 更新信息  
    long getPlay();       // 获得播放次数
    long getDanmu();      // 获得弹幕数量 
    long getReply();      // 获得评论数量
    long getFavorite();   // 获得收藏数量
    long getCoin();       // 获得投币数量
    long getShare();      // 获得分享数量
    long getLikes();      // 获得获赞数量    
 
    String getServerCode(); // 获取服务器响应状态码
    
  private:  
    void _parseVideoInfo(WiFiClient client);      // 解析哔哩哔哩API信息
    
    const char* _host = "api.bilibili.com";     // 服务器地址 
    const int _port = 80;                       // 服务器端口
    String _mid; 
    
    String _status_response; // 服务器响应状态行
    String _response_code;   // 服务器响应状态码 

    long _data_view;      // 播放次数
    long _data_danmaku;   // 弹幕数量 
    long _data_reply;     // 评论数量
    long _data_favorite;  // 收藏数量
    long _data_coin;      // 投币数量
    long _data_share;     // 分享数量
    long _data_like;      // 获赞数量
};

#endif
