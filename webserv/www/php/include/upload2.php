<?php
// phpinfo();
echo "</br>POST </br>";
print_r($_POST);
echo "</br>FILES </br>";
print_r($_FILES);
$f = fopen( 'php://stdin', 'r' );

while( $line = fgets( $f ) ) {
  echo $line;
}

fclose( $f );
// $uploaddir = '/www/upload/';
// $uploadfile = $uploaddir . basename($_FILES['userfile']['name']);

// echo '<pre>';
// if (move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile)) {
//     echo "File is valid, and was successfully uploaded.\n";
// } else {
//     echo "Possible file upload attack!\n";
// }

// echo 'Here is some more debugging info:';
// print_r($_FILES);

// print "</pre>";
