-- MySQL dump 10.13  Distrib 5.1.41, for redhat-linux-gnu (i386)
--
-- Host: localhost    Database: gnuaetest
-- ------------------------------------------------------
-- Server version	5.1.41

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
-- Table structure for table `batteries`
--

DROP TABLE IF EXISTS `batteries`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `batteries` (
  `itemID` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `manufacturer` varchar(255) NOT NULL,
  `price` double NOT NULL,
  `voltage` int(11) NOT NULL,
  `rate20` int(11) NOT NULL,
  `rate100` int(11) NOT NULL,
  KEY `name` (`name`),
  KEY `itemID` (`itemID`),
  KEY `itemID_2` (`itemID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `batteries`
--

LOCK TABLES `batteries` WRITE;
/*!40000 ALTER TABLE `batteries` DISABLE KEYS */;
INSERT INTO `batteries` VALUES (30020,'6HHG-31PS','Surette',279,6,344,430),(30019,'4CS-25S','Surette',718,4,1350,1900),(30018,'4CS-21S','Surette',599,4,1104,1557),(30017,'4CS-17S','Surette',284,4,546,770),(30016,'S-530','Surette',198,6,530,530),(30015,'S-460','Surette',173,6,350,460),(30014,'180AH Gell Cell',' Real Goods',189,6,180,0),(30013,'225AH Gell Cell',' Real Goods',399,12,225,0),(30012,'183AH Gell Cell','Real Goods',339,12,183,0),(30011,'98AH Gell Cell','Real Goods',189,12,98,0),(30010,'86AH Gell Cell','Real Goods',159,12,86,0),(30009,'74AH Gell Cell','Real Goods',149,12,74,0),(30008,'51AH Gell Cell','Real Goods',119,12,51,0),(30007,'32AH Gell Cell','Real Goods',69,12,32,0),(30006,'L16H','Trojan',258,6,395,0),(30005,'L16P','Trojan',234,6,360,0),(30004,'L16G','Trojan',209,6,350,0),(30003,'T145','Trojan',145,6,244,0),(30002,'T125','Trojan',109,6,235,0),(30001,'T105','Trojan',95,6,225,0),(30021,'6EHG-31PS','Surette',332,6,410,512),(30022,'6CS-17PS','Surette',478,6,546,770),(30023,'6CS-21PS','Surette',534,6,683,963),(30024,'6CS-25PS','Surette',642,6,820,1156),(30025,'8HHG-31PS','Surette',372,8,344,430),(30026,'8EHG-31PS','Surette',444,8,410,512),(30027,'8CS-17PS','Surette',621,8,546,770),(30028,'8CS-25PS','Surette',933,8,820,1156);
/*!40000 ALTER TABLE `batteries` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `centers`
--

DROP TABLE IF EXISTS `centers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `centers` (
  `itemID` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `manufacturer` varchar(255) NOT NULL,
  `voltage` int(11) NOT NULL,
  KEY `name` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `centers`
--

LOCK TABLES `centers` WRITE;
/*!40000 ALTER TABLE `centers` DISABLE KEYS */;
INSERT INTO `centers` VALUES (0,'SW4024','Xantrax',24),(0,'SW4048','Xantrax',48),(0,'SW5548','Xantrax',48),(0,'SW4024','Xantrax',24),(0,'SW4048','Xantrax',48),(0,'SW5548','Xantrax',48),(0,'DR1512','Xantrax',12),(0,'DR1512','Xantrax',12),(0,'DR2412','Xantrax',12),(0,'DR2412','Xantrax',12),(0,'DR1524','Xantrax',24),(0,'DR1524','Xantrax',24),(0,'DR2424','Xantrax',24);
/*!40000 ALTER TABLE `centers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `chargers`
--

DROP TABLE IF EXISTS `chargers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chargers` (
  `itemID` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `manufacturer` varchar(255) NOT NULL,
  `price` double NOT NULL,
  `amperage` int(11) NOT NULL,
  `volts_in` int(11) NOT NULL,
  `volts_out` int(11) NOT NULL,
  `efficiency` double NOT NULL,
  `openmax` double NOT NULL,
  `LCD` tinyint(1) NOT NULL,
  `MPPT` tinyint(1) NOT NULL,
  `PWM` tinyint(1) NOT NULL,
  `tempsensor` tinyint(1) NOT NULL,
  `remote` tinyint(1) NOT NULL,
  KEY `name` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chargers`
--

LOCK TABLES `chargers` WRITE;
/*!40000 ALTER TABLE `chargers` DISABLE KEYS */;
INSERT INTO `chargers` VALUES (40017,'PS-30','Morningstar',152,30,24,24,1,0,0,0,0,0,0),(40016,'PS-15M-48V','Morningstar',222,15,48,48,1,0,0,0,0,0,0),(40015,'PS-15M','Morningstar',179,15,24,24,1,0,0,0,0,0,0),(40014,'PS-15','Morningstar',112,15,24,24,1,0,0,0,0,0,0),(40013,'TS-60','Morningstar',199,60,24,24,1,0,0,0,0,0,0),(40012,'TS-45','Morningstar',159,45,24,24,1,0,0,0,0,0,0),(40011,'C60','Xantrex',199,60,24,24,1,0,0,0,0,0,0),(40010,'C40','Xantrex',159,40,48,24,1,0,0,0,0,0,0),(40009,'C35','Xantrex',119,35,24,24,1,0,0,0,0,0,0),(40008,'Solarboost 6024HDL','RV Products',589,60,48,24,0.95,125,0,0,0,0,0),(40007,'Solarboost 6024HL','RV Products',509,60,48,24,0.95,125,0,0,0,0,0),(40006,'Solarboost 3048DL','RV Products',559,30,48,48,0.97,125,0,0,0,0,0),(40005,'Solarboost 3048','RV Products',479,30,48,48,0.97,125,0,0,0,0,0),(40004,'Solarboost 2000E','RV Products',229,30,48,24,0.95,125,0,0,0,0,0),(40003,'Solarboost 50DL','RV Products',499,50,24,24,0.97,125,0,0,0,0,0),(40002,'solarboost 50L','RV Products',419,50,24,24,0.97,125,0,0,0,0,0),(40001,'MX60','Outback',649,60,60,24,1,125,0,0,0,0,0),(40018,'PS-30M','Morningstar',152,30,24,24,1,0,0,0,0,0,0),(40019,'SS-6-12V','Morningstar',48,6,12,12,1,0,0,0,0,0,0),(40020,'SS-6L-12V','Morningstar',59,6,12,12,1,0,0,0,0,0,0),(40021,'SS-10-12V','Morningstar',55,10,12,12,1,0,0,0,0,0,0),(40022,'SS-10L-12V','Morningstar',70,10,12,12,1,0,0,0,0,0,0),(40023,'SS-10L-24V','Morningstar',76,10,24,24,1,0,0,0,0,0,0),(40024,'SS-20L-12V','Morningstar',95,20,12,12,1,0,0,0,0,0,0),(40025,'SS-20L-24V','Morningstar',101,20,24,24,1,0,0,0,0,0,0),(40026,'SG-4','Morningstar',30,5,12,12,1,0,0,0,0,0,0);
/*!40000 ALTER TABLE `chargers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `combiners`
--

DROP TABLE IF EXISTS `combiners`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `combiners` (
  `itemID` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `manufacturer` varchar(255) NOT NULL,
  `price` double NOT NULL,
  `circuits` int(11) NOT NULL,
  `conductors` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `combiners`
--

LOCK TABLES `combiners` WRITE;
/*!40000 ALTER TABLE `combiners` DISABLE KEYS */;
INSERT INTO `combiners` VALUES (20001,'PSPV','Outback',139,12,2),(20002,'TCB10','Trace',229,10,2),(20003,'TCB6','Trace',189,6,1),(20004,'Custom','Yourself',250,12,2),(20005,'PCB10','Pulse',199,10,2);
/*!40000 ALTER TABLE `combiners` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `inverters`
--

DROP TABLE IF EXISTS `inverters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `inverters` (
  `itemID` int(11) NOT NULL,
  `name` text NOT NULL,
  `manufacturer` text NOT NULL,
  `price` double NOT NULL,
  `wattage` double NOT NULL,
  `voltage` int(11) NOT NULL,
  `LCD` tinyint(1) NOT NULL,
  `charger` tinyint(1) NOT NULL,
  `remote` tinyint(1) NOT NULL,
  `tempsensor` tinyint(1) NOT NULL,
  `sinewave` tinyint(1) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `inverters`
--

LOCK TABLES `inverters` WRITE;
/*!40000 ALTER TABLE `inverters` DISABLE KEYS */;
INSERT INTO `inverters` VALUES (0,'Trace 2548','Xantrex',1995,2500,24,0,0,0,0,0),(0,'Trace 2536','Xantrex',1900,2500,24,0,0,0,0,0),(0,'Trace 2232','Xantrex',1475,2200,24,0,0,0,0,0),(0,'Trace DR2424','Xantrex',1225,2400,24,0,0,0,0,0),(0,'Trace DR1524','Xantrex',895,1500,24,0,0,0,0,0),(0,'Trace 724','Xantrex',725,425,24,0,0,0,0,0),(0,'Trace SW2512','Xantrex',2485,2500,12,0,0,0,0,0),(0,'Trace 2512','Xantrex',1575,2500,12,0,0,0,0,0),(0,'Trace DR2412','Xantrex',1285,2400,12,0,0,0,0,0),(0,'Trace DR1512','Xantrex',950,1500,12,0,0,0,0,0),(0,'Trace 812','Xantrex',650,575,2,0,0,0,0,0),(0,'Trace SW4024','Xantrex',3185,4000,24,0,0,0,0,0),(0,'Trace SW4048','Xantrex',3185,4000,48,0,0,0,0,0),(0,'Trace SW5048','Xantrex',3680,5500,48,0,0,0,0,0),(0,'Heart Freedom 10','Xantrex',1095,1000,24,0,0,0,0,0),(0,'Heart Freedom 20','Xantrex',1095,2000,24,0,0,0,0,0),(0,'Heart Freedom 25','Xantrex',1655,2500,24,0,0,0,0,0),(0,'Heart HF-12-600','Xantrex',600,300,24,0,0,0,0,0);
/*!40000 ALTER TABLE `inverters` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `loads`
--

DROP TABLE IF EXISTS `loads`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `loads` (
  `itemID` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `description` varchar(255) NOT NULL,
  `manufacturer` varchar(255) NOT NULL,
  `type` enum('NOLOAD','AC','DC') NOT NULL,
  `group` enum('NOGROUP','HOUSEHOLD','TOOLS','KITCHEN','DIGITAL') NOT NULL,
  `voltage` int(11) NOT NULL,
  `wattage` int(11) NOT NULL,
  `amperage` int(11) NOT NULL,
  KEY `name` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `loads`
--

LOCK TABLES `loads` WRITE;
/*!40000 ALTER TABLE `loads` DISABLE KEYS */;
INSERT INTO `loads` VALUES (50001,'Pressure Booster','Pressure Booster','Flowlight','DC','HOUSEHOLD',24,180,0),(50002,'PC Speakers','PC Speakers','Yamaha','AC','DIGITAL',120,4,0),(50003,'Nokia Charger','5660 Cell Phone Charger','Nokia','AC','DIGITAL',120,3,0),(50004,'Maxon Charger','Charger for Maxon 201+3','','AC','DIGITAL',120,1,0),(50005,'Laser Printer','HP LaserJet 5MP','','AC','DIGITAL',120,200,2),(50006,'Laptop','Omnibook6100 Laptop','HP','AC','DIGITAL',120,24,0),(50007,'Glue Gun','Glue Gun','','AC','TOOLS',120,5,0),(50008,'Gateway Laptop','gateway Solo 5150 Laptop','','AC','DIGITAL',120,20,0),(50010,'Docking Station','Docking Station','Gateway','AC','DIGITAL',120,34,0),(50011,'Dish Washer','Apartment Sized Dish Washer','','AC','KITCHEN',120,687,6),(50012,'DC Lights','Compact Flourescent Light Bulb','','DC','HOUSEHOLD',24,15,1),(50013,'Cordless Charger','Dewalt 18V Battery Charger','','AC','TOOLS',120,70,0),(50014,'Coffee Grinder','Coffe Grinder','','AC','KITCHEN',120,93,0),(50015,'Clothes Washer','Regular washer','','AC','HOUSEHOLD',120,18,0),(50016,'CD Player','Harmon Kardon CD Player','','AC','HOUSEHOLD',120,18,0),(50017,'Blender','Blender','','AC','HOUSEHOLD',120,531,0),(50018,'Alarm Clock','Clock/Radio','','AC','HOUSEHOLD',120,1,0),(50019,'AC Lights','Compact Flourescent Light Bulb','','AC','HOUSEHOLD',120,18,0),(50020,'21in CRT','Panisonic S21 CRT','','AC','DIGITAL',120,103,1),(50021,'19ft Refridgerator','19foot refridgerator','SunFrost','DC','HOUSEHOLD',24,696,29),(50022,'18in LCD Monitor','HP 1820 LCD Monitor','','AC','DIGITAL',120,30,0),(50023,'16ft Refridgerator','16foot refridgerator','SunFrost','DC','HOUSEHOLD',24,696,0),(50024,'133Mhz Pentium','133 Mgz Pentium PC','','AC','DIGITAL',120,53,0),(50025,'12ft Refridgerator','12foot refridgerator','SunFrost','DC','HOUSEHOLD',24,696,29),(50026,'SQ Flex Pump','Grundfos SQ Flex Deep Well Pump','','DC','HOUSEHOLD',24,192,8),(50027,'Sewing Machine','Sewing Machine','Singer','AC','TOOLS',120,51,0),(50028,'Stereo','Stereo/Amp','','AC','HOUSEHOLD',120,18,0),(50029,'TV','small TV','Sony','AC','HOUSEHOLD',120,18,0),(50030,'Tape Deck','Tape Deck','Harmon Kardon ','AC','HOUSEHOLD',120,18,0),(50031,'Terminal Server','Livingston Port Master','','AC','DIGITAL',120,20,0),(50032,'Toaster Oven','Toaster Oven','','AC','HOUSEHOLD',120,240,0),(50033,'Modem','56K US Robotics Modem','US Robotics','AC','DIGITAL',120,4,0),(50035,'Vacumn','Old Upright Vacumn','Hoover','AC','HOUSEHOLD',120,800,7),(50036,'Wireless Phone','PTEL Wireless Phone','Telemobile','DC','HOUSEHOLD',12,3,0),(50037,'FT51 Charger','Charger for Yaesu FT51','Yaesu','AC','DIGITAL',120,1,0),(50038,'Modem','1496+ Modem','Zycel','AC','DIGITAL',120,6,0);
/*!40000 ALTER TABLE `loads` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `modules`
--

DROP TABLE IF EXISTS `modules`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `modules` (
  `itemID` int(11) NOT NULL,
  `Model` varchar(255) NOT NULL,
  `manucturer` varchar(255) NOT NULL,
  `Vintage` year(4) NOT NULL,
  `Area` int(255) NOT NULL,
  `Material` varchar(255) NOT NULL,
  `Series_cells` int(11) NOT NULL,
  `Parallel_C_S` int(11) NOT NULL,
  `Isco` int(11) NOT NULL,
  `Voco` int(11) NOT NULL,
  `Impo` int(11) NOT NULL,
  `Vmpo` int(11) NOT NULL,
  `aIsc` int(11) NOT NULL,
  `aImp` int(11) NOT NULL,
  `C0` int(11) NOT NULL,
  `C1` int(11) NOT NULL,
  `BVoco` int(11) NOT NULL,
  `mBVoc` int(11) NOT NULL,
  `BVmpo` int(11) NOT NULL,
  `mBVmp` int(11) NOT NULL,
  `n` int(11) NOT NULL,
  `C2` int(11) NOT NULL,
  `C3` int(11) NOT NULL,
  `A0` int(11) NOT NULL,
  `A1` int(11) NOT NULL,
  `A2` int(11) NOT NULL,
  `A3` int(11) NOT NULL,
  `A4` int(11) NOT NULL,
  `B0` int(11) NOT NULL,
  `B1` int(11) NOT NULL,
  `B2` int(11) NOT NULL,
  `B3` int(11) NOT NULL,
  `B4` int(11) NOT NULL,
  `B5` int(11) NOT NULL,
  `d(Tc)` int(11) NOT NULL,
  `fd` int(11) NOT NULL,
  `a` int(11) NOT NULL,
  `b` int(11) NOT NULL,
  `C4` int(11) NOT NULL,
  `C5` int(11) NOT NULL,
  `Ixo` int(11) NOT NULL,
  `Ixxo` int(11) NOT NULL,
  `C6` int(11) NOT NULL,
  `C7` int(11) NOT NULL,
  `Picture` varchar(255) NOT NULL,
  `Description` varchar(255) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `modules`
--

LOCK TABLES `modules` WRITE;
/*!40000 ALTER TABLE `modules` DISABLE KEYS */;
INSERT INTO `modules` VALUES (0,'8-KC80-Array','Kyocera',1999,5,'mc-Si',72,4,18,43,17,34,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,18,12,1,0,'0','Array composed of eight Kyocera KC-80 mc-Si modules.  Two modules in series in each module string with four module strings in parallel.  Photo shows application in NTUA stand-alone system designed and integrated  by Kyocera Solar.'),(0,'8-BP275-Array','BP Solar',2000,5,'c-Si',72,4,18,43,17,34,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,18,12,1,0,'0','Array composed of eight BP Solar BP-275 c-Si modules.  Two modules in series in each module string with four module strings in parallel.  Photo shows application in Firefly 600  stand-alone system integrated  by Energia Total; Ltd.'),(0,'ASE-100-ATF/17 (100)','ASE',1999,1,'EFG mc-Si',36,2,6,21,6,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,6,4,1,0,'0','Module area = 0.828 m^2; (33.8 x 38.0). Weight = 12 kg (26 lb). Module with 2 parallel strings of 36 (100 cm^2) EFG multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass sheet on front.  Aluminum foi'),(0,'ASE-100-ATF/17 (85)','ASE',1999,1,'EFG mc-Si',36,2,6,21,5,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,6,4,1,0,'','Module area = 0.828 m^2; (33.8 x 38.0). Weight = 12 kg (26 lb). Module with 2 parallel strings of 36 (100 cm^2) EFG multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass sheet on front.  Aluminum foi'),(0,'ASE-100-ATF/17 (92)','ASE',1999,1,'EFG mc-Si',36,2,6,21,5,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,6,4,1,0,'','Module area = 0.828 m^2; (33.8 x 38.0). Weight = 12 kg (26 lb). Module with 2 parallel strings of 36 (100 cm^2) EFG multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass sheet on front.  Aluminum foi'),(0,'ASE-100-ATF/34 (100)','ASE',1999,1,'EFG mc-Si',72,1,3,42,3,34,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Module area = 0.828 m^2; (33.8 x 38.0). Weight = 12 kg (26 lb). Module with 72 (100 cm^2) EFG multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass sheet on front.  Aluminum foil followed by Tedlar s'),(0,'ASE-100-ATF/34 (85)','ASE',1999,1,'EFG mc-Si',36,2,3,41,3,34,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Module area = 0.828 m^2; (33.8 x 38.0). Weight = 12 kg (26 lb). Module with 72 (100 cm^2) EFG multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass sheet on front.  Aluminum foil followed by Tedlar s'),(0,'ASE-100-ATF/34 (92)','ASE',1999,1,'EFG mc-Si',72,1,3,42,3,34,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Module area = 0.828 m^2; (33.8 x 38.0). Weight = 12 kg (26 lb). Module with 72 (100 cm^2) EFG multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass sheet on front.  Aluminum foil followed by Tedlar s'),(0,'ASE-300-DGF/17 (265)','ASE',1999,2,'EFG mc-Si',36,6,17,21,16,17,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,17,11,1,0,'','Large area = 2.427 m^2; (50.5 x 74.5). Weight = 48 kg (107 lb). Module with 216 (100 cm^2) EFG multicrystalline silicon cells; 36 in series string; 6 parallel strings. Aluminum frame; low-iron cerium-containing tempered glass sheets front and back; module'),(0,'ASE-300-DGF/17 (285)','ASE',1999,2,'EFG mc-Si',36,6,18,21,17,17,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,18,12,1,0,'','Large area = 2.427 m^2; (50.5 x 74.5). Weight = 48 kg (107 lb). Module with 216 (100 cm^2) EFG multicrystalline silicon cells; 36 in series string; 6 parallel strings. Aluminum frame; low-iron cerium-containing tempered glass sheets front and back; module'),(0,'ASE-300-DGF/17 (300)','ASE',1999,2,'EFG mc-Si',36,6,19,21,17,17,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,19,13,1,0,'','Large area = 2.427 m^2; (50.5 x 74.5). Weight = 48 kg (107 lb). Module with 216 (100 cm^2) EFG multicrystalline silicon cells; 36 in series string; 6 parallel strings. Aluminum frame; low-iron cerium-containing tempered glass sheets front and back; module'),(0,'ASE-300-DGF/50','ASE',1995,2,'EFG mc-Si',108,2,6,63,6,50,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,6,4,1,0,'','Large area = 2.427 m^2; (50.5 x 74.5). Weight = 48 kg (107 lb). Module with 216 (100 cm^2) EFG multicrystalline silicon cells; 108 in series string; 2 parallel strings. Aluminum frame; low-iron cerium-containing tempered glass sheets front and back; modul'),(0,'ASE-300-DGF/50 (265)','ASE',1999,2,'EFG mc-Si',108,2,6,62,5,50,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,6,4,1,0,'','Large area = 2.427 m^2; (50.5 x 74.5). Weight = 48 kg (107 lb). Module with 216 (100 cm^2) EFG multicrystalline silicon cells; 108 in series string; 2 parallel strings. Aluminum frame; low-iron cerium-containing tempered glass sheets front and back; modul'),(0,'ASE-300-DGF/50 (285)','ASE',1999,2,'EFG mc-Si',108,2,6,63,6,51,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,6,4,1,0,'','Large area = 2.427 m^2; (50.5 x 74.5). Weight = 48 kg (107 lb). Module with 216 (100 cm^2) EFG multicrystalline silicon cells; 108 in series string; 2 parallel strings. Aluminum frame; low-iron cerium-containing tempered glass sheets front and back; modul'),(0,'ASE-300-DGF/50 (300)','ASE',1999,2,'EFG mc-Si',108,2,7,63,6,51,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,6,4,1,0,'','Large area = 2.427 m^2; (50.5 x 74.5). Weight = 48 kg (107 lb). Module with 216 (100 cm^2) EFG multicrystalline silicon cells; 108 in series string; 2 parallel strings. Aluminum frame; low-iron cerium-containing tempered glass sheets front and back; modul'),(0,'ASE-50-ALF/17','ASE',1997,0,'EFG mc-Si',36,1,3,21,3,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,3,2,1,0,'','Module area = 0.435 m^2; (17.8 x 38.0). Weight = 6.1 kg (13.5 lb). Module with 36 (100 cm^2) EFG multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass sheet on front and aluminum foil back; module la'),(0,'ASE-50-ATF/17 (45)','ASE',1999,0,'EFG mc-Si',36,1,3,21,3,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Module area = 0.435 m^2; (17.8 x 38.0). Weight = 6.1 kg (13.5 lb). Module with 36 (100 cm^2) EFG multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass sheet on front.  Aluminum foil followed by Tedla'),(0,'ASE-50-ATF/17 (50)','ASE',1999,0,'EFG mc-Si',36,1,3,21,3,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Module area = 0.435 m^2; (17.8 x 38.0). Weight = 6.1 kg (13.5 lb). Module with 36 (100 cm^2) EFG multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass sheet on front.  Aluminum foil followed by Tedla'),(0,'AP-100','Astropower',2001,1,'c-Si',36,1,7,21,6,16,0,0,1,0,0,0,0,0,2,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,4,1,0,'','Area = 0.974 m^2; (26.0 x 58.1). Weight = 11.9 kg (26.1 lb). Module with 36 large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction b'),(0,'AP-100','Astropower',2000,1,'c-Si',36,1,7,20,6,16,0,0,1,0,0,0,0,0,1,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,4,1,0,'','Area = 0.974 m^2; (26.0 x 58.1). Weight = 11.9 kg (26.1 lb). Module with 36 large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction b'),(0,'AP-110','Astropower',1999,1,'c-Si',36,1,8,21,7,17,0,0,1,0,0,0,0,0,1,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,5,1,0,'','Area = 0.974 m^2; (26.0 x 58.1). Weight = 11.9 kg (26.1 lb). Module with 36 large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction b'),(0,'AP-110','Astropower',2001,1,'c-Si',36,1,7,21,6,17,0,0,1,0,0,0,0,0,2,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,4,1,0,'','Area = 0.974 m^2; (26.0 x 58.1). Weight = 11.9 kg (26.1 lb). Module with 36 large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction b'),(0,'AP-120','Astropower',2001,1,'c-Si',36,1,7,22,7,17,0,0,1,0,0,0,0,0,2,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,5,1,0,'','Area = 0.974 m^2; (26.0 x 58.1). Weight = 11.9 kg (26.1 lb). Module with 36 large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction b'),(0,'AP-120','Astropower',1999,1,'c-Si',36,1,8,21,7,17,0,0,1,0,0,0,0,0,1,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,8,5,1,0,'','Area = 0.974 m^2; (26.0 x 58.1). Weight = 11.9 kg (26.1 lb). Module with 36 large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction b'),(0,'AP-1206','Astropower',1998,1,'c-Si',36,1,7,21,7,16,0,0,1,0,0,0,0,0,1,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,5,1,0,'','Area = 0.974 m^2; (26.0 x 58.1). Weight = 11.9 kg (26.1 lb). Module with 36 large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction b'),(0,'AP-130','Astropower',2002,1,'c-Si',42,1,8,25,7,19,0,0,1,0,0,0,0,0,2,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,8,5,1,0,'','Area = 1.121 m^2; (38.3 x 45.4). Weight = 12.0 kg (26.5 lb). Module with 40 large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction b'),(0,'AP-130','Astropower',2001,1,'c-Si',42,1,7,25,7,19,0,0,1,0,0,0,0,0,2,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,5,1,0,'','Area = 1.121 m^2; (38.3 x 45.4). Weight = 12.0 kg (26.5 lb). Module with 40 large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction b'),(0,'AP-50','Astropower',2000,1,'c-Si',40,1,3,22,3,17,0,0,1,0,0,0,0,0,1,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.567 m^2; (26.0 x33.8). Weight = 7.5 kg (16.6 lb). Module with 40  (120 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction box with dual'),(0,'AP-50','Astropower',2001,1,'c-Si',40,1,3,22,3,17,0,0,1,0,0,0,0,0,2,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.567 m^2; (26.0 x33.8). Weight = 7.5 kg (16.6 lb). Module with 40  (120 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction box with dual'),(0,'AP-65','Astropower',1999,1,'c-Si',36,1,5,21,4,16,0,0,1,0,0,0,0,0,1,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 0.631 m^2; (20.7 x 47.2). Weight = 8.2 kg (18.1 lb). Module with 36 (150 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction box with inst'),(0,'AP-75','Astropower',1999,1,'c-Si',36,1,5,21,4,17,0,0,1,0,0,0,0,0,1,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.631 m^2; (20.7 x 47.2). Weight = 8.2 kg (18.1 lb). Module with 36 (150 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction box with dual'),(0,'AP-75','Astropower',2001,1,'c-Si',36,1,5,21,4,17,0,0,1,0,0,0,0,0,2,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 0.631 m^2; (20.7 x 47.2). Weight = 8.2 kg (18.1 lb). Module with 36 (150 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junction box with dual'),(0,'AP-8225','Astropower',1997,1,'Si-Film',36,1,6,20,5,15,0,0,1,0,0,0,0,0,2,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,6,4,1,0,'','Area = 0.974 m^2; (26.0 x 58.1). Weight = 11.9 kg (26.1 lb). Module with 36 large-area (240 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with '),(0,'APX-110-SL','Astropower',2002,1,'Si-Film',30,1,11,16,9,12,0,0,1,0,0,0,0,0,2,0,-10,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,10,6,1,0,'','Area = 1.485 m^2; (44.7 x 51.4). Weight = xx.x kg  (xx.x lb). Module with 30 large-area (435 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Frameless laminate; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.'),(0,'APX-110-SL','Astropower',2002,1,'Si-Film',30,1,10,16,9,12,0,0,1,0,0,0,0,0,2,0,-10,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,10,6,1,0,'','Area = 1.485 m^2; (44.7 x 51.4). Weight = xx.x kg  (xx.x lb). Module with 30 large-area (435 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Frameless laminate; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.'),(0,'APX-120','Astropower',2001,2,'Si-Film',36,1,9,19,8,14,0,0,1,0,0,0,0,0,2,0,-10,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,9,5,1,0,'','Area = 1.72 m^2; (34.5 x 77.2). Weight = 20.9 kg  (46.0 lb). Module with 36 large-area (440 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with '),(0,'APX-120','Astropower',2002,2,'Si-Film',36,1,10,19,8,15,0,0,1,0,0,0,0,0,2,0,-10,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,9,5,1,0,'','Area = 1.72 m^2; (34.5 x 77.2). Weight = 20.9  kg (46.0 lb). Module with 36 large-area (440 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with '),(0,'APX-130','Astropower',2001,2,'Si-Film',36,1,10,19,8,14,0,0,1,0,0,0,0,0,2,0,-10,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,9,6,1,0,'','Area = 1.72 m^2; (34.5 x 77.2). Weight = 20.9  kg (46.0 lb). Module with 36 large-area (440 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with '),(0,'APX-130','Astropower',2002,2,'Si-Film',36,1,10,19,9,15,0,0,1,0,0,0,0,0,2,0,-10,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,10,6,1,0,'','Area = 1.72 m^2; (34.5 x 77.2). Weight = 20.9  kg (46.0 lb). Module with 36 large-area (440 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with '),(0,'APX-140','Astropower',2002,2,'Si-Film',36,1,10,19,9,16,0,0,1,0,0,0,0,0,2,0,-10,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,10,6,1,0,'','Area = 1.72 m^2; (34.5 x 77.2). Weight = 20.9  kg (46.0 lb). Module with 36 large-area (440 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with '),(0,'APX-40','Astropower',2002,1,'Si-Film',39,1,3,20,3,16,0,0,1,0,0,0,0,0,2,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.657 m^2; (26.0 x 39.1). Weight = 8.5 kg (18.8 lb). Module with 39 large-area (140 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with E'),(0,'APX-45','Astropower',2001,1,'Si-Film',39,1,3,21,3,16,0,0,1,0,0,0,0,0,2,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.657 m^2; (26.0 x 39.1). Weight = 8.5 kg (18.8 lb). Module with 39 large-area (140 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with E'),(0,'APX-45','Astropower',2002,1,'Si-Film',39,1,3,21,3,17,0,0,1,0,0,0,0,0,2,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.657 m^2; (26.0 x 39.1). Weight = 8.5 kg (18.8 lb). Module with 39 large-area (140 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with E'),(0,'APX-45','Astropower',1999,1,'Si-Film',40,1,3,22,3,17,0,0,1,0,0,0,0,0,2,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.566 m^2; (26.0 x 33.8). Weight = 7.5 kg (16.6 lb). Module with 40  (120 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  Junct'),(0,'APX-50','Astropower',2002,1,'Si-Film',39,1,3,21,3,17,0,0,1,0,0,0,0,0,2,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.657 m^2; (26.0 x 39.1). Weight = 8.5 kg (18.8 lb). Module with 39 large-area (140 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with E'),(0,'APX-65','Astropower',2001,1,'Si-Film',39,1,5,20,4,15,0,0,1,0,0,0,0,0,2,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.955 m^2; (26.0 x56.9). Weight = 12.2 kg (27.0 lb). Module with 39 large-area (215 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with E'),(0,'APX-65','Astropower',2002,1,'Si-Film',39,1,5,21,4,16,0,0,1,0,0,0,0,0,2,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.955 m^2; (26.0 x56.9). Weight = 12.2 kg (27.0 lb). Module with 39 large-area (215 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with E'),(0,'APX-75','Astropower',2002,1,'Si-Film',39,1,5,21,4,17,0,0,1,0,0,0,0,0,2,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.955 m^2; (26.0 x56.9). Weight = 12.2 kg (27.0 lb). Module with 39 large-area (215 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with E'),(0,'APX-75-SC','Astropower',2002,1,'Si-Film',21,1,10,11,9,9,0,0,1,0,0,0,0,0,2,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,10,6,1,0,'','Area = 1.012 m^2; (26.0 x 60.3). Weight = 12.9 kg (28.5 lb). Module with 21 large-area (440 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with '),(0,'APX-90','Astropower',1999,1,'Si-Film',40,1,6,22,5,17,0,0,1,0,0,0,0,0,2,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,6,4,1,0,'','Area = 1.078 m^2; (26.0 x 64.3). Weight = 13.7 kg (30.2 lb). Module with 40 large-area (240 cm^2) Silicon-Film polycrystalline silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with '),(0,'BP2140S','BP Solar',2000,1,'c-Si',72,1,4,43,4,34,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 1.26 m^2; (31.1 x 62.8). Weight = 20.5 kg (45 lb). Module with 72 (145 cm^2)  crystalline  silicon cells connected in series. Available with or without anodized aluminum frame; tempered glass front sheet; trilayer TPT backsheet; module laminated wi'),(0,'BP2150S','BP Solar',2000,1,'c-Si',72,1,5,43,4,34,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 1.26 m^2; (31.1 x 62.8). Weight = 20.5 kg (45 lb). Module with 72 (145 cm^2)  crystalline  silicon cells connected in series. Available with or without anodized aluminum frame; tempered glass front sheet; trilayer TPT backsheet; module laminated wi'),(0,'BP270','BP Solar',2000,1,'c-Si',36,1,4,21,4,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 0.630 m^2; (20.9 x 46.8). Weight = 7.5 kg (16.5 lb). Module with 36 (145 cm^2)  crystalline  silicon cells connected in series. Available with or without anodized aluminum frame; tempered glass front sheet; trilayer TPT backsheet; module laminated '),(0,'BP275','BP Solar',2000,1,'c-Si',36,1,5,21,4,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.630 m^2; (20.9 x 46.8). Weight = 7.5 kg (16.5 lb). Module with 36 (145 cm^2)  crystalline  silicon cells connected in series. Available with or without anodized aluminum frame; tempered glass front sheet; trilayer TPT backsheet; module laminated '),(0,'BP5130','BP Solar`',2000,1,'c-Si',60,1,5,36,5,30,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 1.09 m^2; (31.7 x 53.1). Weight = 13.0 kg (28.6 lb). Module with 60 (145 cm^2) laser-grooved buried-grid crystalline  silicon cells connected in series. Unframed laminate; tempered glass front sheet; trilayer TPT backsheet; module laminated with EV'),(0,'BP580','BP Solar',2002,1,'c-Si',36,1,5,22,4,18,0,0,1,0,0,0,0,0,1,0,-4,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.646 m^2; (21.1 x 47.4). Weight = 7.7 kg (17.0 lb). Module with 36 (145 cm^2) laser-grooved buried-grid crystalline  silicon cells connected in series. Available with or without anodized aluminum frame; tempered glass front sheet; quick-connect ca'),(0,'BP580','BP Solar',2000,1,'c-Si',36,1,5,22,4,18,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.630 m^2; (20.9 x 46.8). Weight = 7.5 kg (16.5 lb). Module with 36 (145 cm^2) laser-grooved buried-grid crystalline  silicon cells connected in series. Available with or without anodized aluminum frame; tempered glass front sheet; trilayer TPT bac'),(0,'BP585','BP Solar',2001,1,'c-Si',36,1,5,22,5,18,0,0,1,0,0,0,0,0,1,0,-4,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,5,3,1,0,'','Area = 0.631 m^2; (20.9 x 46.8). Weight = 7.5 kg (16.5 lb). Module with 36 (145 cm^2) laser-grooved buried-grid crystalline  silicon cells connected in series. Available with or without anodized aluminum frame; tempered glass front sheet; quick-connect ca'),(0,'BP585','BP Solar',2002,1,'c-Si',36,1,5,22,5,18,0,0,1,0,0,0,0,0,1,0,-4,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,4,1,0,'','Area = 0.646 m^2; (21.1 x 47.4). Weight = 7.7 kg (17.0 lb). Module with 36 (145 cm^2) laser-grooved buried-grid crystalline  silicon cells connected in series. Available with or without anodized aluminum frame; tempered glass front sheet; quick-connect ca'),(0,'BP585','BP Solar',2000,1,'c-Si',36,1,5,22,5,18,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.630 m^2; (20.9 x 46.8). Weight = 7.5 kg (16.5 lb). Module with 36 (145 cm^2) laser-grooved buried-grid crystalline  silicon cells connected in series. Available with or without anodized aluminum frame; tempered glass front sheet; trilayer TPT bac'),(0,'BP980','BP Solar',2001,1,'CdTe',57,1,3,45,2,32,0,0,1,0,0,0,0,0,2,0,-6,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,3,2,1,0,'','Area = 0.945 m^2; (24.0 x 61.0).  Weight = 15.1 kg (33.3 lb). Thin-film module with BP Apollo technology; cadmium telluride (CdTe) cells; 57 150-cm^2 cells in series.  Frameless laminate;  with two sheets of low-iron heat-strengthened glass laminated with'),(0,'BP990','BP Solar',2001,1,'CdTe',57,1,3,46,3,35,0,0,1,0,0,0,0,0,2,0,-6,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,3,2,1,0,'','Area = 0.945 m^2; (24.0 x 61.0).  Weight = 15.1 kg (33.3 lb). Thin-film module with BP Apollo technology; cadmium telluride (CdTe) cells; 57 150-cm^2 cells in series.  Frameless laminate;  with two sheets of low-iron heat-strengthened glass laminated with'),(0,'Entech 22X Concentrator','Entex',1994,3,'c-Si',37,1,23,25,21,20,0,0,1,0,0,0,0,0,1,-1,-41,1,0,0,0,0,1,0,0,-1,0,0,13,0,-3,0,1,0,23,16,1,0,'','Large area = 3.18 m^2; (34 x 144). Weight = 100 kg (220 lb). Module has 37 (39 cm^2) crystalline silicon concentrator cells connected in a series string.  Acrylic Fresnel lens provides optical concentration; metal housing; aluminum heat sink for cells; fu'),(0,'EPV-40','unknown',1998,1,'2-a-Si',38,1,1,61,1,45,0,0,1,0,0,0,0,0,3,0,-4,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,1,1,1,0,'','Area = 0.791 m^2;  (25 x 49).  Weight = 13.2 kg (29 lb). Thin-film module with tandem junction amorphous silicon (p-i-n/p-i-n) monolithically-integrated cells.  Frameless module;  with two sheets of low-iron annealed float glass laminated with EVA encapsu'),(0,'FS-50','First Solar',2000,1,'CdTe',116,1,1,89,1,61,0,0,1,0,0,0,0,0,1,-1,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,1,0,1,0,'','Area = 0.720 m^2; (23.6 x 47.2).  Weight = 11.4 kg  (25 lb). Thin-film module with cadmium telluride (CdTe) cells; 116 cells connected in series.  Framless laminate;  with two sheets of low-iron glass laminated with EVA encapsulant.  No junction box; Mult'),(0,'FS-50','First Solar',2001,1,'CdTe',116,1,1,90,1,65,0,0,1,0,0,0,0,0,1,-1,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,1,1,1,0,'','Area = 0.720 m^2; (23.6 x 47.2).  Weight = 11.4 kg  (25 lb). Thin-film module with cadmium telluride (CdTe) cells; 116 cells connected in series.  Framless laminate;  with two sheets of low-iron glass laminated with EVA encapsulant.  No junction box; Mult'),(0,'KC120-1','Kyocera',1998,1,'mc-Si',36,1,7,21,6,17,0,0,1,0,0,0,0,0,1,0,-6,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,5,1,0,'','Area = 0.929 m^2; (25.7 x 68.1). Weight = 11.9 kg (26.2 lb). Module with 36 large-area (230 cm^2) multicrystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; PVF  backsheet; module laminated with EVA.  Junctio'),(0,'KC120-1','Kyocera',1999,1,'mc-Si',36,1,7,22,7,17,0,0,1,0,0,0,0,0,1,0,-6,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,5,1,0,'','Area = 0.929 m^2; (25.7 x 68.1). Weight = 11.9 kg (26.2 lb). Module with 36 large-area (230 cm^2) multicrystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; PVF  backsheet; module laminated with EVA.  Junctio'),(0,'KC150','Kyocera',2002,1,'mc-Si',48,1,7,28,6,22,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,5,1,0,'','Area = 1.277 m^2; (39.0 x50.8). Weight = 16.0 kg (35.2 lb). Module with 48 large-area (230 cm^2) multicrystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; smooth polymer  backsheet; module laminated with EVA'),(0,'KC150','Kyocera',2002,1,'mc-Si',48,1,7,29,7,23,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,5,1,0,'','Area = 1.277 m^2; (39.0 x50.8). Weight = 16.0 kg (35.2 lb). Module with 48 large-area (230 cm^2) multicrystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; smooth polymer  backsheet; module laminated with EVA'),(0,'KC40','Kyocera',1999,0,'mc-Si',36,1,2,22,2,17,0,0,1,0,0,0,0,0,1,0,-6,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,2,2,1,0,'','Area = 0.343 m^2; (25.7 x 20.7). Weight = 6.0 kg (13.2 lb). Module with 36 (75 cm^2) multicrystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; PVF  backsheet; module laminated with EVA.  Junction box with co'),(0,'KC60','Kyocera',1999,0,'mc-Si',36,1,4,22,4,17,0,0,1,0,0,0,0,0,1,0,-6,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 0.489 m^2; (25.7 x 29.6). Weight = 7.8 kg (17.2 lb). Module with 36 (115 cm^2) multicrystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; PVF  backsheet; module laminated with EVA.  Junction box with c'),(0,'KC80','Kyocera',1999,1,'mc-Si',36,1,5,22,5,17,0,0,1,0,0,0,0,0,1,0,-6,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.636 m^2; (25.7 x 38.4). Weight = 9.6 kg (21.2 lb). Module with 36 (155 cm^2) multicrystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; PVF  backsheet; module laminated with EVA.  Junction box with c'),(0,'KC80','Kyocera',1998,1,'mc-Si',36,1,5,22,4,17,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.636 m^2; (25.7 x 38.4). Weight = 9.6 kg (21.2 lb). Module with 36 (155 cm^2) multicrystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; PVF  backsheet; module laminated with EVA.  Junction box with c'),(0,'PW1000 (100W/12V)','Photowatt',2001,1,'mc-Si',36,2,6,22,6,17,0,0,1,0,0,0,0,0,1,0,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,6,4,1,0,'','Module area = 0.898 m^2; (26.5 x 52.5). Weight = 10.5 kg (23.1 lb). Module with 72 (105 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  Tedlar back sheet; module laminated with'),(0,'PW1000 (100W/24V)','Photowatt',2001,1,'mc-Si',72,1,3,43,3,34,0,0,1,0,0,0,0,0,1,0,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Module area = 0.898 m^2; (26.5 x 52.5). Weight = 10.5 kg (23.1 lb). Module with 72 (105 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  Tedlar back sheet; module laminated with'),(0,'PW1000 (105W/12V)','Photowatt',2001,1,'mc-Si',36,2,6,22,6,17,0,0,1,0,0,0,0,0,1,0,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,6,5,1,0,'','Module area = 0.898 m^2; (26.5 x 52.5). Weight = 10.5 kg (23.1 lb). Module with 72 (105 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  Tedlar back sheet; module laminated with'),(0,'PW1000 (105W/24V)','Photowatt',2001,1,'mc-Si',72,1,3,43,3,35,0,0,1,0,0,0,0,0,1,0,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Module area = 0.898 m^2; (26.5 x 52.5). Weight = 10.5 kg (23.1 lb). Module with 72 (105 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  Tedlar back sheet; module laminated with'),(0,'PW1000 (24V)','Photowatt',2000,1,'mc-Si',72,1,3,43,3,34,0,0,1,0,0,0,0,0,1,0,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Module area = 0.898 m^2; (26.5 x 52.5). Weight = 10.5 kg (23.1 lb). Module with 72 (105 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  Tedlar back sheet; module laminated with'),(0,'PW1000 (90W/12V)','Photowatt',2001,1,'mc-Si',36,2,6,22,5,17,0,0,1,0,0,0,0,0,1,0,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,6,4,1,0,'','Module area = 0.898 m^2; (26.5 x 52.5). Weight = 10.5 kg (23.1 lb). Module with 72 (105 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  Tedlar back sheet; module laminated with'),(0,'PW1000 (90W/24V)','Photowatt',2001,1,'mc-Si',72,1,3,43,3,34,0,0,1,0,0,0,0,0,1,0,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Module area = 0.898 m^2; (26.5 x 52.5). Weight = 10.5 kg (23.1 lb). Module with 72 (105 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  Tedlar back sheet; module laminated with'),(0,'PW1000 (95W/12V)','Photowatt',2001,1,'mc-Si',36,2,6,22,6,17,0,0,1,0,0,0,0,0,1,0,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,6,4,1,0,'','Module area = 0.898 m^2; (26.5 x 52.5). Weight = 10.5 kg (23.1 lb). Module with 72 (105 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  Tedlar back sheet; module laminated with'),(0,'PW1000 (95W/24V)','Photowatt',2001,1,'mc-Si',72,1,3,43,3,34,0,0,1,0,0,0,0,0,1,0,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Module area = 0.898 m^2; (26.5 x 52.5). Weight = 10.5 kg (23.1 lb). Module with 72 (105 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  Tedlar back sheet; module laminated with'),(0,'PWX100','Photowatt',2000,0,'mc-Si',36,1,1,22,1,17,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,1,1,1,0,'','Module area = 0.152 m^2; (10.3 x 22.9). Weight = 3.4 kg (7.5  lb). Module with 36 (25 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  back; module laminated with EVA  encapsula'),(0,'PWX200','Photowatt',2000,0,'mc-Si',36,1,1,20,1,16,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,1,1,1,0,'','Module area = 0.266 m^2; (14.5 x 28.3). Weight = 5.2 kg (11.4 lb). Module with 36 (51 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  back; module laminated with EVA  encapsula'),(0,'PWX500','Photowatt',1998,0,'mc-Si',36,1,3,22,3,17,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Module area = 0.463 m^2; (18.2 x 39.4). Weight = 9.2 kg (20.2 lb). Module with 36 (102 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  back; module laminated with EVA  encapsul'),(0,'PWX500 (42W)','Photowatt',2000,0,'mc-Si',36,1,3,21,3,17,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Module area = 0.450 m^2; (17.0 x 41.0). Weight = 9.2 kg (20.2 lb). Module with 36 (102 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  back; module laminated with EVA  encapsul'),(0,'PWX500 (47W)','Photowatt',2000,0,'mc-Si',36,1,3,22,3,17,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Module area = 0.450 m^2; (17.0 x 41.0). Weight = 9.2 kg (20.2 lb). Module with 36 (102 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  back; module laminated with EVA  encapsul'),(0,'PWX500 (52W)','Photowatt',2000,0,'mc-Si',36,1,3,22,3,17,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Module area = 0.450 m^2; (17.0 x 41.0). Weight = 9.2 kg (20.2 lb). Module with 36 (102 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  back; module laminated with EVA  encapsul'),(0,'PWX750 (70W)','Photowatt',2000,1,'mc-Si',36,1,5,21,4,17,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,4,3,1,0,'','Module area = 0.707 m^2; (21.9 x 50.1). Weight = 13 kg (28.6 lb). Module with 36 (156 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  back; module laminated with EVA  encapsula'),(0,'PWX750 (75W)','Photowatt',2000,1,'mc-Si',36,1,5,22,4,17,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,5,3,1,0,'','Module area = 0.707 m^2; (21.9 x 50.1). Weight = 13 kg (28.6 lb). Module with 36 (156 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  back; module laminated with EVA  encapsula'),(0,'PWX750 (80W)','Photowatt',2000,1,'mc-Si',36,1,5,22,5,17,0,0,1,0,0,0,0,0,1,0,-12,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,5,3,1,0,'','Module area = 0.707 m^2; (21.9 x 50.1). Weight = 13 kg (28.6 lb). Module with 36 (156 cm^2) multicrystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass sheet on front and  back; module laminated with EVA  encapsula'),(0,'HIP-6751B','Sanyo',2002,1,'HIT-Si',96,1,4,65,3,51,0,0,1,0,0,0,0,0,1,0,-6,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,2,1,0,'','Area =1.148 m^2; (34.6 x 51.4). Weight = 15 kg (33 lb). Module with 96  large-area (100 cm^2) HIT (heterojunction with intrinsic thin layer) high-efficiency crystalline silicon cells connected in series. Aluminum frame; tempered glass front sheet; polymer'),(0,'HIP-6751B','Sanyo',2001,1,'HIT-Si',96,1,4,66,3,53,0,0,1,0,0,0,0,0,1,0,-6,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area =1.148 m^2; (34.6 x 51.4). Weight = 15 kg (33 lb). Module with 96  large-area (100 cm^2) HIT (heterojunction with intrinsic thin layer) high-efficiency crystalline silicon cells connected in series. Aluminum frame; tempered glass front sheet; polymer'),(0,'HIP-HO97','Sanyo',2002,1,'HIT-Si',96,1,4,66,3,53,0,0,1,0,0,0,0,0,1,-1,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,2,1,0,'','Area =1.148 m^2; (34.6 x 51.4). Weight = 15 kg (33 lb). Module with 96  large-area (100 cm^2) HIT (heterojunction with intrinsic thin layer) high-efficiency crystalline silicon cells connected in series. Aluminum frame; tempered glass front sheet; polymer'),(0,'HIP-HO97','Sanyo',2002,1,'HIT-Si',96,1,4,66,3,53,0,0,1,0,0,0,0,0,1,-1,-19,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,2,1,0,'','Area =1.148 m^2; (34.6 x 51.4). Weight = 15 kg (33 lb). Module with 96  large-area (100 cm^2) HIT (heterojunction with intrinsic thin layer) high-efficiency crystalline silicon cells connected in series. Aluminum frame; tempered glass front sheet; polymer'),(0,'SAPC 165','Schott',2002,1,'mc-Si',72,1,5,43,5,35,0,0,1,0,0,0,0,0,1,0,-5,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area =1.301 m^2; (32.5 x 62.0). Weight = 17 kg (37 lb). Module with 72 large-area (156 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; tempered glass front sheet; smooth polymer backsheet; module laminated with  EVA; integral byp'),(0,'SAPC 165','Schott',2001,1,'mc-Si',72,1,5,44,5,34,0,0,1,0,0,0,0,0,1,0,-5,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area =1.301 m^2; (32.5 x 62.0). Weight = 17 kg (37 lb). Module with 72 large-area (156 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; tempered glass front sheet; smooth polymer backsheet; module laminated with  EVA; integral byp'),(0,'NEH120E1','Sharp',2002,1,'mc-Si',54,1,5,32,5,26,0,0,1,0,0,0,0,0,1,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area =0.96  m^2; (31.6 x 47.2). Weight = 12.5 kg (27.5 lb).  Module with 54 large-area (156 cm^2) textured multicrystalline silicon cells connected in series. Aluminum frame; tempered glass front sheet; smooth polymer backsheet; module laminated with  EVA'),(0,'NEH120E1','Sharp',2001,1,'mc-Si',54,1,5,33,5,26,0,0,1,0,0,0,0,0,1,0,-14,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area =0.944 m^2; (31.2 x 46.9). Weight = 12.5 kg (27.5 lb).  Module with 54 large-area (156 cm^2) textured multicrystalline silicon cells connected in series. Aluminum frame; tempered glass front sheet; smooth polymer backsheet; module laminated with  EVA'),(0,'SM50-H','Shell',2002,0,'c-Si',33,1,3,20,3,16,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.401 m^2; (13 x 48). Weight = 5.2 kg (11.5 lb). Module with 33 (100 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass front sheet; polymer backsheet; module laminated with EV'),(0,'SM55','Shell',2002,0,'c-Si',36,1,3,22,3,17,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.425 m^2; (13.0 x 50.9). Weight = 5.5 kg (12 lb). Module with 36 (100 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; polymer  backsheet; mod'),(0,'SP140','Shell',2002,1,'c-Si',72,1,5,43,4,33,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 1.320 m^2; (32.0 x 63.8). Weight = 17.2 kg (37.8 lb).  Module with 72 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass front sheet; polymer backsheet; module laminated w'),(0,'SP150','Shell',2002,1,'c-Si',72,1,5,43,4,34,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 1.320 m^2; (32.0 x 63.8). Weight = 17.2 kg (37.8 lb).  Module with 72 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron tempered glass front sheet; polymer backsheet; module laminated w'),(0,'SM10','Siemens',1999,0,'c-Si',34,1,1,20,1,16,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,1,0,1,0,'','Area = 0.119 m^2; (14.2 x 13.0). Weight = 1.8 kg (3.7 lb). Module with 34 (25 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multilayer Tedlar backs'),(0,'SM20','Siemens',1999,0,'c-Si',30,1,2,18,1,15,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,2,1,1,0,'','Area = 0.186 m^2; (12.9 x 22.3). Weight = 2.5 kg (5.6 lb). Module with 30 (50 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multilayer Tedlar backs'),(0,'SM46','Siemens',1999,0,'c-Si',30,1,3,18,3,15,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.356 m^2; (13 x 42.7). Weight = 4.6 kg (10.2 lb). Module with 30 (100 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multilayer Tedlar backs'),(0,'SM50','Siemens',1999,0,'c-Si',36,1,3,21,3,17,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.425 m^2; (13 x 50.9). Weight = 5.5 kg (12 lb). Module with 36 (100 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multilayer Tedlar backshe'),(0,'SM50/H','Siemens',1999,0,'c-Si',33,1,3,20,3,16,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.401 m^2; (13 x 48). Weight = 5.2 kg (11.5 lb). Module with 33 (100 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multilayer Tedlar backshe'),(0,'SM55','Siemens',1997,0,'c-Si',36,1,3,21,3,17,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.425 m^2; (13 x 50.9). Weight = 5.5 kg (12 lb). Module with 36 (100 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module '),(0,'SM55','Siemens',1999,0,'c-Si',36,1,3,22,3,17,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.425 m^2; (13 x 50.9). Weight = 5.5 kg (12 lb). Module with 36 (100 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multilayer Tedlar backshe'),(0,'SM6','Siemens',1999,0,'c-Si',33,1,0,20,0,15,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,0,0,1,0,'','Area = 0.058 m^2; (6.9 x 13.0). Weight = 1.0 kg (2.2 lb). Module with 33 (15 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multilayer Tedlar backsh'),(0,'SM6','Siemens',1997,0,'c-Si',33,1,0,19,0,16,0,0,1,0,0,0,0,0,1,1,-6,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,0,0,1,0,'','Area = 0.058 m^2; (6.9 x 13.0). Weight = 1.0 kg (2.2 lb). Module with 33 (15 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multilayer Tedlar backsh'),(0,'SP130','Siemens',2001,1,'c-Si',72,1,4,43,4,34,0,0,1,0,0,0,0,0,1,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 1.317 m^2; (32.0 x 63.8). Weight = 14.8 kg (32.6 lb).  Module with 72 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multi-layered polym'),(0,'SP130','Siemens',2001,1,'c-Si',72,1,5,43,4,33,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 1.317 m^2; (32.0 x 63.8). Weight = 14.8 kg (32.6 lb).  Module with 72 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multi-layered polym'),(0,'SP140','Siemens',2001,1,'c-Si',72,1,5,43,4,33,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 1.317 m^2; (32.0 x 63.8). Weight = 14.8 kg (32.6 lb).  Module with 72 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multi-layered polym'),(0,'SP150','Siemens',2001,1,'c-Si',72,1,5,43,4,34,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 1.317 m^2; (32.0 x 63.8). Weight = 14.8 kg (32.6 lb).  Module with 72 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; multi-layered polym'),(0,'SP18 (12V)','Siemens',1999,0,'c-Si',36,1,1,22,1,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,1,1,1,0,'','Area = 0.174 m^2; (10.8 x 24.9). Weight = 2.7 kg (5.9 lb). Module with 36 (35 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; modul'),(0,'SP18 (6V)','Siemens',1999,0,'c-Si',18,2,2,11,2,9,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,2,1,1,0,'','Area = 0.174 m^2; (10.8 x 24.9). Weight = 2.7 kg (5.9 lb). Module with 2 parallel strings of 18 (70 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; T'),(0,'SP36 (12V)','Siemens',1999,0,'c-Si',36,1,2,22,2,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,2,1,1,0,'','Area = 0.333 m^2; (20.8 x 24.9). Weight = 4.3 kg (9.5 lb). Module with 36 (70 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; modul'),(0,'SP36 (6V)','Siemens',1999,0,'c-Si',18,2,5,11,4,9,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.333 m^2; (20.8 x 24.9). Weight = 4.3 kg (9.5 lb). Module with 2 parallel strings of 18 (70 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; T'),(0,'SP65 (12V)','Siemens',2001,1,'c-Si',36,1,5,21,4,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 0.633 m^2; (20.8 x47.3). Weight = 7.6 kg (16.7 lb). Module with 36 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; modu'),(0,'SP70 (12V)','Siemens',1999,1,'c-Si',36,1,5,21,4,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.633 m^2; (20.8 x47.3). Weight = 7.6 kg (16.7 lb). Module with 36 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; modu'),(0,'SP70 (6V)','Siemens',1999,1,'c-Si',18,2,9,11,9,8,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,9,6,1,0,'','Area = 0.633 m^2; (20.8 x47.3). Weight = 7.6 kg (16.7 lb). Module with 2 parallel strings of 18 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; '),(0,'SP75','Siemens',1997,1,'c-Si',36,1,5,22,4,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.633 m^2; (20.8 x47.3). Weight = 7.6 kg (16.7 lb). Module with 36 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; modu'),(0,'SP75 (12V)','Siemens',1999,1,'c-Si',36,1,5,22,4,17,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.633 m^2; (20.8 x47.3). Weight = 7.6 kg (16.7 lb). Module with 36 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; modu'),(0,'SP75 (6V)','Siemens',1999,1,'c-Si',18,2,10,11,9,9,0,0,1,0,0,0,0,0,1,0,-9,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,10,6,1,0,'','Area = 0.633 m^2; (20.8 x47.3). Weight = 7.6 kg (16.7 lb). Module with 2 parallel strings of 18 (140 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; '),(0,'SR100 (12V)','Siemens',1999,1,'c-Si',36,1,6,22,6,18,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,6,4,1,0,'','Area = 0.890 m^2; (23.4 x 59.0). Weight = 10.9 kg (24.0 lb). Module with 36 circular (175 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar back'),(0,'SR100 (6V)','Siemens',1999,1,'c-Si',18,2,13,11,11,9,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,12,8,1,0,'','Area = 0.890 m^2; (23.4 x 59.0). Weight = 10.9 kg (24.0 lb). Module with 2 parallel strings of18 circular (175 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass fro'),(0,'SR50 (12V)','Siemens',1999,0,'c-Si',36,1,3,22,3,17,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.465 m^2; (23.4 x 30.8). Weight = 5.9 kg (13.0 lb). Module with 36 semi-circular (95 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar b'),(0,'SR50 (6V)','Siemens',1999,0,'c-Si',18,2,6,11,6,9,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,6,4,1,0,'','Area = 0.465 m^2; (23.4 x 30.8). Weight = 5.9 kg (13.0 lb). Module with 2 parallel strings of 18 semi-circular (95 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass'),(0,'SR90 (12V)','Siemens',1999,1,'c-Si',36,1,6,22,5,17,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,6,4,1,0,'','Area = 0.890 m^2; (23.4 x 59.0). Weight = 10.9 kg (24.0 lb). Module with 36 circular (175 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar back'),(0,'SR90 (12V)','Siemens',1998,1,'c-Si',36,1,5,22,5,18,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,4,1,0,'','Area = 0.890 m^2; (23.4 x 59.0). Weight = 10.9 kg (24.0 lb). Module with 36 circular (175 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar back'),(0,'SR90 (6V)','Siemens',1999,1,'c-Si',18,2,12,11,11,9,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,12,7,1,0,'','Area = 0.890 m^2; (23.4 x 59.0). Weight = 10.9 kg (24.0 lb). Module with 2 parallel strings of 18 circular (175 cm^2) pyramidally-textured crystalline silicon cells connected in series. Anodized aluminum frame; low-iron cerium-containing tempered glass fr'),(0,'ST10','Siemens',1999,0,'CIS',42,1,1,21,1,16,0,0,1,0,0,0,0,0,2,1,-3,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,1,0,1,0,'','Small area = 0.127 m^2;  (12.9 x 15.2).  Weight = 2.4 kg  (5.2 lb). Thin-film module with multiple layer copper-indium-diselenide (CIS) cells; with 42 cells connected in series. Designed for use in 12-V systems.  Aluminum framed module;  with low-iron tem'),(0,'ST10','Siemens',1998,0,'CIS',50,1,1,25,1,20,0,0,1,0,0,0,0,0,2,1,-3,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,1,0,1,0,'','Small area = 0.128 m^2;  (12.9 x 15.2).  Weight = 2.4 kg  (5.2 lb). Thin-film module with multiple layer copper-indium-diselenide (CIS) cells; with 50 cells connected in series. Designed for use in 12-V systems.  Aluminum framed module;  with low-iron tem'),(0,'ST20','Siemens',1999,0,'CIS',42,1,1,21,1,16,0,0,1,0,0,0,0,0,2,1,-3,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,1,1,1,0,'','Small area = 0.245 m^2;  (12.9 x 29.4).  Weight = 4.1 kg  (8.8 lb). Thin-film module with multiple layer copper-indium-diselenide (CIS) cells; with 42 cells connected in series. Designed for use in 12-V systems.  Aluminum framed module;  with low-iron tem'),(0,'ST40','Siemens',1999,0,'CIS',42,1,3,22,2,17,0,0,1,0,0,0,0,0,2,1,-3,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,3,2,1,0,'','Small area = 0.424 m^2;  (12.9 x 50.9).  Weight = 3.2 kg  (7 lb). Thin-film module with multiple layer copper-indium-diselenide (CIS) cells; with 44 cells connected in series. Designed for use in 12-V systems.  Aluminum framed module;  with low-iron tempe'),(0,'ST5','Siemens',1999,0,'CIS',42,1,0,22,0,17,0,0,1,0,0,0,0,0,2,0,-8,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,0,0,1,0,'','Small area = 0.0676 m^2;  (12.9 x 8.1).  Weight = 1.4 kg  (3.0 lb). Thin-film module with multiple layer copper-indium-diselenide (CIS) cells; with 50 cells connected in series. Designed for use in 12-V systems.  Aluminum framed module;  with low-iron tem'),(0,'ST5','Siemens',1999,0,'CIS',42,1,0,21,0,16,0,0,1,0,0,0,0,0,2,1,-3,1,0,0,0,0,1,0,0,0,0,0,3,1,-3,0,1,0,0,0,1,0,'','Small area = 0.0676 m^2;  (12.9 x 8.1).  Weight = 1.4 kg  (3.0 lb). Thin-film module with multiple layer copper-indium-diselenide (CIS) cells; with 50 cells connected in series. Designed for use in 12-V systems.  Aluminum framed module;  with low-iron tem'),(0,'SF-100','Solar Fabric',1998,1,'EFG mc-Si',72,1,3,42,3,34,0,0,1,0,0,0,0,0,2,0,-11,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.825 m^2; (25.3 x 50.4). Weight = 10 kg (22.0 lb). Module with 72 ASE Americas  (100 cm^2) EFG multicrystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  '),(0,'SF-115','Solar Fabric',1998,1,'c-Si',36,1,8,21,7,17,0,0,1,0,0,0,0,0,1,0,-10,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,7,5,1,0,'','Area = 0.973 m^2; (26.0 x 58.1). Weight = 10 kg (22.0 lb). Module with 36 AstroPower large-area (240 cm^2) crystalline  silicon cells connected in series. Anodized aluminum frame; tempered glass front sheet; Tedlar backsheet; module laminated with EVA.  J'),(0,'MST-43LV','Solarex',1998,1,'2-a-Si',16,4,3,22,3,16,0,0,1,0,0,0,0,0,4,0,-4,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,3,2,1,0,'','Area = 0.822 m^2; (26.3 x 48.5).  Weight = 16 kg (35 lb). Thin-film module with tandem junction amorphous silicon cells; 4 parallel strings with 16 cells in series.  Anodized aluminum frame;  with two sheets of low-iron heat-strengthened glass laminated w'),(0,'MST-43LV','Solarex',1999,1,'2-a-Si',16,4,4,22,3,17,0,0,1,0,0,0,0,0,4,0,-4,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,3,2,1,0,'','Area = 0.822 m^2; (26.3 x 48.5).  Weight = 16 kg (35 lb). Thin-film module with tandem junction amorphous silicon cells; 4 parallel strings with 16 cells in series.  Anodized aluminum frame;  with two sheets of low-iron heat-strengthened glass laminated w'),(0,'MST-43MV','Solarex',1998,1,'2-a-Si',71,1,1,97,1,74,0,0,1,0,0,0,0,0,3,0,-4,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,1,0,1,0,'','Area = 0.822 m^2; (26.3 x 48.5).  Weight = 16 kg  (35 lb). Mid-voltage; thin-film module with tandem-junction amorphous silicon cells; 71 cells connected in series.  Anodized aluminum frame;  with two sheets of low-iron heat-strengthened glass laminated w'),(0,'MST-43MV','Solarex',1999,1,'2-a-Si',71,1,1,101,1,71,0,0,1,0,0,0,0,0,3,0,-4,1,0,0,0,0,1,0,0,0,0,0,2,1,-3,0,1,0,1,0,1,0,'','Area = 0.822 m^2; (26.3 x 48.5).  Weight = 16 kg  (35 lb). Mid-voltage; thin-film module with tandem-junction amorphous silicon cells; 71 cells connected in series.  Anodized aluminum frame;  with two sheets of low-iron heat-strengthened glass laminated w'),(0,'MSX-110','Solarex',2000,1,'mc-Si',72,1,4,41,3,33,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,2,1,0,'','Area =1.098 m^2; (39.0 x 43.6). Weight = 13 kg (29 lb). Module with 72 large-area (130 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module laminated with'),(0,'MSX-120','Solarex',2000,1,'mc-Si',72,1,4,42,4,34,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area =1.098 m^2; (39.0 x 43.6). Weight = 13 kg (29 lb). Module with 72 large-area (130 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module laminated with'),(0,'MSX-120','Solarex',1999,1,'mc-Si',72,1,4,43,4,34,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area =1.098 m^2; (39.0 x 43.6). Weight = 14 kg (31 lb). Module with 72 large-area (130 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module laminated with'),(0,'MSX-240','Solarex',2000,2,'mc-Si',144,1,4,84,4,68,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area =2.120 m^2; (44.1 x 74.5). Weight = 21.2 kg (46.4 lb). Module with 144 large-area (130 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module laminated'),(0,'MSX-60','Solarex',1999,1,'mc-Si',36,1,4,21,4,17,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 0.556 m^2; (19.75 x 43.63). Weight = 7.2 kg (15.9 lb). Module with 36 large-area (130 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module laminate'),(0,'MSX-64','Solarex',1997,1,'mc-Si',36,1,4,21,4,17,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 0.556 m^2; (19.75 x 43.63). Weight = 7.2 kg (15.9 lb). Module with 36 large-area (130 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module laminate'),(0,'MSX-64','Solarex',1999,1,'mc-Si',36,1,4,21,4,18,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 0.556 m^2; (19.75 x 43.63). Weight = 7.2 kg (15.9 lb). Module with 36 large-area (130 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module laminate'),(0,'MSX-64 (SiNx Proto)','Solarex',1999,1,'mc-Si',36,1,4,22,4,17,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Prototype with SiNx anti-reflection coating on cells. Area = 0.556 m^2; (19.75 x 43.63). Weight = 7.2 kg (15.9 lb). Module with 36 large-area (130 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempere'),(0,'MSX-77','Solarex',1999,1,'mc-Si',36,1,5,21,5,17,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 0.732 m^2; (26.0 x 43.6). Weight = 9.5 kg (20.9 lb). Module with 36 large-area (175 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module laminated '),(0,'MSX-83','Solarex',1999,1,'mc-Si',36,1,5,21,5,17,0,0,1,0,0,0,0,0,1,0,-7,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,4,1,0,'','Area = 0.732 m^2; (26.0 x 43.6). Weight = 9.5 kg (20.9 lb). Module with 36 large-area (175 cm^2) multicrystalline silicon cells connected in series. Aluminum frame; low-iron cerium-containing tempered glass front sheet; Tedlar backsheet; module laminated '),(0,'US-21','Solarex',1999,0,'3-a-Si',11,1,2,24,1,17,0,0,1,0,0,0,0,0,4,-1,-3,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,1,1,1,0,'','Area = 0.356 m^2; (15.1 x 36.5).  Weight = 3.0 kg  (6.6 lb). Flexible; light-weight;  thin-film module with large-area (270 cm^2) triple-junction amorphous silicon cells; 11 cells connected in series.  Anodized aluminum frame;  with dimpled Tefzel front c'),(0,'US-32','Unisolar',1997,1,'3-a-Si',11,1,3,22,2,15,0,0,1,0,0,0,0,0,4,-1,-3,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,2,2,1,0,'','Area = 0.525 m^2; (15.1 x 53.8).  Weight = 4.8 kg  (10.6 lb). Flexible; light-weight;  thin-film module with large-area (410 cm^2) triple-junction amorphous silicon cells; 11 cells connected in series.  Anodized aluminum frame;  with dimpled Tefzel front '),(0,'US-32','Unisolar',1997,1,'3-a-Si',11,1,3,21,2,16,0,0,1,0,0,0,0,0,4,-1,-3,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,2,1,1,0,'','Area = 0.525 m^2; (15.1 x 53.8).  Weight = 4.8 kg  (10.6 lb). Flexible; light-weight;  thin-film module with large-area (410 cm^2) triple-junction amorphous silicon cells; 11 cells connected in series.  Anodized aluminum frame;  with dimpled Tefzel front '),(0,'US-32','Unisolar',1999,1,'3-a-Si',11,1,2,24,2,17,0,0,1,0,0,0,0,0,4,-1,-3,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,2,1,1,0,'','Area = 0.525 m^2; (15.1 x 53.8).  Weight = 4.8 kg  (10.6 lb). Flexible; light-weight;  thin-film module with large-area (410 cm^2) triple-junction amorphous silicon cells; 11 cells connected in series.  Anodized aluminum frame;  with dimpled Tefzel front '),(0,'US-42','Unisolar',1999,1,'3-a-Si',11,2,3,24,3,17,0,0,1,0,0,0,0,0,4,-1,-4,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,3,2,1,0,'','Area = 0.688 m^2; (29.2 x 36.5).  Weight = 6.3 kg  (13.8 lb). Flexible; light-weight;  thin-film module with large-area (270 cm^2)  triple-junction amorphous silicon cells; 11 cells connected in series; 2 parallel cell-strings.  Anodized aluminum frame;  '),(0,'US-64','Unisolar',1997,1,'3-a-Si',11,2,5,22,4,15,0,0,1,0,0,0,0,0,4,-1,-4,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 1.01 m^2; (29.2 x 53.8).  Weight = 9.2 kg  (20.2 lb). Flexible; light-weight;  thin-film module with large-area (410 cm^2) triple-junction amorphous silicon cells; 11 cells connected in series; 2 parallel cell-strings.  Anodized aluminum frame;  wi'),(0,'US-64','Unisolar',1997,1,'3-a-Si',11,2,5,21,4,16,0,0,1,0,0,0,0,0,4,-1,-4,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,5,3,1,0,'','Area = 1.01 m^2; (29.2 x 53.8).  Weight = 9.2 kg  (20.2 lb). Flexible; light-weight;  thin-film module with large-area (410 cm^2)  triple-junction amorphous silicon cells; 11 cells connected in series; 2 parallel cell-strings.  Anodized aluminum frame;  w'),(0,'US-64','Unisolar',1999,1,'3-a-Si',11,2,5,24,4,17,0,0,1,0,0,0,0,0,4,-1,-4,1,0,0,0,0,1,0,0,0,0,0,3,1,-4,0,1,0,4,3,1,0,'','Area = 1.01 m^2; (29.2 x 53.8).  Weight = 9.2 kg  (20.2 lb). Flexible; light-weight;  thin-film module with large-area (410 cm^2)  triple-junction amorphous silicon cells; 11 cells connected in series; 2 parallel cell-strings.  Anodized aluminum frame;  w');
/*!40000 ALTER TABLE `modules` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `prices`
--

DROP TABLE IF EXISTS `prices`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `prices` (
  `itemID` int(11) NOT NULL,
  `vendorID` int(11) NOT NULL,
  `price` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prices`
--

LOCK TABLES `prices` WRITE;
/*!40000 ALTER TABLE `prices` DISABLE KEYS */;
/*!40000 ALTER TABLE `prices` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `profiles`
--

DROP TABLE IF EXISTS `profiles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `profiles` (
  `projectID` int(11) NOT NULL,
  `itemID` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `description` varchar(255) NOT NULL,
  `type` enum('Battery','Center','Charger','Combiner','Inverter','Load','PVPanel','Pump','Wire') NOT NULL,
  `quantity` int(11) NOT NULL,
  `hours` int(11) NOT NULL,
  `minutes` int(11) NOT NULL,
  `days` int(11) NOT NULL,
  KEY `projectID` (`projectID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `profiles`
--

LOCK TABLES `profiles` WRITE;
/*!40000 ALTER TABLE `profiles` DISABLE KEYS */;
INSERT INTO `profiles` VALUES (21,0,'Blender','','Load',0,0,0,0),(21,0,'AC Lights','','Load',0,0,0,0),(21,0,'Dish Washer','','Load',0,0,0,0),(21,0,'Coffee Grinder','','Load',0,0,0,0),(21,0,'Dish Washer','','Load',0,0,0,0),(21,0,'Coffee Grinder','','Load',0,0,0,0),(21,0,'Coffee Grinder','','Load',0,0,0,0),(21,0,'21in CRT','','Load',0,0,0,0),(21,0,'19ft Refridgerator','','Load',0,0,0,0),(21,0,'Alarm Clock','','Load',0,0,0,0),(21,0,'Glue Gun','','Load',0,0,0,0),(21,0,'AC Lights','','Load',0,0,0,0),(21,0,'21in CRT','','Load',0,0,0,0),(21,0,'Blender','','Load',0,0,0,0),(21,0,'Blender','','Load',0,0,0,0),(21,0,'18in LCD Monitor','','Load',0,0,0,0),(21,0,'Blender','','Load',0,0,0,0),(21,0,'18in LCD Monitor','','Load',0,0,0,0),(21,0,'Blender','','Load',0,0,0,0),(21,0,'18in LCD Monitor','','Load',0,0,0,0),(21,0,'Alarm Clock','','Load',0,0,0,0),(21,0,'18in LCD Monitor','','Load',0,0,0,0),(21,0,'Blender','','Load',0,0,0,0),(21,0,'TV','','Load',0,0,0,0),(21,0,'TV','','Load',0,0,0,0),(21,0,'Alarm Clock','','Load',0,0,0,0),(21,0,'AC Lights','','Load',0,0,0,0);
/*!40000 ALTER TABLE `profiles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `projects`
--

DROP TABLE IF EXISTS `projects`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `projects` (
  `id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `description` varchar(255) NOT NULL,
  `sunhours` double NOT NULL,
  `windhours` double NOT NULL,
  `windspeed` double NOT NULL,
  `latitude` double NOT NULL,
  `longitude` double NOT NULL,
  KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `projects`
--

LOCK TABLES `projects` WRITE;
/*!40000 ALTER TABLE `projects` DISABLE KEYS */;
INSERT INTO `projects` VALUES (1,'','',0,0,0,0,0),(2,'My Test','testing, 1,2,3...',1.2,2.3,3.4,4.5,5.6),(3,'My Test','testing, 1,2,3...',1.2,2.3,3.4,4.5,5.6),(4,'My Test','testing, 1,2,3...',1.2,2.3,3.4,4.5,5.6),(5,'My Test','testing, 1,2,3...',1.2,2.3,3.4,4.5,5.6),(6,'My Test','testing, 1,2,3...',1.2,2.3,3.4,4.5,5.6),(7,'My Test','testing, 1,2,3...',1.2,2.3,3.4,4.5,5.6),(8,'unamed project','',0,0,0,0,0),(9,'unamed project','',0,0,0,0,0),(10,'none','',0,0,0,0,0),(11,'unamed project','',0,0,0,0,0);
/*!40000 ALTER TABLE `projects` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pumps`
--

DROP TABLE IF EXISTS `pumps`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pumps` (
  `itemID` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `manufacturer` varchar(255) NOT NULL,
  `price` int(11) NOT NULL,
  `wattage` int(11) NOT NULL,
  `voltage` int(11) NOT NULL,
  `gpm` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pumps`
--

LOCK TABLES `pumps` WRITE;
/*!40000 ALTER TABLE `pumps` DISABLE KEYS */;
INSERT INTO `pumps` VALUES (50001,'ETA','Dankoff',2000,900,24,5);
/*!40000 ALTER TABLE `pumps` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vendors`
--

DROP TABLE IF EXISTS `vendors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vendors` (
  `vendorID` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `address` varchar(255) NOT NULL,
  `city` varchar(255) NOT NULL,
  `state` text NOT NULL,
  `zipcode` int(11) NOT NULL,
  `url` varchar(255) NOT NULL,
  `phone` text NOT NULL,
  `email` varchar(255) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vendors`
--

LOCK TABLES `vendors` WRITE;
/*!40000 ALTER TABLE `vendors` DISABLE KEYS */;
INSERT INTO `vendors` VALUES (10002,' Backwoods Solar',' 1589 Rapid Lightning Rd','Sandpoint','ID',83864,' http://www.backwoodssolar.com',' 208-263-4290',' info@backwoodssolar.com'),(10001,' Real Goods',' 833 W. South Boulder Rd.','Louisville','CO',80027,'http://www.realgoods.com',' (800) 919-2400',' info@realgoods.com'),(10003,' Colorado Solar',' 38150 River Frontage Rd. #1D',' New Castle',' CO',81647,' http://www.cosolar.com',' (800) 766-7644',' info@cosolar.com');
/*!40000 ALTER TABLE `vendors` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2009-12-28 15:05:37
