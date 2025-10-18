#!/bin/bash
set -e

DOMAIN='csubires.42.fr'
USR_LOCAL='csubires'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

command_exists()
{
    command -v "$@" >/dev/null 2>&1
}

install_make()
{
    if ! command_exists make; then
        echo -e "${YELLOW}➡️ Installing Make...${NC}"
        sudo apt-get update -qq > /dev/null
        sudo apt-get install -y make vim > /dev/null
        echo -e "${GREEN}✅ Make installed successfully.${NC}"
    else
        echo -e "${GREEN}✅ Make is already installed.${NC}"
    fi
}

install_docker()
{
    if ! command_exists docker; then
        echo -e "${YELLOW}➡️ Installing Docker...${NC}"
        OLD_PKGS=(
            docker.io
            docker-doc
            docker-compose
            docker-compose-v2
            podman-docker
            containerd
            runc
        )
        echo -e "${YELLOW}➡️ Removing old versions...${NC}"
        for pkg in "${OLD_PKGS[@]}"; do
            sudo apt-get remove -y "$pkg" >/dev/null 2>&1 || true
        done

        echo -e "${YELLOW}➡️ Installing dependencies...${NC}"
        sudo apt-get update -qq > /dev/null
        sudo apt-get install -y software-properties-common apt-transport-https ca-certificates curl gnupg lsb-release > /dev/null
        sudo mkdir -p /etc/apt/keyrings
        
        # Clean up any existing broken docker.list file
        sudo rm -f /etc/apt/sources.list.d/docker.list
 
        # FIXED: Add the component (stable) after the distribution name
        DISTRO_CODENAME=$(lsb_release -cs)
 	curl -fsSL https://download.docker.com/linux/debian/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
	echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/debian $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

        # Set proper permissions
        sudo chmod a+r /etc/apt/keyrings/docker.gpg

        echo -e "${YELLOW}➡️ Installing Docker packages...${NC}"
        sudo apt-get update -qq > /dev/null
        sudo apt-get install -y \
            docker-ce \
            docker-ce-cli \
            containerd.io \
            docker-buildx-plugin \
            docker-compose-plugin > /dev/null

        echo -e "${GREEN}✅ Docker installed successfully.${NC}"
    else
        echo -e "${GREEN}✅ Docker is already installed.${NC}"
    fi
}

configure_user()
{
    if ! id "$USR_LOCAL" >/dev/null 2>&1; then
        echo -e "${YELLOW}➡️ Creating user $USR_LOCAL...${NC}"
        sudo useradd -m -s /bin/bash -G sudo "$USR_LOCAL"
        echo -e "${YELLOW}⚠️  Please set a password for $USR_LOCAL manually with 'sudo passwd $USR_LOCAL'${NC}"
    fi

    if ! groups "$USR_LOCAL" | grep -q docker; then
        echo -e "${YELLOW}➡️ Configuring docker group for user $USR_LOCAL...${NC}"
        sudo groupadd docker 2>/dev/null || true
        sudo usermod -a -G docker "$USR_LOCAL"
        sudo systemctl restart docker
        echo -e "${YELLOW}⚠️  Please restart your session or run 'newgrp docker' to apply changes.${NC}"
    else
        echo -e "${GREEN}✅ User $USR_LOCAL is already in docker group.${NC}"
    fi
}

main()
{
    if ! command_exists lsb_release; then
        echo -e "${RED}❌ This script only works on Debian/Ubuntu-based distributions${NC}"
        exit 1
    fi

    # Check if running as root or with sudo privileges
    if [ "$(id -u)" -eq 0 ]; then
        echo -e "${YELLOW}⚠️  Running as root, some operations may not be needed${NC}"
    else
        echo -e "${YELLOW}⚠️  Some operations may require sudo privileges${NC}"
    fi

    if ! grep -q "${DOMAIN}" /etc/hosts; then
        echo "Adding domain to /etc/hosts"
        echo "127.0.0.1 ${DOMAIN}" | sudo tee -a /etc/hosts
        echo "127.0.0.1 www.${DOMAIN}" | sudo tee -a /etc/hosts
    fi

    install_make
    install_docker
    configure_user

    # Only change ownership if we're not running as the target user
    if [ "$(whoami)" != "$USR_LOCAL" ]; then
        echo -e "${YELLOW}➡️ Setting ownership for current directory...${NC}"
        sudo chown -R "$USR_LOCAL:$USR_LOCAL" ./
    fi

    echo -e "\n${GREEN}✔️  Installation completed successfully${NC}"
    echo -e "To verify Docker, run:"
    echo -e "  ${YELLOW}docker run hello-world${NC}"
    echo -e "You may need to logout and login again for group changes to take effect"
}

# Main execution
echo "Current user: $(whoami)"
main