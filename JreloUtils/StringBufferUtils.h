/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.2
 * */

#pragma once
#include <Arduino.h>
#include <StringBuffer.h>

class StringBufferUtils {

    public :
    
		static bool concatination(StringBuffer *source, StringBuffer *destination);

		static bool substringBetween(StringBuffer *source, StringBuffer *out, const char *firstPatter, const char *secondPattern);
		
		static int search(StringBuffer *source, const char *pattern);
		
		static int tailSearch(StringBuffer *source, const char *pattern);
		
		static bool substring(StringBuffer *source, StringBuffer *out, int first, int last);
		
		static bool escapeQuotes(StringBuffer *source, StringBuffer *out);

};
