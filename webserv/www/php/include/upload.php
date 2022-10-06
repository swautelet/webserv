<?php
// phpinfo();
// var_dump($_POST);
if (strcmp($_ENV["REQUEST_METHOD"], "POST") == 0)
{
    echo '</br>detected post</br>';
    parse_str($_ENV["QUERY_STRING"], $_POST);
    echo '</br>POST </br>';
    print_r($_POST);
}
else if (strcmp($_ENV["REQUEST_METHOD"], "GET") == 0)
{
     echo '</br>detected get</br>';
    parse_str($_ENV["QUERY_STRING"], $_GET);
    echo '</br>GET </br>';
    print_r($_GET);
}
else
{
  echo '</br>detected nothing</br>';
}
echo '</br>ENV </br>';
print_r($_ENV);
echo'</br>SERVER </br>';
print_r($_SERVER);
echo'</br>FILE </br>';
print_r($_FILES);
echo '</br> </br>';

// $file = stream_get_contents(STDIN);
// if ($file === FALSE) { 
// echo 'ERROR: stream_get_content';
// exit (1);
//  }
// var_dump($file);


$target_dir = "www/upload/";
$target_file = $target_dir . 'test.png';
echo $target_file;
file_put_contents($target_file, STDIN);
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION));
// Check if image file is a actual image or fake image
// echo "hello from php upload";
// print_r($_ENV);

// print_r($_POST);
// print_r($_FILES);
if(isset($_POST["myfile"])) {
  $check = getimagesize($target_file);
  if($check !== false) {
    echo "File is an image - " . $check["mime"] . ".";
    $uploadOk = 1;
  } else {
    echo "File is not an image.";
    $uploadOk = 0;
  }
}
if (file_exists($target_file)) {
  echo "Sorry, file already exists.";
  $uploadOk = 0;
}

// Check file size
if ($_FILES["fileToUpload"]["size"] > 500000) {
  echo "Sorry, your file is too large.";
  $uploadOk = 0;
}

// Allow certain file formats
if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
&& $imageFileType != "gif" ) {
  echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
  $uploadOk = 0;
}

// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
  echo "Sorry, your file was not uploaded.";
// if everything is ok, try to upload file
} else {
  if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
    echo "The file ". htmlspecialchars( basename( $_FILES["fileToUpload"]["name"])). " has been uploaded.";
  } else {
    echo "Sorry, there was an error uploading your file.";
  }
}
?>