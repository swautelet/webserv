<?php
spl_autoload_register('myAutoLoader');

function myAutoLoader ($className){
	$url = $_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'];

	if (strpos($url, 'include') !== false){
		$path = '../class/';
	}
	else{
		$path = 'class/';
	}
	$extension = '.class.php';
	require_once $path . $className . $extension;
}
