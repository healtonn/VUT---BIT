/*
 *	Autor: xjochl00, xstast24
 */
 
SET NAMES utf8;
SET foreign_key_checks = 0;
SET time_zone = 'SYSTEM';
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

DROP TABLE IF EXISTS `Dilo`;
DROP TABLE IF EXISTS `Expozice`;
DROP TABLE IF EXISTS `Zamestnanec`;
DROP TABLE IF EXISTS `Zakaznik`;
DROP TABLE IF EXISTS `Mistnost`;
DROP TABLE IF EXISTS `Misto`;

CREATE TABLE `Dilo`(
	`nazev` varchar(50) COLLATE utf8_czech_ci NOT NULL,
	`IDExpozice` int(8) unsigned NOT NULL,
	`autor` varchar (50) COLLATE utf8_czech_ci,
	`typ_dila` varchar(50) COLLATE utf8_czech_ci,
	`cena` varchar(30),
	`IDMista` integer(32),
	PRIMARY KEY (`nazev`),
	KEY `IDExpozice` (`IDExpozice`)
);

INSERT INTO `Dilo` (`nazev`, `IDExpozice`, `autor`, `typ_dila`, `cena`, `IDMista`) VALUES
('Ranní obloha', '1', 'Miloš Heydrich', 'obraz', '105', '1'),
('Odpolední obloha', '1', 'Adolf Zeman', 'obraz', '1800', '2'),
('Večerní obloha', '1', 'Reinhard Obama', 'obraz', '150000', '3'),
('Volání divočiny', '2', 'Miroslav Frosty', 'obraz', '15000', '4'),
('Pan tvrďák', '2', 'Rudolf Rudý', 'socha', '50000', '5');

/*-----------------------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE `Expozice`(
	`IDExpozice` int unsigned NOT NULL AUTO_INCREMENT,
	`IDZakaznika` int unsigned NOT NULL,
	`Nazev_expozice` varchar(50) COLLATE utf8_czech_ci,
	`vystavena_od` varchar(30),
	`vystavena_do` varchar(30),
	`stav_platby` varchar(20) DEFAULT 'nezaplaceno',
	PRIMARY KEY (`IDExpozice`)
);

INSERT INTO `Expozice` (`IDExpozice`, `IDZakaznika`, `Nazev_expozice`, `vystavena_od`, `vystavena_do`, `stav_platby`) VALUES
('1', '1', 'polední slunce', '20.03.1891', '23.02.2020', 'zaplaceno'),
('2', '3', 'katarze', '20.03.2012', '23.02.2018', 'zaplaceno');

/*-----------------------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE `Zamestnanec` (
	`IDZamestnance` int NOT NULL AUTO_INCREMENT,
	`jmeno` varchar (20) COLLATE utf8_czech_ci,
	`prijmeni` varchar(30) COLLATE utf8_czech_ci,
	`ulice` varchar(50) COLLATE utf8_czech_ci,
	`mesto` varchar(50) COLLATE utf8_czech_ci,
	`rodne_cislo` varchar(20),
	`postaveni` varchar(15),
    `login` varchar(20),
    `heslo` varchar(20),
	PRIMARY KEY (`IDZamestnance`)
);

INSERT INTO `Zamestnanec` (`IDZamestnance`, `jmeno`, `prijmeni`, `ulice`, `mesto`, `rodne_cislo`, `postaveni`, `login`, `heslo`) VALUES
('1', 'Karel', 'Karlenko', 'Dlouhá', 'Brno', '8507012129', 'vedoucí', 'KarlenkoK', 'vedouci'),
('2', 'Ivan', 'Ivanovski', 'Krátká', 'Brno', '8507012140', 'zaměstnanec', 'IvanovskiI', 'zamestnanec'),
('3', 'Dežo', 'Demeter', 'Dlouhá', 'Praha', '8507012151', 'zaměstnanec', 'DemeterD', 'zamestnanec');

/*-----------------------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE `Zakaznik` (
	`IDZakaznika` int NOT NULL AUTO_INCREMENT,
	`ulice` varchar(50) COLLATE utf8_czech_ci,
	`mesto` varchar(50) COLLATE utf8_czech_ci,
	`telefon` varchar(15),
	`typ` varchar(10) COLLATE utf8_czech_ci,
	`jmeno` varchar(50) COLLATE utf8_czech_ci,
	`prijmeni` varchar(50) COLLATE utf8_czech_ci,
	`jmeno_firmy` varchar (100) COLLATE utf8_czech_ci,
	`ICO` varchar(20),
    `login` varchar(20),
    `heslo` varchar(20),
	PRIMARY KEY (`IDZakaznika`)
);

INSERT INTO `Zakaznik` (`IDZakaznika`, `ulice`, `mesto`, `telefon`, `typ`, `jmeno`, `prijmeni`, `jmeno_firmy`, `ICO`, `login`, `heslo`) VALUES
('1', 'Střední', 'Popovice', '777696969', 'FO', 'Boris', 'Zbořil', '', '', 'ZborilB', 'zakaznik'),
('2', 'Dlouhá', 'Brno', '777666666', 'FO', 'Boris', 'Postavil', '', '', 'PostavilB', 'zakaznik'),
('3', 'Středně dlouhá', 'Rajhrad', '777999999', 'PO', '', '', 'Yolo, s.r.o.', '12345679', 'Yolofirma', 'zakaznik');

/*-----------------------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE `Mistnost` (
	`IDMistnosti`	int NOT NULL,
	`klimatizace`	varchar(10) COLLATE utf8_czech_ci,
	`vlhkost_vzduchu`	int,
	`bezbarierovy_pristup` varchar(10) COLLATE utf8_czech_ci,
	`bezpecnostni_kamery` varchar(10) COLLATE utf8_czech_ci,
	PRIMARY KEY (`IDMistnosti`)
);

INSERT INTO `Mistnost` (`IDMistnosti`, `klimatizace`, `vlhkost_vzduchu`, `bezbarierovy_pristup`, `bezpecnostni_kamery`) VALUES
('1', 'Ano', '30', 'Ano', 'Ano'),
('2', 'Ne', '50', 'Ne', 'Ano'),
('3', 'Ano', '10', 'Ne', 'Ano');

/*-----------------------------------------------------------------------------------------------------------------------------------*/

CREATE TABLE `Misto`(
	`IDMista` int NOT NULL,
	`IDMistnosti` int NOT NULL,
	`IDExpozice` int NOT NULL,
	`IDZamestnance` int NOT NULL,
	`typ_mista` varchar(30) COLLATE utf8_czech_ci,
	`typ_osvetleni` varchar(30) COLLATE utf8_czech_ci,
	`alarm` varchar(5),
	`velikost` int NOT NULL,
	`cena_za_pronajem` int NOT NULL,
	PRIMARY KEY (`IDMIsta`)
);

INSERT INTO `Misto` (`IDMista`, `IDMistnosti`, `IDExpozice`, `IDZamestnance`, `typ_mista`, `typ_osvetleni`, `alarm`, `velikost`, `cena_za_pronajem`) VALUES
('1', '1', '1', '1', 'stěna', 'zářivka', 'Ne', '4', '900'),
('2', '1', '1', '1', 'stěna', 'zářivka', 'Ano', '8', '1500'),
('3', '1', '1', '1', 'stěna', 'LED', 'Ano', '8', '1600'),

('4', '2', '2', '2', 'stěna', 'žárovka', 'Ano', '4', '1000'),
('5', '2', '2', '2', 'vytrína', 'LED', 'Ano', '3', '2000'),

('6', '3', '0', '3', 'stěna', 'žárovka', 'Ano', '10', '3500'),
('7', '3', '0', '3', 'podstavec', 'zářivka', 'Ano', '1', '2100');

/*-----------------------------------------------------------------------------------------------------------------------------------*/