#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record {
	public:
		Record();
		Record(int recordID, std::string bookName_, int bookID, int lenderID_, int borrowerID_,
			double price_, int borrowTime_, bool completed_);

		bool operator==(const Record &other);
		int getRecordID() const;
		std::string getBookName() const;
		int getBookID() const;
		int getLenderID() const;
		int getBorrowerID() const;
		double getPrice() const;
		int getBorrowTime() const;	

		bool getCompleted() const;
		void setCompleted();

	private:
		int recordID;
		std::string bookName;
		int bookID;
		int lenderID; //借出者
		int borrowerID; //借入者
		double price; //书的价格
		int borrowTime; //借阅时间:天
		bool completed; //该借阅记录是否完成,即书是否归还
};

#endif
