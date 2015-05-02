#include "RecordManager.h"
#include <algorithm>

bool RecordManager::hasInstance = false;
RecordManager* RecordManager::instance = NULL;

RecordManager::RecordManager() {}
RecordManager::~RecordManager() {
	if (instance != NULL) {
		delete instance;
	}
	hasInstance = false;
}

RecordManager* RecordManager::getInstance() {
	if (instance == NULL) {
		instance = new RecordManager();
		hasInstance = true;
	}	
	return instance;
}

void RecordManager::initRecords(const std::vector<Record>& records) {
	this->records.clear();
	std::vector<Record>::const_iterator iter = records.begin();
	while (iter != records.end()) {
		this->records.push_back(*iter);
		iter++;
	}
}

void RecordManager::addRecord(const Record &record) {
	records.push_back(record);
}

std::vector<Record*> RecordManager::listAllMyRecords(int userID) {
	std::vector<Record*> result;
	std::vector<Record>::iterator iter = records.begin();
	while (iter != records.end()) {
		if (userID == iter->getLenderID() || userID == iter->getBorrowerID()) {
			result.push_back(&*iter); //难点,返回地址,方便修改completed
		}
		iter++;
	}
	return result;
}

std::vector<Record*> RecordManager::listMyBorrowerRecords(int userID) {
	std::vector<Record*> result;
	std::vector<Record>::iterator iter = records.begin();
	while (iter != records.end()) {
		if (userID == iter->getBorrowerID()) {
			result.push_back(&*iter);
		}
		iter++;
	}
	return result;
}

std::vector<Record*> RecordManager::listMyLenderRecords(int userID) {
	std::vector<Record*> result;
	std::vector<Record>::iterator iter = records.begin();
	while (iter != records.end()) {
		if (userID == iter->getLenderID()) {
			result.push_back(&*iter);
		}
		iter++;
	}
	return result;
}

void RecordManager::deleteRecord(const Record& record) {
	std::vector<Record>::iterator iter = find(records.begin(), records.end(), record);
	if (iter != records.end()) {
		records.erase(iter);
	}
}