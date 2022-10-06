<?php
phpinfo();
// parse_str($_SERVER["QUERY_STRING"], $_POST);
// print_r($_GET);
// echo '</br>';
// echo $_GET['firstname'];
// if (strcmp($_SERVER["REQUEST_METHOD"], "POST") == 0)
// {
//     parse_str($_SERVER["QUERY_STRING"], $_POST);
// }
// if (strcmp($_SERVER["REQUEST_METHOD"], "GET") == 0)
// {
//     parse_str($_SERVER["QUERY_STRING"], $_GET);
// }
if (isset($_GET['firstname'])) {
    echo '<h3>Form GET Method</h3>';
    $lastname = $_GET['lastname'];
    $firstname = $_GET['firstname'];
    echo 'Your name is '. $lastname . ' ' . $firstname;
    exit;
}
else if (isset($_POST['firstname'])){
    echo '<h3>Form POST Method</h3>';
    $lastname = $_POST['lastname'];
    $firstname = $_POST['firstname'];
    echo 'Your name is '. $lastname . ' ' . $firstname;
    exit;
}
else
    echo "NO SUBMIT";
?>