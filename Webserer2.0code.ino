#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>


#define LED1 23
#define LED2 22

char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Soniya WebServer</title>
    <style>
        #UI{
            margin-top: 15px;
            background-color: #f8d200;
            width: 300px ;
            height: 500px;
            border: 2px solid black;
            border-radius: 70px;
        }

        .content{
            margin-top: 100px;
        }
        button{
            background-color: rgb(236, 50, 186);
            width: 80px;
            height: 40px;
            border: 1px solid burlywood;
            border-radius: 20px;
            text-decoration: underline;
        }
        button:hover{
            background-color: cadetblue;
        }
        button:active{
            background-color: burlywood;
        }
    </style>
</head>
<body>
    <center>
        <main id="UI">
            <center class="content">
                <h1>Home Automation User Interface :</h1>
    
                <h3>LED_1</h3>
                <button onclick="window.location= 'http://'+location.hostname+/led1/on" >led1-on</button>
                <button onclick="window.location= 'http://'+location.hostname+/led1/off" >led1-off</button>
        
                <h3>LED_2</h3>
                <button onclick="window.location= 'http://'+location.hostname+/led2/on" >led2-on</button>
                <button onclick="window.location= 'http://'+location.hostname+/led2/off" >led2-off</button>
            </center>
        </main>
    </center>
</body>
</html>
)=====";

// ipaddress/led1/on
//ipaddress/led1/off

// ipaddress/led2/on
//ipaddress/led2/off

AsyncWebServer server(80); // server port 80

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}

void setup(void)
{
  
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  
  WiFi.softAP("Soniya" , "Soniya");
  Serial.print("softap : ");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("Soniya")) { //Soniya.local/
    Serial.println("MDNS responder started");
  }

  server.on("/", [](AsyncWebServerRequest * request)
  { 
   
  request->send_P(200, "text/html", webpage);
  });

   server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED1,HIGH);
  request->send_P(200, "text/html", webpage);
  });

  server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED1,LOW);
  request->send_P(200, "text/html", webpage);
  });server.on("/led2/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED2,HIGH);
  request->send_P(200, "text/html", webpage);
  });server.on("/led2/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED2,LOW);
  request->send_P(200, "text/html", webpage);
  });
  server.onNotFound(notFound);

  server.begin();  // it will start webserver
}


void loop(void)
{
}
