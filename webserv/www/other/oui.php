<?php
ini_set('display_errors', 'On');
error_reporting(E_ALL);
echo "hello from php script";
if (isset($_GET['submit'])) {
    echo '<h3>Form GET Method</h3>';
    $lastname = $_GET['lastname'];
    $firstname = $_GET['firstname'];
    echo 'Your name is '. $lastname . ' ' . $firstname;
    exit; }
else
	echo "NO SUBMIT";
?>
