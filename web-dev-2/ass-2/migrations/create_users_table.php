<?php
/**
 * Migration: Create Users Table
 */
require_once __DIR__ . '/../config/database.php';

try {
    $sql = "CREATE TABLE IF NOT EXISTS users (
        id INT AUTO_INCREMENT PRIMARY KEY,
        name VARCHAR(100) NOT NULL,
        email VARCHAR(100) NOT NULL UNIQUE,
        password VARCHAR(255) NOT NULL,
        birthdate DATE NOT NULL,
        created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    )";

    if ($conn->query($sql) === TRUE) {
        echo "Users table created successfully!<br>";
    } else {
        echo "Error creating table: " . $conn->error;
    }
} catch(Exception $e) {
    echo "Error: " . $e->getMessage();
}
?>
