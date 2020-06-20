#include "UpInfo.h"

UpInfo::UpInfo(String userMid){
  _mid = userMid;
}

/* 尝试从哔哩哔哩API更新信息
 * @return: bool 成功更新返回真，否则返回假
 */
bool UpInfo::update(){
  WiFiClient _wifiClient;
  
  String reqRes = "/x/space/upstat?mid=" + _mid +
                  + "&type=json";
                  
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
    
    _parseFansInfo(_wifiClient); 
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
void UpInfo::_parseFansInfo(WiFiClient client){
  const size_t capacity = 2*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 70;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
    
  JsonObject data = doc["data"];
  
  _data_archive_view = data["archive"]["view"];   
  _data_article_view = data["article"]["view"];
  _data_likes = data["likes"]; 
}

// 获得视频播放数量
long UpInfo::getPlay(){
  return _data_archive_view;
}

// 获得专栏阅读数量
long UpInfo::getRead(){
  return _data_article_view;
}

// 获得获赞数量   
long UpInfo::getLikes(){
  return _data_likes;
}

// 返回服务器响应状态码
String UpInfo::getServerCode(){
  return _response_code;
}
