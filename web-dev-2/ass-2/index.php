<?php
/**
 * Main Entry Point
 * This file handles all incoming requests and routes them to the correct logic.
 */

// Include the database connection and the controller
require_once 'config/database.php';
require_once 'controllers/LogicController.php';

// Initialize the controller
$controller = new LogicController($conn);

// Start the session to handle flash messages and authentication
if (session_status() === PHP_SESSION_NONE) {
  session_start();
}

// Simple Router
// We use the 'action' parameter in the URL to determine what the user wants to do.
// Example: index.php?action=products
$action = $_GET['action'] ?? 'login';

require_once 'routes.php';
