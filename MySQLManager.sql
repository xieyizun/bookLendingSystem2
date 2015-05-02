#SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT;
#SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS;
#SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION;
SET NAMES "utf8";
SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
	`userID` INT(15) NOT NULL AUTO_INCREMENT,
	`userName` VARCHAR(25) NOT NULL,
	`userPassword` VARCHAR(25) NOT NULL,
	`userEmail` VARCHAR(25) NOT NULL,
	`userPhone` VARCHAR(20) NOT NULL,
	`userAddress` VARCHAR(100) NOT NULL,
	`money` NUMERIC(20,2) NOT NULL,
	PRIMARY KEY (`userID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;

DROP TABLE IF EXISTS `book`;
CREATE TABLE `book` (
	`bookID` INT(15) NOT NULL AUTO_INCREMENT,
	`bookName` VARCHAR(55) NOT NULL,
	`ownerName` VARCHAR(25) NOT NULL,
	`price` NUMERIC(10,2) NOT NULL,
	`state` BOOL NOT NULL default 1,
	`ts` TIMESTAMP NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
	PRIMARY KEY (`bookID`),
	KEY (`bookName`),

	`ownerID` INT(15) NOT NULL,
	KEY (`ownerID`),
	CONSTRAINT `book_ibfk_1` FOREIGN KEY (`ownerID`) REFERENCES `user` (`userID`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;

DROP TABLE IF EXISTS `record`;
CREATE TABLE `record` (
	`recordID` INT(15) NOT NULL AUTO_INCREMENT,
	`bookName` VARCHAR(55) NOT NULL,
	`bookID` INT(15) NOT NULL,
	`lenderID` INT(15),
	`borrowerID` INT(15),
	`price` NUMERIC(10,2) NOT NULL,
	`borrowTime` INT(15) NOT NULL,
	`completed` BOOL NOT NULL default 0,
	PRIMARY KEY (`recordID`),
	
	KEY (`lenderID`),
	KEY (`borrowerID`),
	CONSTRAINT `belong_to_book` FOREIGN KEY (`bookID`) REFERENCES `book` (`bookID`) ON DELETE CASCADE,
	CONSTRAINT `belong_to_lender` FOREIGN KEY (`lenderID`) REFERENCES `user` (`userID`) ON DELETE SET NULL,
	CONSTRAINT `belong_to_borrower` FOREIGN KEY (`borrowerID`) REFERENCES `user` (`userID`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;

DROP PROCEDURE IF EXISTS `lend_book`;

#该存储过程用于在借书时进行行级锁定,同时更新书和用户信息
delimiter $$

CREATE PROCEDURE lend_book (IN bName VARCHAR(55), IN bID INT(15), IN lID INT(15), 
	IN brID INT(15), IN pr NUMERIC(10,2), IN brTime INT(15), IN my NUMERIC(20,2)) 
BEGIN
	START TRANSACTION;

	INSERT INTO record (bookName, bookID, lenderID, borrowerID, price, borrowTime) VALUES (bName, bID, lID, brID, pr, brTime);
	UPDATE user SET money = my WHERE userID = brID;
	UPDATE book SET state = 0 WHERE bookID = bID;

	COMMIT;
END;$$

DROP PROCEDURE IF EXISTS `user_register`;
#用户注册
CREATE PROCEDURE user_register (uName VARCHAR(25), uPassword VARCHAR(25), uEmail VARCHAR(25),
						 uPhone VARCHAR(20), uAddress VARCHAR(100), uMoney  NUMERIC(20,2))
BEGIN
	#SET NAMES "utf8";
	INSERT INTO user (userName, userPassword, userEmail, userPhone, userAddress, money)
	VALUES (uName, uPassword, uEmail, uPhone, uAddress, uMoney);
END;$$

DROP PROCEDURE IF EXISTS `update_userInfo`;
#用户信息更新
CREATE PROCEDURE update_userInfo (type INT(4), info VARCHAR(100), uID INT(15))
BEGIN
	CASE type
	WHEN 1 THEN
		UPDATE user SET userName = info WHERE userID = uID;
	WHEN 2 THEN
		UPDATE user SET userPassword = info WHERE userID = uID;
	WHEN 3 THEN
		UPDATE user SET userEmail = info WHERE userID = uID;
	WHEN 4 THEN
		UPDATE user SET userPhone = info WHERE userID = uID;
	WHEN 5 THEN
		UPDATE user SET userAddress = info WHERE userID = uID;
	END CASE;
END;$$

DROP PROCEDURE IF EXISTS `add_book`;
#添加书籍
CREATE PROCEDURE add_book(bName VARCHAR(55), oName VARCHAR(25), o_id INT(15), pr NUMERIC(10, 2))
BEGIN
	INSERT INTO book (bookName, ownerName, ownerID, price) 
	VALUES (bName, oName, o_id, pr);
END;$$ 

DROP PROCEDURE IF EXISTS `return_book`;
#图书归还
CREATE PROCEDURE return_book (rID INT(15), price NUMERIC(10,2), bID INT(15))
BEGIN
	START TRANSACTION;

	UPDATE record SET completed = 1 WHERE recordID = rID;
	UPDATE user SET money = money + price WHERE userID = bID;
	UPDATE book SET state = 1 WHERE bookID = bID;

	COMMIT;
END;$$