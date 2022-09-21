<!DOCTYPE html>
<html>
<body>
<h2>HTML Forms</h2>

<form action="/post/name.txt" method="POST">
	<input type="text" name="firstname">
	<input type="text" name="lastname">
	<input type="submit" value="Submit">
</form>

<p>If you click the "Submit" button, the form-data will be sent to a page called "/post/info.txt".</p>
</body>
</html>
<?php
ini_set('display_errors', 'On');
error_reporting(E_ALL);
echo "test<br/>";
if (isset($_GET['submit'])) {
    echo '<h3>Form GET Method</h3>';
    $lastname = $_GET['lastname'];
    $firstname = $_GET['firstname'];
    echo 'Your name is '. $lastname . ' ' . $firstname;
    exit; }
else
	echo "NO SUBMIT";
?>
