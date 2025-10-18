![Rating](/assets/images/header.png)

# Inception Project Summary

## Project Overview
Inception is a system administration project focused on Docker containerization technology. The objective is to create a small infrastructure using Docker containers that runs a WordPress website with MariaDB database and NGINX web server, all connected through a Docker network and using volumes for data persistence.

## Key Features & Requirements

### Infrastructure Components
- **NGINX container** with TLSv1.2 or TLSv1.3 only
- **WordPress container** with php-fpm (without nginx)
- **MariaDB container** (without nginx)
- **Two persistent volumes** for WordPress database and website files
- **Docker network** connecting all containers
- **Automatic container restart** in case of crashes

### Technical Specifications
- **Base images**: Alpine or Debian (penultimate stable version only)
- **Custom Dockerfiles** required for each service
- **Docker Compose** for orchestration
- **Forbidden practices**:
  - Network: host, --link, or links:
  - Infinite loop commands (tail -f, bash, sleep infinity, while true)
  - Ready-made Docker images (except Alpine/Debian base)
  - Latest tag
  - Passwords in Dockerfiles

### Security Requirements
- **Environment variables** mandatory for configuration
- **Docker secrets** recommended for confidential information
- **.env file** for variable storage
- **NGINX as sole entry point** on port 443 with TLS only
- **Custom domain**: login.42.fr pointing to local IP
- **Database security**: Administrator username cannot contain 'admin', 'Admin', 'administrator', or 'Administrator'

### File Structure Requirements
- **srcs folder** containing all configuration files
- **Makefile** at root directory building entire application
- **Docker Compose** configuration in srcs directory
- **Separate directories** for each service (nginx, mariadb, wordpress)
- **Secrets directory** for credentials storage

### Development Environment
- **Virtual Machine** required for project completion
- **Volume storage** in /home/login/data on host machine
- **Git security**: Credentials must be ignored and not committed

## Bonus Features
- **Redis cache** for WordPress
- **FTP server** pointing to WordPress volume
- **Static website** (non-PHP) for portfolio/resume
- **Adminer** database management tool
- **Custom service** with justification during evaluation

## AI Usage Guidelines
The project emphasizes responsible AI usage:
- Use AI to reduce repetitive tasks, not generate core functionality
- Develop prompting skills for technical and non-technical tasks
- Critically assess all AI-generated content
- Ensure full understanding of any AI-assisted code
- Prioritize peer review and collaboration

## Evaluation Criteria
- Mandatory part must be **perfect** for bonus evaluation
- Infrastructure must function without manual intervention
- Proper error handling and container management
- Security compliance and best practices
- Understanding of Docker concepts and implementation details

This project focuses on practical system administration skills, Docker containerization expertise, security awareness, and infrastructure management using modern DevOps tools and practices.

[$${\color{red}BACK}$$](../../README.md)
