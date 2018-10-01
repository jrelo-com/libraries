#include <ATConsoleModule.h>
#include <StringBufferUtils.h>

ATConsoleModule::ATConsoleModule(char *key, SIM900i2 *sim) : Module(key){
	this->at = sim->getAT();
	this->box = sim->getStringBox();
	this->inBuffer = new StringBuffer(this->box);
	this->outBuffer = new StringBuffer(this->box);
}

ATConsoleModule::~ATConsoleModule(){
	delete inBuffer;
	delete outBuffer;
}

void ATConsoleModule::inputData(char *data){
	this->inBuffer->appendString(data);
	needActionFlag = true;
}

void ATConsoleModule::outputData(Pipe *pipe){
	pipe->push('"');
	pipe->push(this->outBuffer->toString());
	pipe->push('"');
	this->outBuffer->clear();
}

void ATConsoleModule::update() {	
	if(!needActionFlag)
		return;
	
	needActionFlag = false;
	
	char *data = inBuffer->toString();
	char *part = strtok(data, "&");	
	
	while(part != NULL) {
				
		StringBuffer buffer0(box, part);
		StringBuffer cmd(box);
		StringBuffer pat(box);
		StringBuffer temp(box);
		
		bool result0 = StringBufferUtils::substringBetween(&buffer0 , &cmd, "'",  "'");
		bool result1 = StringBufferUtils::substringBetween(&buffer0 , &pat, ",'",  "'");
				
		if(!result0 || !result1){
			this->inBuffer->clear(); 
			this->outBuffer->clear();
			this->outBuffer->appendString("Wrong format");
			inform();
			return;
		}
						
		at->flush();	
		at->send(cmd.toString());
		cmd.clear();
		
		at->send(AT_END);
		delay(25);
		at->readAndCheck(&temp, pat.toString(), AT_END, 20000, 15000);
		pat.clear();
		delay(25);
		at->flush();
		
		StringBufferUtils::escapeQuotes(&temp, outBuffer);

		part = strtok(NULL, "&");	
	}
		
	inBuffer->clear();
	inform();
}
