class CosmicWebsite {
    constructor() {
        this.particles = [];
        this.particleCount = 100;
        this.canvas = null;
        this.ctx = null;
        this.mouse = { x: 0, y: 0 };
        this.isAudioPlaying = false;

        this.init();
    }

    init() {
        // Wait for DOM to load
        if (document.readyState === 'loading') {
            document.addEventListener('DOMContentLoaded', () => this.setup());
        } else {
            this.setup();
        }
    }

    setup() {
        this.setupParticleSystem();
        this.setupCustomCursor();
        this.setupSmoothScrolling();
        this.setupNavigationEffects();
        this.setupFormAnimations();
        this.setupTiltEffect();
        this.setupIntersectionObserver();
        this.setupAudioControl();
        this.setupResponsiveNavigation();
        this.setupGlitchEffect();
    }

    // Particle System
    setupParticleSystem() {
        this.canvas = document.getElementById('particle-canvas');
        if (!this.canvas) return;

        this.ctx = this.canvas.getContext('2d');
        this.resizeCanvas();

        window.addEventListener('resize', () => this.resizeCanvas());

        this.createParticles();
        this.animateParticles();
    }

    resizeCanvas() {
        this.canvas.width = window.innerWidth;
        this.canvas.height = window.innerHeight;
    }

    createParticles() {
        this.particles = [];
        for (let i = 0; i < this.particleCount; i++) {
            this.particles.push({
                x: Math.random() * this.canvas.width,
                y: Math.random() * this.canvas.height,
                vx: (Math.random() - 0.5) * 0.5,
                vy: (Math.random() - 0.5) * 0.5,
                size: Math.random() * 2 + 1,
                opacity: Math.random() * 0.5 + 0.3,
                color: Math.random() > 0.5 ? '#00ffff' : '#ff00ff'
            });
        }
    }

    animateParticles() {
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);

        this.particles.forEach((particle, index) => {
            // Update position
            particle.x += particle.vx;
            particle.y += particle.vy;

            // Bounce off edges
            if (particle.x < 0 || particle.x > this.canvas.width) particle.vx *= -1;
            if (particle.y < 0 || particle.y > this.canvas.height) particle.vy *= -1;

            // Draw particle
            this.ctx.globalAlpha = particle.opacity;
            this.ctx.fillStyle = particle.color;
            this.ctx.beginPath();
            this.ctx.arc(particle.x, particle.y, particle.size, 0, Math.PI * 2);
            this.ctx.fill();

            // Draw connections to nearby particles
            for (let j = index + 1; j < this.particles.length; j++) {
                const otherParticle = this.particles[j];
                const distance = Math.sqrt(
                    Math.pow(particle.x - otherParticle.x, 2) +
                    Math.pow(particle.y - otherParticle.y, 2)
                );

                if (distance < 100) {
                    this.ctx.globalAlpha = (100 - distance) / 100 * 0.2;
                    this.ctx.strokeStyle = particle.color;
                    this.ctx.lineWidth = 0.5;
                    this.ctx.beginPath();
                    this.ctx.moveTo(particle.x, particle.y);
                    this.ctx.lineTo(otherParticle.x, otherParticle.y);
                    this.ctx.stroke();
                }
            }
        });

        requestAnimationFrame(() => this.animateParticles());
    }

    // Custom Cursor
    setupCustomCursor() {
        const cursor = document.querySelector('.cursor-trail');
        if (!cursor) return;

        document.addEventListener('mousemove', (e) => {
            this.mouse.x = e.clientX;
            this.mouse.y = e.clientY;

            cursor.style.left = e.clientX + 'px';
            cursor.style.top = e.clientY + 'px';
        });

        // Hide cursor on mobile
        if ('ontouchstart' in window) {
            cursor.style.display = 'none';
            document.body.style.cursor = 'auto';
        }
    }

    // Smooth Scrolling
    setupSmoothScrolling() {
        document.querySelectorAll('a[href^="#"]').forEach(anchor => {
            anchor.addEventListener('click', (e) => {
                e.preventDefault();
                const target = document.querySelector(anchor.getAttribute('href'));
                if (target) {
                    target.scrollIntoView({
                        behavior: 'smooth',
                        block: 'start'
                    });
                }
            });
        });

        // Parallax scrolling effect
        window.addEventListener('scroll', () => {
            const scrolled = window.pageYOffset;
            const stars = document.querySelector('.stars');
            if (stars) {
                stars.style.transform = `translateY(${scrolled * 0.5}px)`;
            }
        });
    }

    // Navigation Effects
    setupNavigationEffects() {
        const navbar = document.querySelector('.navbar');
        if (!navbar) return;

        window.addEventListener('scroll', () => {
            if (window.scrollY > 100) {
                navbar.style.background = 'rgba(0, 0, 0, 0.95)';
                navbar.style.backdropFilter = 'blur(15px)';
            } else {
                navbar.style.background = 'rgba(0, 0, 0, 0.9)';
                navbar.style.backdropFilter = 'blur(10px)';
            }
        });
    }

    // Form Animations
    setupFormAnimations() {
        const form = document.querySelector('.contact-form');
        if (!form) return;

        form.addEventListener('submit', (e) => {
            e.preventDefault();

            const submitBtn = form.querySelector('.submit-btn');
            const originalText = submitBtn.textContent;

            submitBtn.textContent = 'SENDING MESSAGE...';
            submitBtn.style.background = 'linear-gradient(45deg, #ff6b6b, #4ecdc4)';

            // Simulate form submission
            setTimeout(() => {
                submitBtn.textContent = 'MESSAGE SENT!';
                submitBtn.style.background = 'linear-gradient(45deg, #51cf66, #339af0)';

                setTimeout(() => {
                    submitBtn.textContent = originalText;
                    submitBtn.style.background = 'linear-gradient(45deg, #00ffff, #ff00ff)';
                    form.reset();
                }, 2000);
            }, 1500);
        });

        // Input focus effects
        document.querySelectorAll('.form-group input, .form-group textarea').forEach(input => {
            input.addEventListener('focus', () => {
                input.parentElement.style.transform = 'scale(1.02)';
            });

            input.addEventListener('blur', () => {
                input.parentElement.style.transform = 'scale(1)';
            });
        });
    }

    // Tilt Effect
    setupTiltEffect() {
        const tiltElements = document.querySelectorAll('[data-tilt]');

        tiltElements.forEach(element => {
            element.addEventListener('mousemove', (e) => {
                const rect = element.getBoundingClientRect();
                const x = e.clientX - rect.left;
                const y = e.clientY - rect.top;

                const centerX = rect.width / 2;
                const centerY = rect.height / 2;

                const rotateX = (y - centerY) / 10;
                const rotateY = (centerX - x) / 10;

                element.style.transform = `perspective(1000px) rotateX(${rotateX}deg) rotateY(${rotateY}deg) scale3d(1.05, 1.05, 1.05)`;
            });

            element.addEventListener('mouseleave', () => {
                element.style.transform = 'perspective(1000px) rotateX(0deg) rotateY(0deg) scale3d(1, 1, 1)';
            });
        });
    }

    // Intersection Observer for animations
    setupIntersectionObserver() {
        const observerOptions = {
            threshold: 0.1,
            rootMargin: '0px 0px -50px 0px'
        };

        const observer = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    entry.target.style.opacity = '1';
                    entry.target.style.transform = 'translateY(0)';

                    // Stagger animation for grid items
                    if (entry.target.classList.contains('about-card') ||
                        entry.target.classList.contains('feature-card')) {
                        const siblings = [...entry.target.parentElement.children];
                        const index = siblings.indexOf(entry.target);
                        entry.target.style.transitionDelay = `${index * 0.1}s`;
                    }
                }
            });
        }, observerOptions);

        // Observe elements
        document.querySelectorAll('.about-card, .feature-card, .section-title').forEach(el => {
            el.style.opacity = '0';
            el.style.transform = 'translateY(30px)';
            el.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
            observer.observe(el);
        });
    }

    // Audio Control (placeholder)
    setupAudioControl() {
        const audioToggle = document.getElementById('audio-toggle');
        if (!audioToggle) return;

        audioToggle.addEventListener('click', () => {
            this.isAudioPlaying = !this.isAudioPlaying;
            audioToggle.textContent = this.isAudioPlaying ? '🔇' : '🔊';

            // Add visual feedback
            audioToggle.style.transform = 'scale(0.9)';
            setTimeout(() => {
                audioToggle.style.transform = 'scale(1)';
            }, 150);
        });
    }

    // Responsive Navigation
    setupResponsiveNavigation() {
        const hamburger = document.querySelector('.hamburger');
        const navMenu = document.querySelector('.nav-menu');

        if (!hamburger || !navMenu) return;

        hamburger.addEventListener('click', () => {
            navMenu.classList.toggle('active');
            hamburger.classList.toggle('active');

            // Animate hamburger lines
            const spans = hamburger.querySelectorAll('span');
            if (hamburger.classList.contains('active')) {
                spans[0].style.transform = 'rotate(-45deg) translate(-5px, 6px)';
                spans[1].style.opacity = '0';
                spans[2].style.transform = 'rotate(45deg) translate(-5px, -6px)';
            } else {
                spans[0].style.transform = 'rotate(0) translate(0, 0)';
                spans[1].style.opacity = '1';
                spans[2].style.transform = 'rotate(0) translate(0, 0)';
            }
        });

        // Close menu when clicking on links
        document.querySelectorAll('.nav-link').forEach(link => {
            link.addEventListener('click', () => {
                navMenu.classList.remove('active');
                hamburger.classList.remove('active');
            });
        });
    }

    // Enhanced Glitch Effect
    setupGlitchEffect() {
        const glitchElement = document.querySelector('.glitch');
        if (!glitchElement) return;

        let glitchInterval;

        const startGlitch = () => {
            glitchInterval = setInterval(() => {
                glitchElement.style.textShadow = `
                    ${Math.random() * 10 - 5}px ${Math.random() * 10 - 5}px #ff00ff,
                    ${Math.random() * 10 - 5}px ${Math.random() * 10 - 5}px #00ffff,
                    ${Math.random() * 10 - 5}px ${Math.random() * 10 - 5}px #ffff00
                `;

                setTimeout(() => {
                    glitchElement.style.textShadow = '';
                }, 50);
            }, 3000);
        };

        startGlitch();

        // Enhanced glitch on hover
        glitchElement.addEventListener('mouseenter', () => {
            clearInterval(glitchInterval);
            let count = 0;
            const hoverGlitch = setInterval(() => {
                glitchElement.style.transform = `skew(${Math.random() * 10 - 5}deg)`;
                count++;
                if (count > 10) {
                    clearInterval(hoverGlitch);
                    glitchElement.style.transform = '';
                    startGlitch();
                }
            }, 100);
        });
    }

    // Utility method for random colors
    getRandomColor() {
        const colors = ['#00ffff', '#ff00ff', '#ffff00', '#ff6b6b', '#4ecdc4', '#45b7d1'];
        return colors[Math.floor(Math.random() * colors.length)];
    }

    // Add floating elements effect
    createFloatingElements() {
        const floatingContainer = document.createElement('div');
        floatingContainer.className = 'floating-elements';
        floatingContainer.style.cssText = `
            position: fixed;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            pointer-events: none;
            z-index: -1;
        `;
        document.body.appendChild(floatingContainer);

        for (let i = 0; i < 20; i++) {
            const element = document.createElement('div');
            element.style.cssText = `
                position: absolute;
                width: ${Math.random() * 6 + 2}px;
                height: ${Math.random() * 6 + 2}px;
                background: ${this.getRandomColor()};
                border-radius: 50%;
                opacity: ${Math.random() * 0.6 + 0.2};
                left: ${Math.random() * 100}%;
                top: ${Math.random() * 100}%;
                animation: float ${Math.random() * 10 + 10}s infinite linear;
            `;
            floatingContainer.appendChild(element);
        }

        // Add CSS animation
        const style = document.createElement('style');
        style.textContent = `
            @keyframes float {
                0% { transform: translateY(100vh) rotate(0deg); }
                100% { transform: translateY(-100vh) rotate(360deg); }
            }
        `;
        document.head.appendChild(style);
    }
}

// Initialize the cosmic website
const cosmicSite = new CosmicWebsite();

// Add some extra interactive features
document.addEventListener('DOMContentLoaded', () => {
    // Typewriter effect for hero subtitle
    const subtitle = document.querySelector('.hero-subtitle');
    if (subtitle) {
        const text = subtitle.textContent;
        subtitle.textContent = '';
        let i = 0;
        const typeWriter = () => {
            if (i < text.length) {
                subtitle.textContent += text.charAt(i);
                i++;
                setTimeout(typeWriter, 100);
            }
        };
        setTimeout(typeWriter, 2000);
    }

    // Add click ripple effect to buttons
    document.querySelectorAll('button, .nav-link').forEach(button => {
        button.addEventListener('click', function(e) {
            const ripple = document.createElement('span');
            const rect = this.getBoundingClientRect();
            const size = Math.max(rect.width, rect.height);
            const x = e.clientX - rect.left - size / 2;
            const y = e.clientY - rect.top - size / 2;

            ripple.style.cssText = `
                position: absolute;
                width: ${size}px;
                height: ${size}px;
                left: ${x}px;
                top: ${y}px;
                background: rgba(255, 255, 255, 0.3);
                border-radius: 50%;
                transform: scale(0);
                animation: ripple 0.6s linear;
                pointer-events: none;
            `;

            this.style.position = 'relative';
            this.style.overflow = 'hidden';
            this.appendChild(ripple);

            setTimeout(() => ripple.remove(), 600);
        });
    });

    // Add upload button functionality
    const uploadButton = document.querySelector('.cta-button');
    if (uploadButton) {
        uploadButton.addEventListener('click', () => {
            const input = document.createElement('input');
            input.type = 'file';
            input.multiple = true;
            input.click();

            input.addEventListener('change', (event) => {
                const files = event.target.files;
                const formData = new FormData();
                for (let i = 0; i < files.length; i++) {
                    formData.append('files[]', files[i]);
                }
                fetch('/upload', {
                    method: 'POST',
                    body: formData,
                    headers: {
                        'Accept': 'application/json'
                    }
                }).then(response => response.json()).then(uploadedFiles => {
                    // alert('Upload successful!');
                    // Display uploaded files and a delete button for each file
                    const fileList = document.getElementById('file-list');
                    if (fileList) {
                        uploadedFiles.forEach((fileInfo, index) => {
                            const li = document.createElement('li');
                            li.textContent = fileInfo.original;

                            // Create delete button
                            const deleteButton = document.createElement('button');
                            deleteButton.textContent = 'Delete';
                            deleteButton.className = 'delete-button';
                            deleteButton.addEventListener('click', () => {
                                const filename = encodeURIComponent(fileInfo.original);

                                fetch(`/delete/?filename=${filename}`, {
                                    method: 'DELETE'
                                }).then(response => {
                                    if (response.ok) {
                                        li.remove();
                                        //alert('File deleted successfully!');
                                    } else {
                                        alert('Delete failed.');
                                    }
                                }).catch(() => {
                                    alert('Delete failed.');
                                });
                            });

                            li.appendChild(deleteButton);
                            li.className = 'file-item';
                            fileList.appendChild(li);

                            // Animate new file entry
                            setTimeout(() => {
                                li.classList.add('show');
                            }, 100 * index);
                        });
                    }
                }).catch(() => {
                    alert('Upload failed.');
                });
            });
        });
    }

    // Add ripple animation CSS
    const rippleStyle = document.createElement('style');
    rippleStyle.textContent = `
        @keyframes ripple {
            to {
                transform: scale(4);
                opacity: 0;
            }
        }
    `;
    document.head.appendChild(rippleStyle);
});

console.log('🚀 Cosmic Web Experience loaded successfully!');
