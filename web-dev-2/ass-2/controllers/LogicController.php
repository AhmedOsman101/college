<?php
/**
 * LogicController
 * This controller handles authentication, product CRUD, and sales logic.
 */
require_once __DIR__ . '/../config/database.php';
require_once __DIR__ . '/../models/User.php';
require_once __DIR__ . '/../models/Product.php';

// Start session at the top of the controller
if (session_status() === PHP_SESSION_NONE) {
  session_start();
}

class LogicController {
  private $userModel;
  private $productModel;

  public function __construct($conn) {
    $this->userModel = new User($conn);
    $this->productModel = new Product($conn);
  }

  // --- Authentication Logic ---

  public function register() {
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      $name = $_POST['name'];
      $email = $_POST['email'];
      $password = $_POST['password'];
      $birthdate = $_POST['birthdate'];

      // Simple Validation
      if (empty($name) || empty($email) || empty($password) || empty($birthdate)) {
        $_SESSION['error'] = "All fields are required.";
        header("Location: index.php?action=register");
        exit();
      }

      // Check if email exists
      if ($this->userModel->findByEmail($email)) {
        $_SESSION['error'] = "Email already registered.";
        header("Location: index.php?action=register");
        exit();
      }

      if ($this->userModel->register($name, $email, $password, $birthdate)) {
        $_SESSION['success'] = "Registration successful! Please login.";
        header("Location: index.php?action=login");
        exit();
      }
    }
  }

  public function login() {
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      $email = $_POST['email'];
      $password = $_POST['password'];

      $user = $this->userModel->findByEmail($email);

      if ($user && password_verify($password, $user['password'])) {
        $_SESSION['user_id'] = $user['id'];
        $_SESSION['user_name'] = $user['name'];
        header("Location: index.php?action=products");
        exit();
      } else {
        $_SESSION['error'] = "Invalid email or password.";
        header("Location: index.php?action=login");
        exit();
      }
    }
  }

  public function logout() {
    session_destroy();
    header("Location: index.php?action=login");
    exit();
  }

  // --- Product CRUD Logic ---

  public function createProduct() {
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      $data = [
        'name'        => $_POST['name'],
        'description' => $_POST['description'],
        'price'       => $_POST['price'],
        'stock'       => $_POST['stock'],
        'image'       => '',
      ];

      // Handle Image Upload
      if (isset($_FILES['image']) && $_FILES['image']['error'] === 0) {
        $targetDir = "uploads";
        $fileName = time() . "_" . basename($_FILES["image"]["name"]);
        $targetFilePath = "$targetDir/$fileName";

        if (move_uploaded_file($_FILES["image"]["tmp_name"], $targetFilePath)) {
          $data['image'] = $fileName;
        }
      }

      if ($this->productModel->create($data)) {
        $_SESSION['success'] = "Product created successfully!";
        header("Location: index.php?action=products");
        exit();
      }
    }
  }

  public function updateProduct($id) {
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      $data = [
        'name'        => $_POST['name'],
        'description' => $_POST['description'],
        'price'       => $_POST['price'],
        'stock'       => $_POST['stock'],
      ];

      if ($this->productModel->update($id, $data)) {
        // If a new image is uploaded
        if (isset($_FILES['image']) && $_FILES['image']['error'] === 0) {
          $targetDir = "uploads";
          $fileName = time() . "_" . basename($_FILES["image"]["name"]);
          $targetFilePath = "$targetDir/$fileName";

          if (move_uploaded_file($_FILES["image"]["tmp_name"], $targetFilePath)) {
            $this->productModel->updateImage($id, $fileName);
          }
        }
        $_SESSION['success'] = "Product updated successfully!";
        header("Location: index.php?action=products");
        exit();
      }
    }
  }

  public function deleteProduct($id) {
    $success = $this->productModel->delete($id);

    // Check if it's an AJAX request
    if (!empty($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) == 'xmlhttprequest') {
      header('Content-Type: application/json');
      echo json_encode(['success' => $success]);
      exit();
    }

    if ($success) {
      $_SESSION['success'] = "Product deleted successfully!";
    }
    header("Location: index.php?action=products");
    exit();
  }



  // Helper to check if user is logged in
  public function checkAuth() {
    if (!isset($_SESSION['user_id'])) {
      header("Location: index.php?action=login");
      exit();
    }

    // --- Cookie Example ---
    // Set a cookie named "last_visit" with the current date/time
    // It will expire in 30 days (86400 seconds * 30)
    $expireTime = time() + 86400 * 30;
    setcookie("last_visit", date("Y-m-d H:i:s"), $expireTime, "/");
  }
}
