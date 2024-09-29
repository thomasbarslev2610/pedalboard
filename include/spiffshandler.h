#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"

void setupSpiffs();
void readFile(fs::FS &fs, const char * path);
String returnFileString(fs::FS &fs, const char * path);
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void writeFile(fs::FS &fs, const char * path, const char * message);