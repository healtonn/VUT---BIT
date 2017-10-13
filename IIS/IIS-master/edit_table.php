<?
 include "funkce.php";
 
 if(isset($_POST["registraceFO"])){		//registrace jednotlivce
	if(empty($_POST['jmeno']) or empty($_POST['prijmeni']) or empty($_POST['email']) or empty($_POST['login']) or empty($_POST['heslo'])){
		echo "<br>Vyplnìte povinná pole<br>";
	}
	else{
		$dotaz="INSERT INTO Zakaznik (IDZakaznika, ulice, mesto, telefon, typ, jmeno, prijmeni,jmeno_firmy, ICO, login, heslo) VALUES
		('', '{$_POST['ulice']}', '{$_POST['mesto']}', '{$_POST['telefon']}', 'FO', '{$_POST['jmeno']}', '{$_POST['prijmeni']}', '', '', '{$_POST['login']}', '{$_POST['heslo']}')";
		$vysledek=mysql_query($dotaz, $databaze);
		if(!($vysledek))
			echo  "Chyba: ©patnì vyplnìný formuláø.<br>";
	}
 }
 
 if(isset($_POST["registracePO"])){	//registrace firmy
	if(empty($_POST['jmeno']) or empty($_POST['ico']) or empty($_POST['prijmeni']) or empty($_POST['jmeno_firmy']) or empty($_POST['email']) or empty($_POST['login']) or empty($_POST['heslo'])){
		echo "<br>Vyplnìte povinná pole<br>";
	}
	else{
		$dotaz="INSERT INTO Zakaznik (IDZakaznika, ulice, mesto, telefon, typ, jmeno, prijmeni,jmeno_firmy, ICO, login, heslo) VALUES
		('', '{$_POST['ulice']}', '{$_POST['mesto']}', '{$_POST['telefon']}', 'FO', '{$_POST['jmeno']}', '{$_POST['prijmeni']}', '{$_POST['jmeno_firmy']}', '{$_POST['ico']}', '{$_POST['login']}', '{$_POST['heslo']}')";
		$vysledek=mysql_query($dotaz, $databaze);
		if(!($vysledek))
			echo  "Chyba: ©patnì vyplnìný formuláø.<br>";
	}
 }
 
 if(isset($_GET["mistnost"])){	//zobrazeni mistnosti
	prohlidka_mistnosti($databaze, $_GET['mistnost']);
 }
 
 if(isset($_POST["vytvorit_expizici"])){	//tvorba expozice zakaznikem
	if(zkontroluj_datum($_POST["vystaveno_od"]) and zkontroluj_datum($_POST["vystaveno_do"])){
		if(zkontroluj_datum_chronologicky($_POST["vystaveno_od"], $_POST["vystaveno_do"])){
			$dotaz="INSERT INTO Expozice (IDExpozice, IDZakaznika, Nazev_expozice, vystavena_od, vystavena_do, stav_platby) VALUES
			('','{$_SESSION["id_zakaznika"]}','{$_POST['nazev_expozice']}', '{$_POST['vystaveno_od']}', '{$_POST['vystaveno_do']}', '{$_POST['stav_platby']}')";
			$vysledek=mysql_query($dotaz, $databaze);
			if(!($vysledek))
				echo  "Chyba: ©patnì vyplnìný formuláø.";
		}//chronologicky
		else{
			echo "©patnì zadaný datum.Expozice musí v galerii strávit aspoò jednu noc.<br>";
		}
	}//if zkontroluj datum
	else{
		echo "©patnì zadaný datum. Format je DD.MM.YYYY<br>";
	}
 }
 
 if(isset($_POST["upravit_expozici_zakaznik"]) and isset($_POST["upravit_expozici"])){	//uprava expozice zakaznikem
	if($_POST["upravit_expozici"]=="upravit"){
		$_GET["zakaznik"]="5";
	}
	else if($_POST["upravit_expozici"]=="smazat"){
		$dotaz="DELETE FROM Expozice WHERE IDExpozice='".$_POST["id_expozice"]."'";
		$odpoved=mysql_query($dotaz, $databaze);
		if(!$odpoved){
			echo "Nelze smazat expozici<br>";
		}
		else{
			$update="DELETE FROM Dilo WHERE IDExpozice='".$_POST["id_expozice"]."'";
			$odpoved=mysql_query($update, $databaze);
			if(!$databaze){
				echo "Nastala chyba<br>";
			}
			else{
				$update="UPDATE Misto SET IDExpozice='0' WHERE IDExpozice='".$_POST["id_expozice"]."'";
				$odpoved=mysql_query($update, $databaze);
				if(!$odpoved)
					echo "Nastala chyba<br>";
			}
		}
	}
	else if($_POST["upravit_expozici"]=="pridat_dilo"){
		$_SESSION["id_expozice"]=$_POST["id_expozice"];
		$_GET["zakaznik"]="6";
	}
 }
 
 if(isset($_POST["smaz_dilo_submit"])){	//zakaznik maze dilo
	$dotaz="DELETE FROM Dilo WHERE nazev='".$_POST["smaz_dilo"]."'";
	$vysledek=mysql_query($dotaz, $databaze);
	if(!$vysledek)
		echo "Nastala chyba<br>";
 }
 
 if(isset($_POST["vytvorit_dilo"])){//zakaznik tvori dilo
	$dotaz="INSERT INTO Dilo (nazev, IDExpozice, autor, typ_dila, cena, IDMista) VALUES
	('{$_POST['nazev_dila']}', '{$_SESSION['id_expozice']}', '{$_POST['autor']}','{$_POST['typ_dila']}', '{$_POST['cena_dila']}', '{$_POST['pozice']}')";
	$odpoved=mysql_query($dotaz, $databaze);
	if(!$odpoved){
		echo "Dilo nelze vlozit<br>";
	}
	else{
		$update="UPDATE Misto SET IDExpozice='".$_SESSION["id_expozice"]."' WHERE IDMista='".$_POST["pozice"]."'";
		$odpoved=mysql_query($update, $databaze);
		if(!$odpoved)
			echo "Nastala chyba<br>";
	}
 }
 
 if(isset($_POST["vytvorit_expizici_spravce"])){	//zamestnanec tvori expozici
	if(empty($_POST["nazev_expozice"]) or empty($_POST["id_zakaznika_sprava"]) or !preg_match("/[0-9]+/",$_POST["id_zakaznika_sprava"])){
		echo "<br>©patnì vyplnìný formuláø<br>";
	}
	else{
		if(zkontroluj_datum($_POST["vystaveno_od"]) and zkontroluj_datum($_POST["vystaveno_do"])){
			if(zkontroluj_datum_chronologicky($_POST["vystaveno_od"], $_POST["vystaveno_do"])){
				$dotaz="SELECT * FROM Zakaznik WHERE IDZakaznika='".$_POST["id_zakaznika_sprava"]."'";
				$odpoved=mysql_query($dotaz, $databaze);
				if(!$odpoved){
					echo "<br>Dilo nelze vytvoøit<br>";
				}
				else{
					$test=mysql_fetch_array($odpoved, MYSQL_ASSOC);
					if(!$test){
						echo "<br>Zakaznis s ID: {$_POST["id_zakaznika_sprava"]} neexistuje<br>";
					}
					else{
						$dotaz="INSERT INTO Expozice (IDExpozice, IDZakaznika, Nazev_expozice, vystavena_od, vystavena_do, stav_platby) VALUES
						('','{$_POST['id_zakaznika_sprava']}','{$_POST['nazev_expozice']}', '{$_POST['vystaveno_od']}', '{$_POST['vystaveno_do']}', '{$_POST['stav_platby']}')";
						$odpoved=mysql_query($dotaz, $databaze);
						if(!($odpoved))
							echo  "Chyba: ©patnì vyplnìný formuláø.";
					}
				}
			}
			else{
				echo "©patnì zadaný datum.Expozice musí v galerii strávit aspoò jednu noc.<br>";
			}
		}
		else{
			echo "©patnì zadaný datum. Format je DD.MM.YYYY<br>";
		}
	}
 }
 
 if(isset($_POST["mistnost_zmenena"])){	//spravce meni mistnost
	$update="UPDATE Mistnost SET klimatizace='".$_POST["klimatizace_sprava"]."', vlhkost_vzduchu='".$_POST["vlhkost_vzduchu_sprava"]."', bezbarierovy_pristup='".$_POST["bezbarierovy_pristup_sprava"]."', bezpecnostni_kamery='".$_POST["bezpecnostni_kamery_sprava"]."'
	WHERE IDMistnosti='".$_POST["id_mistnosti_sprava"]."'";
	$odpoved=mysql_query($update, $databaze);
	if(!$odpoved)
		echo "<br>Nelze ulo¾it zmìnu<br>";
 }
 
 if(isset($_POST["upravit_expozici_zamestnanec"])){//spravce upravuje exopozici
	if($_POST["upravit_expozici"]=="zaplaceno"){
	$dotaz="UPDATE Expozice SET stav_platby='zaplaceno' WHERE IDExpozice='".$_POST["id_expozice"]."'";
	$odpoved=mysql_query($dotaz, $databaze);
	if(!$odpoved)
		echo "<br>Chyba pøi spracovávání dotazu<br>";
	}
	else if($_POST["upravit_expozici"]=="upravit"){
		$_SESSION["id_expozice"]=$_POST["id_expozice"];
		$_GET["zamestnanec"]="5";
	}
	else if($_POST["upravit_expozici"]=="smazat"){
		$dotaz="DELETE FROM Expozice WHERE IDExpozice='".$_POST["id_expozice"]."'";
		$odpoved=mysql_query($dotaz, $databaze);
		if(!$odpoved){
			echo "Nelze smazat expozici<br>";
		}
		else{
			$update="DELETE FROM Dilo WHERE IDExpozice='".$_POST["id_expozice"]."'";
			$odpoved=mysql_query($update, $databaze);
			if(!$databaze){
				echo "Nastala chyba<br>";
			}
			else{
				$update="UPDATE Misto SET IDExpozice='0' WHERE IDExpozice='".$_POST["id_expozice"]."'";
				$odpoved=mysql_query($update, $databaze);
				if(!$odpoved)
					echo "Nastala chyba<br>";
			}
		}
	}
 }
 
 if(isset($_POST["smaz_dilo_sprava"])){	//spravce maze dilo
	$dotaz="DELETE FROM Dilo WHERE nazev='".$_POST["smaz_dilo"]."'";
	$vysledek=mysql_query($dotaz, $databaze);
	if(!$vysledek)
		echo "Nastala chyba<br>";
 }
 
 if(isset($_POST["volba_upravit_expozici_sprava"])){	//uprava expozice spravce
	if(zkontroluj_datum($_POST["upravit_vystaveno_od"]) and zkontroluj_datum($_POST["upravit_vystaveno_do"])){
		if(zkontroluj_datum_chronologicky($_POST["upravit_vystaveno_od"], $_POST["upravit_vystaveno_do"])){
			$dotaz="UPDATE Expozice SET vystavena_od='".$_POST["upravit_vystaveno_od"]."', vystavena_do='".$_POST["upravit_vystaveno_do"]."'
			WHERE IDExpozice='".$_SESSION["id_expozice"]."'";
			$odpoved=mysql_query($dotaz, $databaze);
			if(!$odpoved)
				echo "<br>Chyba pøi spracovávání dotazu<br>";
		}
		else{
			echo "©patnì zadaný datum.Expozice musí v galerii strávit aspoò jednu noc.<br>";
		}
	}
	else{
		echo "©patnì zadaný datum. Format je DD.MM.YYYY<br>";
	}
 }
 
  if(isset($_POST["upravit_expozici_admin"])){//spravce upravuje exopozici
	if($_POST["upravit_expozici"]=="zaplaceno"){
	$dotaz="UPDATE Expozice SET stav_platby='zaplaceno' WHERE IDExpozice='".$_POST["id_expozice"]."'";
	$odpoved=mysql_query($dotaz, $databaze);
	if(!$odpoved)
		echo "<br>Chyba pøi spracovávání dotazu<br>";
	}
	else if($_POST["upravit_expozici"]=="upravit"){
		$_SESSION["id_expozice"]=$_POST["id_expozice"];
		$_GET["admin"]="5";
	}
	else if($_POST["upravit_expozici"]=="smazat"){
		$dotaz="DELETE FROM Expozice WHERE IDExpozice='".$_POST["id_expozice"]."'";
		$odpoved=mysql_query($dotaz, $databaze);
		if(!$odpoved){
			echo "Nelze smazat expozici<br>";
		}
		else{
			$update="DELETE FROM Dilo WHERE IDExpozice='".$_POST["id_expozice"]."'";
			$odpoved=mysql_query($update, $databaze);
			if(!$databaze){
				echo "Nastala chyba<br>";
			}
			else{
				$update="UPDATE Misto SET IDExpozice='0' WHERE IDExpozice='".$_POST["id_expozice"]."'";
				$odpoved=mysql_query($update, $databaze);
				if(!$odpoved)
					echo "Nastala chyba<br>";
			}
		}
	}
 }
 
 if(isset($_POST["vytvorit_zamestnance"])){//tvorba zamestnance
	if(empty($_POST["jmeno"]) or empty($_POST["prijmeni"]) or empty($_POST["ulice"]) or empty($_POST["mesto"]) or empty($_POST["rc"]) or empty($_POST["login"]) or empty($_POST["heslo"])){
		echo "<br>Formuláø musí být kompletnì vyplnìný<br>";
	}
	else{
		$dotaz="INSERT INTO Zamestnanec (IDZamestnance, jmeno, prijmeni, ulice, mesto, rodne_cislo, postaveni, login, heslo) VALUES
		('', '{$_POST['jmeno']}', '{$_POST['prijmeni']}', '{$_POST['ulice']}', '{$_POST['mesto']}', '{$_POST['rc']}', '{$_POST['pozice']}', '{$_POST['login']}', '{$_POST['heslo']}')";
		$odpoved=mysql_query($dotaz, $databaze);
		if(!$odpoved)
			echo "<br>Nepodaøilo se vlo¾it nového zamìstnance. Zkontrolujte vlo¾ené údaje<br>";
	}
 }
 
 if(isset($_POST["prohlidka_mistnosti"])){	//prohlidka mistnosti
	$_SESSION["mistnost"]=$_POST["id_mistnosti"];
	$_GET["menu"]="7";
 }
 
  if(isset($_POST["prohlidka_mistnosti_zakaznik"])){	//prohlidka mistnosti zakaznika
	$_SESSION["mistnost"]=$_POST["id_mistnosti"];
	$_GET["zakaznik"]="7";
 }
 
 if(isset($_POST["upravit_zamestnance_admin"])){	//sprava zamestnancu
	if($_POST["upravit_zamestnance"]=="upravit"){
		$_GET["admin"]="8";
		$_SESSION["id_zamestnance"]=$_POST["id_zamestnance"];
	}
	else if($_POST["upravit_zamestnance"]=="smazat"){
		$chudacek_dostane_padacek="DELETE FROM Zamestnanec WHERE IDZamestnance='".$_POST["id_zamestnance"]."'";
		$vyhozen=mysql_query($chudacek_dostane_padacek, $databaze);
		if(!$vyhozen){
			echo "Nelze smazat zamìstnance<br>";
		}
		else{
			$dotaz="UPDATE Misto SET IDZamestnance='0' WHERE IDZamestnance='".$_POST["id_zamestnance"]."'";
			$odpoved=mysql_query($dotaz, $databaze);
			if(!$odpoved){
				echo "Nastala chyba<br>";
			}
		}
	}
 }
 
 if(isset($_POST["upravit_zamestnance_volba_admin"])){
	if(empty($_POST["jmeno"]) or empty($_POST["prijmeni"]) or empty($_POST["jmeno"]) or empty($_POST["ulice"]) or empty($_POST["mesto"]) or empty($_POST["rc"]) or empty($_POST["login"]) or empty($_POST["heslo"])){
		echo "<br>Formuláø musí být kompletnì vyplnìný<br>";
	}
	else{
		$dotaz="UPDATE Zamestnanec SET jmeno='".$_POST["jmeno"]."', prijmeni='".$_POST["prijmeni"]."', ulice='".$_POST["ulice"]."',
		mesto='".$_POST["mesto"]."', rodne_cislo='".$_POST["rc"]."', postaveni='".$_POST["postaveni"]."', login='".$_POST["login"]."',
		heslo='".$_POST["heslo"]."' WHERE IDZamestnance='".$_POST["id_zamestnance"]."'";
		$odpoved=mysql_query($dotaz, $databaze);
		if(!$odpoved)
			echo "Nelze upravit zamìstnance<br>";
	}
 }
?>