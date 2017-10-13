<!DOCTYPE html>
<html>
<head>
  <title>Kniha Jízd</title>
  <!--bootstrap-->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
  <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>

<?php
/*	
 *	Projekt do predmetu ITU pro tema Kniha jizd
 *	Autor: xchalu13, xjochl00
 */
 
 ini_set("default_charset", "UTF-8");
 if (!isset($_SESSION)){
	 ini_set('session.save_path',getcwd(). '/');
	 session_start();
	}
 
 include "db_connect.php";
 include "spravce.php";
 include "admin.php";
 
 if(!isset($_GET["menuSelector"]))
  $_GET["menuSelector"]=0;
 
 
 if(isset($_POST["loginAdmin"])){		//pokud byl vyplnen formular  pro admina
	$proverLogin="SELECT * FROM Admin WHERE login='".$_POST["loginAdmin"]."'";
	$provereno=mysql_query($proverLogin, $databaze);
  $pocetVysledku=mysql_num_rows($provereno);
  if($pocetVysledku == 0){    //login neexistuje
    echo "<div class=\"alert alert-danger\" id=\"adminLoginErr\">Špatný login</div>";
  }
  else{     //login exisutje
    $admin=mysql_fetch_array($provereno, MYSQL_ASSOC);
    if($admin["heslo"]==$_POST["hesloAdmin"]){
      $_SESSION["typPrihlaseni"]="admin";
      $_SESSION["idAdmina"]=$admin["idAdmina"];
      $_GET["menuSelector"]=0;
    }
    else{       //heslo se neshoduje
      echo "<div class=\"alert alert-danger\" id=\"adminLoginErr\">Špatné heslo</div>";
    }
  }
}

if(isset($_POST["loginSpravce"])){    //pokud byl vyplnen formular  pro spravce
	$proverLogin="SELECT * FROM Spravce WHERE login='".$_POST["loginSpravce"]."'";
	$provereno=mysql_query($proverLogin, $databaze);
  $pocetVysledku=mysql_num_rows($provereno);
  if($pocetVysledku == 0){    //login neexistuje
    echo "<div class=\"alert alert-danger\" id=\"spravceLoginErr\">Špatný login</div>";
  }
  else{     //login exisutje
    $spravce=mysql_fetch_array($provereno, MYSQL_ASSOC);
    if($spravce["heslo"] == $_POST["hesloSpravce"]){
      $_SESSION["typPrihlaseni"]="spravce";
      $_SESSION["idSpravce"]=$spravce["idSpravce"];
      $_GET["menuSelector"]=0;
    }
    else{       //heslo se neshoduje
      echo "<div class=\"alert alert-danger\" id=\"spravceLoginErr\">Špatné heslo</div>";
    }
  }
}

if(isset($_SESSION["typPrihlaseni"])){
  switch($_SESSION["typPrihlaseni"]){
    case "admin":
      admin($databaze, $_GET["menuSelector"]);
      break;
    case "spravce":
      spravce($databaze, $_GET["menuSelector"]);
      break;
  }
}
else{
?>

<nav class="navbar navbar-static-top"> 
	<div class="container">
	<div class="navbar-header">
        <a class="navbar-brand" href="http://www.stud.fit.vutbr.cz/~xjochl00/index.php">
			<img id="car" src="car.png" alt="Online Kniha Jízd"/>Online Kniha Jízd
		</a>
    </div>
	</div>
</nav>

<div class="mainBody">

<div class="loginPage">
  <div class="row">
    <div class="col-xs-6">
	<div id="spravceLogin" class="panel panel-default">
	  <div class="panel-heading">
		<h4 class="prihlas">Přihlášení Správce</h4>
	  </div>
	  <div class="panel-body bg-info">
		  <form method="post" class="form-horizontal">
			<div class="form-group">
			  <label for="loginSpravce" class="control-label col-sm-2">Login:</label>
			  <div class="col-sm-10">
				<input type="text" name="loginSpravce" id="loginSpravceId" class="form-control">
			  </div>
			</div>
			<div class="form-group">
			  <label for="hesloSpravce" class="control-label col-sm-2">Heslo:</label>
			  <div class="col-sm-10">
				<input type="password" name="hesloSpravce" id="hesloSpravceId" class="form-control">
			  </div>
			</div>
			<div class="col-sm-offset-2 col-sm-10">
			  <input type="submit" name="prihlaseniSpravceSubmit" value="Přihlásit" class="btn btn-default">
			</div>
		</form>
	  </div>
  </div>
  </div>
    
  <div class="col-xs-6">
  <div id="adminLogin" class="panel panel-default">
	  <div class="panel-heading">
		<h4 class="prihlas">Přihlášení Admina</h4>
	  </div>
	  <div class="panel-body bg-info">
		<form method="post"class="form-horizontal">
			<div class="form-group">
			  <label for="loginAdmin" class="control-label col-sm-2">Login:</label>
			  <div class="col-sm-10">
				<input type="text" name="loginAdmin" id="loginAdminId" class="form-control">
			  </div>
			</div>
			<div class="form-group">
			  <label for="hesloAdmin" class="control-label col-sm-2">Heslo:</label>
			  <div class="col-sm-10">
				<input type="password" name="hesloAdmin" id="hesloAdminId" class="form-control">
			  </div>
			</div>
			<div class="col-sm-offset-2 col-sm-10">
			  <input type="submit" name="prihlaseniAdminSubmit" value="Přihlásit" class="btn btn-default">
			</div>
		</form>
	  </div>
  </div>
  </div>

  </div>
</div>

</div>
<?php
}   //konec else if(isset($_SESSION["typPrihlaseni"]))
?>

	</body>
</html>