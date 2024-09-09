/*
SQLyog Community v13.1.5  (64 bit)
MySQL - 10.4.22-MariaDB : Database - db_oms_xo
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`db_oms_xo` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;

USE `db_oms_xo`;

/*Table structure for table `tbl_trades` */

DROP TABLE IF EXISTS `tbl_trades`;

CREATE TABLE `tbl_trades` (
  `id` int(12) unsigned NOT NULL AUTO_INCREMENT,
  `num_of_shares` int(12) DEFAULT NULL,
  `symbol` varchar(12) DEFAULT NULL,
  `market_order` varchar(12) DEFAULT NULL,
  `user_id` varchar(12) DEFAULT NULL,
  `total_amount` float DEFAULT NULL,
  `date_executed` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8mb4;

/*Data for the table `tbl_trades` */

insert  into `tbl_trades`(`id`,`num_of_shares`,`symbol`,`market_order`,`user_id`,`total_amount`,`date_executed`) values 
(1,14,'PRV','BOUGHT','1123',942,'2024-09-07 18:21:02'),
(2,23,'PNT','BOUGHT','1123',1000,'2024-09-07 18:22:32'),
(3,83,'MBU','BOUGHT','1123',600,'2024-09-07 18:25:34'),
(4,51,'UUE','BOUGHT','1123',343,'2024-09-07 18:28:25'),
(5,26,'PEW','BOUGHT','1123',799,'2024-09-07 18:28:28'),
(6,50,'SIC','SOLD','1123',566,'2024-09-07 18:28:29'),
(7,55,'JZI','SOLD','1123',455,'2024-09-07 18:28:30'),
(8,50,'YOG','BOUGHT','1123',511,'2024-09-07 18:33:39'),
(9,89,'DNJ','SOLD','1123',234,'2024-09-07 18:33:43'),
(10,12,'OEC','SOLD','1123',532,'2024-09-07 18:34:05'),
(11,41,'CMP','SELL','1123',909,'2024-09-07 18:55:39'),
(12,56,'SMO','SELL','1123',311,'2024-09-07 19:00:12'),
(13,89,'WXA','BOUGHT','1123',500,'2024-09-07 20:42:11'),
(14,12,'DHN','BOUGHT','1123',12423,'2024-09-07 21:12:09'),
(15,15,'ATM','BOUGHT','1123',444,'2024-09-07 21:18:25'),
(16,25,'UCQ','BOUGHT','1123',158,'2024-09-09 00:46:35'),
(17,32,'KJT','SELL','1123',245,'2024-09-09 00:48:27'),
(18,38,'AZQ','BOUGHT','1123',208,'2024-09-09 09:11:19'),
(19,78,'VUU','BOUGHT','1123',310,'2024-09-09 13:59:38'),
(20,69,'KJO','SELL','1123',272,'2024-09-09 13:59:41'),
(21,31,'MEB','BOUGHT','1123',992,'2024-09-09 14:32:31'),
(22,71,'ZTH','SELL','1123',903,'2024-09-09 14:32:34'),
(23,63,'SSM','BOUGHT','sven33',629,'2024-09-09 14:35:23'),
(24,36,'NND','SELL','sven33',495,'2024-09-09 14:35:26'),
(25,82,'EBI','BOUGHT','Tin23',744,'2024-09-09 15:02:05'),
(26,94,'SOT','BOUGHT','Tin23',664,'2024-09-09 15:02:07'),
(27,12,'XDN','SELL','Tin23',971,'2024-09-09 15:02:10'),
(28,21,'LEZ','SELL','Tin23',969,'2024-09-09 15:02:13'),
(29,46,'YDM','BOUGHT','sven33',193,'2024-09-09 15:55:03'),
(30,95,'JJQ','SELL','sven33',197,'2024-09-09 15:55:06');

/*Table structure for table `tbl_user` */

DROP TABLE IF EXISTS `tbl_user`;

CREATE TABLE `tbl_user` (
  `id` int(12) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(64) DEFAULT NULL,
  `age` int(4) unsigned DEFAULT NULL,
  `user_id` varchar(12) DEFAULT NULL,
  `date_created` datetime DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8mb4;

/*Data for the table `tbl_user` */

insert  into `tbl_user`(`id`,`name`,`age`,`user_id`,`date_created`) values 
(1,'Julia',30,'1123','2024-09-08 12:22:19'),
(2,'Hanshin',30,'345','2024-09-08 12:21:53'),
(3,'Andrei',30,'xyz','2024-09-08 12:21:58'),
(4,'Bambi',30,'def','2024-09-08 12:22:02'),
(5,'Yhuan',30,'abc','2024-09-08 12:21:15'),
(6,'Yhuna',30,'9876','2024-09-08 12:21:18'),
(7,'Yhuni',30,'1234','2024-09-08 12:21:20'),
(8,'Don',30,'admin','2024-09-08 12:21:24'),
(11,'Naru',44,'Naru44','2024-09-09 10:40:56'),
(12,'Sven',33,'Sven33','2024-09-09 10:54:40'),
(13,'gon',12,'gon12','2024-09-09 13:07:12'),
(14,'Tina',36,'Tin23','2024-09-09 15:01:37');

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
