</div> <!-- Close main-content -->

<footer class="main-footer">
  <div class="footer-container">
    <!-- Brand Column -->
    <div class="footer-column">
      <a href="index.php?action=home" class="footer-logo">
        <div class="logo-icon">
          <svg width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="#2b4c6a" stroke-width="2">
            <path
              d="M12 21.35l-1.45-1.32C5.4 15.36 2 12.28 2 8.5 2 5.42 4.42 3 7.5 3c1.74 0 3.41.81 4.5 2.09C13.09 3.81 14.76 3 16.5 3 19.58 3 22 5.42 22 8.5c0 3.78-3.4 6.86-8.55 11.54L12 21.35z" />
          </svg>
        </div>
        <div class="logo-text">ElderCare</div>
      </a>
      <p class="footer-tagline">
        Supporting the elderly with care, comfort, and essential needs since 2026.
      </p>
      <div class="footer-contact-info">
        <div class="footer-contact-item">
          <svg width="18" height="18" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24">
            <path
              d="M3 5a2 2 0 012-2h3.28a1 1 0 01.948.684l1.498 4.493a1 1 0 01-.502 1.21l-2.257 1.13a11.042 11.042 0 005.516 5.516l1.13-2.257a1 1 0 011.21-.502l4.493 1.498a1 1 0 01.684.949V19a2 2 0 01-2 2h-1C9.716 21 3 14.284 3 6V5z" />
          </svg>
          1-800-ELDER-CARE
        </div>
        <div class="footer-contact-item">
          <svg width="18" height="18" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24">
            <path
              d="M3 8l7.89 5.26a2 2 0 002.22 0L21 8M5 19h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v10a2 2 0 002 2z" />
          </svg>
          help@eldercare.org
        </div>
        <div class="footer-contact-item">
          <svg width="18" height="18" fill="none" stroke="currentColor" stroke-width="2" viewBox="0 0 24 24">
            <path d="M17.657 16.657L13.414 20.9a1.998 1.998 0 01-2.827 0l-4.244-4.243a8 8 0 1111.314 0z" />
            <path d="M15 11a3 3 0 11-6 0 3 3 0 016 0z" />
          </svg>
          Serving Communities Nationwide
        </div>
      </div>
    </div>

    <!-- Company Column -->
    <div class="footer-column">
      <h4 class="footer-heading">Company</h4>
      <ul class="footer-nav">
        <li><a href="#">About Us</a></li>
        <li><a href="#">Our Mission</a></li>
        <li><a href="#">Contact</a></li>
      </ul>
    </div>

    <!-- Services Column -->
    <div class="footer-column">
      <h4 class="footer-heading">Services</h4>
      <ul class="footer-nav">
        <li><a href="index.php?action=products">Supplies Catalog</a></li>
        <li><a href="#">Donate Items</a></li>
        <li><a href="index.php?action=locations">Find Care Homes</a></li>
      </ul>
    </div>

    <!-- Legal Column -->
    <div class="footer-column">
      <h4 class="footer-heading">Legal</h4>
      <ul class="footer-nav">
        <li><a href="#">Privacy Policy</a></li>
        <li><a href="#">Terms of Service</a></li>
        <li><a href="#">Accessibility</a></li>
      </ul>
    </div>
  </div>

  <div class="footer-bottom">
    <div>&copy; 2026 Elder Care. All rights reserved.</div>
    <div>
      Made with <span class="heart-gold">❤</span> for our seniors
    </div>
  </div>
</footer>

<!-- SweetAlert2 Library for beautiful popup dialogs -->
<script src="https://cdn.jsdelivr.net/npm/sweetalert2@11"></script>

<script>
  document.addEventListener("DOMContentLoaded", function () {
    // Scroll animations and counter
    const observer = new IntersectionObserver((entries) => {
      entries.forEach(entry => {
        if (entry.isIntersecting) {
          entry.target.classList.add('visible');

          // Check if this element contains stat numbers to animate
          const statNumbers = entry.target.querySelectorAll('.stat-number');
          if (statNumbers.length > 0 && !entry.target.classList.contains('counted')) {
            entry.target.classList.add('counted');
            statNumbers.forEach(stat => {
              const target = parseInt(stat.getAttribute('data-target'));
              const duration = 2000; // 2 seconds
              const step = target / (duration / 16); // 60fps
              let current = 0;

              const updateCounter = () => {
                current += step;
                if (current < target) {
                  stat.innerText = Math.ceil(current).toLocaleString();
                  requestAnimationFrame(updateCounter);
                } else {
                  stat.innerText = target.toLocaleString();
                }
              };
              updateCounter();
            });
          }
        }
      });
    }, { threshold: 0.1 });

    document.querySelectorAll('.fade-up, .fade-up-stagger').forEach(el => {
      observer.observe(el);
    });

    // Auto-hide alert messages after 5 seconds
    const alerts = document.querySelectorAll('.alert');
    alerts.forEach(function (alert) {
      setTimeout(function () {
        alert.style.transition = 'opacity 0.5s ease';
        alert.style.opacity = '0';
        setTimeout(function () {
          alert.style.display = 'none';
        }, 500);
      }, 5000);
    });

    // Replace standard confirm() with SweetAlert2 for forms
    const deleteForms = document.querySelectorAll('form[action*="delete"], form[action*="remove"]');
    deleteForms.forEach(function (form) {
      form.addEventListener('submit', function (e) {
        e.preventDefault();
        Swal.fire({
          title: 'Are you sure?',
          text: "You won't be able to revert this!",
          icon: 'warning',
          showCancelButton: true,
          confirmButtonColor: '#ef4444',
          cancelButtonColor: '#64748b',
          confirmButtonText: 'Yes, proceed!'
        }).then((result) => {
          if (result.isConfirmed) {
            form.submit();
          }
        });
      });
    });

    // Replace standard confirm() with SweetAlert2 for links
    const deleteLinks = document.querySelectorAll('a[href*="delete"], a[href*="remove"]');
    deleteLinks.forEach(function (link) {
      link.addEventListener('click', function (e) {
        e.preventDefault();
        const targetUrl = this.getAttribute('href');
        Swal.fire({
          title: 'Are you sure?',
          text: "Do you want to proceed with this action?",
          icon: 'warning',
          showCancelButton: true,
          confirmButtonColor: '#ef4444',
          cancelButtonColor: '#64748b',
          confirmButtonText: 'Yes, proceed!'
        }).then((result) => {
          if (result.isConfirmed) {
            window.location.href = targetUrl;
          }
        });
      });
    });
  });
</script>
</body>

</html>
