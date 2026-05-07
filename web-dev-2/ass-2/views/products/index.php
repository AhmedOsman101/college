<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <title>Products - Educational App</title>
  <link rel="stylesheet" href="style.css">
</head>

<body>
  <div class="container">
    <nav>
      <strong>Welcome, <?= $_SESSION['user_name'] ?></strong> |
      <a href="index.php?action=products">Products List</a> |
      <a href="index.php?action=create_product">Add New Product</a> |
      <a href="index.php?action=logout">Logout</a>
    </nav>

    <?php if (isset($_COOKIE['last_visit'])): ?>
      <p style="font-size: 0.8em; color: #666;">
        Your last visit was on: <strong><?= $_COOKIE['last_visit']; ?></strong>
      </p>
    <?php else: ?>
      <p style="font-size: 0.8em; color: #666;">This is your first visit recently!</p>
    <?php endif; ?>

    <h1>Product List</h1>

    <?php if (isset($_SESSION['success'])): ?>
      <div class="alert alert-success">
        <?php
        echo $_SESSION['success'];
        unset($_SESSION['success']);
        ?>
      </div>
    <?php endif; ?>

    <?php if (isset($_SESSION['error'])): ?>
      <div class="alert alert-error">
        <?php
        echo $_SESSION['error'];
        unset($_SESSION['error']);
        ?>
      </div>
    <?php endif; ?>

    <table>
      <thead>
        <tr>
          <th>Image</th>
          <th>Name</th>
          <th>Price</th>
          <th>Stock</th>
          <th>Actions</th>
        </tr>
      </thead>
      <tbody>
        <?php foreach ($products as $product): ?>
          <tr id="product-row-<?= $product['id'] ?>">
            <td>
              <?php if ($product['image']): ?>
                <img src="uploads/<?= $product['image'] ?>" class="product-img">
              <?php else: ?>
                No Image
              <?php endif; ?>
            </td>
            <td><?= $product['name'] ?></td>
            <td>$<?= $product['price'] ?></td>
            <td><?= $product['stock'] ?></td>
            <td>
              <a href="index.php?action=edit_product&id=<?= $product['id'] ?>">Edit</a> |
              <a href="javascript:void(0)" class="btn-delete" style="color: red;"
                onclick="deleteProduct(<?= $product['id'] ?>)">
                Delete
              </a>
            </td>
          </tr>
        <?php endforeach; ?>
      </tbody>
    </table>
  </div>

  <script>
    function deleteProduct(id) {
      if (confirm('Are you sure you want to delete this product using AJAX?')) {
        // Fetch is the modern way to do AJAX in Vanilla JavaScript
        fetch('index.php?action=delete_product&id=' + id, {
          method: 'GET',
          headers: {
            'X-Requested-With': 'XMLHttpRequest' // Tell PHP this is an AJAX request
          }
        })
          .then(response => response.json())
          .then(data => {
            if (data.success) {
              // Remove the row from the table smoothly
              const row = document.getElementById('product-row-' + id);
              row.style.opacity = '0';
              setTimeout(() => row.remove(), 300);
            } else {
              alert('Error deleting product.');
            }
          })
          .catch(error => {
            console.error('Error:', error);
            alert('Something went wrong!');
          });
      }
    }
  </script>
</body>

</html>
