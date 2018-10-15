#pragma once
#include <Arduino.h>
#include <StringBuffer.h>

class StringBufferUtils {

    public :
    
		static bool concatination(StringBuffer *source, StringBuffer *destination);

		static bool substringBetween(StringBuffer *source, StringBuffer *out, char *firstPatter, char *secondPattern);
		
		static int search(StringBuffer *source, char *pattern);
		
		static int tailSearch(StringBuffer *source, char *pattern);
		
		static bool substring(StringBuffer *source, StringBuffer *out, int first, int last);
		
		static bool escapeQuotes(StringBuffer *source, StringBuffer *out);

};
