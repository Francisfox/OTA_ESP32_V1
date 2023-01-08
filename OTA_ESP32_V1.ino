#include "configuration.h"

Botao LED1(2);
/*
 * setup function
 */
void setup(void) {
  esp_task_wdt_init(20, true);
  esp_task_wdt_add(NULL);
  startRede();
}

void loop(void) {
  esp_task_wdt_reset();
  LED1.test_Botao();
  server.handleClient();
  delay(1);
}