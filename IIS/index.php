<?php
/*
 *	Projekt do predmetu IIS pro tema Galerie
 *	Autor: xjochl00, xstast24
 */

 include "hlavicka1.html";
 if (!isset($_SESSION)){
	ini_set('session.save_path',getcwd(). '/');

	session_start();
	}
 include "db_connect.php";
 include "start.php";
 include "edit_table.php";
 include "zakaznik.php";
 include "zamestnanec.php";
 include "admin.php";
 
 necinnost();//pokud bude uzivatel neaktivni, probehne odhlaseni
 
 
 if(!isset($_GET["menu"]))
	$_GET["menu"]=0; 
 if(!isset($_GET["zakaznik"]))
	$_GET["zakaznik"]=0;
 if(!isset($_GET["zamestnanec"]))
	$_GET["zamestnanec"]=0;
 if(!isset($_GET["admin"]))
	$_GET["admin"]=0;
	
 if(isset($_POST["typ_prihlaseni"])){	//pokud byl vyplnen prihlasovaci formular
	if($_POST["typ_prihlaseni"]=="zakaznik" and isset($_POST["login"]) and $_POST["login"]!=""){//zakaznik
		$prover_login="SELECT * FROM Zakaznik WHERE login='".$_POST["login"]."'";
		$provereno=mysql_query($prover_login, $databaze);
		if(!($provereno))
			echo "<br>Neexistujci login.<br>";
		else{	//login existuje
			$zakaznik=mysql_fetch_array($provereno, MYSQL_ASSOC);
			if($zakaznik["heslo"]==$_POST["pwd"]){//kontrola hesla
				$_GET["zakaznik"]=0;
				$_SESSION["prihlasen_je"]="zakaznik";
				$_SESSION["posledni_pohyb"]=time();
				$_SESSION["id_zakaznika"]=$zakaznik["IDZakaznika"];
				$_GET["menu"]=0;
			}
			else {
				echo "<br>nespravné údaje<br>";
			}
		}
	}//konec if zakaznik
	else if($_POST["typ_prihlaseni"]=="zamestnanec" and isset($_POST["login"]) and $_POST["login"]!=""){//zamestnanec
		$prover_login="SELECT * FROM Zamestnanec WHERE login='".$_POST["login"]."' AND postaveni='zamìstnanec'";
		$provereno=mysql_query($prover_login, $databaze);
		if(!$provereno){
			echo "<br>¹patné pøihlá¹ení";
		}
		else{
			$zamestnanec=mysql_fetch_array($provereno, MYSQL_ASSOC);
			if($zamestnanec["heslo"]==$_POST["pwd"]){
				$_GET["zamestnanec"]=0;
				$_SESSION["prihlasen_je"]="zamestnanec";
				$_SESSION["posledni_pohyb"]=time();
				$_SESSION["id_zamestnance"]=$zamestnanec["IDZamestnance"];
				$_GET["menu"]=0;
			}
			else{
				echo "<br>nespravné údaje<br>";
			}
		}
	}//konec zamestnanec
	else if($_POST["typ_prihlaseni"]=="admin" and isset($_POST["login"]) and $_POST["login"]!=""){//admin
		$prover_login="SELECT * FROM Zamestnanec WHERE login='".$_POST["login"]."' AND postaveni='vedouci'";
		$provereno=mysql_query($prover_login, $databaze);
		if(!$provereno){
			echo "<br>¹patné pøihlá¹ení";
		}
		else{
			$zamestnanec=mysql_fetch_array($provereno, MYSQL_ASSOC);
			if($zamestnanec["heslo"]==$_POST["pwd"]){
				$_GET["admin"]=0;
				$_SESSION["prihlasen_je"]="admin";
				$_SESSION["posledni_pohyb"]=time();
				$_SESSION["id_zamestnance"]=$zamestnanec["IDZamestnance"];
				$_GET["menu"]=0;
			}
			else{
				echo "<br>nespravné údaje<br>";
			}
		}
	}//konec admin
	else{
		echo "<br>Chybné pøihlá¹ení<br>";
	}//konec admin
 }
 
 if(!isset($_SESSION["prihlasen_je"])){		//pokud nikdo neni prihlaseny
	menu($databaze, $_GET["menu"]);	 //zavolam zobrazeni home
 }
 else{
	$_SESSION["posledni_pohyb"]=time();
	switch($_SESSION["prihlasen_je"]){	//tady budu zobrazovat obash podle toho, kdo je prihlasen
	case "zakaznik":
		zakaznik($databaze, $_GET["zakaznik"]);
		break;
	case "zamestnanec":
		zamestnanec($databaze, $_GET["zamestnanec"]);
		break;
	case "admin":
		admin($databaze, $_GET["admin"]);
		break;
	}
 }
 
 

 
 include "hlavicka2.html"
?>