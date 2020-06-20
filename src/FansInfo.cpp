#include "FansInfo.h"
 
FansInfo::FansInfo(String userMid){
  _mid = userMid;
}

/* 尝试从哔哩哔哩API更新信息
 * @return: bool 成功更新返回真，否则返回假
 */
bool FansInfo::update(){
  WiFiClient _wifiClient;
  
  String reqRes = "/x/relation/stat?vmid=" + _mid +
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
void FansInfo::_parseFansInfo(WiFiClient client){
  const size_t capacity = JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 70;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
   
  JsonObject data = doc["data"];
  _data_following = data["following"];
  _data_black = data["black"]; 
  _data_follower = data["follower"];
}

// 获取粉丝数量
long FansInfo::getFansNumber(){
  return _data_follower;
}

// 获取关注数量
int FansInfo::getFollowing(){
  return _data_following;
}

// 获取黑名单数量
int FansInfo::getBlack(){
  return _data_black;
}

// 返回服务器响应状态码
String FansInfo::getServerCode(){
  return _response_code;
}
