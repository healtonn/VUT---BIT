<?
 function menu($databaze, $prepinac){
?>
<div class="layout_content_wrap">
	<div class="menu">
		<ul>
			<li <?if($prepinac==0){?>class="selected"<?}?>><a href="?menu=0">Home</a></li>
			<li <?if($prepinac==1){?>class="selected"<?}?>><a href="?menu=1">Na¹e místnosti</a></li>
			<li <?if($prepinac==2){?>class="selected"<?}?>><a href="?menu=2">Pøihlásit</a></li>
			<li <?if($prepinac==3){?>class="selected"<?}?>><a href="?menu=3">Registrovat</a></li>
		</ul>
	</div>
	
	<!-- obaleni switche, aby se obsah vypisoval vpravo od menu a vystredeny, ne nalepeny na okraj ci menu -->
	<div class="layout_content_outer">
	<div class="layout_content_middle">
	<div class="layout_content_inner">

	<?
	switch($prepinac){
	case 0://home
	?>
		<div>
			<h2>Vítejte na stránkách Famózní galerie</h2><br/><br/>
			<h4>Galerie zalo¾ené roku 2077, urèené pro vystavování nejrùznìj¹ích expozic jak klasického, tak moderního umìní napøíè v¹emi obory.</h4>
		</div>
	<?
		break;
	case 1://nase mistnosti
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
						<input type="submit" name="prohlidka_mistnosti" value="Prohlédnout místnost">
					</form>
				</td>
			</tr>
	<?
		}
	?>
		</table>
		
	<?
		break;
	case 2:
	?>
	<!------------------Prihlsovaci formular------------------>
	<!-- <FORM>je identifikace pro formular. To, kam se zadana hodnota ulozi je definovano promenou "name"
		pro pristup k dane hodnote pak staci pouzit $_POST['name'] -->
		<DIV class="prihlaseni">
			<FORM method="post" style="margin: 5px 5px 5px 5px">
				<LABEL for="typ_prihlaseni">Skupina:</LABEL>
				<SELECT name="typ_prihlaseni">
					<OPTION value="nic">Vybrat...</OPTION>
					<OPTION value="zakaznik">Zakaznik</OPTION>
					<OPTION value="zamestnanec">Zamestnanec</OPTION>
					<OPTION value="admin">Administrátor</OPTION>
				</SELECT>
				<BR>
				<LABEL for="login">Login:</LABEL>
				<INPUT type="text" name="login" id="login">
				<BR>
				<LABEL for="pwd">Heslo:</LABEL>
				<INPUT type="password" name="pwd" id="pwd">
				<BR>
				<INPUT type="submit" name="prihlasit" value="Prihlasit" style="margin: 10px">
			</FORM>
		</DIV>
	
	<?
		break;
	case 3://registrace
	?> 
		<div>
			<menu class="registrovat_jako">
				<li><a href="?menu=5"><h3>REGISTRACE JAKO UMÌLEC</h3></a></li>
				<br></br>
				<li><a href="?menu=6"><h3>REGISTRACE JAKO FIRMA</h3></a></li>
			</menu>
		</div>
	<?
		break;
	case 5://registrace fo
	?> 
		<DIV class="registrace">
			<FORM method="post">
				<LABEL class="povin" for="jmeno">Jmeno:</LABEL> <!--Tohle musi byt-->
				<INPUT type="text" name="jmeno" id="jmeno">
				<BR>
				<LABEL class="povin" for="prijmeni">Pøíjmení:</LABEL> <!--Tohle musi byt-->
				<INPUT type="text" name="prijmeni"id="prijmeni">
				<BR>
				<LABEL class="povin" for="email">Email:</LABEL> <!--Tohle musi byt-->
				<INPUT type="text" name="email" id="email">
				<BR>
				<LABEL class="povin" for="login">Login:</LABEL> <!--Tohle musi byt-->
				<INPUT type="text" name="login" id="login">
				<BR>
				<LABEL class="povin" for="heslo">Heslo:</LABEL> <!--Tohle musi byt-->
				<INPUT type="password" name="heslo" id="heslo">
				<BR>
				<LABEL for="mesto">Mesto:</LABEL>
				<INPUT type="text" name="mesto" id="mesto">
				<BR>
				<LABEL for="ulice">Ulice:</LABEL>
				<INPUT type="text" name="ulice" id="ulice">
				<BR>
				<LABEL for="telefon">Telefon:</LABEL>
				<INPUT type="text" name="telefon" id="telefon">
				<BR/>
				<p class="povin"> Èervená pole jsou povinná.</p>
				<BR/>
				<INPUT type="submit" name="registraceFO" value="Odeslat">
			</FORM>
		</DIV>
	<?
		break;
	case 6://registrace po
	?> 
		<DIV class="registrace">
				<p><h4>Do polí uveïte informace zástupce, který bude za firmu jednat</h4></p>
				<FORM method="post">
					<LABEL class="povin" for="jmeno">Jmeno firmy:</LABEL> <!--Tohle musi byt-->
					<INPUT type="text" name="jmeno_firmy" id="jmeno">
					<BR>
					<LABEL class="povin" for="jmeno">ICO:</LABEL> <!--Tohle musi byt-->
					<INPUT type="text" name="ico" id="jmeno">
					<BR>
					<LABEL class="povin" for="jmeno">Jmeno:</LABEL> <!--Tohle musi byt-->
					<INPUT type="text" name="jmeno" id="jmeno">
					<BR>
					<LABEL class="povin" for="prijmeni">Pøíjmení:</LABEL> <!--Tohle musi byt-->
					<INPUT type="text" name="prijmeni"id="prijmeni">
					<BR>
					<LABEL class="povin" for="email">Email:</LABEL> <!--Tohle musi byt-->
					<INPUT type="text" name="email" id="email">
					<BR>
					<LABEL class="povin" for="login">Login:</LABEL> <!--Tohle musi byt-->
					<INPUT type="text" name="login" id="login">
					<BR>
					<LABEL class="povin" for="heslo">Heslo:</LABEL> <!--Tohle musi byt-->
					<INPUT type="password" name="heslo" id="heslo">
					<BR>
					<LABEL for="mesto">Mesto:</LABEL>
					<INPUT type="text" name="mesto" id="mesto">
					<BR>
					<LABEL for="ulice">Ulice:</LABEL>
					<INPUT type="text" name="ulice" id="ulice">
					<BR>
					<LABEL for="telefon">Telefon:</LABEL>
					<INPUT type="text" name="telefon" id="telefon">
					<BR/>
					<p class="povin"> Èervená pole jsou povinná.</p>
					<BR/>
					<INPUT type="submit" name="registracePO" value="Odeslat">
				</FORM>
			</DIV>
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
 } //konec funkce menu
?>