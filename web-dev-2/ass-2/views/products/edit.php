<?php
$title = "Edit Product";
include 'views/partials/header.php';
?>

<div class="container"
  style="display: flex; justify-content: center; align-items: center; min-height: 80vh; padding: 2rem;">
  <div class="auth-card" style="width: 100%; max-width: 600px; padding: 3rem; margin-top: 0;">
    <div class="auth-header">
      <h2 class="auth-title" style="font-size: 2rem;">Edit Product</h2>
      <p class="auth-subtitle">Update inventory details</p>
    </div>

    <form method="POST" action="index.php?action=edit_product" enctype="multipart/form-data">
      <input type="hidden" name="id" value="<?= htmlspecialchars($product['id']) ?>">

      <div class="form-group">
        <label for="name"
          style="color: var(--primary); font-weight: 700; margin-bottom: 0.5rem; display: block;">Product Name</label>
        <input type="text" id="name" name="name" value="<?= htmlspecialchars($product['name']) ?>"
          style="width: 100%; padding: 1rem; border-radius: 1rem; border: 1px solid var(--border); font-family: inherit;">
      </div>

      <div class="form-group">
        <label for="description"
          style="color: var(--primary); font-weight: 700; margin-bottom: 0.5rem; display: block;">Description</label>
        <textarea id="description" name="description" rows="4"
          style="width: 100%; padding: 1rem; border-radius: 1rem; border: 1px solid var(--border); font-family: inherit; resize: vertical;"><?= htmlspecialchars($product['description'] ?? '') ?></textarea>
      </div>

      <div style="display: flex; gap: 1rem; margin-bottom: 1.5rem;">
        <div class="form-group" style="flex: 1; margin-bottom: 0;">
          <label for="price"
            style="color: var(--primary); font-weight: 700; margin-bottom: 0.5rem; display: block;">Price ($)</label>
          <input type="number" id="price" name="price" step="0.01" min="0"
            value="<?= htmlspecialchars($product['price']) ?>"
            style="width: 100%; padding: 1rem; border-radius: 1rem; border: 1px solid var(--border); font-family: inherit;">
        </div>

        <div class="form-group" style="flex: 1; margin-bottom: 0;">
          <label for="stock"
            style="color: var(--primary); font-weight: 700; margin-bottom: 0.5rem; display: block;">Stock
            Quantity</label>
          <input type="number" id="stock" name="stock" min="0" value="<?= htmlspecialchars($product['stock']) ?>"
            style="width: 100%; padding: 1rem; border-radius: 1rem; border: 1px solid var(--border); font-family: inherit;">
        </div>
      </div>

      <div class="form-group" style="margin-bottom: 1.5rem;">
        <label for="image"
          style="color: var(--primary); font-weight: 700; margin-bottom: 0.5rem; display: block;">Update Product Image
          (Optional)</label>
        <input type="file" id="image" name="image" accept="image/png, image/jpeg, image/gif, image/webp"
          style="width: 100%; padding: 1rem; border-radius: 1rem; border: 1px solid var(--border); font-family: inherit; background: white;">
        <?php if (!empty($product['image']) && $product['image'] !== 'default.png'): ?>
          <p style="font-size: 0.85rem; color: #64748b; margin-top: 0.5rem;">Current image:
            <?= htmlspecialchars($product['image']) ?></p>
        <?php endif; ?>
      </div>

      <div style="display: flex; gap: 1rem; margin-top: 2rem;">
        <a href="index.php?action=products" class="btn-signup"
          style="flex: 1; text-align: center; background: white; color: #64748b; border: 1px solid var(--border); box-shadow: none;">Cancel</a>
        <button type="submit" class="btn-signup" style="flex: 2; border: none; cursor: pointer;">Update Product</button>
      </div>
    </form>
  </div>
</div>

<?php include 'views/partials/footer.php'; ?>
