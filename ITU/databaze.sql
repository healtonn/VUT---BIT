/*
 *	Autor: xchalu13, xjochl00
 */
 
 SET NAMES utf8;
 SET foreign_key_checks = 0;
 SET time_zone = 'SYSTEM';
 SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';
 
 
 DROP TABLE IF EXISTS `Cesta`;
 DROP TABLE IF EXISTS `Ridic`;
 DROP TABLE IF EXISTS `Spravce`;
 DROP TABLE IF EXISTS `Admin`;
 
 CREATE TABLE `Cesta`(
	`nazevCesty` varchar(50) COLLATE utf8_czech_ci NOT NULL,
	`idCesty` int unsigned NOT NULL AUTO_INCREMENT,
	`idRidice` int unsigned NOT NULL,
	`naklad` varchar(50) COLLATE utf8_czech_ci,
	`startCesty` varchar(50) COLLATE utf8_czech_ci,
	`cilCesty` varchar(50) COLLATE utf8_czech_ci,
	`casOdjezdu` DATETIME,
	`casPrijezdu` DATETIME,
	PRIMARY KEY (`idCesty`),
	KEY `idRidice` (`idRidice`)
);

INSERT INTO `Cesta` (`nazevCesty`, `idCesty`, `idRidice`, `naklad`, `startCesty`, `cilCesty`, `casOdjezdu`, `casPrijezdu`) VALUES
('Převoz brambor', '1', '1', 'Brambory', 'Praha', 'Berlin', '2016-04-25 11:00:00', '2016-04-25 18:12:00'),
('Stavební suroviny', '2', '1', 'Cement', 'Oslo', 'Wien', '2016-04-27 05:30:00', '2016-04-28 06:00:00'),

('Těžká technika pro výkopní práce', '3', '2', 'Bagry', 'Mladá Boleslav', 'Paris', '2016-05-01 14:00:00', '2016-05-02 20:00:00'),
('Převoz hrášku', '4', '2', 'Hrášek v konzervách', 'Paris', 'Rome', '2016-05-03 07:00:00', '2016-05-04 12:15:00'),

('Boty značky adidas', '5', '3', 'Boty', 'Moskva', 'Brno', '2016-04-26 18:00:00', '2016-04-28 11:50:00'),
('Pilsner Urquell', '6', '3', 'Pivo', 'Brno', 'London', '2016-05-10 15:00:00', '2016-05-11 19:00:00');

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE `Ridic`(
	`idRidice` int unsigned NOT NULL AUTO_INCREMENT,
	`jmeno` varchar(50) COLLATE utf8_czech_ci,
	`prijmeni` varchar(50) COLLATE utf8_czech_ci,
	`rodneCislo` varchar(16) COLLATE utf8_czech_ci,
	`narodnost` varchar(20) COLLATE utf8_czech_ci,
	`mesto` varchar(50) COLLATE utf8_czech_ci,
	`ulice` varchar(50) COLLATE utf8_czech_ci,
	PRIMARY KEY(`idRidice`)
);

INSERT INTO `Ridic` (`idRidice`, `jmeno`, `prijmeni`, `rodneCislo`, `narodnost`, `mesto`, `ulice`) VALUES
('1', 'Carl', 'Jhonson', '850615-3258', 'USA', 'Junction City', 'George St'),
('2', 'Wolf', 'Kreig', '564892-5168', 'GE', 'Berlin', 'Johanes St'),
('3', 'Franta', 'Krop', '468416-1654', 'CZ', 'Pardubice', 'Podolní');

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE `Spravce`(
	`idSpravce` int unsigned NOT NULL AUTO_INCREMENT,
	`jmeno` varchar(30) COLLATE utf8_czech_ci,
	`prijmeni` varchar(30) COLLATE utf8_czech_ci,
	`login` varchar(30) COLLATE utf8_czech_ci,
	`heslo` varchar(30) COLLATE utf8_czech_ci,
	PRIMARY KEY(`idSpravce`)
);

INSERT INTO `Spravce` (`idSpravce`, `jmeno`, `prijmeni`, `login`, `heslo`) VALUES
('1', 'spravce1', 'spravce1', 'spravce1', 'spravce1');

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE `Admin`(
	`idAdmina` int unsigned NOT NULL AUTO_INCREMENT,
	`jmeno` varchar(30) COLLATE utf8_czech_ci,
	`prijmeni` varchar(30) COLLATE utf8_czech_ci,
	`login` varchar(30) COLLATE utf8_czech_ci,
	`heslo` varchar(30) COLLATE utf8_czech_ci,
	PRIMARY KEY(`idAdmina`)
);

INSERT INTO `Admin` (`idAdmina`, `jmeno`, `prijmeni`, `login`, `heslo`) VALUES
('1', 'admin1', 'admin1', 'admin1', 'admin1
