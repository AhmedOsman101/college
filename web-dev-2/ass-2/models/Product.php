<?php
/**
 * Product Model
 * Handles all database operations related to the products table.
 */
class Product {
  private $db;

  public function __construct($conn) {
    $this->db = $conn;
  }

  // Get all products
  public function getAll() {
    $sql = "SELECT * FROM products ORDER BY created_at DESC";
    $result = $this->db->query($sql);
    return $result->fetch_all(MYSQLI_ASSOC);
  }

  // Get single product
  public function getById($id) {
    $sql = "SELECT * FROM products WHERE id = ?";
    $stmt = $this->db->prepare($sql);
    $stmt->bind_param("i", $id);
    $stmt->execute();
    $result = $stmt->get_result();
    return $result->fetch_assoc();
  }

  // Create product
  public function create($data) {
    $sql = "INSERT INTO products (name, description, price, stock, image) VALUES (?, ?, ?, ?, ?)";
    $stmt = $this->db->prepare($sql);
    $stmt->bind_param(
      "ssdis",
      $data['name'],
      $data['description'],
      $data['price'],
      $data['stock'],
      $data['image']
    );
    return $stmt->execute();
  }

  // Update product
  public function update($id, $data) {
    $sql = "UPDATE products SET name = ?, description = ?, price = ?, stock = ? WHERE id = ?";
    $stmt = $this->db->prepare($sql);
    $stmt->bind_param(
      "ssdii",
      $data['name'],
      $data['description'],
      $data['price'],
      $data['stock'],
      $id
    );
    return $stmt->execute();
  }

  // Update product image separately if needed
  public function updateImage($id, $imagePath) {
    $sql = "UPDATE products SET image = ? WHERE id = ?";
    $stmt = $this->db->prepare($sql);
    $stmt->bind_param("si", $imagePath, $id);
    return $stmt->execute();
  }

  // Delete product
  public function delete($id) {
    $sql = "DELETE FROM products WHERE id = ?";
    $stmt = $this->db->prepare($sql);
    $stmt->bind_param("i", $id);
    return $stmt->execute();
  }


}
