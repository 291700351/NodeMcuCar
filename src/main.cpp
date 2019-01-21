#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <MotorControl.h>

// 配置热点的ssid
#define SSID "ESP8266-CAR"

#define MAX_PACKAGE_SIZE 4

// 电机相关
#define LEFT_EN D1
#define RIGHT_EN D6
#define IN1 D2
#define IN2 D3
#define IN3 D4
#define IN4 D5

void parseData(unsigned char data[2]);
void carMove(unsigned char ctrl);

WiFiServer server(8888);

WiFiClient client;
unsigned char buffer[8];

MotorControl motroCtrl(LEFT_EN, RIGHT_EN, IN1, IN2, IN3, IN4);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setDebugOutput(true);

  IPAddress softLocal(192, 168, 1, 1);
  IPAddress softGateway(192, 168, 1, 1);
  IPAddress softSubnet(255, 255, 255, 0);
  WiFi.softAPConfig(softLocal, softGateway, softSubnet);
  WiFi.softAP(SSID);

  //启动UART传输和服务器
  server.begin();
  server.setNoDelay(true);
  // Serial.println("The Server is start,")
  // Serial.printf("The UDP server IP is : %s , Port is : %d", WiFi.localIP().toString().c_str(), UDP_SERVER_PORT);

  delay(3000);
}

void loop()
{
  // motroCtrl.forward();
  // put your main code here, to run repeatedly:
  if (client && client.connected())
  {
    if (client.available() >= MAX_PACKAGE_SIZE)
    {
      memset(buffer, 0x00, sizeof(buffer));
      client.read(buffer, MAX_PACKAGE_SIZE);

      if (buffer[0] == 0xFF && buffer[MAX_PACKAGE_SIZE - 1] == 0xFF)
      {
        unsigned char data[MAX_PACKAGE_SIZE - 2];
        for (int i = 0; i < MAX_PACKAGE_SIZE - 2; i++)
        {
          data[i] = buffer[i + 1];
        }

        parseData(data);
      }
    }
  }
  else
  {
    client = server.available();
  }
}
void carMove(unsigned char ctrl)
{

  Serial.print("Ctrl= ");
  Serial.print(ctrl);

  if (ctrl == 0x00)
  {

    Serial.print("value = ");
    Serial.println(0);
    motroCtrl.stop();
  }
  else if (ctrl == 0x01)
  {
    Serial.print("value = ");
    Serial.println(1);
    motroCtrl.turnLeft();
  }
  else if (ctrl == 0x02)
  {
    Serial.print("value = ");
    Serial.println(2);
    motroCtrl.forward();
  }
  else if (ctrl == 0x03)
  {
    Serial.print("value = ");
    Serial.println(3);
    motroCtrl.turnRight();
  }
  else if (ctrl == 0x04)
  {
    Serial.print("value = ");
    Serial.println(4);
    motroCtrl.backward();
  }
}

void parseData(unsigned char data[2])
{
  if (data[0] == 0x01)
  {

    carMove(data[1]);
  }
}
