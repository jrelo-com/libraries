#include <StringBox.h>
#include <StringBuffer.h>
#include <StringBufferUtils.h>

void setup() {

    Serial.begin(9600);
    Serial.print(F("StringBufferUtils\r\n\r\n"));

    StringBox box(128);
    box.init();

    StringBuffer buffer0(&box);
    StringBuffer buffer1(&box);

    Serial.println(F("Method => bool concatination(StringBuffer *source, StringBuffer *destination)"));

    buffer0.appendString("FirstString");
    buffer1.appendString("SecondString");

    Serial.print(F("source => "));
    Serial.println(buffer1.toString());
    Serial.print(F("distanation => "));
    Serial.println(buffer0.toString());

    bool result = StringBufferUtils::concatination(&buffer1, &buffer0);
    Serial.println(F("After calling the method"));
    Serial.print(F("Return => "));
    Serial.println(result);
        
	Serial.print(F("source => "));
    Serial.println(buffer1.toString());
    Serial.print(F("distanation => "));
    Serial.println(buffer0.toString());

    Serial.print(F("Test => "));
    if(strcmp(buffer0.toString(), "FirstStringSecondString") == 0) {
        Serial.println(F("PASSED"));
    } else {
        Serial.println(F("FAILURE"));
    }

    buffer0.clear();
    buffer1.clear();
/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */
    Serial.println(F("\r\n\r\nMethod => bool substringBetween(StringBuffer *source, StringBuffer *out, char *firstPatter, char *secondPattern)"));
    
    buffer0.appendString("text >>>AREA<<< text");
    const char *firstPattern = ">>>";
    const char *secondPattern = "<<<";
    Serial.print(F("source => "));
    Serial.println(buffer0.toString());
    Serial.print(F("out => "));
    Serial.println(buffer1.toString());
    Serial.print(F("firstPattern => "));
    Serial.println(firstPattern);
    Serial.print(F("secondPattern => "));
    Serial.println(secondPattern);
    
    result = StringBufferUtils::substringBetween(&buffer0, &buffer1, firstPattern, secondPattern);
    Serial.println(F("After calling the method"));
    Serial.print(F("Returt => "));
    Serial.println(result);
    	
	Serial.print(F("source => "));
    Serial.println(buffer0.toString());
    Serial.print(F("out => "));
    Serial.println(buffer1.toString());

	Serial.print(F("Test => "));
    if(strcmp(buffer1.toString(), "AREA") == 0) {
        Serial.println(F("PASSED"));
    } else {
        Serial.println(F("FAILURE"));
    }
    
    buffer0.clear();
    buffer1.clear();
/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */
    Serial.println(F("\r\n\r\nMethod => int search(StringBuffer *source, char *pattern)"));

    buffer0.appendString("#abc 123AREA123 xyz$$");
    const char *pattern = "123";
    Serial.print(F("source => "));
    Serial.println(buffer0.toString());
    Serial.print(F("pattern => "));
    Serial.println(pattern);

    int index = StringBufferUtils::search(&buffer0, pattern);
    Serial.println(F("After calling the method"));
    Serial.print(F("Index => "));
    Serial.println(index);

	Serial.print(F("Test => "));
    if(index == 5) {
        Serial.println(F("PASSED"));
    } else {
        Serial.println(F("FAILURE"));
    }
	buffer0.clear();
/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */
    Serial.println(F("\r\n\r\nMethod => int tailSearch(StringBuffer *source, char *pattern)"));

    buffer0.appendString("#abc 123_123 xyz$$");
    pattern = "123";
    Serial.print(F("source => "));
    Serial.println(buffer0.toString());
    Serial.print(F("pattern => "));
    Serial.println(pattern);

    index = StringBufferUtils::tailSearch(&buffer0, pattern);
    Serial.println(F("After calling the method"));
    Serial.print(F("Index => "));
    Serial.println(index);

	Serial.print(F("Test => "));
    if(index == 9) {
        Serial.println(F("PASSED"));
    } else {
        Serial.println(F("FAILURE"));
    }
	buffer0.clear();
/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */
    Serial.println(F("\r\n\r\nMethod => bool substring(StringBuffer *source, StringBuffer *out, int first, int last)"));
    
    buffer0.appendString("https://jrelo.com");
	int first = 8;
	int last  = 13;
    Serial.print(F("source => "));
    Serial.println(buffer0.toString());
    Serial.print(F("out => "));
    Serial.println(buffer1.toString());
    Serial.print(F("first => "));
    Serial.println(first);
    Serial.print(F("last => "));
    Serial.println(last);
    
    result = StringBufferUtils::substring(&buffer0, &buffer1, first, last);
	Serial.println(F("After calling the method"));
	
	Serial.print(F("Returt => "));
    Serial.println(result);
		
	Serial.print(F("source => "));
    Serial.println(buffer0.toString());
    Serial.print(F("out => "));
    Serial.println(buffer1.toString());

	Serial.print(F("Test => "));
    if(strcmp(buffer1.toString(), "jrelo") == 0) {
        Serial.println(F("PASSED"));
    } else {
        Serial.println(F("FAILURE"));
    }
    
    buffer0.clear();
    buffer1.clear();
/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */
    Serial.println(F("\r\n\r\nMethod => bool escapeQuotes(StringBuffer *source, StringBuffer *out)"));
    
    buffer0.appendString("welcome to \"MAY\" world");
    Serial.print(F("source => "));
    Serial.println(buffer0.toString());
    Serial.print(F("out => "));
    Serial.println(buffer1.toString());
    
    Serial.println(F("After calling the method"));
    
    result = StringBufferUtils::escapeQuotes(&buffer0, &buffer1);
    Serial.print(F("Returt => "));
    Serial.println(result);
    	
	Serial.print(F("source => "));
    Serial.println(buffer0.toString());
    Serial.print(F("out => "));
    Serial.println(buffer1.toString());

	Serial.print(F("Test => "));
    if(strcmp(buffer1.toString(), "welcome to \\\"MAY\\\" world") == 0) {
        Serial.println(F("PASSED"));
    } else {
        Serial.println(F("FAILURE"));
    }
    
    buffer0.clear();
    buffer1.clear();

}

void loop() {}
