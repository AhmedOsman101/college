<?php
/**
 * Migration Runner
 * Run this file in your browser to set up the database tables.
 * Example: http://localhost/web_assignment2/run_migrations.php
 */

function runMigrations(bool $showOutput = true) {
  global $conn;

  if ($showOutput) {
    echo "<h2>Starting Migrations...</h2>";
  }

  require_once __DIR__ . '/migrations/create_users_table.php';
  require_once __DIR__ . '/migrations/create_products_table.php';

  createUsersTable($conn, $showOutput);
  createProductsTable($conn, $showOutput);

  if ($showOutput) {
    echo "<h3>Migrations finished successfully!</h3>";
    echo "<a href='index.php'>Go to Login Page</a>";
  }
}

if (basename(__FILE__) === basename($_SERVER['SCRIPT_FILENAME'] ?? '')) {
  require_once __DIR__ . '/config/database.php';
  runMigrations();
}
