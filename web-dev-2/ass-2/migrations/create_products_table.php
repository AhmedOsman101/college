<?php
/**
 * Migration: Create Products Table
 */
require_once __DIR__ . '/../config/database.php';

try {
    $sql = "CREATE TABLE IF NOT EXISTS products (
        id INT AUTO_INCREMENT PRIMARY KEY,
        image VARCHAR(255),
        name VARCHAR(100) NOT NULL,
        description TEXT,
        price DECIMAL(10, 2) NOT NULL,
        stock INT NOT NULL,
        sold_quantity INT DEFAULT 0,
        sold_amount DECIMAL(15, 2) DEFAULT 0.00,
        created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    )";

    if ($conn->query($sql) === TRUE) {
        echo "Products table created successfully!<br>";
    } else {
        echo "Error creating table: " . $conn->error;
     }
} catch(Exception $e) {
    echo "Error: " . $e->getMessage();
}
?>
