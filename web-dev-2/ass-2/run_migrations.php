<?php
/**
 * Migration Runner
 * Runs automatically when needed to set up the database tables.
 */

function runMigrations() {
  // Globals are set from config/database.php file.
  global $conn, $db_name, $databaseExists;

  if (!$databaseExists) {
    // Create database if it doesn't exist
    $sql = "CREATE DATABASE IF NOT EXISTS `$db_name`;";
    if (!$conn->query($sql)) die("Error creating database: $conn->error");
    $databaseExists = true;
  }

  // Select the database
  $conn->select_db($db_name);

  $requiredTables = ['users', 'products'];
  $missingTables = false;

  foreach ($requiredTables as $tableName) {
    $checkTableSql = "SHOW TABLES LIKE '$tableName'";
    $tableCheckResult = $conn->query($checkTableSql);

    if (!$tableCheckResult || $tableCheckResult->num_rows === 0) {
      $missingTables = true;
      break;
    }
  }

  // If the tables are missing, create them.
  if ($missingTables) {
    require_once __DIR__ . '/migrations/create_users_table.php';
    require_once __DIR__ . '/migrations/create_products_table.php';

    createUsersTable($conn, $showOutput);
    createProductsTable($conn, $showOutput);
  }
}
