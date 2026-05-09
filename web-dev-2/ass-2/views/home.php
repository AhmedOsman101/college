<?php
$title = "Dashboard";
include __DIR__ . '/partials/header.php';
?>

<main>

  <!-- Hero Section -->
  <section class="section bg-pattern" style="padding-top: 4rem; padding-bottom: 6rem;">
    <div class="container hero-layout">

      <!-- Left content -->
      <div class="fade-up">
        <div class="badge">
          <span class="badge-gold">💛</span> COMPASSION PRIORITY
        </div>

        <h1 class="hero-title">
          Every <span class="underline text-primary">Senior</span><br>
          Lives with<br>
          <span class="text-gold">Dignity.</span>
        </h1>

        <p class="hero-subtitle">
          We bridge the gap between those who care and those who need, providing essential mobility and medical support
          for our global elder community.
        </p>

        <div class="hero-actions">
          <button class="btn btn-primary" style="border-radius: var(--radius-md);">
            Get Supplies
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"
              style="margin-left: 8px;">
              <path d="m5 12h14" />
              <path d="m12 5 7 7-7 7" />
            </svg>
          </button>
          <button class="btn btn-outline" style="border-radius: var(--radius-md); background: white;">
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"
              style="margin-right: 8px; color: var(--accent-gold);">
              <rect x="3" y="8" width="18" height="4" rx="1" />
              <path d="M12 8v13" />
              <path d="M19 12v7a2 2 0 0 1-2 2H7a2 2 0 0 1-2-2v-7" />
              <path d="M7.5 8a2.5 2.5 0 0 1 0-5A4.8 8 0 0 1 12 8a4.8 8 0 0 1 4.5-5 2.5 2.5 0 0 1 0 5" />
            </svg>
            Give Back
          </button>
        </div>

        <div class="social-proof">
          <div class="avatars">
            <img src="https://i.pravatar.cc/150?img=1" alt="User">
            <img src="https://i.pravatar.cc/150?img=2" alt="User">
            <img src="https://i.pravatar.cc/150?img=3" alt="User">
            <img src="https://i.pravatar.cc/150?img=4" alt="User">
          </div>
          <div>
            <div class="stars">★★★★★</div>
            <div style="font-size: 0.8rem; font-weight: 700; color: var(--text-primary);">5,000+ Verified Reviews</div>
          </div>
        </div>
      </div>

      <!-- Right image -->
      <div class="hero-image-wrapper fade-up" style="transition-delay: 0.2s;">
        <div class="hero-image-card"
          style="border: 12px solid var(--bg-surface); border-radius: var(--radius-xl); overflow: hidden;">
          <img src="assets/img/hero-illustration.jpg" alt="Elder Care Illustration"
            style="width: 100%; height: auto; display: block;">
        </div>

        <!-- Impact Badge -->
        <div class="hero-badge-impact"
          style="background: white; border: none; padding: 1.25rem 1.5rem; bottom: -20px; left: -30px; box-shadow: var(--shadow-lg);">
          <div class="hero-badge-icon"
            style="background: var(--primary-dark); border-radius: var(--radius-sm); width: 48px; height: 48px;">
            <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
              <path d="M16 21v-2a4 4 0 0 0-4-4H6a4 4 0 0 0-4 4v2" />
              <circle cx="9" cy="7" r="4" />
              <path d="M22 21v-2a4 4 0 0 0-3-3.87" />
              <path d="M16 3.13a4 4 0 0 1 0 7.75" />
            </svg>
          </div>
          <div>
            <div
              style="font-family: var(--font-heading); font-size: 1.5rem; font-weight: 800; line-height: 1; color: var(--primary-dark);">
              10,000+</div>
            <div
              style="font-size: 0.65rem; color: var(--text-muted); font-weight: 700; letter-spacing: 1px; text-transform: uppercase;">
              LIVES IMPACTED</div>
          </div>
        </div>

        <!-- Goal Badge -->
        <div class="hero-badge-goal"
          style="top: 40px; right: 20px; padding: 1.5rem; background: rgba(255,255,255,0.7); backdrop-filter: blur(20px);">
          <div
            style="font-size: 0.65rem; font-weight: 800; color: var(--primary-dark); letter-spacing: 1px; margin-bottom: 0.5rem; text-transform: uppercase;">
            IMPACT GOAL</div>
          <div
            style="font-family: var(--font-body); font-size: 2.5rem; font-weight: 800; color: var(--primary-dark); line-height: 1;">
            85%</div>
          <div
            style="width: 120px; height: 6px; background: rgba(0,0,0,0.1); border-radius: 4px; margin-top: 0.8rem; overflow: hidden;">
            <div style="width: 85%; height: 100%; background: var(--primary-dark); border-radius: 4px;"></div>
          </div>
        </div>
      </div>

    </div>
  </section>

  <!-- Stats Section -->
  <section class="section section-dark pt-0" style="padding-top: var(--space-8); padding-bottom: var(--space-12);">
    <div class="container">
      <div class="stats-row fade-up-stagger">
        <div class="stat-card-blue">
          <div class="stat-number-wrap"><span class="stat-number" data-target="9996">0</span><span
              class="stat-plus">+</span></div>
          <div class="stat-label">SENIORS HELPED</div>
        </div>
        <div class="stat-card-blue">
          <div class="stat-number-wrap"><span class="stat-number" data-target="499">0</span><span
              class="stat-plus">+</span></div>
          <div class="stat-label">CARE HOMES</div>
        </div>
        <div class="stat-card-blue">
          <div class="stat-number-wrap"><span class="stat-number" data-target="24991">0</span><span
              class="stat-plus">+</span></div>
          <div class="stat-label">ITEMS DONATED</div>
        </div>
        <div class="stat-card-blue">
          <div class="stat-number-wrap"><span class="stat-number" data-target="99">0</span><span
              class="stat-plus">+</span></div>
          <div class="stat-label">COMMUNITIES</div>
        </div>
      </div>
    </div>
  </section>

  <!-- Empowering Seniors Bento Grid Section -->
  <section class="section section-muted">
    <div class="container">

      <div class="bento-header fade-up">
        <div>
          <div class="badge" style="background: rgba(30,58,74,0.05); border: 1px solid rgba(30,58,74,0.1);">
            <span style="color: var(--primary-dark);">●</span> OUR SERVICE PILLARS
          </div>
          <h2 class="bento-title">Empowering Seniors with <span class="text-gold">Holistic Care Tools.</span></h2>
        </div>
        <p class="bento-subtitle">More than just supplies — we build a supportive ecosystem where dignity, health, and
          community converge to serve our elders.</p>
      </div>

      <div class="bento-grid-complex fade-up-stagger">

        <!-- Left Large Card -->
        <div class="bento-large">
          <div class="icon-wrap">
            <svg xmlns="http://www.w3.org/2000/svg" width="36" height="36" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
              <circle cx="16" cy="4" r="1" />
              <path d="m18 19 1-7-6 1" />
              <path d="m5 8 3-3 5.5 3-2.36 3.5" />
              <path d="M4.24 14.5a5 5 0 0 0 6.88 6" />
              <path d="M13.76 17.5a5 5 0 0 0-6.88-6" />
            </svg>
          </div>
          <h3>Revolutionizing Mobility</h3>
          <p>Our comprehensive catalog of advanced wheelchairs, smart walkers, and ergonomic canes is curated to restore
            independence and confidence in every step.</p>

          <div style="display: flex; align-items: center; gap: 12px; margin-top: 2rem;">
            <div class="avatars">
              <img src="https://i.pravatar.cc/150?img=5" alt="User">
              <img src="https://i.pravatar.cc/150?img=6" alt="User">
              <img src="https://i.pravatar.cc/150?img=7" alt="User">
            </div>
            <span style="font-size: 0.85rem; font-weight: 700; color: rgba(255,255,255,0.9);">Trusted by 5,000+
              seniors</span>
          </div>
        </div>

        <!-- Right Top Small Card -->
        <div class="bento-small bento-small-white">
          <div class="icon-wrap">
            <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
              <path
                d="M4.8 2.3A.3.3 0 1 0 5 2H4a2 2 0 0 0-2 2v5a6 6 0 0 0 6 6v0a6 6 0 0 0 6-6V4a2 2 0 0 0-2-2h-1a.2.2 0 1 0 .3.3" />
              <path d="M8 15v1a6 6 0 0 0 6 6v0a6 6 0 0 0 6-6v-4" />
              <circle cx="20" cy="10" r="2" />
            </svg>
          </div>
          <div>
            <h3 style="color: var(--text-primary);">Health Precision</h3>
            <p style="color: var(--text-muted);">Professional-grade monitoring tools for early detection and daily
              management.</p>
          </div>
        </div>

        <!-- Right Bottom Small Card -->
        <div class="bento-small bento-small-gold">
          <div class="icon-wrap">
            <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
              stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
              <rect x="3" y="8" width="18" height="4" rx="1" />
              <path d="M12 8v13" />
              <path d="M19 12v7a2 2 0 0 1-2 2H7a2 2 0 0 1-2-2v-7" />
              <path d="M7.5 8a2.5 2.5 0 0 1 0-5A4.8 8 0 0 1 12 8a4.8 8 0 0 1 4.5-5 2.5 2.5 0 0 1 0 5" />
            </svg>
          </div>
          <div>
            <h3>Direct Donation</h3>
            <p>Seamlessly contribute essentials to certified care homes in your region.</p>
          </div>
        </div>

        <!-- Bottom Wide Card -->
        <div class="bento-wide">
          <div>
            <div
              style="font-size: 0.7rem; font-weight: 800; letter-spacing: 1px; color: var(--text-muted); background: rgba(0,0,0,0.05); padding: 4px 12px; border-radius: 12px; display: inline-block; margin-bottom: 12px; text-transform: uppercase;">
              NEAR YOU</div>
            <h3 style="color: var(--text-primary);">Intelligent Care Home Discovery</h3>
            <p>Connect with over 500+ verified elderly communities. Our smart mapping system shows real-time
              availability and service details.</p>
          </div>
          <div style="display: flex; align-items: center; gap: 16px;">
            <button class="btn btn-outline" style="border-radius: var(--radius-pill); background: var(--bg-surface);">
              Explore Map
              <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"
                style="margin-left: 4px;">
                <path d="m22 2-7 20-4-9-9-4Z" />
                <path d="M22 2 11 13" />
              </svg>
            </button>
            <div
              style="width: 64px; height: 64px; background: rgba(30,58,74,0.1); border-radius: var(--radius-md); display: flex; align-items: center; justify-content: center; color: var(--primary-dark);">
              <svg xmlns="http://www.w3.org/2000/svg" width="28" height="28" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path d="M20 10c0 6-8 12-8 12s-8-6-8-12a8 8 0 0 1 16 0Z" />
                <circle cx="12" cy="10" r="3" />
              </svg>
            </div>
          </div>
        </div>

      </div>
    </div>
  </section>



  <!-- Generosity Section -->
  <section class="section">
    <div class="container generosity-layout">

      <!-- Left text content -->
      <div class="fade-up">
        <div class="badge"
          style="background: rgba(184, 148, 46, 0.1); border-color: rgba(184, 148, 46, 0.2); color: var(--accent-gold);">
          💛 IMPACT THAT LASTS
        </div>

        <h2 class="gen-title">
          Your Generosity,<br>
          <span class="text-gold" style="color: var(--primary-dark);">Their Independence.</span>
        </h2>

        <p class="gen-desc">
          Don't let your unused mobility aids sit in storage. Your donation connects directly with seniors who lack the
          basic tools for daily dignity. Join our community of <strong
            style="color: var(--text-primary); border-bottom: 2px solid rgba(184, 148, 46, 0.4);">10,000+
            donors</strong> today.
        </p>

        <div style="display: flex; gap: 1rem; margin-bottom: 2rem;">
          <button class="btn btn-primary">Start Donation <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16"
              viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"
              stroke-linejoin="round" style="margin-left: 4px;">
              <path d="M5 12h14" />
              <path d="m12 5 7 7-7 7" />
            </svg></button>
          <button class="btn btn-outline" style="background: transparent;">Our Process</button>
        </div>

        <div class="transparency-hub">
          <div class="hub-title">LIVE TRANSPARENCY HUB</div>
          <div class="hub-stats">
            <div>
              <div class="hub-stat-num" style="color: var(--primary-dark);">2,540</div>
              <div class="hub-stat-label">MOBILITY AIDS</div>
            </div>
            <div>
              <div class="hub-stat-num" style="color: var(--accent-gold);">15.2k</div>
              <div class="hub-stat-label">CARE KITS</div>
            </div>
            <div>
              <div class="hub-stat-num" style="color: var(--text-primary);">100+</div>
              <div class="hub-stat-label">COMMUNITIES</div>
            </div>
          </div>
        </div>
      </div>

      <!-- Right offset grid -->
      <div class="offset-grid fade-up-stagger">
        <div>
          <!-- Card 1 -->
          <div class="offset-card">
            <div class="icon-wrap">
              <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <circle cx="16" cy="4" r="1" />
                <path d="m18 19 1-7-6 1" />
                <path d="m5 8 3-3 5.5 3-2.36 3.5" />
                <path d="M4.24 14.5a5 5 0 0 0 6.88 6" />
                <path d="M13.76 17.5a5 5 0 0 0-6.88-6" />
              </svg>
            </div>
            <h3 style="color: var(--text-primary);">Mobility</h3>
            <p>Providing wheelchairs, walkers, and canes to regain movement.</p>
          </div>
          <!-- Card 2 -->
          <div class="offset-card">
            <div class="icon-wrap">
              <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path
                  d="M4.8 2.3A.3.3 0 1 0 5 2H4a2 2 0 0 0-2 2v5a6 6 0 0 0 6 6v0a6 6 0 0 0 6-6V4a2 2 0 0 0-2-2h-1a.2.2 0 1 0 .3.3" />
                <path d="M8 15v1a6 6 0 0 0 6 6v0a6 6 0 0 0 6-6v-4" />
                <circle cx="20" cy="10" r="2" />
              </svg>
            </div>
            <h3 style="color: var(--text-primary);">Diagnostics</h3>
            <p>Monitoring tools that keep seniors safe in their own homes.</p>
          </div>
        </div>

        <div class="offset-col-2">
          <!-- Card 3 -->
          <div class="offset-card">
            <div class="icon-wrap">
              <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <rect x="3" y="8" width="18" height="4" rx="1" />
                <path d="M12 8v13" />
                <path d="M19 12v7a2 2 0 0 1-2 2H7a2 2 0 0 1-2-2v-7" />
                <path d="M7.5 8a2.5 2.5 0 0 1 0-5A4.8 8 0 0 1 12 8a4.8 8 0 0 1 4.5-5 2.5 2.5 0 0 1 0 5" />
              </svg>
            </div>
            <h3 style="color: var(--text-primary);">Comfort</h3>
            <p>Daily aids that transform routine tasks into easy successes.</p>
          </div>
          <!-- Card 4 -->
          <div class="offset-card">
            <div class="icon-wrap">
              <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none"
                stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
                <path
                  d="M19 14c1.49-1.46 3-3.21 3-5.5A5.5 5.5 0 0 0 16.5 3c-1.76 0-3 .5-4.5 2-1.5-1.5-2.74-2-4.5-2A5.5 5.5 0 0 0 2 8.5c0 2.3 1.5 4.05 3 5.5l7 7Z" />
              </svg>
            </div>
            <h3 style="color: var(--text-primary);">Personal Care</h3>
            <p>Essential hygiene kits that preserve dignity and wellness.</p>
          </div>
        </div>
      </div>

    </div>
  </section>

</main>



<?php include __DIR__ . '/partials/footer.php'; ?>
