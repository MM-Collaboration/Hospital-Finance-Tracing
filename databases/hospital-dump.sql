-- MariaDB dump 10.19  Distrib 10.7.3-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: hospital
-- ------------------------------------------------------
-- Server version	10.7.3-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `doctors`
--

DROP TABLE IF EXISTS `doctors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `doctors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `specialization` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `qualification` varchar(50) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `doctors`
--

LOCK TABLES `doctors` WRITE;
/*!40000 ALTER TABLE `doctors` DISABLE KEYS */;
INSERT INTO `doctors` VALUES
(19,'Абу Али ибн Сина','хирург','высшая'),
(20,'Агапов Н. И.','невролог','первая'),
(21,'Альбрехт фон Галлер','терапевт','высшая'),
(22,'Аничков Н. Н.','окулист','вторая'),
(23,'Антон де Гане','психолог','первая'),
(24,'Бакулев А. Н.','хирург','вторая'),
(26,'Лучников','хирург','первая');
/*!40000 ALTER TABLE `doctors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `doctors_qualifications`
--

DROP TABLE IF EXISTS `doctors_qualifications`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `doctors_qualifications` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `qualification` varchar(30) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `doctors_qualifications`
--

LOCK TABLES `doctors_qualifications` WRITE;
/*!40000 ALTER TABLE `doctors_qualifications` DISABLE KEYS */;
INSERT INTO `doctors_qualifications` VALUES
(1,'первая'),
(2,'вторая'),
(3,'высшая');
/*!40000 ALTER TABLE `doctors_qualifications` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `doctors_specializations`
--

DROP TABLE IF EXISTS `doctors_specializations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `doctors_specializations` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `specialization` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `doctors_specializations`
--

LOCK TABLES `doctors_specializations` WRITE;
/*!40000 ALTER TABLE `doctors_specializations` DISABLE KEYS */;
INSERT INTO `doctors_specializations` VALUES
(1,'хирург'),
(2,'психолог'),
(3,'невролог'),
(4,'окулист'),
(5,'терапевт');
/*!40000 ALTER TABLE `doctors_specializations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `patients`
--

DROP TABLE IF EXISTS `patients`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `patients` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `date_of_birth` year(4) DEFAULT NULL,
  `phone_number` varchar(15) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `snils` char(11) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=46 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `patients`
--

LOCK TABLES `patients` WRITE;
/*!40000 ALTER TABLE `patients` DISABLE KEYS */;
INSERT INTO `patients` VALUES
(35,'Иванов И. И.',1925,'12345678901','45647898645'),
(36,'Иванов И. В.',2000,'89222446556','45687932451'),
(37,'Алексеев А. М.',1968,'89931330312','12046535973'),
(39,'Александров И. С.',2006,'+79547772442','73595432604'),
(40,'Фдоров',2001,'+79121231234','14253258697'),
(41,'Никитин Э. С.',1992,'89525234434','48787653213'),
(42,'Новиков И. С.',1985,'89772345433','79875434356'),
(43,'Петров',1967,'89131232131','89783434972'),
(44,'Михеев',1999,'89135656343','47376887672'),
(45,'Стрелцов Х. Э.',1999,'89245184020','12345678901');
/*!40000 ALTER TABLE `patients` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `visits`
--

DROP TABLE IF EXISTS `visits`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `visits` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `date` date DEFAULT NULL,
  `patients_id` int(11) DEFAULT NULL,
  `doctors_id` int(11) DEFAULT NULL,
  `diagnosis` varchar(255) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `repeated_visit` tinyint(1) DEFAULT 0,
  `price` double DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `fk_doctor_name` (`doctors_id`),
  KEY `fk_patients_name` (`patients_id`),
  CONSTRAINT `fk_doctor_name` FOREIGN KEY (`doctors_id`) REFERENCES `doctors` (`id`),
  CONSTRAINT `fk_patients_name` FOREIGN KEY (`patients_id`) REFERENCES `patients` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=38 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `visits`
--

LOCK TABLES `visits` WRITE;
/*!40000 ALTER TABLE `visits` DISABLE KEYS */;
INSERT INTO `visits` VALUES
(26,'2022-06-20',35,19,'аппендицит',0,5500),
(30,'2022-05-22',39,24,'короновирус',0,500),
(31,'2022-06-22',39,22,'болен',0,1500),
(32,'2022-06-25',39,24,'болен',1,2500),
(33,'2022-05-03',40,19,'Простуда',0,1500),
(34,'2022-05-16',41,19,'болен',0,1000),
(35,'2022-05-22',40,23,'болен',1,1500),
(36,'2022-05-31',42,21,'Болен',0,2500),
(37,'2022-06-09',35,19,'аппендицит',1,2500);
/*!40000 ALTER TABLE `visits` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-05-26 14:54:45
