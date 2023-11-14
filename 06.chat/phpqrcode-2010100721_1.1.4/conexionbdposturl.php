<?php

$host = "localhost";
$dbname = "id21534186_diplomadoiot";
$username = "id21534186_dgvesp8266";
$password = "Celena+1";

$mysqli = new mysqli($host, $username, $password);

if ($mysqli->connect_error) {
    echo "Error de conexión: " . $mysqli -> connect_error;
} else {
    $dato = $_POST['dato'];
    $sql = "INSERT INTO url (dato) VALUES ('$dato')";
    $resultado = $mysqli->query($sql);
    if ($resultado) {
        echo "Inserción realizada con éxito!";
    } else {
        echo "Error al insertar los datos: " . $mysqli -> error;
    }

    $mysqli->close();
}

?>