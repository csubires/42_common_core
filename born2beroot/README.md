
![Rating](/assets/images/header.png)

# BORN2BEROOT [subject](es.born2beroot.pdf)

- [Download](#url-download)
- [Installation](#using-the-disk-installer)
- [Partitioning (BONUS)](#partitioning-and-encryption)
- [Configuration](#host-configuration)
- [Password Requirements](#strong-password-requirements)
- [Sudo Requirements](#the-strong-password-for-your-sudo-group-must-meet-the-following-requirements)
- [SSH Server](#ssh-service)
- [Script monitoring.sh](#monitoringsh)
- [Get Signature](#get-the-signature-signaturetxt)
- [During Evaluation](#during-evaluation)
- [When Evaluating](#when-evaluating)

---

## Debian Website and Versions
[https://www.debian.org](https://www.debian.org/releases/index.en.html)

## URL Download
- [List of versions](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/)
- [ISO File 5/2024 12.5.0](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/debian-12.5.0-amd64-netinst.iso)
- [Alternative](https://gemmei.ftp.acc.umu.se/debian-cd/current/amd64/iso-cd/debian-12.5.0-amd64-netinst.iso)


## Creating Encrypted Partitions

### Using the disk installer
	Hostname csubires42

	root
	pass: user42

	New user: csubires
	pass: user42

### Partitioning and encryption
1. Manual partitioning (***BONUS***)

	| Partition | Mount Point | Size | Format | Type |
	| --- | --- | :---: | --- | :---: |
	| sda1 | /boot | 500m | ext4 | Primary |
	| sda5 | Do not mount | 30g | ext4 | Logical |

2. Create an encrypted volume on `sda5`.
3. Configure with Logical Volume Manager (LVM), a group `VLMGroup` within sda5.
4. Within the volume group create logical partitions using `"Create a logical volume"`:

	| Partition | Mount Point | Size | Format |
	| --- | --- | :---: | :---: |
	| root | / | 10g | ext4 |
	| swap | | 2.3g | swap area |
	| home | /home | 5g | ext4 |
	| var | /var | 3g | ext4 |
	| srv | /srv | 3g | ext4 |
	| tmp | /tmp | 3g | ext4 |
	| var-log | /var/log * | 4g | ext4 |
	| **Table1:** _* Enter manually_ |

5. Install grub

	Choose /dev/sda

5. Restart and install sudo
```
su
apt update
apt upgrade
apt install sudo
reboot
sudo -V
```

## Host Configuration

### 1. Your virtual machine's hostname must be your login ending in 42.

During installation or later:

>Check current name

	hostname

Modifying files:

	nano /etc/hostname
	nano /etc/hosts

Or with the command:

	hostnamectl set-hostname csubires42
	hostnamectl

>Restart

	reboot

>Verify name changed

	hostname


### 2. You must implement a strong password policy.

`nano /etc/login.defs`
```
PASS_MAX_DAYS 30
PASS_MIN_DAYS 2
PASS_WARN_AGE 7

chage -l csubires
```

>This will only apply policies to users created after modifying `login.defs`. To apply restrictions to existing users, use:

	chage username -W 7 -M 30 -m 2

Where:

	-W: Warning time before expiration, in days.
	-M: Maximum password expiration time, in days.
	-m: Number of days that must pass between password changes.


`apt install libpam-pwquality` + `nano /etc/pam.d/common-password`

After "retry 3" add:
```
minlen=10
ucredit=-1
dcredit=-1
lcredit=-1
maxrepeat=3
reject_username
difok=7
enforce_for_root
```
[_+ INFO_](https://blog.tiraquelibras.com/?p=1101)


### 3. You must install and configure sudo following strict rules

>Save sudo command history

	mkdir -p /var/log/sudo
	touch /var/log/sudo/sudo.log

`nano /etc/sudoers.d/sudo`

```
Defaults  passwd_tries=3
Defaults  badpass_message="PASSWORD IS NOT VALID"
Defaults  logfile="/var/log/sudo/sudo.log"
Defaults  log_input, log_output
Defaults  iolog_dir="/var/log/sudo"
Defaults  requiretty
Defaults  secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
```
	sudo -l

### 4. Besides root user, a user with your login as name must exist. Also must belong to user42 and sudo groups

> Create group, user, add user to groups and change password

	addgroup user42
	adduser csubires
	adduser csubires sudo
	adduser csubires user42
	passwd csubires

`visudo`
>Add

	csubires  	ALL=(ALL:ALL) ALL

>Check with:

	cat /etc/group
	getent group sudo
	getent group user42

## Strong Password Requirements:
>`nano /etc/login.defs`
- Your password must expire every 30 days.
`PASS_MAX_DAYS 30`
- The minimum number of days allowed before modifying a password should be 2. `PASS_MIN_DAYS 2`
- The user must receive a warning message 7 days before their password expires.
`PASS_WARN_AGE 7`

>`nano /etc/pam.d/common-password`
- Your password must have at least 10 characters length. `minlen=10`
- Must contain an uppercase letter `ucredit=-1` and a number `dcredit=-1`.
- By the way, it cannot have more than 3 consecutive same characters. `maxrepeat=3`
- The password cannot contain the username. `reject_username`
- The following rule does not apply to root password: The password must have at least 7 characters that are not part of the old password. `difok=7`
- Obviously, your root password must follow this policy. `enforce_for_root`

_Extra:_ Contain at least one lowercase letter. `lcredit=-1`

## The strong password for your sudo group must meet the following requirements:
>`nano /etc/sudoers.d/sudo42`
- Authenticating with sudo must be limited to three attempts when entering an incorrect password. `Defaults  passwd_tries=3`
- A custom message of your choice must be displayed if the entered password is incorrect when using sudo. `Defaults  badpass_message="PASSWORD IS NOT VALID"`
- For each command executed with sudo, both input and output must be archived in the /var/log/sudo/ directory. `Defaults  iolog_dir="/var/log/sudo"`,
`Defaults  logfile="/var/log/sudo/sudo42.log"`, `Defaults  log_input, log_output`
- TTY mode must be enabled for security reasons. `Defaults  requiretty`
- For security, directories usable by sudo must be restricted. For
example: /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin `Defaults  secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"`

## SSH Service
1. Install ssh and check that the service is running.

```
sudo su
apt install openssh-server
service ssh status
systemctl status ssh
```

2. Configure

>Modify files:

`nano /etc/ssh/sshd_config` and `nano /etc/ssh/ssh_config`
- Port 4242 `#Port 22 -> Port 4242`
- It should not be possible to connect through `SSH` as root. `#PermitRootLogin prohibit-password -> PermitRootLogin no`
- [&#11093;] creating a new user???.


### You must configure the UFW firewall, leaving only port 4242 open.

	apt install ufw
	ufw enable
	ufw allow 4242
	ufw status numbered

3. Restart services
```
service ssh restart
systemctl restart ssh
service ssh status
```

## monitoring.sh
- Must be developed in bash. `#!/bin/bash`
- The script will display certain information (listed below) on all terminals every 10 minutes (Take a look at wall). The wall banner is optional. No error should be visible.
```
/usr/local/sbin/monitoring.sh
crontab -u root -e
*/10 * * * * sh /usr/local/sbin/monitoring.sh

systemctl status cron
grep -a "monitoring.sh" /var/log/syslog
```

### Your script must always display the following information (See PDF):
- Your operating system architecture and its kernel version. `$(uname -a)`
- The number of physical cores.
`$(grep "physical id" /proc/cpuinfo | sort | uniq | wc -l)`
- The number of virtual cores.
`$(grep "processor" /proc/cpuinfo | wc -l)`
- The RAM memory currently available on your server and its usage percentage.
- The memory currently available on your server and its utilization as a percentage.
``` sh
mem_total=$(free --mega | grep Mem: | awk '{print $2}')
mem_used=$(free --mega | grep Mem: | awk '{print $3}')
mem_perce=$(free --mega | grep Mem: | awk '{printf("%.2f"), $3/$2*100}')
Memory Usage: ${mem_used}/${mem_total}MB (${mem_perce}%)
```
- The current usage percentage of your cores.
`cpu_load=$(expr 100 - $(vmstat 1 2 | tail -1 | awk '{printf $15}') | xargs | awk '{printf("%.1f%%"), $1 + $3}')`
- The date and time of the last reboot.
`$(who -b | awk '$1 == "system" {print $3 " " $4}')`
- Whether LVM is active or not.
`$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)`
- The number of active connections.
`$(ss -ta | grep ESTAB | wc -l)`
- The number of server users.
`$(users | wc -w)`
- Your server's IPv4 address and its MAC (Media Access Control)
`"IP $(hostname -I) ($(ip link show | awk '$1 == "link/ether" {print $2}'))"`
- The number of commands executed with sudo.
`$(journalctl _COMM=sudo | grep COMMAND | wc -l)`

>Example:
```
Broadcast message from root@wil (tty1) (Sun Apr 25 15:45:00 2021):
#Architecture: Linux wil 4.19.0-16-amd64 #1 SMP Debian 4.19.181-1 (2021-03-19) x86_64 GNU/Linux
#CPU physical : 1
#vCPU : 1
#Memory Usage: 74/987MB (7.50 %)
#Disk Usage: 1009/2Gb (49 %)
#CPU load: 6.7 %
#Last boot: 2021-04-25 14:45
#LVM use: yes
#TCP Connections : 1 ESTABLISHED
#User log: 1
#Network: IP 10.0.2.15 (08:00:27:51:9b:a5)
#Sudo : 42 cmd
```

## Get the Signature Signature.txt
_Linux:_ `sha1sum born2beroot.vdi`

>For corrections remember to clone the machine so you can start it without fear of the signature changing.
<br>

## During Evaluation
- During the defense, you must create a user and assign it to a group.

```
getent group sudo
getent group user42
sudo adduser name_user
sudo addgroup evaluating
sudo adduser name_user sudo
hostname
dpkg -s sudo
ls  /etc/sudoers.d
sudo passwd <user>
ver user cut -d: -f1 /etc/passwd
delgroup <group>
deluser --remove-all-files <user>
sudo cat /etc/group | grep csubires
```

- SSH usage will be checked during the defense by creating a new user.

```
ssh csubires@localhost -p 4242
	...
```

- During the defense, you will be asked how this script works. You must interrupt it without modifying it. Take a look at cron.
```
service cron stop
sudo /etc/init.d/cron stop
sudo /etc/init.d/cron start
```

- During the defense, the content of the signature.txt file will be compared with your virtual machine's signature. If the two are not identical, your grade will be 0.

## QUESTIONS ¿?
> Differences between aptitude and apt?

**APT**, the Advanced Package Tool, a high-level global tool that includes dpkg as backend, and adds functionality for managing external repositories for dependencies and updates.
For DEB-based distros, the standard package manager is dpkg, and allows installing, uninstalling,
apt consolidates the features of apt-get, apt-cache

**Aptitude** is another package management tool in Debian systems. Unlike apt and apt-get, aptitude is a curses-based text interface that provides an interactive and powerful approach to package administration.

	The main difference is that apt is a low-level package manager, which can be used by other high-level managers like aptitude
		Aptitude being high-level has more functionality, as it integrates those of apt and its other variants like apt-mark and apt-cache.

> What is SELinux?

**SELinux** defines access controls for applications, processes, and files within a system. It uses security policies, which consist of a set of rules to tell SELinux which elements can be accessed.
When an application or process (known as subjects) requests access to an object, such as a file, SELinux consults the access vector cache (AVC), where object and subject permissions are stored.

>What is AppArmor?

**AppArmor** ("Application Armor") is a Linux kernel security module that allows the system administrator to restrict program capabilities. To define restrictions it associates a security profile with each program. This profile can be created manually or automatically. It complements the traditional Unix discretionary access control model (DAC) by providing mandatory access control (MAC).

> What is a virtual machine?

	It is software that allows emulating a computer within another physical one.

> Why did you choose Debian?

	Because it is one of the most used and from which many distributions derive, with a lot of information available about its use.

> What is the purpose of virtual machines?

	To emulate the operation of a computer to be able to install an operating system on it, isolating it from the physical machine. This can be useful for security reasons, avoiding viruses, having backups of their states, having several services running simultaneously and balancing them, etc.

> What is LVM?

	Logical Volume Manager. A way of partitioning by creating a volume group that will contain the logical volumes inside.

> What is a script?

	To avoid having to execute commands one by one, scripts can be created which is nothing more than a list of commands that when called will be executed one by one. Automation.

> What is crontab?

	Scheduling tasks that will be executed with a certain frequency.

> What is tty?

	In the context of UNIX and Linux, 'tty' refers to the standard terminals of the operating system, numbered and used for textual interaction with the computer.

## Some commands for evaluation

```
lscpu
ssh -vvvvA 127.0.0.1 -p 4242

apparmor_status
ls /usr/bin/*session
sudo ufw status
sudo service ufw status
sudo service ssh status
uname -v or uname --kernel-version

sudo nano lokesea
ls  /var/log/sudo..
ssh newuser@localhost -p 4242

sudo service ufw status
sudo ufw allow 8080
sudo ufw status numbered
sudo ufw delete num_rule

crontab -u root -e
sudo /etc/init.d/cron stop
sudo /etc/init.d/cron start

# Commands to view partitions
lsblk -f
fdisk -l
findmnt
df -T
blkid
ls /dev/mapper/
cat /etc/fstab
lvdisplay
lvmdiskscan
lvscan
cryptsetup status /dev/mapper/NVME0N1-P6_CRYPT

# Review
nano /mnt/root/etc/fstab
nano /mnt/root/etc/crypttab

crontab -l
hostname -I
ip a
```


### OTHERS
>Remove keyboard sound

	sudo nano /etc/inputrc
	set bell-style none

>Make vmware-tools work for sharing folders:

	apt install open-vm-tools
	sudo vmhgfs-fuse .host:/ /mnt/hgfs/ -o allow_other -o uid=1000

>Change system date

	date --set 1998-11-02
	date --set 21:08:00


### TO-DO
- Connect to ssh not root.
- Only port 4242.
- Confirm script starts every 10 min.

## Glossary:

**pvs**: shows one line per physical volume. Information appears in a configurable way and offers a high level of control in the format.

**pvdisplay**: provides a multi-line output message for each of the physical volumes. Also shows physical properties such as size, extent or volume groups, among others.

**pvscan**: is responsible for scanning the LVM disk block devices that the system supports.

---

**lvs**: this command shows information about the logical volume in an adjustable way. Allows great format management and is ideal for scripts.

**lvdisplay**: provides LV information such as its size, distribution and allocation, through a fixed format.

**lvscan**: is responsible for searching and listing the logical volumes in the system.

[$${\color{red}BACK}$$](../../README.md)
