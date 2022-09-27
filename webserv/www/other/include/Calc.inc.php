<?php
declare (strict_types = 1);
include "Calc.class.php";

parse_str($_SERVER["QUERY_STRING"], $variable);
// echo '</br>';
// printf($_SERVER["QUERY_STRING"]);
// echo '</br>';
// echo $_GET[0];
// echo $_SERVER["REQUEST_METHOD"];
// echo $_POST ;
// echo '</br>';
// echo $_GET["num1"];
// echo  '</br>';
// echo $_GET["num2"];
// echo '</br>';

$calc = new Calc($variable["oper"], (int)$variable["num1"], (int)$variable["num2"]);

try{
    echo $calc->calculator();
}
catch (TypeError $e) {
    echo 'Error! : ' . $e->getMessage();
}