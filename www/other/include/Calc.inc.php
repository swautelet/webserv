<?php
declare (strict_types = 1);
include "Calc.class.php";

parse_str($_SERVER["QUERY_STRING"], $variable);

$calc = new Calc($variable["oper"], (int)$variable["num1"], (int)$variable["num2"]);

try{
    echo $calc->calculator();
}
catch (TypeError $e) {
    echo 'Error! : ' . $e->getMessage();
}