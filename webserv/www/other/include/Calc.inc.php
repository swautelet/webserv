<?php
declare (strict_types = 1);
include "Calc.class.php";

print_r($_POST);
echo '</br>';
$oper = $_POST['oper'];
$num1 = $_POST['num1'];
$num2 = $_POST['num2'];

echo "$oper</br>";
echo "$num1</br>";
echo "$num2</br>";

$calc = new Calc($oper, (int)$num1, (int)$num2);

try{
    echo $calc->calculator();
}
catch (TypeError $e) {
    echo 'Error! : ' . $e->getMessage();
}