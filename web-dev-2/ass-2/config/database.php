<?php
/**
 * Database Configuration
 * This file handles the connection to the MySQL database.
 */

$host = '127.0.0.1';
$db_name = 'web_assignment_db';
$username = 'root';
$password = PHP_OS_FAMILY === "Dariwn" ? 'root' : '';
$port = PHP_OS_FAMILY === "Dariwn" ? 8889 : 3306; // SQL port

// Create connection
$conn = new mysqli($host, $username, $password, null, $port);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Run migrations when the database is new or required tables are missing.
$checkDatabaseSql = "SHOW DATABASES LIKE '$db_name';";
$databaseCheckResult = $conn->query($checkDatabaseSql);
$databaseExists = $databaseCheckResult->num_rows > 0;

require_once __DIR__ . '/../run_migrations.php';
runMigrations();
