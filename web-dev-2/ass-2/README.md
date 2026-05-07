# 🎓 Educational Web App Setup Guide (PHP + MySQL)

This project is a simple, educational web application built with Native PHP and MySQL using a basic **MVC (Model-View-Controller)** structure. It is designed to help students understand the fundamentals of backend development.

---

## 🛠️ Project Structure Overview

- **`index.php`**: The entry point. Every request starts here.
- **`routes.php`**: The "traffic controller." It decides which logic or view to show based on the URL.
- **`config/database.php`**: Handles the connection to your MySQL database.
- **`models/`**: Contains classes that talk to the database (`User.php` and `Product.php`).
- **`controllers/`**: Contains the business logic (`LogicController.php`), like checking passwords or calculating sales.
- **`views/`**: Contains the HTML files that the user sees.
- **`migrations/`**: Contains SQL scripts (wrapped in PHP) to create your tables automatically.
- **`uploads/`**: The folder where product images are saved.

---

## 🚀 Step-by-Step Setup

### 1. Requirements
- **XAMPP** or **WAMP** installed on your computer.
- PHP 7.4 or higher.
- MySQL/MariaDB.

### 2. Database Configuration
1. Open `config/database.php`.
2. Ensure the `$username` (usually `root`) and `$password` (usually empty `''`) match your XAMPP settings.
3. The script will automatically create a database named `web_assignment_db` for you.

### 3. Running Migrations
Before you can use the app, you need to create the tables.
- Open your browser and go to: `http://localhost/web_assignment2/run_migrations.php`
- You should see messages saying "Users table created" and "Products table created."

### 4. How to Use the App
1. **Register**: Go to `index.php?action=register` and create an account.
2. **Login**: Use your email and password to log in.
3. **Products**: Once logged in, you can add, edit, or delete products.
4. **Selling**: Click "Sell" on any product, enter a quantity, and watch the stock decrease and total sales increase!

---

## 💡 Key Logic Explanation

### Password Hashing
We never store passwords as plain text. In `User.php`:
- **Registration**: We use `password_hash($password, PASSWORD_DEFAULT)` to encrypt it.
- **Login**: We use `password_verify($password, $hashed_from_db)` to check if the user entered the correct one.

### Sales Logic
The "Sell" logic in `Product.php` follows these steps:
1. Check if the requested quantity is available in `stock`.
2. Subtract quantity from `stock`.
3. Add quantity to `sold_quantity`.
4. Calculate the total price (`price * quantity`) and add it to `sold_amount`.

### Simple Routing
Instead of complex URLs, we use a query parameter called `action`.
- `index.php?action=login`
- `index.php?action=products`
The `switch` statement in `routes.php` handles these values.

---

## 🗄️ Database Schema

### `users` table
- `id`: Unique identifier (Primary Key).
- `name`: Full name.
- `email`: Used for login (Unique).
- `password`: Hashed password string.
- `birthdate`: User's date of birth.

### `products` table
- `id`: Unique identifier.
- `image`: Filename of the uploaded image.
- `name`: Name of the product.
- `price`: Unit price.
- `stock`: How many are left.
- `sold_quantity`: Total number of units sold.
- `sold_amount`: Total revenue generated ($).
