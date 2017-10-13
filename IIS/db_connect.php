<?
/*	Autor: xjochl00, xstast24
 *
 *
 *	Pro pripojeni pouzijeme parametry, ktery vygeneroval WIS
 *	Server='localhost:/var/run/mysql/mysql.sock'
 *	Databáze='xjochl00'
 *	U¾ivatel='xjochl00'
 *	Heslo='j6ufajko'
 */
$DB_SERVER = "localhost:/var/run/mysql/mysql.sock";
$DB_IDENTIFICATION = "xjochl00";
$DB_USER = "xjochl00";
$DB_PASSWORD = "j6ufajko";

$databaze = mysql_connect($DB_SERVER, $DB_USER, $DB_PASSWORD);	//Pokusim se pripojit k databazi
mysql_set_charset("latin2",$databaze);

if(!$databaze)	//checknu jestli jsem se spojil
	die ('Nelze navazat spojeni '.mysql_error());

if(!mysql_select_db($DB_IDENTIFICATION, $databaze))	//Checknu jeslti je db dostupna
	die ('Databaze neni dostupna '.mysql_error());
?>