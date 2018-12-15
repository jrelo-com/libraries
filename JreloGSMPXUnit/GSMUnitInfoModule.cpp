#include <GSMUnitInfoModule.h>

GSMUnitInfoModule::GSMUnitInfoModule(char *key, SIMX *simx) : Module(key){
	this->simx = simx;
}

GSMUnitInfoModule::~GSMUnitInfoModule() {}

void GSMUnitInfoModule::update() {
	if(timer.event()){
		inform();
	}
}

void GSMUnitInfoModule::inputData(char *data) {}

void GSMUnitInfoModule::outputData(Pipe *pipe) {
	char temp[5] = {0};
	
	pipe->push("{\"rc\":");
	TypeConverter::intToCharArray(temp, simx->getResetCounter());
	pipe->push(temp);

	pipe->push(",\"v\":");
	TypeConverter::intToCharArray(temp, simx->getVoltage());
	pipe->push(temp);
		
	pipe->push(",\"sq\":");
	TypeConverter::intToCharArray(temp, simx->getSignalQuality());
	pipe->push(temp);
	
	pipe->push("}");	
}
