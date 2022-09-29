<!DOCTYPE html>
<html>
<body>
<h2>HTML Forms</h2>

<form action="/page/form_query.php" method="form.auto">
	<input type="text" name="firstname">
	<input type="password" name="lastname">
	<input type="submit" value="Submit">
</form>

<p>If you click the "Submit" button, the form-data will be sent to a page called "/post/info.txt".</p>

<?php parse_str($_SERVER["QUERY_STRING"], $_GET);?>
lastname : <?php echo $_GET["lastname"];?> </br>
firstname : <?php echo $_GET["firstname"];?> </br>
</body>
</html>
