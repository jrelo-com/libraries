#include <ATCmdExModule.h>

ATCmdExModule::ATCmdExModule(char *key, ATCommandExecutor *atEx, StringBox *stringBox) : Module(key){
	this->atEx = atEx;
	this->inputBuffer  = new StringBuffer(stringBox);
	this->outputBuffer = new StringBuffer(stringBox);
	this->stringBox = stringBox;
}

ATCmdExModule::~ATCmdExModule(){
	delete this->inputBuffer;
	delete this->outputBuffer;
}

void ATCmdExModule::inputData(char *data){
	this->inputBuffer->appendString(data);
	this->needActionFlag = true;
}

void ATCmdExModule::outputData(Pipe *pipe){
	pipe->push('"');
	pipe->push(this->outputBuffer->toString());
	pipe->push('"');
	this->outputBuffer->clear();
}

void ATCmdExModule::update() {	
	if(!this->needActionFlag)
		return;
				
	this->needActionFlag = false;	
	
	char *data = inputBuffer->toString();
	char *part = strtok(data, "&");	
	
	while(part != NULL) {
				
		StringBuffer buffer0(stringBox, part);
		StringBuffer cmd(stringBox);
		StringBuffer pat(stringBox);
		StringBuffer temp(stringBox);
		
		bool result0 = StringBufferUtils::substringBetween(&buffer0 , &cmd, "'",  "'");
		bool result1 = StringBufferUtils::substringBetween(&buffer0 , &pat, ",'",  "'");
				
		if(!result0 || !result1){
			this->inputBuffer->clear(); 
			this->outputBuffer->clear();
			this->outputBuffer->appendString("Wrong format");
			inform();
			return;
		}
							
		cmd.appendString(AT_END_LINE);
		atEx->sendAndCheck(&cmd, &temp, pat.toString(), 15000, 15000);
								
		
		StringBufferUtils::escapeQuotes(&temp, outputBuffer);

		part = strtok(NULL, "&");	
	}
		
	inputBuffer->clear();
	inform();
}
