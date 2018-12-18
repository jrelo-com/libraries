#include <StringBufferUtils.h>

bool StringBufferUtils::concatination(StringBuffer *source, StringBuffer *destination) {
    if(!destination->appendString(source->toString())) {
        return false;
    }

    return source->trim();
}

bool StringBufferUtils::substringBetween(StringBuffer *source, StringBuffer *out, const char *firstPattern, const char *secondPattern) {

    const char *s = source->toString();

    char *start = strstr(s, firstPattern);
    if(start == NULL) {
        return false;
    }

    int temp0 = start - s + strlen(firstPattern);

    char *stop = strstr(&start[strlen(firstPattern) + 1], secondPattern);
    if(stop == NULL) {
        return false;
    }

    int temp1 = stop - s;
    int length = temp1 - temp0;

    if(length == 0){
        return false;
    }   
      
    for(int i=temp0, j=0; j < length; i++, j++) {
        if(!out->append(s[i])) {
            return false;
        }
    }

    out->trim();
		
    return true;
}

int StringBufferUtils::search(StringBuffer *source, const char *pattern) {
    const char *s = source->toString();

    char *start = strstr(s, pattern);

    if(start == NULL)
        return -1;

    return start - s;
}

int StringBufferUtils::tailSearch(StringBuffer *source, const char *pattern) {
    const char *s = source->toString();
    int index0 = source->size() - 1;
    int length = strlen(pattern);
    int index1 = length -1;
    int count = 0;

    while(index0 >= 0) {
        if(s[index0] == pattern[index1]) {
            ++count;
            --index1;
            if(count == length) {
                return index0;
            }
        } else {
            count = 0;
        }
        index0--;
    }
    return -1;
}

bool StringBufferUtils::substring(StringBuffer *source, StringBuffer *out, int first, int last) {

    const char *s = source->toString();

    for(int i = first, j=0; i < last; i++, j++) {
        if(!out->append(s[i])) {
            return false;
        }
    }

    return out->trim();
}

bool StringBufferUtils::escapeQuotes(StringBuffer *source, StringBuffer *out) {
    const char *s = source->toString();

    bool result = true;
    for(int i=0; i < source->size(); i++) {
        if(s[i] == '"') {
            result = out->append('\\');
            result = out->append('"');
        } else {
            result = out->append(s[i]);
        }
    }

    if(!result) {
        return false;
    }

    return out->trim();
}
