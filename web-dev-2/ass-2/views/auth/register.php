<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ElderCare - Create Your Account</title>
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link
    href="https://fonts.googleapis.com/css2?family=Nunito:wght@400;600;700;800&family=Playfair+Display:wght@500;600;700;800&display=swap"
    rel="stylesheet">
  <link rel="stylesheet" href="assets/css/eldercare.css">
</head>

<body class="auth-layout">

  <div class="nav-logo" style="margin-bottom: 2rem;">
    <div class="logo-icon" style="width: 56px; height: 56px; background: var(--primary);">
      <svg width="28" height="28" viewBox="0 0 24 24" fill="white">
        <path
          d="M12 21.35l-1.45-1.32C5.4 15.36 2 12.28 2 8.5 2 5.42 4.42 3 7.5 3c1.74 0 3.41.81 4.5 2.09C13.09 3.81 14.76 3 16.5 3 19.58 3 22 5.42 22 8.5c0 3.78-3.4 6.86-8.55 11.54L12 21.35z" />
      </svg>
    </div>
    <div class="logo-text" style="font-size: 2rem;">ElderCare</div>
  </div>

  <div class="auth-card">
    <div class="auth-header">
      <h1 class="auth-title">Create Your Account</h1>
      <p class="auth-subtitle">Join our community of caregivers and supporters</p>
    </div>
    <?php if (isset($_SESSION['error'])): ?>
      <div class="alert alert-error"
        style="margin-bottom: 2rem; padding: 1rem; background: #fff1f2; color: #e11d48; border-radius: 0.75rem; display: flex; align-items: center; gap: 0.75rem;">
        <svg width="20" height="20" fill="currentColor" viewBox="0 0 20 20">
          <path fill-rule="evenodd"
            d="M18 10a8 8 0 11-16 0 8 8 0 0116 0zm-7 4a1 1 0 11-2 0 1 1 0 012 0zm-1-9a1 1 0 00-1 1v4a1 1 0 102 0V6a1 1 0 00-1-1z"
            clip-rule="evenodd"></path>
        </svg>
        <?php
        echo $_SESSION['error'];
        unset($_SESSION['error']);
        ?>
      </div>
    <?php endif; ?>

    <form action="index.php?action=register" method="POST">
      <div class="form-group">
        <label for="name">Full Name</label>
        <div class="input-icon-wrapper">
          <span class="input-icon">
            <svg width="20" height="20" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24">
              <path d="M16 7a4 4 0 11-8 0 4 4 0 018 0zM12 14a7 7 0 00-7 7h14a7 7 0 00-7-7z" />
            </svg>
          </span>
          <input type="text" id="name" name="name" class="input-with-icon" style="background: rgba(43, 76, 106, 0.05);"
            placeholder="e.g. Adam Ahmed">
        </div>
      </div>

      <div class="form-group">
        <label for="email">Email Address</label>
        <div class="input-icon-wrapper">
          <span class="input-icon">
            <svg width="20" height="20" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24">
              <path
                d="M3 8l7.89 5.26a2 2 0 002.22 0L21 8M5 19h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v10a2 2 0 002 2z" />
            </svg>
          </span>
          <input type="email" id="email" name="email" class="input-with-icon"
            style="background: rgba(43, 76, 106, 0.05);" placeholder="adamshawky222@gmail.com">
        </div>
      </div>

      <div class="form-group">
        <label for="birthdate">Birthdate</label>
        <div class="input-icon-wrapper">
          <span class="input-icon">
            <svg width="20" height="20" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24">
              <path d="M8 7V3m8 4V3m-9 8h10M5 21h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v12a2 2 0 002 2z" />
            </svg>
          </span>
          <input type="date" id="birthdate" name="birthdate" class="input-with-icon"
            style="background: rgba(43, 76, 106, 0.05);">
        </div>
      </div>

      <div class="form-group">
        <label for="password">Password</label>
        <div class="input-icon-wrapper">
          <span class="input-icon">
            <svg width="20" height="20" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24">
              <path
                d="M12 15v2m-6 4h12a2 2 0 002-2v-6a2 2 0 00-2-2H6a2 2 0 00-2 2v6a2 2 0 002 2zm10-10V7a4 4 0 00-8 0v4h8z" />
            </svg>
          </span>
          <input type="password" id="password" name="password" class="input-with-icon" placeholder="••••••••">
        </div>
      </div>

      <button type="submit" class="btn-submit">Create Account</button>
    </form>

    <div class="auth-footer">
      Already have an account? <a href="index.php?action=login">Login</a>
    </div>
  </div>

  <div class="help-link">
    Need help? <a href="#">Contact our support team</a>
  </div>

</body>

</html>
