#! interpréteur [php]
<?php

parse_str($_SERVER["QUERY_STRING"], $_GET);

if (isset($_GET['submit'])) {
    echo '<h3>Form GET Method</h3>';
    $lastname = $_GET['lastname'];
    $firstname = $_GET['firstname'];
    echo 'Your name is '. $lastname . ' ' . $firstname;
    exit; }
else
	echo "NO SUBMIT";
?>

