<!-- app/views/partials/header.php -->
<?php
$cartCount = 0;

$currentRole = $_SESSION['role'] ?? '';
?>
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ElderCare - Quality Support</title>
  <?php
  // Calculate base URL so all relative paths work regardless of entry point
  $scriptPath = str_replace('\\', '/', dirname($_SERVER['SCRIPT_NAME']));
  $projectFolder = PHP_OS_FAMILY === 'Linux' ? '' : '/webassignment2/web_assignment2';


  $baseHref = "$scriptPath/";

  if (str_contains($scriptPath, $projectFolder) && $scriptPath !== $projectFolder) {
    $baseHref = "$projectFolder/";
  }
  ?>
  <base href="<?= $baseHref ?>">
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link
    href="https://fonts.googleapis.com/css2?family=Nunito:wght@400;600;700;800&family=Playfair+Display:wght@500;600;700;800&display=swap"
    rel="stylesheet">
  <link rel="stylesheet" href="assets/css/eldercare.css">

  <!-- jQuery Library -->
  <script src="https://code.jquery.com/jquery-3.7.1.min.js"
    integrity="sha256-/JqT3SQfawRcv/BIHPThkBvs0OEvtFFmqPF/lYI/Cxo=" crossorigin="anonymous"></script>
</head>

<body>
  <nav class="navbar">
    <a href="index.php?action=home" class="nav-logo">
      <div class="logo-icon">
        <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="#2b4c6a" stroke-width="2">
          <path
            d="M12 21.35l-1.45-1.32C5.4 15.36 2 12.28 2 8.5 2 5.42 4.42 3 7.5 3c1.74 0 3.41.81 4.5 2.09C13.09 3.81 14.76 3 16.5 3 19.58 3 22 5.42 22 8.5c0 3.78-3.4 6.86-8.55 11.54L12 21.35z" />
        </svg>
      </div>
      <div class="logo-text-wrapper">
        <div class="logo-text">Elder<span>Care</span></div>
        <div class="logo-tagline">Support & Community</div>
      </div>
    </a>

    <div class="nav-links">
      <a href="index.php?action=home" class="nav-link active">Home</a>
      <a href="index.php?action=products" class="nav-link">Supplies</a>
      <a href="index.php?action=about" class="nav-link">About Us</a>
    </div>

    <div class="nav-right">
      <?php if (isset($_SESSION['user_id'])): ?>
        <?php if ($currentRole !== 'admin'): ?>
          <a href="index.php?action=cart"
            style="position: relative; color: #64748b; margin-right: 1.5rem; display: flex; align-items: center; transition: color 0.2s;">
            <svg width="28" height="28" fill="none" stroke="currentColor" stroke-width="1.5" viewBox="0 0 24 24">
              <path stroke-linecap="round" stroke-linejoin="round"
                d="M3 3h2l.4 2M7 13h10l4-8H5.4M7 13L5.4 5M7 13l-2.293 2.293c-.63.63-.184 1.707.707 1.707H17m0 0a2 2 0 100 4 2 2 0 000-4zm-8 2a2 2 0 11-4 0 2 2 0 014 0z" />
            </svg>
            <?php if ($cartCount > 0): ?>
              <span id="cart-count-badge"
                style="position: absolute; top: -5px; right: -8px; background: var(--secondary); color: white; font-size: 0.7rem; font-weight: 800; padding: 0.1rem 0.4rem; border-radius: 1rem; border: 2px solid var(--background);"><?= $cartCount ?></span>
            <?php else: ?>
              <span id="cart-count-badge"
                style="display: none; position: absolute; top: -5px; right: -8px; background: var(--secondary); color: white; font-size: 0.7rem; font-weight: 800; padding: 0.1rem 0.4rem; border-radius: 1rem; border: 2px solid var(--background);">0</span>
            <?php endif; ?>
          </a>
        <?php endif; ?>
        <a href="index.php?action=profile"
          style="text-decoration: none; font-weight: 700; color: var(--primary); margin-right: 1rem; transition: color 0.2s;"
          onmouseover="this.style.color='var(--secondary)'" onmouseout="this.style.color='var(--primary)'">
          Hello, <?php echo htmlspecialchars($_SESSION['user_name'] ?? 'User'); ?>
        </a>
        <a href="index.php?action=logout" class="btn-signup"
          style="background: #ef4444; padding: 0.6rem 1.2rem; font-size: 0.9rem;">Logout</a>
      <?php else: ?>
        <a href="index.php?action=login" class="nav-link">Login</a>
        <a href="index.php?action=register" class="btn-signup">Sign Up</a>
      <?php endif; ?>
    </div>
  </nav>
  <div class="main-content">

    <!-- Flash Messages -->
    <?php if (isset($_SESSION['error'])): ?>
      <div
        style="max-width: 800px; margin: 1rem auto; padding: 1rem 1.5rem; background: #fff1f2; color: #e11d48; border-radius: 0.75rem; font-weight: 600; display: flex; align-items: center; gap: 0.75rem; border: 1px solid #fecdd3;">
        <svg width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
          <path fill-rule="evenodd"
            d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-7 4a1 1 0 11-2 0 1 1 0 012 0zm-1-9a1 1 0 00-1 1v4a1 1 0 102 0V6a1 1 0 00-1-1z"
            clip-rule="evenodd"></path>
        </svg>
        <?php echo htmlspecialchars($_SESSION['error']);
        unset($_SESSION['error']); ?>
      </div>
    <?php endif; ?>
    <?php if (isset($_SESSION['success'])): ?>
      <div
        style="max-width: 800px; margin: 1rem auto; padding: 1rem 1.5rem; background: #f0fdf4; color: #16a34a; border-radius: 0.75rem; font-weight: 600; display: flex; align-items: center; gap: 0.75rem; border: 1px solid #bbf7d0;">
        <svg width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
          <path fill-rule="evenodd"
            d="M10 18a8 8 0 100-16 8 8 0 000 16zm3.707-9.293a1 1 0 00-1.414-1.414L9 10.586 7.707 9.293a1 1 0 00-1.414 1.414l2 2a1 1 0 001.414 0l4-4z"
            clip-rule="evenodd"></path>
        </svg>
        <?php echo htmlspecialchars($_SESSION['success']);
        unset($_SESSION['success']); ?>
      </div>
    <?php endif; ?>
