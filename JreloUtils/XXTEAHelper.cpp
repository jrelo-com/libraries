#include <xxtea.h>
#include <XXTEAHelper.h>
#include <Base64.h>


static char* XXTEAHelper::encryptData(const char *input, int inputLen, const char *encryptionPassword) {
    int size;
    char *data = xxtea_encrypt(input, inputLen, encryptionPassword, &size);
    int encodedLen = base64_enc_len(size)+1;
    char *encoded = new char[encodedLen];
    base64_encode(encoded, data, size);
    delete [] data;

    return encoded;
}


static char* XXTEAHelper::decryptData(const char *input, int inputLen, const char *encryptionPassword) {
    int decodedLen = base64_dec_len(input, inputLen);
    char* decodedData = new char[inputLen] {'\0'};
    base64_decode(decodedData, input, inputLen);
    char *data = xxtea_decrypt(decodedData, decodedLen, encryptionPassword, &decodedLen);
    delete [] decodedData;

    return data;
}
