#include <ExternalLogger.h>
#include <StringBox.h>

StringBox stringBox(512);
ExternalLogger logger("LOG.txt", &Serial, &stringBox);

void setup() {
  Serial.begin(9600);
  
  stringBox.init();
  logger.init();
}

void loop() {

  logger.update();
  stringBox.update();
  
}
