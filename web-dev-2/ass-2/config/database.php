<?php
/**
 * Database Configuration
 * This file handles the connection to the MySQL database.
 */

$host = 'localhost';
$db_name = 'web_assignment_db';
$username = 'root'; // Default XAMPP username
$password = '';     // Default XAMPP password

// Create connection
$conn = new mysqli($host, $username, $password);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Run migrations when the database is new or required tables are missing.
$databaseExists = false;
$checkDatabaseSql = "SHOW DATABASES LIKE '$db_name';";
$databaseCheckResult = $conn->query($checkDatabaseSql);

if ($databaseCheckResult->num_rows > 0) {
  $databaseExists = true;
}

// Create database if it doesn't exist
$sql = "CREATE DATABASE IF NOT EXISTS `$db_name`;";
if ($conn->query($sql) === true) {
  // Select the database
  $conn->select_db($db_name);

  $requiredTables = ['users', 'products'];
  $missingTables = [];

  foreach ($requiredTables as $tableName) {
    $checkTableSql = "SHOW TABLES LIKE '$tableName'";
    $tableCheckResult = $conn->query($checkTableSql);

    if ($tableCheckResult === false || $tableCheckResult->num_rows === 0) {
      $missingTables[] = $tableName;
    }
  }

  if (!$databaseExists || !empty($missingTables)) {
    require_once __DIR__ . '/../run_migrations.php';
    runMigrations(false);
  }
} else {
  die("Error creating database: " . $conn->error);
}
