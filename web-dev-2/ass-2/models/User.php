<?php
/**
 * User Model
 * Handles all database operations related to the users table.
 */
class User {
  private $db;

  public function __construct($conn) {
    $this->db = $conn;
  }

  // Register a new user
  public function register($name, $email, $password, $birthdate) {
    $hashed_password = password_hash($password, PASSWORD_DEFAULT);
    $sql = "INSERT INTO users (name, email, password, birthdate) VALUES (?, ?, ?, ?)";
    $stmt = $this->db->prepare($sql);
    $stmt->bind_param("ssss", $name, $email, $hashed_password, $birthdate);
    return $stmt->execute();
  }

  // Find user by email (for login and checking duplicates)
  public function findByEmail($email) {
    $sql = "SELECT * FROM users WHERE email = ?";
    $stmt = $this->db->prepare($sql);
    $stmt->bind_param("s", $email);
    $stmt->execute();
    $result = $stmt->get_result();
    return $result->fetch_assoc();
  }
}
