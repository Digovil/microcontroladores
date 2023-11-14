<?php
// Incluye la biblioteca PHP QR Code
require './phpqrcode/qrlib.php';


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

// Crear una declaración preparada
// Consulta para obtener el último dato insertado basado en el ID más grande
$sqlConsulta = "SELECT * FROM url WHERE id = (SELECT MAX(id) FROM url)";

// Ejecutar la consulta
$resultado = $mysqli->query($sqlConsulta);

// Procesar el resultado
if ($fila = $resultado->fetch_assoc()) {
    // $fila contiene la información del último dato insertado
    // Puedes acceder a los valores utilizando $fila['nombre_de_columna']
    
    // Configuración del código QR (puedes personalizar según tus necesidades)
    $tamaño = 10; // Tamaño de los módulos
    $nivelCorreccion = 'L'; // Nivel de corrección de errores (L, M, Q, H)

    // Genera el código QR
    QRcode::png($fila['dato'], 'nombre_del_archivo.png', $nivelCorreccion, $tamaño);

    // Muestra la imagen generada
    echo '<img src="nombre_del_archivo.png" alt="Código QR">';

} else {
    echo "No se encontraron resultados para el último dato insertado.";
}


// Cerrar la conexión
$mysqli->close();

?>
