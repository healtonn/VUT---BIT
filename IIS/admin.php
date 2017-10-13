<?
 function admin($databaze, $stranka){
?>
<div class="layout_content_wrap">
	<div class="menu">
		<ul>
			<li <?if($stranka==0){?>class="selected"<?}?>><a href="?admin=0">Home</a></li>
			<li <?if($stranka==1){?>class="selected"<?}?>><a href="?admin=1">Spravovat místnosti</a></li>
			<li <?if($stranka==2){?>class="selected"<?}?>><a href="?admin=2">Vytvoøit expozice</a></li>
			<li <?if($stranka==3){?>class="selected"<?}?>><a href="?admin=3">Spravovat expozice</a></li>
			<li <?if($stranka==3){?>class="selected"<?}?>><a href="?admin=6">Vytvoøit zamìstnance</a></li>
			<li <?if($stranka==3){?>class="selected"<?}?>><a href="?admin=7">Spravovat zamìstnance</a></li>
			<li <?if($stranka==4){?>class="selected"<?}?>><a href="?admin=4">Odhlásit</a></li>
		</ul>
	</div>
	
	<!-- obaleni switche, aby se obsah vypisoval vpravo od menu a vystredeny, ne nalepeny na okraj ci menu -->
	<div class="layout_content_outer">
	<div class="layout_content_middle">
	<div class="layout_content_inner">
<?
	switch($stranka){
	case 0://home
?>
		<div>
			<h1>Vítejte zpìt, pane admine!</h1><br/><br/>
			<h3>Mùž¾ete zaèít kouzlit s databází.</h3>
		</div>
<?
		break;
	case 1://Spravovat mistnost
		$dotaz="SELECT * FROM Mistnost";
		$odpoved=mysql_query($dotaz, $databaze);
?>
		<table style="width:90%">
			<tr>
				<th>ID Místnosti</th>
				<th>Klimatizace</th>
				<th>Vlhkost vzduchu v místnosti (%)</th>
				<th>Bezbarierový pøístup</th>
				<th>Bezpeènostní kamery</th>
			</tr>
			<?while($vysledek=mysql_fetch_array($odpoved, MYSQL_ASSOC)){?>
			<tr>
				<form method="POST">
					<td><input type="text" name="id_mistnosti_sprava" value="<?echo $vysledek["IDMistnosti"]?>" readonly /></td>
					<td><input type="text" name="klimatizace_sprava" value="<?echo $vysledek["klimatizace"]?>"/></td>
					<td><input type="text" name="vlhkost_vzduchu_sprava" value="<?echo $vysledek["vlhkost_vzduchu"]?>"/></td>
					<td><input type="text" name="bezbarierovy_pristup_sprava" value="<?echo $vysledek["bezbarierovy_pristup"]?>"/></td>
					<td><input type="text" name="bezpecnostni_kamery_sprava" value="<?echo $vysledek["bezpecnostni_kamery"]?>"/></td>
					<td><input type="submit" name="mistnost_zmenena" value="Ulo¾it"/></td>
				</form>
			</tr>
			<?}?>
		</table>
<?
		break;
	case 2://vytvorit expozice
?>
		<div class="nova_expozice">
			<p><h3>Vytváøíte novou expozici. Expozici nutno pøiøadit k ji¾ existujícímu zákazníkovi!</h3></p>
			<form method="POST">
				<label for="id_zakaznika_sprava">ID Zákazníka</label>
				<input type="text" name="id_zakaznika_sprava">
				<br/>
				<label for="nazev_expozice">Název expozice</label>
				<input type="text" name="nazev_expozice">
				<br/>
				<label class="povin" for="vystaveno_od">Zaèátek expozice</label>	<!--data musi byt formatu DD.MM.YYYY-->
				<input type="text" name="vystaveno_od">
				<br/>
				<label class="povin" for="vystaveno_do">Konec expozice</label>
				<input type="text" name="vystaveno_do">
				<br/><p class="povin"> Datum ve formátu DD.MM.RRRR</p>
				<br/>
				<input type="hidden" name="stav_platby" value="nezaplaceno">
				<input type="submit" name="vytvorit_expizici_spravce" value="vytvoøit expozici"/>
			</form>
		</div>
<?
		break;
	case 3://spravovat expozice
		$dotaz="SELECT * FROM Expozice NATURAL JOIN Zakaznik";
		$odpoved=mysql_query($dotaz, $databaze);
		if(!$odpoved){
?>
		<div class="haha">
			<p>Tato galerie nemá ¾ádné zakázky</p><br><p>Chtìlo by to reklamu...</p>
		</div>
<?		}
		else{
?>
			<table style="width:90%">
			<tr>
				<th>ID expozice</th>
				<th>Název expozice</th>
				<th>ID Zakaznika</th>
				<th>Vystavena od</th>
				<th>Výstava konèí</th>
				<th>Stav objednávky</th>
				<th>Mo¾nosti</th>
			</tr>
				<?while($expozice=mysql_fetch_array($odpoved, MYSQL_ASSOC)){?>
					<tr>
						<td><?echo $expozice["IDExpozice"]?></td>
						<td><?echo $expozice["Nazev_expozice"]?></td>
						<td><?echo $expozice["IDZakaznika"]?></td>
						<td><?echo $expozice["vystavena_od"]?></td>
						<td><?echo $expozice["vystavena_do"]?></td>
						<td><?echo $expozice["stav_platby"]?></td>
						<td>
							<form method="POST">
								<input type="hidden" name="id_expozice" value="<?echo $expozice["IDExpozice"]?>">
								<input type="radio" name="upravit_expozici" value="zaplaceno">Faktura zaplacena
								<input type="radio" name="upravit_expozici" value="upravit">Upravit expozici
								<input type="radio" name="upravit_expozici" value="smazat">Smazat expozici
								<input type="submit" name="upravit_expozici_admin" value="Potvrïit">
							</form>
						</td>
					</tr>
				<?}?>
				</table>
			
	  <?}?>

<?
		break;
	case 4://odhlasit
		unset($_GET["zamestnanec"]);
		unset($_SESSION["prihlasen_je"]);
		session_unset();
		session_destroy();
?>
		<script>
			window.location.href="index.php";	//redirect na hlavni stranku
        </script>
<?
		break;
	case 5://upravit expozici
		$dotaz="SELECT * FROM Expozice WHERE IDExpozice='".$_SESSION["id_expozice"]."'";
		$odpoved=mysql_query($dotaz, $databaze);
		$upravovana_expozice=mysql_fetch_array($odpoved, MYSQL_ASSOC);
?>
		<form method="POST">
			<label for="nazev_expozice">Název expozice</label>
			<input type="text" name="upravit_nazev_expozice" value="<?echo $upravovana_expozice["Nazev_expozice"]?>" readonly>
			<br>
			<label for="id_zakaznika">Zakaznik èíslo</label>
			<input type="text" name="id_zakaznika" value="<?echo $upravovana_expozice["IDZakaznika"]?>" readonly>
			<br>
			<label class="povin" for="vystaveno_od">Zaèátek expozice</label>	<!--data musi byt formatu DD.MM.YYYY-->
			<input type="text" name="upravit_vystaveno_od" value="<?echo $upravovana_expozice["vystavena_od"]?>">
			<br>
			<label class="povin" for="vystaveno_do">Konec expozice</label>
			<input type="text" name="upravit_vystaveno_do" value="<?echo $upravovana_expozice["vystavena_do"]?>">
			<br/><p class="povin"> Datum ve formátu DD.MM.RRRR</p>
			<br>
			<input type="submit" name="volba_upravit_expozici_sprava" value="upravit expozici"/>
		</form>
<?
		$dotaz2="SELECT nazev, IDMista, IDMistnosti, typ_dila FROM Dilo NATURAL JOIN Misto WHERE IDExpozice='".$upravovana_expozice["IDExpozice"]."'";
		$odpoved2=mysql_query($dotaz2, $databaze);
?>		<p></br><h3>Expozice obsahuje tato díla:</h3></p>
		<table style="width:60%">
			<tr>
				<th>Nazev díla</th>
				<th>Le¾í na místì</th>
				<th>Èíslo místnosti</th>
				<th>Typ díla</th>
			</tr>
			<?while($vypis_dila=mysql_fetch_array($odpoved2, MYSQL_ASSOC)){?>
			<tr>
				<td><?echo $vypis_dila["nazev"]?></td>
				<td><?echo $vypis_dila["IDMista"]?></td>
				<td><?echo $vypis_dila["IDMistnosti"]?></td>
				<td><?echo $vypis_dila["typ_dila"]?></td>
				<td>
					<form method="POST">
						<input type="hidden" name="smaz_dilo" value="<?echo $vypis_dila["nazev"]?>"/>
						<input type="submit" name="smaz_dilo_sprava" value="Smazat dílo"/>
					</form>
				</td>
			</tr>
			<?}?>
		</table>
<?
		break;
	case 6://tvorba zamestnance
?>
		<p><h3>Chystáte se pøidat zamìstnance</h3></p>
		<form method="POST">
			<label for="pozice">Postavení</label>
			<select name="pozice">
				<option value="zamìstnanec">Zamìstnanec</option>
				<option value="vedoucí">Vedoucí</option>
			</select>
			<br>
			<label for="jmeno">Jméno</label>
			<input type="text" name="jmeno"/>
			<br>
			<label for="prijmeni">Pøíjmení</label>
			<input type="text" name="prijmeni"/>
			<br>
			<label for="ulice">Ulice</label>
			<input type="text" name="ulice"/>
			<br>
			<label for="mesto">Mìsto</label>
			<input type="text" name="mesto"/>
			<br>
			<label for="rc">Rodné èíslo</label>
			<input type="text" name="rc"/>
			<br>
			<label for="login">Login</label>
			<input type="text" name="login"/>
			<br>
			<label for="heslo">Heslo</label>
			<input type="text" name="heslo"/>
			<br>
			<input type="submit" name="vytvorit_zamestnance" value="Vytvoøit zamìstnance"/>
		</form>
<?
		break;
	case 7://sprava zamestnancu
		$dotaz="SELECT * FROM Zamestnanec";
		$odpoved=mysql_query($dotaz, $databaze);
?>
		<table style="width:90%">
			<tr>
				<th>ID Zamìstnance</th>
				<th>Jméno</th>
				<th>Pøíjmení</th>
				<th>Ulice</th>
				<th>Mìsto</th>
				<th>Rodné èíslo</th>
				<th>Pozice</th>
				<th>Login</th>
				<th>Heslo</th>
				<th>Mo¾nosti</th>
			</tr>
			<?while($seznam=mysql_fetch_array($odpoved, MYSQL_ASSOC)){?>
			<tr>
				<td><?echo $seznam["IDZamestnance"]?></td>
				<td><?echo $seznam["jmeno"]?></td>
				<td><?echo $seznam["prijmeni"]?></td>
				<td><?echo $seznam["ulice"]?></td>
				<td><?echo $seznam["mesto"]?></td>
				<td><?echo $seznam["rodne_cislo"]?></td>
				<td><?echo $seznam["postaveni"]?></td>
				<td><?echo $seznam["login"]?></td>
				<td><?echo $seznam["heslo"]?></td>
				<td>
					<form method="POST">
						<input type="hidden" name="id_zamestnance" value="<?echo $seznam["IDZamestnance"]?>">
						<input type="radio" name="upravit_zamestnance" value="upravit">Upravit zamìstnance
						<input type="radio" name="upravit_zamestnance" value="smazat">Smazat zamìstnance
						<input type="submit" name="upravit_zamestnance_admin" value="Potvrïit">
					</form>
				</td>
			</tr>
			<?}?>
		</table>
<?
		break;
	case 8://uprava zamestnance
		$dotaz="SELECT * FROM Zamestnanec WHERE IDZamestnance='".$_POST["id_zamestnance"]."'";
		$odpoved=mysql_query($dotaz, $databaze);
		$vysledek=mysql_fetch_array($odpoved, MYSQL_ASSOC);
?>
		<table style="width:90%">
			<tr>
				<th>ID Zamestnance</th>
				<th>Jméno</th>
				<th>Pøíjmení</th>
				<th>Ulice</th>
				<th>Mìsto</th>
			</tr>
			<tr>
				<form method="POST">
					<td><input type="text" name="id_zamestnance" value="<?echo $vysledek["IDZamestnance"]?>" readonly /></td>
					<td><input type="text" name="jmeno" value="<?echo $vysledek["jmeno"]?>"/></td>
					<td><input type="text" name="prijmeni" value="<?echo $vysledek["prijmeni"]?>"/></td>
					<td><input type="text" name="ulice" value="<?echo $vysledek["ulice"]?>"/></td>
					<td><input type="text" name="mesto" value="<?echo $vysledek["mesto"]?>"/></td>
				</form>
			</tr>
			<tr>
				<th>Rodné èíslo</th>
				<th>Postavení</th>
				<th>Login</th>
				<th>Heslo</th>
			</tr>
			<tr>
				<form method="POST">
					<td><input type="text" name="rc" value="<?echo $vysledek["rodne_cislo"]?>"/></td>
					<td><input type="text" name="postaveni" value="<?echo $vysledek["postaveni"]?>"/></td>
					<td><input type="text" name="login" value="<?echo $vysledek["login"]?>"/></td>
					<td><input type="text" name="heslo" value="<?echo $vysledek["heslo"]?>"/></td>
					<td><input type="submit" name="upravit_zamestnance_volba_admin" value="Ulo¾it"/></td>
				</form>
			</tr>
		</table>
<?
		break;
?>
	</div>
	</div>
	</div>
</div>
<?
	}//switch
?>
<?
 }
?>