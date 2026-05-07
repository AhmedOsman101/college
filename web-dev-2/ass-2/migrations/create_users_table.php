<?php
/**
 * Migration: Create Users Table
 */

function createUsersTable(mysqli $conn, bool $showOutput = true) {
  try {
    $sql = <<<SQL
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    birthdate DATE NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
  )
SQL;

    if ($conn->query($sql) === true) {
      if ($showOutput) {
        echo "Users table created successfully!<br>";
      }
    } else {
      throw new Exception("Error creating table: $conn->error");
    }
  } catch (Exception $e) {
    if ($showOutput) {
      echo "Error: " . $e->getMessage();
      return;
    }

    throw $e;
  }
}
