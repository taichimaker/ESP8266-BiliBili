#include "VideoInfo.h"

VideoInfo::VideoInfo(String userMid){
  _mid = userMid;
}

/* 尝试从哔哩哔哩API更新信息
 * @return: bool 成功更新返回真，否则返回假
 */
bool VideoInfo::update(){
  WiFiClient _wifiClient;
  
  String reqRes = "/x/web-interface/archive/stat?bvid=" + _mid;
                  
  String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" + 
                              "Host: " + _host + "\r\n" + 
                              "Connection: close\r\n\r\n";
                              
  #ifdef DEBUG
  Serial.print("Connecting to ");Serial.print(_host);
  #endif DEBUG
  
  if (_wifiClient.connect(_host, 80)){
    #ifdef DEBUG
    Serial.println(" Success!");
    #endif DEBUG       
 
    // 向服务器发送http请求信息
    _wifiClient.print(httpRequest);
    
    #ifdef DEBUG
    Serial.println("Sending request: ");
    Serial.println(httpRequest); 
    #endif DEBUG        
 
    // 获取并显示服务器响应状态行 
    String _status_response = _wifiClient.readStringUntil('\n');
    #ifdef DEBUG
    Serial.print("_status_response: ");
    Serial.println(_status_response);
    #endif DEBUG
    
    // 查验服务器是否响应200 OK
    _response_code = _status_response.substring(9, 12);
    if (_response_code == "200") {
      #ifdef DEBUG
      Serial.println("Response Code: 200");
      #endif DEBUG 
    } else {
      #ifdef DEBUG
      Serial.println(F("Response Code: NOT 200"));
      #endif DEBUG   
      _wifiClient.stop();    
      return false;
    }  

    // 使用find跳过HTTP响应头
    if (_wifiClient.find("\r\n\r\n")) {
      #ifdef DEBUG
      Serial.println("Found Header End. Start Parsing.");
      #endif DEBUG              
    }
    
    _parseVideoInfo(_wifiClient); 
    _wifiClient.stop();
    return true;
  } else {
    #ifdef DEBUG
    Serial.println(" connection failed!");
    #endif DEBUG       
    _wifiClient.stop();
    return false;
  }                           
}

// 解析哔哩哔哩API信息
void VideoInfo::_parseVideoInfo(WiFiClient client){
  const size_t capacity = JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(15) + 170;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
  
  int code = doc["code"];
  const char* message = doc["message"];
  int ttl = doc["ttl"];
  
  JsonObject data = doc["data"];
  _data_view = data["view"];
  _data_danmaku = data["danmaku"]; 
  _data_reply = data["reply"];
  _data_favorite = data["favorite"];
  _data_coin = data["coin"]; 
  _data_share = data["share"];
  _data_like = data["like"];
}
// 获得播放次数
long VideoInfo::getPlay(){
  return _data_view;
}
  
// 获得弹幕数量  
long VideoInfo::getDanmu(){
  return _data_danmaku;
}

// 获得评论数量  
long VideoInfo::getReply(){
  return _data_reply;
}

// 获得收藏数量   
long VideoInfo::getFavorite(){
  return _data_favorite;
}

// 获得投币数量 
long VideoInfo::getCoin(){
  return _data_coin;
} 

// 获得分享数量    
long VideoInfo::getShare(){
  return _data_share;
}

// 获得获赞数量        
long VideoInfo::getLikes(){
  return _data_like;
}    

// 返回服务器响应状态码
String VideoInfo::getServerCode(){
  return _response_code;
}
