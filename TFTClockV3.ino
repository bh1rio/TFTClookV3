#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include "TFT_eSPI.h"
#include "binaryttf.h"
#include "OpenFontRender.h"

TFT_eSPI tft;
OpenFontRender render;

uint8_t now_date[16],now_hour[3],now_minute[3],now_second[3],colon[2];
time_t now;
char Date[16],tDate[16],Hour[3],tHour[3],Minute[3],tMinute[3],Second[3];
struct tm timeinfo;

void setup() {
  Serial.begin(115200);
  delay(100);

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
  time(&now);
  localtime_r(&now, &timeinfo);
  //Serial.printf("%d-%d-%d %d:%d:%d\n",timeinfo.tm_year+1900,timeinfo.tm_mon+1,timeinfo.tm_mday,timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
  render.setFontColor(TFT_WHITE);
  render.printf("%d-%d-%d\n",timeinfo.tm_year+1900,timeinfo.tm_mon+1,timeinfo.tm_mday);
  delay(1000);
}
