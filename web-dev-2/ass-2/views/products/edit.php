<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <title>Edit Product - Educational App</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>
  <div class="container">
    <nav>
      <a href="index.php?action=products">Back to List</a>
    </nav>

    <h1>Edit Product</h1>

    <form action="index.php?action=edit_product&id=<?= $product['id'] ?>" method="POST" enctype="multipart/form-data">
      <label for="name">Product Name</label>
      <input type="text" name="name" id="name" value="<?= $product['name'] ?>" required>

      <label for="description">Description</label>
      <textarea name="description" id="description" rows="4">
        <?= $product['description'] ?>
      </textarea>

      <label for="price">Price ($)</label>
      <input type="number" step="0.01" name="price" id="price" value="<?= $product['price'] ?>" required>

      <label for="stock">Current Stock</label>
      <input type="number" name="stock" id="stock" value="<?= $product['stock'] ?>" required>

      <label for="image">Change Product Image (optional)</label>
      <input type="file" name="image" id="image">
      <?php if ($product['image']): ?>
        <p>Current image: <img src="uploads/<?= $product['image'] ?>" class="product-img"></p>
      <?php endif; ?>

      <button type="submit">Update Product</button>
    </form>
  </div>
</body>

</html>
