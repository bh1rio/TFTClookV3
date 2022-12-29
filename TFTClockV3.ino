#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include "TFT_eSPI.h"
#include "binaryttf.h"
#include "OpenFontRender.h"

TFT_eSPI tft;
OpenFontRender render;
int i=0;

//串口输出时间
void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

//时间可用的回调函数
void timeavailable(struct timeval *t)
{
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}

void setup() {
  Serial.begin(115200);
  delay(100);

  sntp_set_time_sync_notification_cb(timeavailable);
  sntp_setoperatingmode(SNTP_OPMODE_POLL);
  sntp_setservername(0, "time.windows.com");
  sntp_init();
  // 将时区设置为中国标准时间
  setenv("TZ", "CST-8", 1);
  tzset();

  Serial.print("Connecting......");
  WiFi.begin("zhangchi","070329yy");
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(300);
    Serial.print(".");
  }

  Serial.println("WiFi connected.");
  Serial.println("IP Address:");
  Serial.println(WiFi.localIP());

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  if(render.loadFont(binaryttf,sizeof(binaryttf)))
  {
    Serial.println("Render initialize error");
  }
  render.setDrawer(tft);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  render.setFontColor(TFT_WHITE,TFT_BLACK);
  render.printf("HelloWorld");
  render.seekCursor(0,10*i);
  i++;
}
