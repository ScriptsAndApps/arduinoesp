#include <esp_now.h>
#include <WiFi.h>
bool iets=false;
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;
int pinnnn = 1;
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  pinnnn = myData.b;
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("Bool: ");
  Serial.println(myData.d);
  Serial.println();
  iets=true;
}
 
void setup() {

  pinMode(23, OUTPUT);
  pinMode(2, OUTPUT);

  // Initialize Serial Monitor
  Serial.begin(115200);
  
 

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  if(iets){
    digitalWrite(pinnnn, HIGH); 
 // turn the LED on (HIGH is the voltage level)
    delay(1000); 
    iets=false;
  } 
  else{
    digitalWrite(23, LOW); 
    digitalWrite(2, LOW); 
    delay(10);
  }                   // wait for a second

}