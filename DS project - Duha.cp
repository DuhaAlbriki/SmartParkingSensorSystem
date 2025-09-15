#include <WiFi.h>
#include <ThingSpeak.h>

/* الكهرباء
    السلك الأحمر + PIN : VIN
    السلك الأسود - PIN : GND
*/

#define TRIG_PIN_SENSOR 2 // Trig Of Ultrasonic السلك البرتقالي
#define ECHO_PIN_SENSOR 15 // Echo Of Ultrasonic السلك الأرق

#define LEDG_PIN 4 // Green LED السلك الأخضر
#define LEDY_PIN 5 // Yellow LED السلك الأصفر
#define LEDR_PIN 18 // Red LED السلاك الأحمر

#define BEEP 19 // Sound of Notification السلك الأبيض

//WiFi
const char* WIFI_SSID = "UJ"; // اسم الوايفاي
const char* WIFI_PASSWORD = "#"; // الباسورد

//ThingSpeak
WiFiClient client; 
unsigned long myChannelNumber = 2342335; // thingspeak channel number
const char * myWriteAPIKey = "9QTH2WNC8PZIOGVQ";  // write API KEY

float duration, distance;

void setup() {

  Serial.begin(9600); // عشان اقدر اطبع في المونيتور
  ThingSpeak.begin(client);

  pinMode(TRIG_PIN_SENSOR, OUTPUT); // send data or control signals
  pinMode(ECHO_PIN_SENSOR, INPUT); // receive data or read signals 


  // بعد القراءة ابغا يطلع لي اياها على اللدات
  pinMode(LEDG_PIN,OUTPUT); 
  pinMode(LEDY_PIN,OUTPUT);
  pinMode(LEDR_PIN,OUTPUT);
  // الصوت
  pinMode(BEEP,OUTPUT);

  //Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi!");

}

void loop() {

  digitalWrite(TRIG_PIN_SENSOR, LOW); // نطفي قراءة الالتراسونيك
  /* LOW, it typically means that you are disabling or
  deactivating a component or device connected to that pin. */
  delayMicroseconds(2); // لمدة ٢ مايكروسكند

  digitalWrite(TRIG_PIN_SENSOR, HIGH); // نشغل قراءة الالتراسونيك
  delayMicroseconds(10); // لمدة ١٠ مايكروسكند

  digitalWrite(TRIG_PIN_SENSOR, LOW); // نطفي قراءة الالتراسونيك

  duration = pulseIn(ECHO_PIN_SENSOR, HIGH); // ؟
  distance = (duration*.0343)/2; // ؟

  // نطبع
  Serial.print("Distance: "); 
  Serial.println(distance);

  int x = ThingSpeak.writeField(myChannelNumber, 1, distance, myWriteAPIKey);
  if(x == 200)
  {
    Serial.println("Channel update successful.");
  }

  // نفترض طول الموقف ٢٠
  // الأخضر لما يكون أكبر من ٢٠ ، يعني الموقف متاح    1
  // 2    الأصفر لما يكون بين ٢٠ و ١٠ ، يعني الموقف داخل أو خارج منه سيارة
  // 3    الأحمر لما يكون أصغر من ١٠ ، يعني الموقف غير متاح 

  if (distance >= 20)
  { // 1
    digitalWrite (LEDG_PIN, HIGH);
    noTone(BEEP);
  }
  else
  { // غيرو حيطفيه
    digitalWrite(LEDG_PIN, LOW);
  }

  if(distance >= 10 && distance <= 20)
  { // 2
    digitalWrite (LEDY_PIN, HIGH);

    for (int i = 0; i < 10; i++)
    {
      tone(BEEP, 1000);
      delay(250);
      noTone(BEEP);
      delay(250);
    }
  }
  else
  { // غيرو حيطفيه
    noTone(BEEP);
    digitalWrite (LEDY_PIN, LOW);
  }

  if(distance <= 10 )
  { // 3
    digitalWrite (LEDR_PIN, HIGH);
    tone(BEEP, 1000); 
  }
  else
  { // غيرو حيطفيه
    noTone(BEEP);
    digitalWrite (LEDR_PIN, LOW);
  }

  delay(500);

  }
