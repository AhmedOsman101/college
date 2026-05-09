<?php
$title = "Products Dashboard";
include 'views/partials/header.php';
?>

<div class="container" style="max-width: 1300px; margin: 4rem auto; padding: 0 4rem;">
  <div style="display: flex; justify-content: space-between; align-items: flex-end; margin-bottom: 3rem;">
    <div>
      <div class="badge-priority" style="margin-bottom: 1rem;">
        <svg width="14" height="14" fill="var(--secondary)" viewBox="0 0 24 24">
          <path
            d="M12 21.35l-1.45-1.32C5.4 15.36 2 12.28 2 8.5 2 5.42 4.42 3 7.5 3c1.74 0 3.41.81 4.5 2.09C13.09 3.81 14.76 3 16.5 3 19.58 3 22 5.42 22 8.5c0 3.78-3.4 6.86-8.55 11.54L12 21.35z" />
        </svg>
        <?= ($_SESSION['role'] ?? '') === 'admin' ? 'Inventory' : 'Shop' ?>
      </div>
      <?php if (($_SESSION['role'] ?? '') === 'admin'): ?>
        <h1 class="hero-title" style="font-size: 3.5rem; margin-bottom: 0;">Products <span
            class="italic-gold">Dashboard</span></h1>
      <?php else: ?>
        <h1 class="hero-title" style="font-size: 3.5rem; margin-bottom: 0;">Care <span class="italic-gold">Supplies</span>
        </h1>
        <p style="color: #64748b; margin-top: 0.5rem;">Browse quality medical and comfort items for daily living.</p>
      <?php endif; ?>
    </div>
    <div>
      <?php if (($_SESSION['role'] ?? '') === 'admin'): ?>
        <a href="index.php?action=create_product" class="btn-hero-primary"
          style="padding: 1rem 1.5rem; font-size: 0.95rem; display: inline-flex;">
          <svg width="18" height="18" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24"
            style="margin-right: 0.5rem;">
            <path d="M12 5v14M5 12h14" />
          </svg>
          Add Product
        </a>
      <?php endif; ?>
    </div>
  </div>

  <?php if (isset($_SESSION['flash'])): ?>
    <div
      style="background: <?= $_SESSION['flash']['type'] === 'success' ? '#ecfdf5' : '#fee2e2' ?>; color: <?= $_SESSION['flash']['type'] === 'success' ? '#065f46' : '#991b1b' ?>; padding: 1rem 1.5rem; border-radius: 1rem; margin-bottom: 2rem; font-weight: 700;">
      <?= $_SESSION['flash']['message'] ?>
    </div>
    <?php unset($_SESSION['flash']); ?>
  <?php endif; ?>

  <div class="fade-up-stagger"
    style="display: grid; grid-template-columns: repeat(auto-fill, minmax(300px, 1fr)); gap: 2rem;">
    <?php
    $hasProducts = !empty($products);
    if ($hasProducts):
      foreach ($products as $row):
        $imgPath = (!empty($row['image']) && $row['image'] !== 'default.png') ? 'uploads/' . $row['image'] : 'assets/img/default.png';
        ?>
        <div class="auth-card fade-up"
          style="margin-top: 0; padding: 0; overflow: hidden; border-radius: 1.5rem; display: flex; flex-direction: column;">
          <div
            style="height: 200px; background: white; overflow: hidden; display: flex; align-items: center; justify-content: center; border-bottom: 1px solid var(--border);">
            <img src="<?= htmlspecialchars($imgPath) ?>" alt="<?= htmlspecialchars($row['name']) ?>"
              style="width: 100%; height: 100%; object-fit: cover;">
          </div>

          <div style="padding: 1.5rem; flex: 1; display: flex; flex-direction: column;">
            <div style="display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 0.5rem;">
              <h3 style="font-size: 1.25rem; color: var(--foreground); font-family: 'Playfair Display', serif; margin: 0;">
                <?= htmlspecialchars($row['name']) ?>
              </h3>
              <span style="font-weight: 800; color: var(--primary);">$<?= number_format($row['price'], 2) ?></span>
            </div>

            <div
              style="color: #64748b; font-size: 0.85rem; margin-bottom: 1.5rem; display: flex; align-items: center; gap: 0.5rem;">
              <div
                style="width: 8px; height: 8px; border-radius: 50%; background: <?= $row['stock'] > 10 ? '#10b981' : ($row['stock'] > 0 ? '#f59e0b' : '#ef4444') ?>;">
              </div>
              <?= $row['stock'] ?> in stock
            </div>

            <div style="margin-top: auto; display: flex; flex-direction: column; gap: 0.5rem;">


              <?php if (isset($_SESSION['user_id']) && ($_SESSION['role'] ?? '') === 'admin'): ?>
                <div style="display: flex; gap: 0.5rem; margin-top: 0.5rem;">
                  <a href="index.php?action=edit_product&id=<?= $row['id'] ?>" class="btn-signup"
                    style="flex: 1; text-align: center; padding: 0.6rem; font-size: 0.8rem; background: var(--secondary); box-shadow: none;">Edit</a>
                  <a href="index.php?action=delete_product&id=<?= $row['id'] ?>" class="btn-signup"
                    style="flex: 1; text-align: center; padding: 0.6rem; font-size: 0.8rem; background: white; border: 1px solid #fee2e2; color: #ef4444; box-shadow: none;"
                    onclick="return confirm('Are you sure you want to delete this product?')">Delete</a>
                </div>
              <?php endif; ?>
            </div>
          </div>
        </div>
      <?php endforeach; else: ?>
      <div
        style="grid-column: 1 / -1; background: white; border-radius: 2rem; padding: 4rem; text-align: center; box-shadow: 0 10px 30px rgba(0,0,0,0.02);">
        <svg width="48" height="48" fill="none" stroke="#cbd5e1" stroke-width="1.5" viewBox="0 0 24 24"
          style="margin-bottom: 1rem;">
          <path stroke-linecap="round" stroke-linejoin="round"
            d="M20 7l-8-4-8 4m16 0l-8 4m8-4v10l-8 4m0-10L4 7m8 4v10M4 7v10l8 4" />
        </svg>
        <h3 style="font-size: 1.5rem; color: #64748b; margin-bottom: 0.5rem; font-family: 'Playfair Display', serif;">No
          Products Found</h3>
        <?php if (($_SESSION['role'] ?? '') === 'admin'): ?>
          <p style="color: #94a3b8;">Start by adding your first product to the inventory.</p>
          <a href="index.php?action=create_product" class="btn-signup"
            style="display: inline-block; margin-top: 1.5rem;">Add Product</a>
        <?php else: ?>
          <p style="color: #94a3b8;">No products are available at the moment. Please check back later.</p>
        <?php endif; ?>
      </div>
    <?php endif; ?>
  </div>
</div>

<?php include 'views/partials/footer.php'; ?>
