<?
 function prohlidka_mistnosti($databaze, $cislo_mistnosti){
	$mista="SELECT * FROM Misto WHERE IDMistnosti=$cislo_mistnosti";
	$dostal_jsem=mysql_query($mista, $databaze);
	while($tady_to_mas=mysql_fetch_array($dostal_jsem, MYSQL_ASSOC)){
?>
	<table class="mista">
		<tr>
			<td>Misto cislo: <?echo $tady_to_mas["IDMista"]?></td>
			<td>Nachazi se v mistnosti: <?echo $tady_to_mas["IDMistnosti"]?></td>
			<td>Typ místa: <?echo $tady_to_mas["typ_mista"]?></td>
			<td>Typ osvìtlení: <?echo $tady_to_mas["typ_osvetleni"]?></td>
			<td>Alarm: <?echo $tady_to_mas["alarm"]?></td>
			<td>Velikost plochy: <?echo $tady_to_mas["velikost"]?></td>
			<td>Cena: <?echo $tady_to_mas["cena_za_pronajem"]?></td>
		</tr>
	</table>
<?
	}
 }	//function prohlidka_mistnosti
 ?>
 
<?
 function necinnost(){
	 if(isset($_SESSION["posledni_pohyb"])){
		if((time() - $_SESSION["posledni_pohyb"]) > 1800){	//po 30 minutach odpoj
			session_unset();
			session_destroy();
		}
 }
 }//function necinnost
 
 function zkontroluj_datum($datum1){	//zkontrolue spravny format data
	if(substr_count($datum1, '.') == 2){
		if(!preg_match("/[0-9]{1,2}.[0-9]{1,2}.[0-9]{4}$/", $datum1))
			return false;
		list($den, $mesic, $rok)=explode('.', $datum1);
		if(checkdate($mesic, $den, $rok))
			return true;
		else
			return false;
	}//if substr
	else
		return false;
 }
 
  function zkontroluj_datum_chronologicky($datum1, $datum2){//zkontroluje zadane datum
	list($den1, $mesic1, $rok1)=explode('.', $datum1);
	list($den2, $mesic2, $rok2)=explode('.', $datum2);
	if($rok1 < $rok2){
		return true;
	}
	else{
		if($rok1 == $rok2 and $mesic1 < $mesic2){
			return true;
		}
		else{
			if($rok1 == $rok2 and $mesic1 == $mesic2 and $den1 < $den2){
				return true;
			}
			else{
				return false;
			}
		}
	}
  }//function zkontroluj_datum_chronologicky
?>