#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>

aREST_UI rest = aREST_UI();
WiFiServer server(80);

void setup(void) {
  Serial.begin(115200);

  rest.title("Relay Control");
  rest.button(5);

  WiFi.begin("SSID", "Password");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if(!client) {
    return;
  }

  while(!client.available()) {
    delay(1);
  }

  rest.handle(client);
}
