#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include <string>
#include <vector>
#include "Record.h"

class RecordManager {
	public:
		~RecordManager();
		static RecordManager* getInstance();

		void initRecords(const std::vector<Record> &records);
		void addRecord(const Record &record);
		std::vector<Record*> listAllMyRecords(int userID);
		std::vector<Record*> listMyBorrowerRecords(int userID);
		std::vector<Record*> listMyLenderRecords(int userID);

		void deleteRecord(const Record& record);

	private:
		RecordManager();
		RecordManager(const RecordManager&);
		RecordManager& operator=(const RecordManager&);

		std::vector<Record> records;

		static bool hasInstance;
		static RecordManager *instance;
};

#endif
