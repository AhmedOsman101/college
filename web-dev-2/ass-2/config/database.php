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

// Create database if it doesn't exist
$sql = "CREATE DATABASE IF NOT EXISTS `$db_name` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci";
if ($conn->query($sql) === true) {
  // Select the database
  $conn->select_db($db_name);
} else {
  die("Error creating database: " . $conn->error);
}
