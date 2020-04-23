void initWebserver() {
  http = new(ESP8266WebServer);
  //http= new ESP8266WebServer(8080);

  if (http !=NULL) {

    // TODO USE_WEBUPDATE
    httpUpdater = new(ESP8266HTTPUpdateServer);
    #ifdef WEBAUTH
    // TODO: Definitionen für User/Passwort
    httpUpdater->setup(http, clientId.c_str(), clientId.c_str());
    #else
    httpUpdater->setup(http);
    #endif
    
    //http->on("/update", routeUpload);

    /** 404 */
    http->onNotFound(routeNotFound);

    /** root page */
    http->on("/", routeHome);

    /** get config JSON */
    http->on("/getconfig", routeGetConfig); 

    /** send confid */
    http->on("/setconfig", routeSetConfig); 

    
    // TODO

    /** stub for favicon  **/
    http->on("/favicon.ico", []() {
      // TODO
      http->send(404, "text/plain", "none");
    });

    http->begin();
    
    //LOG.println("Webserver startet at url: http://%s.local/\r\n", clientId.c_str());
  } else {
    LOG.println("Error creating webserver!");
  }
}

/*
void routeUpload() {
  String html = "";
    html += "<html lang='de'>";
      html += "<head>";
        html += "<meta charset='utf-8'>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>";
        html += "<title>FireLamp Firmware Update</title>";
        html += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css' integrity='sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm' crossorigin='anonymous'>";
      html += "</head>";
      html += "<body>";
        html += "<nav class='navbar navbar-expand-md navbar-dark bg-dark mb-4'>";
          html += "<div class='container'>";
            html += "<a href='/' class='navbar-brand'>FireLamp Hauptmen&uuml;</a>";
          html += "</div>";
        html += "</nav>";
        html += "<main role='main' class='container'>";
          html += "<div class='jumbotron'>";
            html += "<form id='data' action='' method='POST' enctype='multipart/form-data'>";
              html += "<div class='input-group mb-3'>";
                html += "<div class='custom-file'>";
                  html += "<input type='file' accept='.bin' class='custom-file-input' id='inputGroupFile04' name='firmware'>";
                  html += "<label class='custom-file-label' for='inputGroupFile04'>Firmware</label>";
                html += "</div>";
                html += "<div class='input-group-append'>";
                  html += "<button style='width:200px;' class='btn btn-danger' type='submit'>Update Firmware</button>";
                html += "</div>";
              html += "</div>";
            html += "</form>";
            html += "<form id='data' action='' method='POST' enctype='multipart/form-data'>";
              html += "<div class='input-group mb-3'>";
                html += "<div class='custom-file'>";
                  html += "<input type='file' accept='.bin' class='custom-file-input' id='inputGroupFile04' name='filesystem'>";
                  html += "<label class='custom-file-label' for='inputGroupFile04'>SPIFFS</label>";
                html += "</div>";
                html += "<div class='input-group-append'>";
                  html += "<button style='width:200px;' class='btn btn-danger' type='submit'>Update Filesystem</button>";
                html += "</div>";
              html += "</div>";
            html += "</form>";
            html += "<form>";
              html += "<div class='form-group'>";
                html += "<button type='button' class='btn btn-Primary' onclick='window.location.href=\"/\"'>Back</button>";
              html += "</div>";
            html += "</form>";
          html += "</div>";
        html += "</main>";
      html += "</body>";
    html += "</html>";


  http->send(200, "text/html; charset=utf-8", html); 

     <!DOCTYPE html>
     <html lang='en'>
     <head>
         <meta charset='utf-8'>
         <meta name='viewport' content='width=device-width,initial-scale=1'/>
     </head>
     <body>
     <form method='POST' action='' enctype='multipart/form-data'>
         Firmware:<br>
         <input type='file' accept='.bin' name='firmware'>
         <input type='submit' value='Update Firmware'>
     </form>
     <form method='POST' action='' enctype='multipart/form-data'>
         FileSystem:<br>
         <input type='file' accept='.bin' name='filesystem'>
         <input type='submit' value='Update FileSystem'>
     </form>
     </body>
     </html>

}
*/

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
  // TODO: Definitionen für User/Passwort
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

          out += "<option value='0'>0. White Color</option>";
          out += "<option value='1'>1. Color</option>";
          out += "<option value='2'>2. Madness</option>";
          out += "<option value='3'>3. Clouds</option>";
          out += "<option value='4'>4. Lava</option>";
          out += "<option value='5'>5. Plasma</option>";
          out += "<option value='6'>6. Rainbow 3D</option>";
          out += "<option value='7'>7. Peacock</option>";
          out += "<option value='8'>8. Zebra</option>";
          out += "<option value='9'>9. Forest</option>";
          out += "<option value='10'>10. Ocean</option>";
          out += "<option value='11'>11. Bouncing balls</option>";
          out += "<option value='12'>12. White bouncing balls</option>";
          out += "<option value='13'>13. Balls with a train</option>";
          out += "<option value='14'>14. Spirals</option>";
          out += "<option value='15'>15. Prismata</option>";
          out += "<option value='16'>16. Flock</option>";
          out += "<option value='17'>17. Flock and predator</option>";
          out += "<option value='18'>18. Sinusoid</option>";
          out += "<option value='19'>19. Metaballs</option>";
          out += "<option value='20'>20. Matrix</option>";
          out += "<option value='21'>21. Fire 2018</option>";
          out += "<option value='22'>22. Fire</option>";
          out += "<option value='23'>23. White Fire</option>";
          out += "<option value='24'>24. Blue Fire</option>";
          out += "<option value='25'>25. Green Fire</option>";
          out += "<option value='26'>26. Whirls of flame</option>";
          out += "<option value='27'>27. Color whirls</option>";
          out += "<option value='28'>28. Waterfall</option>";
          out += "<option value='29'>29. White waterfall</option>";
          out += "<option value='30'>30. Waterfall 4 in 1</option>";
          out += "<option value='31'>31. Pool</option>";
          out += "<option value='32'>32. Slow pulse</option>";
          out += "<option value='33'>33. Fast pulse</option>";
          out += "<option value='34'>34. Rainbow pulse</option>";
          out += "<option value='35'>35. White pulse</option>";
          out += "<option value='36'>36. Comet</option>";
          out += "<option value='37'>37. White comet</option>";
          out += "<option value='38'>38. Plain Comet</option>";
          out += "<option value='39'>39. Pulsating comet</option>";
          out += "<option value='40'>40. Two comets</option>";
          out += "<option value='41'>41. Three comets</option>";
          out += "<option value='42'>42. Soaring fire</option>";
          out += "<option value='43'>43. Top fire</option>";
          out += "<option value='44'>44. Rainbow snake</option>";
          out += "<option value='45'>45. Confetti</option>";
          out += "<option value='46'>46. Rainbow vertical</option>";
          out += "<option value='47'>47. Rainbow horizontal</option>";
          out += "<option value='48'>48. Rainbow diagonal</option>";
          out += "<option value='49'>49. Waves</option>";
          out += "<option value='50'>50. Snowfall</option>";
          out += "<option value='51'>51. Colored rain</option>";
          out += "<option value='52'>52. Snowstorm</option>";
          out += "<option value='53'>53. Starfall</option>";
          out += "<option value='54'>54. Fireflies</option>";
          out += "<option value='55'>55. Fireflies with a train</option>";
          out += "<option value='56'>56. Paintball</option>";
          out += "<option value='57'>57. Wandering Cube</option>";
          out += "<option value='58'>58. Change of color</option>";
          out += "<option value='59'>59. Cloud in the jar</option>";
          out += "<option value='60'>60. Thunder in the jar</option>";
          out += "<option value='61'>61. Twinkles</option>";
          out += "<option value='62'>62. Ticker</option>";
          
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
  // TODO: Definitionen für User/Passwort
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
  // TODO: Definitionen für User/Passwort
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
    EepromManager::SaveModesSettings(&currentMode, modes);
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

  if(http->hasArg("scale")){
    byte scale = http->arg("scale").toInt();
    
    modes[currentMode].Scale = scale;
    loadingFlag = true;
    settChanged = true;
    eepromTimeout = millis();

    //sendCurrent(inputBuffer);

    #if (USE_MQTT)
    if (espMode == 1U)
    {
      MqttManager::needToPublish = true;
    }
    #endif
  }

  if(http->hasArg("brightness")){
    modes[currentMode].Brightness = http->arg("brightness").toInt();
    
    ONflag = true;
    changePower();
    
    FastLED.setBrightness(modes[currentMode].Brightness);

    loadingFlag = true;
    settChanged = true;
    eepromTimeout = millis();

    //sendCurrent(inputBuffer);

    #if (USE_MQTT)
    if (espMode == 1U)
    {
      MqttManager::needToPublish = true;
    }
    #endif
  }
   
  if(http->hasArg("speed")){
    modes[currentMode].Speed = http->arg("speed").toInt();
    loadingFlag = true;
    settChanged = true;
    eepromTimeout = millis();

    //sendCurrent(inputBuffer);

    #if (USE_MQTT)
    if (espMode == 1U)
    {
      MqttManager::needToPublish = true;
    }
    #endif
  }

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
