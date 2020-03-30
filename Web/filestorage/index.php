<?php 
if(!isset($_SESSION)) 
{ 
	session_start(); 
}
?>
<html>
	<head>
		<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
	</head>
	<body>
	<?php
		if(isset($_POST['name'])) {
			$_SESSION['name'] = $_POST['name'];
		}

		if(isset($_SESSION['name'])) {
			if(isset($_GET['file'])) {
				echo "<a class=\"btn btn-primary\" href=\"index.php\" role=\"button\">🡄 Go back</a><br>";
				include 'files/' . $_GET['file'];
			} else {
				echo "Hello, " . $_SESSION['name'] . "<br>";
				echo "<ul class=\"list-group mx-2\">";
				foreach (scandir("files") as $val) {
					if(strcmp($val, ".") and strcmp($val, "..")) {
						echo "<li class=\"list-group-item my-1\"><a href='?file=$val'>$val</a></li>";
					}
				}
				echo "</ul>";
			}
		} else {
			echo "What is your name?";
			echo "<form action=\"/index.php\" method=\"post\">";
			echo "<input type=\"text\" name=\"name\" >";
			echo "<input type=\"submit\" value=\"Submit\">";
			echo "</form> ";
		}
	?>
	</body>
</html>
