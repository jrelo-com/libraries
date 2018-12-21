//~ #include <XUnit.h>

//~ void XUnit::executor(const char *json) {

//~ #ifdef DEBUG
    //~ Serial.print(F("download. json : "));
    //~ Serial.println(json);
//~ #endif

    //~ UJsonListener listener;
    //~ listener.setModules(modules);

    //~ JsonStreamingParser parser;
    //~ parser.setListener(&listener);

    //~ for (unsigned int i = 0; i < strlen(json); i++) {
        //~ parser.parse(json[i]);
    //~ }
    //~ parser.reset();
//~ }

//~ void XUnit::updateValuesInModules() {
    //~ for (int i = 0; i < modules->size(); i++) {

        //~ modules->get(i)->update();

        //~ if (modules->get(i)->needToApply()) {
            //~ modules->get(i)->applied();

            //~ if(modules->get(i)->isFeedback())
                //~ modules->get(i)->inform();
        //~ }
    //~ }
//~ }

//~ void XUnit::getRequest() {
    //~ if(!isReady())
        //~ return;

    //~ StringBuffer sb = StringBuffer(&stringBox);
    //~ bool result = getData(&sb);

    //~ Serial.print(F("GET data - "));
    //~ if(result) {
        //~ Serial.println(F("Success"));
    //~ } else {
        //~ Serial.println(F("Failure"));
    //~ }

    //~ if (!result) {
        //~ return;
    //~ }

    //~ if(encryption) {
        //~ char* json = XXTEAHelper::decryptData(sb.toString(), sb.size(), encryptionPassword);
        //~ executor(json);
        //~ delete [] json;

    //~ } else {
        //~ executor(sb.toString());
    //~ }

//~ }

//~ void XUnit::prepareOutgoingData() {
    //~ if(!isReady())
        //~ return;

    //~ if (!needToSend())
        //~ return;

    //~ bool first = true;
    //~ StringBuffer sb = StringBuffer(&stringBox);
    //~ StringBufferPipe pipe = StringBufferPipe(&sb); // adapter

    //~ sb.append('{');
    //~ for (int i = 0; i < modules->size(); i++) {
        //~ if (modules->get(i)->needToInform()) {

            //~ Module *module = modules->get(i);

            //~ if (!first) {
                //~ sb.append(',');
            //~ } else {
                //~ first = false;
            //~ }

            //~ sb.append('\"');
            //~ sb.appendString(module->getKey());
            //~ sb.appendString("\":");
            //~ module->outputData(&pipe);
            //~ module->informed();
        //~ }
    //~ }
    //~ sb.append('}');
    //~ sb.trim();

//~ #ifdef DEBUG
    //~ Serial.print(F("upload. json : "));
    //~ Serial.println(sb.toString());
//~ #endif

    //~ if (encryption) {
        //~ char *json  = XXTEAHelper::encryptData(sb.toString(), sb.size(), encryptionPassword);
        //~ sb.clear();
        //~ sb.appendString(json);
        //~ sb.trim();
        //~ delete [] json;
    //~ }

    //~ bool result = postData(&sb);
    //~ Serial.print(F("POST data - "));
    //~ if(result) {
        //~ Serial.println(F("Success"));
    //~ } else {
        //~ Serial.println(F("Failure"));
    //~ }
//~ }

//~ bool XUnit::needToSend() {
    //~ bool result = false;

    //~ for (int i = 0; i < modules->size(); i++) {
        //~ if (modules->get(i)->needToInform()) {
            //~ result = true;
            //~ break;
        //~ }
    //~ }
    //~ return result;
//~ }

//~ void XUnit::useEncryption(bool encryption) {
    //~ this->encryption = encryption;
//~ }

//~ void XUnit::setEncryptionPassword(const char *encryptionPassword) {
    //~ this->encryptionPassword = encryptionPassword;
//~ }

//~ void XUnit::putModule(Module *module) {
    //~ this->modules->add(module);
//~ }

//~ XUnit::~XUnit() {
    //~ delete modules;
//~ }

//~ StringBox* XUnit::getStringBox() {
    //~ return &stringBox;
//~ }
