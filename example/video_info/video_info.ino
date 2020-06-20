/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : video_info
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 初版建立时间20200619
程序目的/Purpose          : 
使用ESP8266_BiliBili库通过哔哩哔哩API获取视频播放信息，这些信息包括：
视频播放量(long getPlay)
弹幕数量（long getDanmu）
评论数量（long getReply）
收藏（long getFavorite）
投币量(long getCoin)
分享次数（long getShare）
点赞次数（long getLikes）
-----------------------------------------------------------------------
本程序所属仓库网址
GitHub: https://github.com/taichi-maker/ESP8266-BiliBili
Gitee: https://gitee.com/taijichuangke/ESP8266-BiliBili
                             
***********************************************************************/
#include <ESP8266WiFi.h>
#include "ESP8266_BiliBili.h"

const char* ssid     = "taichimaker"; // 连接WiFi名（此处使用taichimaker为示例）
                                      // 请将您需要连接的WiFi名填入引号中
const char* password = "ZAQ1xsw2cde3VFR4";    // 连接WiFi密码（此处使用12345678为示例）
                                      // 请将您需要连接的WiFi密码填入引号中

VideoInfo videoInfo("BV1L7411c7jw");       // 建立对象用于获取粉丝信息
                                      // 括号中的参数是B站的UUID
void setup(){
  Serial.begin(9600);          
  Serial.println("");

  connectWiFi();    // 连接wifi
}
 
void loop(){
  if(videoInfo.update()){  // 更新信息成功   
    Serial.println("Update OK");
    Serial.print("Server Response: "); 
    Serial.println(videoInfo.getServerCode());
    Serial.print("Bo Fang: "); 
    Serial.println(videoInfo.getPlay());   
    Serial.print("Dan Mu: "); 
    Serial.println(videoInfo.getDanmu()); 
    Serial.print("Ping Lun: "); 
    Serial.println(videoInfo.getReply());     
    Serial.print("Shou Cang: "); 
    Serial.println(videoInfo.getFavorite());     
    Serial.print("Tou Bi: "); 
    Serial.println(videoInfo.getCoin());  
    Serial.print("Fen Xiang: "); 
    Serial.println(videoInfo.getShare());        
    Serial.print("Fen Xiang: "); 
    Serial.println(videoInfo.getShare());     
    Serial.print("Huo Zan: "); 
    Serial.println(videoInfo.getLikes());           
  } else {     // 更新失败
    Serial.println("Update Fail...");  
    Serial.print("Server Response: ");           
  }       
  Serial.println(F("======================"));  
  delay(3000);
}

// 连接WiFi
void connectWiFi(){
  WiFi.begin(ssid, password);                  // 启动网络连接
  Serial.print("Connecting to ");              // 串口监视器输出网络连接信息
  Serial.print(ssid); Serial.println(" ...");  // 告知用户NodeMCU正在尝试WiFi连接
  
  int i = 0;                                   // 这一段程序语句用于检查WiFi是否连接成功
  while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。 
    delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED                       
    Serial.print(i++); Serial.print(' ');      // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
  }                                            // 同时NodeMCU将通过串口监视器输出连接时长读秒。
                                               // 这个读秒是通过变量i每隔一秒自加1来实现的。                                              
  Serial.println("");                          // WiFi连接成功后
  Serial.println("Connection established!");   // NodeMCU将通过串口监视器输出"连接成功"信息。
  Serial.print("IP address:    ");             // 同时还将输出NodeMCU的IP地址。这一功能是通过调用
  Serial.println(WiFi.localIP());              // WiFi.localIP()函数来实现的。该函数的返回值即NodeMCU的IP地址。  
}                     
