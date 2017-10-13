<?
  function spravce($databaze, $stranka){
?>

<div class="contentWrap"> <!--??-->
	<nav class="navbar navbar-static-top"> 
		<div class="container">
			<div class="navbar-header">
				<a class="navbar-brand" href="http://www.stud.fit.vutbr.cz/~xjochl00/index.php">
					<img id="car" src="car.png" alt="Online Kniha Jízd"/>Online Kniha Jízd
				</a>
			</div>

			<ul class="nav navbar-nav">
			  <li <?if($stranka==0){?>class="selected"<?}?>><a href="?menuSelector=0">Seznam jízd</a></li>
			  <li <?if($stranka==1){?>class="selected"<?}?>><a href="?menuSelector=1">Vytvořit jízdu</a></li>
			  <li <?if($stranka==2){?>class="selected"<?}?>><a href="?menuSelector=2">Seznam řidičů</a></li>
			  <li <?if($stranka==3){?>class="selected"<?}?>><a href="?menuSelector=3">Přidat řidiče</a></li>
			  <li <?if($stranka==4){?>class="selected"<?}?>><a href="?menuSelector=4">Odhlásit</a></li>
			</ul>

		</div>
	</nav>
    
    <div class="obsahStranky">
<?
    switch($stranka){
    case 0: //seznam jizd
    $dotaz = "SELECT * FROM Cesta NATURAL JOIN Ridic";
    $odpoved=mysql_query($dotaz, $databaze);
?>
    <div class="panel panel-default seznamJizd">
		<div class="panel-heading">
			<h4 class="prihlas">Seznam jízd</h4>
		</div>
		<div class="panel-body tabulka">
			<table class="table table-hover seznamJizdTable">
			  <tr>
				<th>ID cesty</th>
				<th>Název cesty</th>
				<th>Řidič</th>
				<th>Náklad</th>
				<th>Start cesty</th>
				<th>Cíl cesty</th>
				<th>Čas odjezdu</th>
				<th>Čas příjezdu</th>
				<th></th>
				<th></th>
			  </tr>
			<?while($vysledek=mysql_fetch_array($odpoved, MYSQL_ASSOC)){?>
				<tr>
				  <td><?echo $vysledek["idCesty"]?></td>
				  <td><?echo $vysledek["nazevCesty"]?></td>
				  <td><?echo $vysledek["jmeno"]; echo " "; echo $vysledek["prijmeni"]?></td>
				  <td><?echo $vysledek["naklad"]?></td>
				  <td><?echo $vysledek["startCesty"]?></td>
				  <td><?echo $vysledek["cilCesty"]?></td>
				  <td><?echo $vysledek["casOdjezdu"]?></td>
				  <td><?echo $vysledek["casPrijezdu"]?></td>
				  <form method="POST">
					<td><input type="submit" name="upravaZaznamuJizdy" value="Upravit" class="btn btn-default"></td>
					<td><input type="submit" name="smazatZaznamJizdy" value="Smazat" class="btn btn-default"></td>
				  </form>
				</tr>
			<?}  //konec while cyklu ?>
			</table>
		</div>
    </div>
     <?
       break;
     case 1:      //tworba nove jizdy
     ?>
    <div class="panel panel-default novaJizda">
		<div class="panel-heading">
			<h4 class="prihlas">Nová jízda</h4>
		</div>
		<div class="panel-body tabulka">
		<div class="nove">
			<p>Vytváříte nový záznam o převozu nákladu. Všecha pole musí být vyplněna!</p>
		<div class="form-inside">
		  <form method="POST" class="form-horizontal">
		   <div class="form-group">
			<label for="nazevCesty" class="control-label">Název cesty</label>
			<input type="text" name="nazevCesty" class="form-control">
		   </div>
		   <div class="form-group">
			<label for="naklad" class="control-label">Převážený náklad</label>
			<input type ="text" name="naklad" class="form-control">
		   </div>
		   <div class="form-group">
			<label for="ridic" class="control-label">Jméno Řidiče</label>
			<input type ="text" name="ridic" class="form-control">
		   </div>
		   <div class="form-group">
			<label for="startCesty" class="control-label">Místo naložení</label>
			<input type ="text" name="startCesty" class="form-control">
		   </div>
		   <div class="form-group">
			<label for="cilCesty" class="control-label">Místo doručení</label>
			<input type ="text" name="cilCesty" class="form-control">
		   </div>
			<input type="submit" name="potvrditNovouJizdu" value="Potvrdit" class="btn btn-default">
		  </form>
		  </div>
		</div
		</div>
    </div>
    <?
      break;
    case 2:    //sezam ridicu
    $dotaz = "SELECT * FROM Ridic";
    $odpoved=mysql_query($dotaz, $databaze);
    ?>
	
    <div class="panel panel-default seznamJizd">
		<div class="panel-heading">
			<h4 class="prihlas">Seznam řidičů</h4>
		</div>
		<div class="panel-body tabulka">
			<table class="table table-hover kartaRidiceTable">
				<?while($ridic=mysql_fetch_array($odpoved, MYSQL_ASSOC)){?>
				  <tr>
					<div class="fotoRidice"><td rowspan="3">FOTO</td></div>
					<div class="jmenoRidice">
					  <th>Jmeno:</td>
					  <td><?echo $ridic["jmeno"]?></td>
					</div>
					</div class="prijmeniRidice">
					  <th>Prijmeni:</th>
					  <td><?echo $ridic["prijmeni"]?></td>
					</div>
				  </tr>
				  <tr>
					<div class="rodneCisloRidice">
					  <th>RČ:</th>
					  <td><?echo $ridic["rodneCislo"]?></td>
					</div>
					<div class="narodnostRidice">
					  <th>Národnost:</th>
					  <td><?echo $ridic["narodnost"]?></td>
					</div>
				  </tr>
				  <tr>
					<div class="mestoRidice">
					  <th>Město:</th>
					  <td><?echo $ridic["mesto"]?></td>
					</div>
					<div class="uliceRidice">
					  <th>Ulice:</th>
					  <td><?echo $ridic["ulice"]?></td>
					</div>
				  </tr>
				  <tr>
					  <td></td>
					  <td></td>
					  <td></td>
					<form method="POST">
						<td><input type="submit" name="upravaZaznamuRidice" value="Upravit" class="btn btn-default"></td>
						<td><input type="submit" name="smazatZaznamRidice" value="Smazat" class="btn btn-default"></td>
					</form>
				  </tr>

				<?} //konec while cyklu?>
			</table>
		</div>
    </div>    <!--konec div class seznam ridicu-->
    <?
      break;
    case 3:     //pridat ridice
    ?>
 
	<div class="panel panel-default novaJizda">
		<div class="panel-heading">
			<h4 class="prihlas">Přidat řidiče</h4>
		</div>
		<div class="panel-body tabulka">
		<div class="nove">
			<p>Vytváříte nový záznam o řidiči. Všechna pole musí být vyplněna!</p>
			<div class="form-inside">
			  <form method="POST" class="form-vertical">
				<div class="form-group">
					<label for="jmenoRidice" class="control-label">Jméno</label>
					<input type="text" name="jmenoRidice" class="form-control">
				</div>
				<div class="form-group">
					<label for="prijmeniRidice" class="control-label">Příjmení</label>
					<input type ="text" name="prijmeniRidice" class="form-control">
				</div>
				<div class="form-group">
					<label for="rodneCisloRidice" class="control-label">Rodné číslo</label>
					<input type ="text" name="rodneCisloRidice" class="form-control">
				</div>
				<div class="form-group">
					<label for="narodnostRidice" class="control-label">Národnost</label>
					<input type ="text" name="narodnostRidice" class="form-control">
				</div>
				<div class="form-group">
					<label for="mestoRidice" class="control-label">Město</label>
					<input type ="text" name="mestoRidice" class="form-control">
				</div>
				<input type="submit" name="vlozitNovehoRidice" value="Potvrdit" class="btn btn-default" >
			  </form>
			</div>
		</div>
		</div>
    </div>
	  <?
      break;
    case 4:     //odhlasit
      unset($_GET["menuSelector"]);
      unset($_SESSION["typPrihlaseni"]);
      session_unset();
      session_destroy();
    ?>
      <script>
        window.location.href="index.php";     //navrat na hlavni stranku
      </script>
      <?
	  break;
    }         //konec switche
?>
    </div>      <!--konec div class obsahStranky-->
</div>
<?
  }         //konec funkce spravce
?>