<?
 function zakaznik($databaze, $stranka){
?>
<div class="layout_content_wrap">
	<div class="menu">
		<ul>
			<li <?if($stranka==0){?>class="selected"<?}?>><a href="?zakaznik=0">Home</a></li>
			<li <?if($stranka==1){?>class="selected"<?}?>><a href="?zakaznik=1">Na¹e místnosti</a></li>
			<li <?if($stranka==2){?>class="selected"<?}?>><a href="?zakaznik=2">Vytvoøit expozici</a></li>
			<li <?if($stranka==3){?>class="selected"<?}?>><a href="?zakaznik=3">Spravovat expozici</a></li>
			<li <?if($stranka==4){?>class="selected"<?}?>><a href="?zakaznik=4">Odhlasit</a></li>
		</ul>
	</div>
	
	<!-- obaleni switche, aby se obsah vypisoval vpravo od menu a vystredeny, ne nalepeny na okraj ci menu -->
	<div class="layout_content_outer">
	<div class="layout_content_middle">
	<div class="layout_content_inner">
<?
	switch($stranka){
	case 0:
?>
		<div>
			<h2>Jste pøihlá¹en jako ZÁKAZNÍK Famózní galerie</h2><br/><br/>
		</div>
<?
		break;
	case 1:
		$vsechny_mistnosti="SELECT * FROM Mistnost";
		$dostal_jsem=mysql_query($vsechny_mistnosti, $databaze);
?>
		<table class="nase_mistnosti">
			<tr>
				<td><h4>Mistnost cislo</h4></td> 
				<td><h4>Klimatizace</h4></td>
				<td><h4>Vlhkost vzduchu v mistnosti</h4></td>
				<td><h4>Bezbarierový pøístup do místnosti</h4></td>
				<td><h4>Bezpecnostni kamery</h4></td>
				<td></td>
			</tr>
<?
		while ($tady_to_mas=mysql_fetch_array($dostal_jsem, MYSQL_ASSOC)){
?>
			<tr>
				<td><?echo $tady_to_mas["IDMistnosti"]?></td>
				<td> <?echo $tady_to_mas["klimatizace"]?></td>
				<td><?echo $tady_to_mas["vlhkost_vzduchu"]?></td>
				<td><?echo $tady_to_mas["bezbarierovy_pristup"]?></td>
				<td><?echo $tady_to_mas["bezpecnostni_kamery"]?></td>
				<td>
					<form method="POST">
						<input type="hidden" name="id_mistnosti" value="<?echo $tady_to_mas["IDMistnosti"]?>">
						<input type="submit" name="prohlidka_mistnosti_zakaznik" value="Prohlédnout místnost">
					</form>
				</td>
			</tr>
<?
		}
?>
		</table>
<?
		break;
	case 2://tvorba nove expozice
?> 
		<div class="nova_expozice">
			<h3>Vytvoøte novou expozici</h3>
			<form method="POST">
				<label for="nazev_expozice">Název expozice</label>
				<input type="text" name="nazev_expozice" id="nazev_expozice">
				<br/>
				<label class="povin" for="vystaveno_od">Zaèátek expozice</label>	<!--data musi byt formatu DD.MM.YYYY-->
				<input type="text" name="vystaveno_od" id="vystaveno_od">
				<br/>
				<label class="povin" for="vystaveno_do">Konec expozice</label>
				<input type="text" name="vystaveno_do" id="vystaveno_do">
				<input type="hidden" name="stav_platby" value="nezaplaceno">
				<br/><p class="povin"> Datum ve formátu DD.MM.RRRR</p></br>
				<input type="submit" name="vytvorit_expizici" value="vytvoøit expozici"/>
			</form>
		</div>
<?
		break;
	case 3://spravovat expozici
		$expozice="SELECT * FROM Expozice WHERE IDZakaznika='".$_SESSION["id_zakaznika"]."'";
		$odpoved=mysql_query($expozice, $databaze);
		$test=mysql_fetch_array($odpoved, MYSQL_ASSOC);
		if($test){
		$expozice="SELECT * FROM Expozice WHERE IDZakaznika='".$_SESSION["id_zakaznika"]."'";
		$odpoved=mysql_query($expozice, $databaze);
?>
			<table class="zakaznik_spravovat_expozice ">
				<tr>
					<td></td>
					<td><h4>ID Va¹í expozice:</h4></td>
					<td><h4>Vystavena od:</h4></td>
					<td><h4>Výstava konèí:</h4></td>
				</tr>
<?
			while($expozice=mysql_fetch_array($odpoved, MYSQL_ASSOC)){
?>
				<tr>
					<td></td>
					<td><?echo $expozice["IDExpozice"]?></td>
					<td><?echo $expozice["vystavena_od"]?></td>
					<td><?echo $expozice["vystavena_do"]?></td>
					<td>
						<form method="POST">
							<input type="hidden" name="id_expozice" value="<?echo $expozice["IDExpozice"]?>">
							<input type="radio" name="upravit_expozici" value="pridat_dilo">Pøidat dílo
							<input type="radio" name="upravit_expozici" value="upravit">Upravit expozici
							<input type="radio" name="upravit_expozici" value="smazat">Smazat expozici
							<input type="submit" name="upravit_expozici_zakaznik" value="Potvrïit">
						</form>
					</td>
					<td></td>
				</tr>
<?
			}
?>
			</table>
<?
		}//if odpoved
		else{
?>
			<table class="vypis_expozice">
				<tr>
					<td>Zatím jste nevytvoøil ¾ádnou expozici</td>
					<a href="?zakaznik=2">Vytvoøit expozici</a>
				</tr>
			</table>
<?
		}
?> 
<?
		break;
	case 4://odhlasit
		unset($_GET["zakaznik"]);
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
		$dotaz="SELECT * FROM Expozice WHERE IDExpozice='".$_POST["id_expozice"]."'";
		$odpoved=mysql_query($dotaz, $databaze);
		$upravovana_expozice=mysql_fetch_array($odpoved, MYSQL_ASSOC);
?> 
		<form method="POST">
			<label for="nazev_expozice">Název expozice</label>
			<input type="text" name="upravit_nazev_expozice" value="<?echo $upravovana_expozice["Nazev_expozice"]?>">
			<br/>
			<label class="povin" for="vystaveno_od">Zaèátek expozice</label>	<!--data musi byt formatu DD.MM.YYYY-->
			<input type="text" name="upravit_vystaveno_od" value="<?echo $upravovana_expozice["vystavena_od"]?>">
			<br/>
			<label class="povin" for="vystaveno_do">Konec expozice</label>
			<input type="text" name="upravit_vystaveno_do" value="<?echo $upravovana_expozice["vystavena_do"]?>">
			<br/><p class="povin"> Datum ve formátu DD.MM.RRRR</p>
			<br/>
			<input type="submit" name="volba_upravit_expozici" value="upravit expozici"/>
		</form>
<?
		$dotaz2="SELECT nazev, IDMista, IDMistnosti, typ_dila FROM Dilo NATURAL JOIN Misto WHERE IDExpozice='".$upravovana_expozice["IDExpozice"]."'";
		$odpoved2=mysql_query($dotaz2, $databaze);
		?><p></br><h3>Expozice obsahuje tato díla:</h3></p><?
		while($vypis_dila=mysql_fetch_array($odpoved2, MYSQL_ASSOC)){
?>
		<table>
			<tr>
				<td>Dílo s názvem <?echo $vypis_dila["nazev"]?></td>
				<td>se nachází na místì <?echo $vypis_dila["IDMista"]?></td>
				<td>, které je v místnosti: <?echo $vypis_dila["IDMistnosti"]?></td>
				<td>. Dílo je typu <?echo $vypis_dila["typ_dila"]?></td>
				<td>
					<form method="POST">
						<input type="hidden" name="smaz_dilo" value="<?echo $vypis_dila["nazev"]?>"/>
						<input type="submit" name="smaz_dilo_submit" value="Smazat dílo"/>
					</form>
				</td>
			</tr>
		</table>
<?
		}
?>
<?
		break;
	case 6://pridat dilo
		$vyber="SELECT * FROM Misto";
		$vyber2=mysql_query($vyber, $databaze);
?>
		<p><h4>Chystáte se pøidat dílo do expozice: </h4><?echo $_SESSION["id_expozice"]?></p>
		<form method="POST">
			<input type="hidden" name="id_expozice" value="<?echo $_SESSION["id_expozice"]?>"/>
			<label for="nazev_dila">Název díla</label>
			<input type="text" name="nazev_dila"/>
			<br>
			<label for="autor">Autor díla</label>
			<input type="text" name="autor"/>
			<br>
			<label for="typ_dila">Typ díla</label>
			<input type="text" name="typ_dila"/>
			<br>
			<label for="cena_dila">Cena díla je stanovena na</label>
			<input type="text" name="cena_dila"/>
			<br>
			<label for="pozie">Dílo umístit na místo èíslo</label>
			<select name="pozice">
			<?while($vyber3=mysql_fetch_array($vyber2, MYSQL_ASSOC)){?>
				<option value="<?echo $vyber3["IDMista"]?>"><?echo $vyber3["IDMista"]?></option>
			<?}?>
			</select>
			<br>
			<input type="submit" name="vytvorit_dilo" value="Vlo¾it dílo do expoze"/>
		</form>
<?
		break;
	case 7://obsah mistnosti
		$mista="SELECT * FROM Misto WHERE IDMistnosti='".$_SESSION["mistnost"]."'";
		$odpoved=mysql_query($mista, $databaze);
?>
		<table class="mistnosti">
			<tr>
				<th>Místo èíslo</th>
				<th>Nachází se v místnosti</th>
				<th>Typ místa</th>
				<th>Typ osvìtlení</th>
				<th>Alarm</th>
				<th>Velikost Plochy</th>
				<th>Cena</th>
			</tr>
			<?while($mista=mysql_fetch_array($odpoved, MYSQL_ASSOC)){?>
			<tr>
				<td><?echo $mista["IDMista"]?></td>
				<td><?echo $mista["IDMistnosti"]?></td>
				<td><?echo $mista["typ_mista"]?></td>
				<td><?echo $mista["typ_osvetleni"]?></td>
				<td><?echo $mista["alarm"]?></td>
				<td><?echo $mista["velikost"]?></td>
				<td><?echo $mista["cena_za_pronajem"]?></td>
			</tr>
			<?}?>
		</table>
<?
		break;
	} //konec switch($prepinac)
?>
	</div>
	</div>
	</div>
</div>
<?
}//konec function zakaznik
?>