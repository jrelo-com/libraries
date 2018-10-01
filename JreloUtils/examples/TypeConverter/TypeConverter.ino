#include <TypeConverter.h>

void setup() {

    Serial.begin(9600);
    Serial.print(F("TypeConverter\r\n\r\n"));
    
	Serial.println(F("Long => char array"));
    long l = -2147483648;
    char data0[12] = {0};
    TypeConverter::longToCharArray(data0, l);
    Serial.println(data0);


	Serial.println(F("UnsignedLong => char array"));
    unsigned long ul = 3333333333;
    char data[11] = {0};
    TypeConverter::unsignedLongToCharArray(data, ul);
    Serial.println(data);


	Serial.println(F("Integer => char array"));
    int i = -32768;
    char data1[7] = {0};
    TypeConverter::intToCharArray(data1, i);
    Serial.println(data1);
	
	
	Serial.println(F("Boolean => char array"));
	bool b = true;
    char data2[6] = {0};
    TypeConverter::boolToCharArray(data2, b);
    Serial.println(data2);
	
	
	Serial.println(F("Float => char array"));
	float f = -3.14159265359;
    char data3[14] = {0};
    TypeConverter::floatToCharArray(data3, f, 8, 7);
    Serial.println(data3);
	

	Serial.println(F("Char array => integer"));
	char data4[] = "-32768";
	int result0 = TypeConverter::charArrayToInt(data4);
	Serial.println(result0);
	
	
	Serial.println(F("Char array => long"));
	char data5[] = "-2147483648";
	long result1 = TypeConverter::charArrayToLong(data5);
	Serial.println(result1);
	
		
	Serial.println(F("Char array => boolean"));
	char data6[] = "true";
	bool result2 = TypeConverter::charArrayToBool(data6);
	Serial.println(result2);
	
	
	Serial.println(F("Char array => float"));	
	char data7[] = "-3.1415";
	float result3 = TypeConverter::charArrayToFloat(data7);
	char data8[9] = {0};
	TypeConverter::floatToCharArray(data8, result3, 8, 4);
	Serial.print(F("f => "));
	Serial.print(f);
	Serial.print(F(" toCharArray => "));
	Serial.println(data8);
	
	
	
	Serial.println(F("Char array => unsigned long"));	
	char data9[] = "1538268971";
	unsigned long result4 = TypeConverter::charArrayToUnsignedLong(data9);
	Serial.println(result4);

}

void loop() {}
