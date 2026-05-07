<?php
/**
 * Migration Runner
 * Run this file in your browser to set up the database tables.
 * Example: http://localhost/web_assignment2/run_migrations.php
 */

echo "<h2>Starting Migrations...</h2>";

require_once 'migrations/create_users_table.php';
require_once 'migrations/create_products_table.php';

echo "<h3>Migrations finished successfully!</h3>";
echo "<a href='index.php'>Go to Login Page</a>";
