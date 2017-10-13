<?
 function zamestnanec($databaze, $stranka){
?>
<div class="layout_content_wrap">
	<div class="menu">
		<ul>
			<li <?if($stranka==0){?>class="selected"<?}?>><a href="?zamestnanec=0">Home</a></li>
			<li <?if($stranka==1){?>class="selected"<?}?>><a href="?zamestnanec=1">Spravovat m�stnosti</a></li>
			<li <?if($stranka==2){?>class="selected"<?}?>><a href="?zamestnanec=2">Vytvo�it expozice</a></li>
			<li <?if($stranka==3){?>class="selected"<?}?>><a href="?zamestnanec=3">Spravovat expozice</a></li>
			<li <?if($stranka==4){?>class="selected"<?}?>><a href="?zamestnanec=4">Odhlasit</a></li>
		</ul>
	</div>
	
	<div class="layout_content_outer">
	<div class="layout_content_middle">
	<div class="layout_content_inner">
<?
	switch($stranka){
	case 0://home
?>
		<div>
			<h2>Jste p�ihl�en jako ZAM�STNANEC Fam�zn� galerie</h2><br/><br/>
		</div>
<?
		break;
	case 1://Spravovat mistnost
		$dotaz="SELECT * FROM Mistnost";
		$odpoved=mysql_query($dotaz, $databaze);
?>
		<table class="zamestnanec_vypis_mistnosti">
			<tr>
				<th>ID M�stnosti</th>
				<th>Klimatizace</th>
				<th>Vlhkost vzduchu v m�stnosti (%)</th>
				<th>Bezbarierov� p��stup</th>
				<th>Bezpe�nostn� kamery</th>
			</tr>
			<?while($vysledek=mysql_fetch_array($odpoved, MYSQL_ASSOC)){?>
			<tr>
				<form method="POST">
					<td><input type="text" name="id_mistnosti_sprava" value="<?echo $vysledek["IDMistnosti"]?>" readonly /></td>
					<td><input type="text" name="klimatizace_sprava" value="<?echo $vysledek["klimatizace"]?>"/></td>
					<td><input type="text" name="vlhkost_vzduchu_sprava" value="<?echo $vysledek["vlhkost_vzduchu"]?>"/></td>
					<td><input type="text" name="bezbarierovy_pristup_sprava" value="<?echo $vysledek["bezbarierovy_pristup"]?>"/></td>
					<td><input type="text" name="bezpecnostni_kamery_sprava" value="<?echo $vysledek["bezpecnostni_kamery"]?>"/></td>
					<td><input type="submit" name="mistnost_zmenena" value="Ulo�it"/></td>
				</form>
			</tr>
			<?}?>
		</table>
<?
		break;
	case 2://vytvorit expozice
?>
		<div class="nova_expozice">
			<p>Vytv���te novou expozici. Expozici nutno p�i�adit k ji� existuj�c�mu z�kazn�kovi!</p></br>
			<form method="POST">
				<label for="id_zakaznika_sprava">ID Z�kazn�ka</label>
				<input type="text" name="id_zakaznika_sprava">
				<br>
				<label for="nazev_expozice">N�zev expozice</label>
				<input type="text" name="nazev_expozice">
				<br>
				<label class="povin" for="vystaveno_od">Za��tek expozice</label>	<!--data musi byt formatu DD.MM.YYYY-->
				<input type="text" name="vystaveno_od">
				<br>
				<label class="povin" for="vystaveno_do">Konec expozice</label>
				<input type="text" name="vystaveno_do">
				<br/><p class="povin"> Datum ve form�tu DD.MM.RRRR</p>
				<br>
				<input type="hidden" name="stav_platby" value="nezaplaceno">
				<input type="submit" name="vytvorit_expizici_spravce" value="vytvo�it expozici"/>
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
			<p>Tato galerie nem� ��dn� zak�zky</p><br><p>Cht�lo by to reklamu...</p>
		</div>
<?		}
		else{
?>
			<table class="zamestnanec_spravovat_expozice">
			<tr>
				<th>ID expozice</th>
				<th>N�zev expozice</th>
				<th>ID Zakaznika</th>
				<th>Vystavena od</th>
				<th>V�stava kon��</th>
				<th>Stav objedn�vky</th>
				<th>Mo�nosti</th>
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
								<input type="submit" name="upravit_expozici_zamestnanec" value="Potvr�it">
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
			<label for="nazev_expozice">N�zev expozice</label>
			<input type="text" name="upravit_nazev_expozice" value="<?echo $upravovana_expozice["Nazev_expozice"]?>" readonly>
			<br>
			<label for="id_zakaznika">Zakaznik ��slo</label>
			<input type="text" name="id_zakaznika" value="<?echo $upravovana_expozice["IDZakaznika"]?>" readonly>
			<br>
			<label class="povin" for="vystaveno_od">Za��tek expozice</label>	<!--data musi byt formatu DD.MM.YYYY-->
			<input type="text" name="upravit_vystaveno_od" value="<?echo $upravovana_expozice["vystavena_od"]?>">
			<br>
			<label class="povin" for="vystaveno_do">Konec expozice</label>
			<input type="text" name="upravit_vystaveno_do" value="<?echo $upravovana_expozice["vystavena_do"]?>">
			<br/><p class="povin"> Datum ve form�tu DD.MM.RRRR</p>
			<br>
			<input type="submit" name="volba_upravit_expozici_sprava" value="upravit expozici"/>
		</form>
<?
		$dotaz2="SELECT nazev, IDMista, IDMistnosti, typ_dila FROM Dilo NATURAL JOIN Misto WHERE IDExpozice='".$upravovana_expozice["IDExpozice"]."'";
		$odpoved2=mysql_query($dotaz2, $databaze);
?>		<p>expozice obsahuje tyto d�la</p>
		<table class="sprava_expozice">
			<tr>
				<th>Nazev d�la</th>
				<th>Le�� na m�st�</th>
				<th>��slo m�stnosti</th>
				<th>Typ d�la</th>
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
						<input type="submit" name="smaz_dilo_sprava" value="Smazat d�lo"/>
					</form>
				</td>
			</tr>
			<?}?>
		</table>
	</div>
	</div>
	</div>
</div>
<?
		break;
?>
<?
	}//switch
?>
<?
 }
?>