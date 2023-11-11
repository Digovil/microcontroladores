<?php

$host = "localhost";
$dbname = "id21534186_diplomadoiot";
$username = "id21534186_dgvesp8266";
$password = "Celena+1";

// Conexión a la base de datos
$mysqli = new mysqli($host, $username, $password, $dbname);

// Verificar la conexión
if ($mysqli->connect_error) {
    die("Error de conexión: " . $mysqli->connect_error);
}

// Evitar SQL injection usando declaraciones preparadas
$dato = $_GET['dato'];

// Crear una declaración preparada
$sql = "INSERT INTO lectura (dato) VALUES (?)";
$stmt = $mysqli->prepare($sql);

// Verificar si la preparación fue exitosa
if ($stmt) {
    // Vincular parámetros y ejecutar la consulta
    $stmt->bind_param("s", $dato);
    $resultado = $stmt->execute();

    // Verificar el resultado de la ejecución
    if ($resultado) {
        echo "Inserción realizada con éxito!";
    } else {
        echo "Error al insertar los datos: " . $stmt->error;
    }

    // Cerrar la declaración preparada
    $stmt->close();
} else {
    echo "Error en la preparación de la consulta: " . $mysqli->error;
}

// Cerrar la conexión
$mysqli->close();
?>
