-- MySQL dump 10.13  Distrib 5.7.12, for Win64 (x86_64)
--
-- Host: localhost    Database: erasmus
-- ------------------------------------------------------
-- Server version	5.7.16-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `catalog`
--

DROP TABLE IF EXISTS `catalog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `catalog` (
  `ID` int(11) NOT NULL,
  `Nume_curs` longtext CHARACTER SET utf8mb4,
  `Cod_curs` varchar(50) CHARACTER SET utf8mb4 DEFAULT NULL,
  `ECTS` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `catalog`
--

LOCK TABLES `catalog` WRITE;
/*!40000 ALTER TABLE `catalog` DISABLE KEYS */;
INSERT INTO `catalog` VALUES (1,'Technical Mechanics','UPB.06.D.01.O.001',5),(2,'Mathematics 1','UPB.06.F.01.O.002',4),(3,'General Chemistry','UPB.06.F.01.O.003',5),(4,'Computer Programming 1','UPB.06.F.01.O.004',6),(5,'Communication','UPB.06.C.01.O.005',4),(6,'English language','UPB.06.C.01.O.006',3),(7,'Foreign Languages 1 - French','UPB.06.C.01.A.008',3),(8,'Foreign Languages 1 - Romanian','UPB.06.C.01.A.009',3),(9,'Foreign Languages 1 - German','UPB.06.C.01.A.010',3),(10,'Sport','UPB.06.C.01.L.001',2),(11,'Ethics','UPB.06.C.01.L.002',5),(1,'Technical Mechanics','UPB.06.D.01.O.001',5),(2,'Mathematics 1','UPB.06.F.01.O.002',4),(3,'General Chemistry','UPB.06.F.01.O.003',5),(4,'Computer Programming 1','UPB.06.F.01.O.004',6),(5,'Communication','UPB.06.C.01.O.005',4),(6,'English language','UPB.06.C.01.O.006',3),(7,'Foreign Languages 1 - French','UPB.06.C.01.A.008',3),(8,'Foreign Languages 1 - Romanian','UPB.06.C.01.A.009',3),(9,'Foreign Languages 1 - German','UPB.06.C.01.A.010',3),(10,'Sport','UPB.06.C.01.L.001',2),(11,'Ethics','UPB.06.C.01.L.002',5);
/*!40000 ALTER TABLE `catalog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `elevi`
--

DROP TABLE IF EXISTS `elevi`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `elevi` (
  `ID` int(11) NOT NULL,
  `Nume` varchar(50) DEFAULT NULL,
  `Prenume` varchar(50) DEFAULT NULL,
  `CNP` varchar(13) DEFAULT NULL,
  `Tara_provenienta` varchar(50) DEFAULT NULL,
  `Mail` varchar(50) DEFAULT NULL,
  `Universitate_prov` varchar(50) DEFAULT NULL,
  `Tip_studii` varchar(50) DEFAULT NULL,
  `Catalog` longtext,
  `Durata_stagiu` double DEFAULT NULL,
  `Semestru` int(11) DEFAULT NULL,
  `Observatii` longtext
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `elevi`
--

LOCK TABLES `elevi` WRITE;
/*!40000 ALTER TABLE `elevi` DISABLE KEYS */;
INSERT INTO `elevi` VALUES (1,'Popa','Ion','1950222035286','Japonia','ion2345@yahoo.com',NULL,NULL,NULL,NULL,NULL,NULL),(1,'Popa','Ion','1950222035286','Japonia','ion2345@yahoo.com',NULL,NULL,NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `elevi` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tari`
--

DROP TABLE IF EXISTS `tari`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `tari` (
  `ID` int(11) NOT NULL,
  `Cod_tara` varchar(50) DEFAULT NULL,
  `Nume_tara` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tari`
--

LOCK TABLES `tari` WRITE;
/*!40000 ALTER TABLE `tari` DISABLE KEYS */;
/*!40000 ALTER TABLE `tari` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `universitati`
--

DROP TABLE IF EXISTS `universitati`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `universitati` (
  `ID` int(11) NOT NULL,
  `Universitatea` longtext,
  `Cod_acord` longtext,
  `Pers_contact` longtext
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `universitati`
--

LOCK TABLES `universitati` WRITE;
/*!40000 ALTER TABLE `universitati` DISABLE KEYS */;
/*!40000 ALTER TABLE `universitati` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-12-05  9:42:37
