<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Add Product - Educational App</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="container">
        <nav>
            <a href="index.php?action=products">Back to List</a>
        </nav>

        <h1>Add New Product</h1>
        
        <form action="index.php?action=create_product" method="POST" enctype="multipart/form-data">
            <label for="name">Product Name</label>
            <input type="text" name="name" id="name" required>

            <label for="description">Description</label>
            <textarea name="description" id="description" rows="4"></textarea>

            <label for="price">Price ($)</label>
            <input type="number" step="0.01" name="price" id="price" required>

            <label for="stock">Initial Stock</label>
            <input type="number" name="stock" id="stock" required>

            <label for="image">Product Image</label>
            <input type="file" name="image" id="image">

            <button type="submit">Save Product</button>
        </form>
    </div>
</body>
</html>
