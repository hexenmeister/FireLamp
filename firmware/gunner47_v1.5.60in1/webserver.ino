void initWebserver() {
  http = new(ESP8266WebServer);
  //http= new ESP8266WebServer(8080);

  if (http !=NULL) {
    /** 404 */
    http->onNotFound(routeNotFound);

   /** root page */
   http->on("/", routeHome);

   /** get config JSON */
   http->on("/getconfig", routeGetConfig); 

   /** send confid */
   http->on("/setconfig", routeSetConfig); 

    
  // TODO

    http->begin();
    //LOG.println("Webserver startet at url: http://%s.local/\r\n", clientId.c_str());
  } else {
    LOG.println("Error creating webserver!");
  }
}


/*  
    /** страница настройка будильника * /
    http->on("/alarm", routeAlarm); 
    
    /** прием конфигурации будильника * /
    http->on("/setalarmconfig", routeSetAlarmConfig); 
    
    /** получить текущие настройки/конфигурацию будильника * /
    http->on("/getalarmconfig", routeGetAlarmConfig);
  
}*/


/**
 * шаблон/отправщик страницы
 */
void responseHtml(String out, String title = "FireLamp", int code = 200) {
  #ifdef WEBAUTH
  if (!http->authenticate(clientId.c_str(), clientId.c_str())) {
      return http->requestAuthentication();
  }
  #endif
   
  String html;
  
  html = "<html>";
    html += "<head>";
      html += "<title>" + title + "</title>";
      //html += "<meta http-equiv=\"refresh\" content=\"30\" >";
      html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1\" />";
      html += "<link rel=\"stylesheet\" href=\"https://demos.jquerymobile.com/1.4.5/css/themes/default/jquery.mobile-1.4.5.min.css\">";
      html += "<link rel=\"stylesheet\" href=\"http://fonts.googleapis.com/css?family=Open+Sans:300,400,700\">";
      html += "<script src=\"https://demos.jquerymobile.com/1.4.5/js/jquery.js\"></script>";
      html += "<script src=\"https://demos.jquerymobile.com/1.4.5/js/jquery.mobile-1.4.5.min.js\"></script>";
    html += "</head>";
    html += "<body>";
      html += "<div data-role='page'>";
        html += "<div data-role='header' class='jqm-header'><h2><a class='ui-link' data-ajax='false' href='/'><img style='width: 100%' src='//i0.wp.com/alexgyver.ru/wp-content/uploads/2018/07/site_mob-1.png'></a></h2></div><!-- /header -->";
        html += "<div role='main' class='ui-content jqm-content' style='padding-bottom: 100px;'>";
        html += "";
        html += out;
        html += "";
        html += "</div>";
        html += "<div data-role='footer' data-theme='b' style='position: fixed;width: 100%;bottom: 0;z-index: 1;'>";
            html += "<div data-role='navbar' data-iconpos='bottom'>";
                html += "<ul>";
                    html += "<li><a href='/' data-ajax='false' data-icon='gear'>Einstellungen</a></li>"; // сдлеать активной class='ui-btn-active'
                    html += "<li><a href='/alarm' data-ajax='false' data-icon='clock'>Wecker</a></li>";
                    html += "<!--<li><a href='/timer' data-ajax='false' data-icon='power'>Timer</a></li>-->";
                html += "</ul>";
            html += "</div>"; // .navbar
        html += "</div>"; // .footer
      html += "</div>"; // .page

      // js функция отправки/получения данных формы
      html += "    <script type=\"text/javascript\">\n";
      html += "    function syncConfig(getconfig = '/getconfig', setconfig = '/setconfig'){\n";
      html += "        $.ajax({url: getconfig, dataType:'json', success: init});\n";
      html += "        function init(config){\n";
      html += "            /**\n";
      html += "             * костыль/фича\n";
      html += "             * лень было искать как нормально установить параметы в виджеты\n";
      html += "             * пока не установятся параметры из ESP, отправка не будет осуществляться\n";
      html += "             * @type {boolean}\n";
      html += "             */\n";
      html += "            window.changeReaction = false;\n";
      html += "                let timeouts = {};\n";
      html += "                $('select, input').on('change',(v) => {\n";
      html += "                    /** если данные не пришли, ничего не отправляем/сохраненяем */\n";
      html += "                    if(window.changeReaction === false) return;\n";
      html += "                    let that = $(v.currentTarget), name = that.attr('name'), outData = {};\n";
      html += "                    /** если в очереди на отправку/сохранение есть такой параметр, то снимим предыдущее значение */\n";
      html += "                    if(timeouts[name] != undefined)\n";
      html += "                        clearTimeout(timeouts[name]);\n";
      html += "                    /**\n";
      html += "                     * установим измененный параметр в очередь на отправку/сохранение в ESP\n";
      html += "                     * @type {number}\n";
      html += "                     */\n";
      html += "                    timeouts[name] = setTimeout(() => {\n";
      html += "                        window.changeReaction = false;\n";
      html += "                        outData[name] = that.val();\n";
      html += "                        $.ajax({\n";
      html += "                            url:setconfig,\n";
      html += "                            data: outData,\n";
      html += "                            dataType: 'json',\n";
      html += "                            success: (json) => {\n";
      html += "                                if(json[name] = outData[name])\n";
      html += "                                    window.changeReaction = true;\n";
      html += "                                else\n";
      html += "                                    alert('Fehler beim Speichern der Einstellungen.');\n";
      html += "                                setConfig(json);\n";
      html += "                            },\n";
      html += "                            error: (event) => alert(`Fehler beim Speichern der Einstellungen.\nFehler \"${event.status} ${event.statusText}\".`)\n";
      html += "                        });\n";
      html += "                    }, 500);\n";
      html += "                });\n";
      html += "                setConfig(config);\n";
      html += "                /** установим актуальные параметры из ESP */\n";
      html += "                function setConfig(config){\n";
      html += "                  window.changeReaction = false;\n";
      html += "                  for (let key in config){\n";
      html += "                      let that = $(`[name=${key}]`);\n";
      html += "                      that.val(config[key]);\n";
      html += "                      that.trigger('change');\n";
      html += "                  }\n";
      html += "                  /**\n";
      html += "                   * разрешаем вносить изменеия в конфигу\n";
      html += "                   * @type {boolean}\n";
      html += "                   */\n";
      html += "                  window.changeReaction = true;\n";
      html += "                }\n";
      html += "        }\n";
      html += "    }\n";
      html += "    </script>\n";
      
    html += "</body>";
  html += "</html>";
  
  http->sendHeader("Cache-Control","max-age=0, private, must-revalidate");
  http->send(code, "text/html; charset=utf-8", html); 
}

/**
 * Hauptmenü
 */
void routeHome(){
  
  String out;
 
  out = "<form>";

      out += "<div class='ui-field-contain'>";
        out += "<label for='on'>Power:</label>";
        out += "<select name='on' id='on' data-role='slider' data-mini='true'>";
          out += "<option value='0'>aus</option>";
          out += "<option value='1'>an</option>";
        out += "</select>";
      out += "</div>";
      
      out += "<div class='ui-field-contain'>";
        out += "<label for='currentMode'>Effekt:</label>";
        out += "<select name='currentMode' id='currentMode' data-mini='true'>";
          
          out += "<option value='0'>Konfetti</option>";
          out += "<option value='1'>Feuer</option>";
          out += "<option value='2'>Regenbogen vertikal</option>";
          out += "<option value='3'>Regenbogen horizontal</option>";
          out += "<option value='4'>Farbwechsel</option>";
          out += "<option value='5'>Wahnsinn 3D</option>";
          out += "<option value='6'>Wolken 3D</option>";
          out += "<option value='7'>Lava 3D</option>";
          out += "<option value='8'>Plasma 3D</option>";
          out += "<option value='9'>Regenbogen 3D</option>";
          out += "<option value='10'>Pfau 3D</option>";
          out += "<option value='11'>Zebra 3D</option>";
          out += "<option value='12'>Wald 3D</option>";
          out += "<option value='13'>Ozean 3D</option>";
          out += "<option value='14'>Farbe</option>";
          out += "<option value='15'>Schneefall</option>";
          out += "<option value='16'>Matrix</option>";
          out += "<option value='17'>Glühwürmchen</option>";
          out += "<option value='18'>Demo</option>";
          
        out += "</select>";
      out += "</div>";
      
      out += "<div class='ui-field-contain'>";
        out += "<label for='brightness'>Helligkeit:</label>";
        out += "<input type='range' name='brightness' id='brightness' value='50' min='1' max='255' data-highlight='true'>";
      out += "</div>";
      
      out += "<div class='ui-field-contain'>";
        out += "<label for='speed'>Geschwindigkeit:</label>";
        out += "<input type='range' name='speed' id='speed' value='50' min='0' max='255' data-highlight='true'>";
      out += "</div>";
      
      out += "<div class='ui-field-contain'>";
        out += "<label for='scale'>Skalieren:</label>";
        out += "<input type='range' name='scale' id='scale' value='50' min='0' max='100' data-highlight='true'>";
      out += "</div>";
      
    
  out += "</form>";
  out += "<script type='text/javascript'>$(()=>{syncConfig('/getconfig','/setconfig');});</script>";
  out += "<br>";
  out += getTimeStampString();

  responseHtml(out);
}

char buf[40]; 
String getTimeStampString() {
  time_t currentLocalTime = localTimeZone.toLocal(timeClient.getEpochTime());
  sprintf_P(buf, PSTR("%02u.%02u.%02u - %02u:%02u:%02u"), day(currentLocalTime), month(currentLocalTime), year(currentLocalTime), hour(currentLocalTime), minute(currentLocalTime), second(currentLocalTime));
  return String(buf);
}


/**
 * send config data JSON
 */
void routeGetConfig() {

  #ifdef WEBAUTH
  if (!http->authenticate(clientId.c_str(), clientId.c_str())) {
      return http->requestAuthentication();
  }
  #endif

  String out;

  out += "{";
  out += "\"status\": \"ok\",";
  //out += "\"value\": " + String(modes[currentMode].Brightness) + ",";
  out += "\"currentMode\": " + String(currentMode) + ",";
  out += "\"brightness\": " + String(modes[currentMode].Brightness) + ",";
  out += "\"speed\": " + String(modes[currentMode].Speed) + ",";
  out += "\"scale\": " + String(modes[currentMode].Scale) + ",";
  out += "\"on\": " + String(ONflag) + ",";
  out += "\"espMode\": " + String(espMode);
  out += "}";
  
  http->send(200, "text/json", out);
}

/**
 * изменение/применение новой конфигурации
 */
void routeSetConfig() {

  #ifdef WEBAUTH
  if (!http->authenticate(clientId.c_str(), clientId.c_str())) {
      return http->requestAuthentication();
  }
  #endif
  
  if (http->hasArg("on")) {
    ONflag = (http->arg("on").toInt() > 0) ? true : false;
    loadingFlag = true;
    settChanged = true;
    eepromTimeout = millis();
    changePower();
    
    #if (USE_MQTT)
    if (espMode == 1U)
    {
      MqttManager::needToPublish = true;
    }
    #endif
  }
  
  if (http->hasArg("currentMode")) {
    String value;
    value = http->arg("currentMode");
    currentMode =  value.toInt();

    //manualOff = true;
    //dawnFlag = false;
    
    //settChanged = true;
    //loadingFlag = true;
    //FastLED.clear();
    //delay(1);
    //sendCurrent();
    //FastLED.setBrightness(modes[currentMode].brightness);


    EepromManager::SaveModesSettings(&currentMode, modes);
    //memcpy(buff, &inputBuffer[3], strlen(inputBuffer));   // взять подстроку, состоящую последних символов строки inputBuffer, начиная с символа 4
    //currentMode = (uint8_t)atoi(buff);
    loadingFlag = true;
    settChanged = true;
    eepromTimeout = millis();
    FastLED.clear();
    delay(1);
    //sendCurrent(inputBuffer);
    FastLED.setBrightness(modes[currentMode].Brightness);

    #if (USE_MQTT)
    if (espMode == 1U)
    {
      MqttManager::needToPublish = true;
    }
    #endif
  }

  //TODO
  
  /*
  if(http->hasArg("scale")){

    byte scale = http->arg("scale").toInt();
    if (currentMode == 17 && scale > 100) scale = 100;
    
    modes[currentMode].scale = scale;
    loadingFlag = true;
    settChanged = true;
    eepromTimer = millis();

  }
  
  if(http->hasArg("brightness")){
    ONflag = true;    
    modes[currentMode].brightness = http->arg("brightness").toInt();
    changePower();
    FastLED.setBrightness(modes[currentMode].brightness);

    sendCurrent();
    settChanged = true;
    eepromTimer = millis();

  }
  
  if(http->hasArg("speed")){
    modes[currentMode].speed = http->arg("speed").toInt();
    loadingFlag = true;
    settChanged = true;
    eepromTimer = millis();

  }
  */
  /** в знак завершения операции отправим текущую конфигурацию */
  routeGetConfig();
  //MQTTUpdateState();
  
}

/**
 * handle 404
 */
void routeNotFound() {
  String out;
  
  out = "Not found";
  out += "<br />URI: ";
  out += http->uri();
  out += "<br />Method: ";
  out += (http->method() == HTTP_GET) ? "GET" : "POST";
  out += "<br />Arguments: ";
  out += http->args();
  out += "<br /><pre>";
  for (uint8_t i = 0; i < http->args(); i++) {
    out += " " + http->argName(i) + ": " + http->arg(i) + "<br />";
  }
  out += "</pre><hr /><a class='ui-link' data-ajax='false' href=\"/\">Hauptmenü</a>";
  responseHtml(out, "Error 404", 404);
}
