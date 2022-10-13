<?php

// declare (strict_type = 1);
include 'www/other/class/calc.class.php';

$operation = $_POST["variable"];
$num1 = $_POST["num1"];
$num2 = $_POST["num2"];

$calc = new Calc($operation, (int)$num1, (int)$num2);

try{
	echo $calc->calculator();
}
catch (TypeError $e) {
	echo "Error! : " . $e->getMessage();
}