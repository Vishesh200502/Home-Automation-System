#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "";   //WIFI SSID
const char* password = "";    //WIFI PASSWORD

/* data received from application */
String  data = "";

/* define L298N or L293D motor control pins */
int Relay1 = 12;    //D6
int Relay2 = 5;    //D1

void setup()
{
  /* initialize motor control pins as output */
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);

  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);

  /* start server communication */
  Serial.begin(115200);
  server.begin();
}

void loop()
{
  /* If the server available, run the "checkClient" function */
  client = server.available();
  if (!client) return;
  data = checkClient ();
  Serial.print(data);
  /************************ Run function according to incoming data from application *************************/

  if (data == "Relay1ON")
  {
    digitalWrite(Relay1, LOW);
  }

  else if (data == "Relay1OFF")
  {
    digitalWrite(Relay1, HIGH);
  }

  else if (data == "Relay2ON")
  {
    digitalWrite(Relay2, LOW);
  }

  else if (data == "Relay2OFF")
  {
    digitalWrite(Relay2, HIGH);
  }
}

/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while (!client.available()) delay(1);
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length() - 9, 9);
  return request;
}
