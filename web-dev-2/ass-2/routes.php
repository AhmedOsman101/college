<?php
/**
 * Routing Logic
 * Maps the 'action' parameter to specific controller methods or views.
 */

switch ($action) {
  // --- Auth Routes ---
  case 'login':
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      $controller->login();
    } else {
      include 'views/auth/login.php';
    }
    break;

  case 'register':
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      $controller->register();
    } else {
      include 'views/auth/register.php';
    }
    break;

  case 'logout':
    $controller->logout();
    break;

  // --- Product Routes (Protected by Auth) ---
  case 'products':
    $controller->checkAuth();
    $productModel = new Product($conn);
    $products = $productModel->getAll();
    include 'views/products/index.php';
    break;

  case 'create_product':
    $controller->checkAuth();
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      $controller->createProduct();
    } else {
      include 'views/products/create.php';
    }
    break;

  case 'edit_product':
    $controller->checkAuth();
    $id = $_GET['id'];
    $productModel = new Product($conn);
    $product = $productModel->getById($id);
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
      $controller->updateProduct($id);
    } else {
      include 'views/products/edit.php';
    }
    break;

  case 'delete_product':
    $controller->checkAuth();
    $id = $_GET['id'];
    $controller->deleteProduct($id);
    break;

  default:
    echo "404 - Page Not Found";
    break;
}
