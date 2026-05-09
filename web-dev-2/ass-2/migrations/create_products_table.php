<?php
/**
 * Migration: Create Products Table
 */

function createProductsTable(mysqli $conn) {
  try {
    $sql = <<<SQL
CREATE TABLE IF NOT EXISTS products (
    id INT AUTO_INCREMENT PRIMARY KEY,
    image VARCHAR(255),
    name VARCHAR(100) NOT NULL,
    description TEXT,
    price DECIMAL(10, 2) NOT NULL,
    stock INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
  )
SQL;

    if ($conn->query($sql) === false) {
      throw new Exception("Error creating table: $conn->error");
    }
  } catch (Exception $e) {
    die("Error: " . $e->getMessage());
  }
}
