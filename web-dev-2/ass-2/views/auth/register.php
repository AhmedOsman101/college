<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Register - Educational App</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <h1>Register</h1>
        
        <?php if (isset($_SESSION['error'])): ?>
            <div class="alert alert-error"><?php echo $_SESSION['error']; unset($_SESSION['error']); ?></div>
        <?php endif; ?>

        <form action="index.php?action=register" method="POST">
            <label for="name">Full Name</label>
            <input type="text" name="name" id="name" required>

            <label for="email">Email</label>
            <input type="email" name="email" id="email" required>

            <label for="password">Password</label>
            <input type="password" name="password" id="password" required>

            <label for="birthdate">Birthdate</label>
            <input type="date" name="birthdate" id="birthdate" required>

            <button type="submit">Register</button>
        </form>

        <p>Already have an account? <a href="index.php?action=login">Login here</a></p>
    </div>
</body>
</html>
