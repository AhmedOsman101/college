<?php
$title = "About Us";
include 'views/partials/header.php';
?>

<main style="background-color: var(--bg-surface);">
  <!-- Hero & Mission Section -->
  <section class="section bg-pattern" style="padding-top: 5rem; padding-bottom: 5rem;">
    <div class="container fade-up">

      <div style="text-align: center; margin-bottom: 4rem;">
        <div class="badge"
          style="background: rgba(30,58,74,0.05); border: 1px solid rgba(30,58,74,0.1); display: inline-flex; margin-bottom: 1.5rem;">
          <span style="color: var(--accent-gold);">✨</span> OUR STORY & VISION
        </div>

        <h1 class="hero-title" style="font-size: 4rem; line-height: 1.1; margin-bottom: 1.5rem;">
          Restoring <span class="italic-gold" style="color: var(--primary-dark);">Dignity</span><br>
          to Aging.
        </h1>

        <p class="hero-subtitle" style="max-width: 650px; margin: 0 auto;">
          ElderCare was founded on a simple truth: our seniors are our legacy. We've built a bridge of compassion to
          ensure their golden years are supported by a community that truly cares.
        </p>
      </div>

      <div class="about-mission-grid">
        <!-- Left Side Text -->
        <div class="fade-up" style="transition-delay: 0.2s;">
          <h2
            style="font-size: 2.5rem; line-height: 1.2; margin-bottom: 1.5rem; font-family: var(--font-heading); font-weight: 800; color: var(--primary-dark);">
            Our Mission<br>Beyond Borders.
          </h2>
          <p style="color: var(--text-muted); line-height: 1.8; margin-bottom: 2.5rem;">
            We believe that aging should be a journey filled with support, comfort, and connection. ElderCare bridges
            the gap between seniors who need assistance and the community ready to help.
          </p>

          <div class="mission-feature">
            <div class="mission-feature-icon">
              <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M16 21v-2a4 4 0 0 0-4-4H6a4 4 0 0 0-4 4v2" />
                <circle cx="9" cy="7" r="4" />
                <path d="M22 21v-2a4 4 0 0 0-3-3.87" />
                <path d="M16 3.13a4 4 0 0 1 0 7.75" />
              </svg>
            </div>
            <div class="mission-feature-text">
              <h4>Community Pickups</h4>
              <p>Free professional pickup for all donations.</p>
            </div>
          </div>

          <div class="mission-feature">
            <div class="mission-feature-icon">
              <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M12 22s8-4 8-10V5l-8-3-8 3v7c0 6 8 10 8 10z" />
                <path d="m9 12 2 2 4-4" />
              </svg>
            </div>
            <div class="mission-feature-text">
              <h4>Verified Facilities</h4>
              <p>All partner care homes undergo strict vetting.</p>
            </div>
          </div>

          <button class="btn btn-primary"
            style="margin-top: 1rem; border-radius: var(--radius-pill); padding: 12px 32px;">
            Explore Services
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"
              style="margin-left: 8px;">
              <path d="M5 12h14" />
              <path d="m12 5 7 7-7 7" />
            </svg>
          </button>
        </div>

        <!-- Right Side Stats Bento -->
        <div class="stats-bento-grid fade-up-stagger">
          <div class="stat-bento-card stat-bento-dark">
            <div class="stat-val-wrap"><span class="stat-number" data-target="10000">0</span>+</div>
            <div class="stat-title">Seniors Helped</div>
            <div class="stat-desc">IMPACTED ACROSS ALL REGIONS</div>
          </div>
          <div class="stat-bento-card stat-bento-gold">
            <div class="stat-val-wrap"><span class="stat-number" data-target="500">0</span>+</div>
            <div class="stat-title">Care Homes</div>
            <div class="stat-desc">VERIFIED PARTNER FACILITIES</div>
          </div>
          <div class="stat-bento-card stat-bento-muted">
            <div class="stat-val-wrap"><span class="stat-number" data-target="25000">0</span>+</div>
            <div class="stat-title">Supplies</div>
            <div class="stat-desc">DONATED AND DISTRIBUTED</div>
          </div>
          <div class="stat-bento-card stat-bento-white">
            <div class="stat-val-wrap"><span class="stat-number" data-target="100">0</span>+</div>
            <div class="stat-title">Nodes</div>
            <div class="stat-desc">ACTIVE COMMUNITY HUBS</div>
          </div>
        </div>
      </div>
    </div>
  </section>

  <!-- Core Principles Section -->
  <section class="section" style="background: #fdfdfd; padding-top: 4rem; padding-bottom: 6rem;">
    <div class="container">
      <div class="section-header-center fade-up">
        <h2>Core Principles</h2>
        <p>Our culture is built upon these values that guide every interaction.</p>
      </div>

      <div class="principles-grid fade-up-stagger">
        <div class="principle-card">
          <div class="principle-icon" style="background: rgba(239, 68, 68, 0.1); color: #ef4444;">
            <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
              <path
                d="M19 14c1.49-1.46 3-3.21 3-5.5A5.5 5.5 0 0 0 16.5 3c-1.76 0-3 .5-4.5 2-1.5-1.5-2.74-2-4.5-2A5.5 5.5 0 0 0 2 8.5c0 2.3 1.5 4.05 3 5.5l7 7Z" />
            </svg>
          </div>
          <h3>Compassion</h3>
          <p>We believe every senior deserves care, dignity, and respect. Our work is driven by genuine love for the
            elderly community.</p>
        </div>

        <div class="principle-card">
          <div class="principle-icon" style="background: rgba(59, 130, 246, 0.1); color: #3b82f6;">
            <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
              <circle cx="12" cy="12" r="10" />
              <path d="M12 2a14.5 14.5 0 0 0 0 20 14.5 14.5 0 0 0 0-20" />
              <path d="M2 12h20" />
            </svg>
          </div>
          <h3>Community</h3>
          <p>Together, we create a network of support that connects caregivers, volunteers, donors, and families.</p>
        </div>

        <div class="principle-card">
          <div class="principle-icon" style="background: rgba(245, 158, 11, 0.1); color: #f59e0b;">
            <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
              <circle cx="12" cy="12" r="10" />
              <circle cx="12" cy="12" r="4" />
              <circle cx="12" cy="12" r="1" />
            </svg>
          </div>
          <h3>Accessibility</h3>
          <p>We ensure that essential supplies and resources are available to all seniors, regardless of their
            circumstances.</p>
        </div>

        <div class="principle-card">
          <div class="principle-icon" style="background: rgba(16, 185, 129, 0.1); color: #10b981;">
            <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
              <path
                d="M3.85 8.62a4 4 0 0 1 4.78-4.77 4 4 0 0 1 6.74 0 4 4 0 0 1 4.78 4.78 4 4 0 0 1 0 6.74 4 4 0 0 1-4.77 4.78 4 4 0 0 1-6.75 0 4 4 0 0 1-4.78-4.77 4 4 0 0 1 0-6.76Z" />
              <path d="m9 12 2 2 4-4" />
            </svg>
          </div>
          <h3>Quality</h3>
          <p>Every product we offer meets high standards of safety and reliability, because our seniors deserve the
            best.</p>
        </div>
      </div>
    </div>
  </section>

  <!-- Join Our Mission (Contact) Section -->
  <section class="section bg-pattern" style="padding-top: 4rem; padding-bottom: 6rem;">
    <div class="container fade-up">
      <div class="contact-wrapper">

        <!-- Left Info Panel -->
        <div class="contact-info-panel">
          <h2 style="font-family: var(--font-heading); font-weight: 800;">Join Our<br>Mission.</h2>
          <p>Whether you're looking to donate, volunteer, or find care solutions, our dedicated team is ready to assist
            you in every step.</p>

          <div class="contact-detail">
            <div class="contact-detail-icon">
              <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path
                  d="M22 16.92v3a2 2 0 0 1-2.18 2 19.79 19.79 0 0 1-8.63-3.07 19.5 19.5 0 0 1-6-6 19.79 19.79 0 0 1-3.07-8.67A2 2 0 0 1 4.11 2h3a2 2 0 0 1 2 1.72 12.84 12.84 0 0 0 .7 2.81 2 2 0 0 1-.45 2.11L8.09 9.91a16 16 0 0 0 6 6l1.27-1.27a2 2 0 0 1 2.11-.45 12.84 12.84 0 0 0 2.81.7A2 2 0 0 1 22 16.92z" />
              </svg>
            </div>
            <div>
              <div class="contact-detail-label">OPERATIONS SUPPORT</div>
              <div class="contact-detail-value">+1-800-CARE-NOW</div>
            </div>
          </div>

          <div class="contact-detail">
            <div class="contact-detail-icon">
              <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <rect width="20" height="16" x="2" y="4" rx="2" />
                <path d="m22 7-8.97 5.7a1.94 1.94 0 0 1-2.06 0L2 7" />
              </svg>
            </div>
            <div>
              <div class="contact-detail-label">GENERAL INQUIRIES</div>
              <div class="contact-detail-value">help@eldercare.org</div>
            </div>
          </div>

          <div class="contact-detail">
            <div class="contact-detail-icon">
              <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M20 10c0 6-8 12-8 12s-8-6-8-12a8 8 0 0 1 16 0Z" />
                <circle cx="12" cy="10" r="3" />
              </svg>
            </div>
            <div>
              <div class="contact-detail-label">OUR LOCATION</div>
              <div class="contact-detail-value">San Francisco, CA HUB</div>
            </div>
          </div>
        </div>

        <!-- Right Form Panel -->
        <div class="contact-form-panel">
          <form action="#" method="POST"
            onsubmit="event.preventDefault(); Swal.fire('Success', 'Your message has been sent successfully.', 'success');">
            <div class="form-grid">
              <div class="form-group">
                <label for="name">FULL NAME</label>
                <input type="text" id="name" class="form-input" placeholder="John Doe" required>
              </div>
              <div class="form-group">
                <label for="email">EMAIL ADDRESS</label>
                <input type="email" id="email" class="form-input" placeholder="john@example.com" required>
              </div>
            </div>
            <div class="form-group" style="margin-bottom: 2rem;">
              <label for="message">MESSAGE</label>
              <textarea id="message" class="form-input" rows="5" placeholder="How can we help your journey?"
                required></textarea>
            </div>
            <button type="submit" class="btn btn-primary"
              style="width: 100%; border-radius: var(--radius-md); padding: 16px;">
              Send Secure Message
            </button>
          </form>
        </div>

      </div>
    </div>
  </section>
</main>

<?php include 'views/partials/footer.php'; ?>
