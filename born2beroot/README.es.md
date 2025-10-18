![Rating](/assets/images/header.png)

# BORN2BEROOT [subject](es.born2beroot.pdf)

- [Descarga](#url-descarga)
- [Instalación](#usando-el-instalador-del-disco)
- [Particionado (BONUS)](#particionado-y-cifrado)
- [Configuración](#configuración-host)
- [Requisitos de contraseña](#requisítos-de-contraseña-fuerte)
- [Requisitos de sudo](#la-contraseña-fuerte-para-tu-grupo-sudo-debes-cumplir-con-los-siguientes-requisitos)
- [Servidor SSH](#servicio-ssh)
- [Script monitoring.sh](#monitoringsh)
- [Obtener firma](#obtener-la-firma-signaturetxt)
- [Al ser evaluado](#al-ser-evaluado)
- [Al evaluar](#al-evaluar)

---

## Web y versiones de debian
[https://www.debian.org](https://www.debian.org/releases/index.es.html)

## URL Descarga
- [Listado de versiones](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/)
- [Archivo ISO 5/2024 12.5.0](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/debian-12.5.0-amd64-netinst.iso)
- [Alternativa](https://gemmei.ftp.acc.umu.se/debian-cd/current/amd64/iso-cd/debian-12.5.0-amd64-netinst.iso)


## Creación de las particiones cifradas

### Al usar el instalador del disco
	Hostname csubires42

	root
	pass: user42

	Nuevo usuario: csubires
	pass: user42

### Particionado y cifrado
1. Particionado manual (***BONUS***)

	| Partición | Anclaje | Tamaño | Formato | Tipo |
	| --- | --- | :---: | --- | :---: |
	| sda1 | /boot | 500m | ext4 | Primaria |
	| sda5 | No montar | 30g | ext4 |Lógica |

2. Crear un volumen cifrado en `sda5`.
3. Configurar con el Gestor de Volúmenes Lógicos (LVM), un grupo `VLMGroup` dentro de sda5.
4. Dentro del grupo de volumenes crear las particiones lógicas mediante `"Crear un volumen lógico"`:

	| Partición | Anclaje | Tamaño | Formato |
	| --- | --- | :---: | :---: |
	| root | / | 10g | ext4 |
	| swap | | 2.3g | swap area |
	| home | /home | 5g | ext4 |
	| var | /var | 3g | ext4 |
	| srv | /srv | 3g | ext4 |
	| tmp | /tmp | 3g | ext4 |
	| var-log | /var/log * | 4g | ext4 |
	| **Tabla1:** _* Insertar manualmente_ |

5. Instalar el grub

	Elegir /dev/sda

5. Reiniciar e instalar sudo
```
su
apt update
apt upgrade
apt install sudo
reboot
sudo -V
```

## Configuración host

### 1.  El hostname de tu máquina virtual debe ser tu login terminado en 42.

Durante la instalación o posteriormente:

>Comprobar el nombre actual

	hostname

Modificando archivos:

	nano /etc/hostname
	nano /etc/hosts

O bien con el comando:

	hostnamectl set-hostname csubires42
	hostnamectl

>Reiniciar

	reboot

>Comprobar que el nombre se cambio

	hostname


### 2. Debes implementar una política de contraseñas fuerte.

`nano /etc/login.defs`
```
PASS_MAX_DAYS 30
PASS_MIN_DAYS 2
PASS_WARN_AGE 7

chage -l csubires
```

>Esto sólo aplicará las politicas a los usuarios que se creen a partir de la modificación de `login.defs`. Para aplicar las restriciones a usuarios que ya existen, usar:

	chage nombre_usuario -W 7 -M 30 -m 2

Donde:

	-W: Tiempo en el que se muestra la advertencia previo a la caducidad, en días.
	-M: Tiempo máximo de caducidad de la contraseña, en días.
	-m: Número de días que han de transcurrir entre un cambio de contraseña y el siguiente.


`apt install libpam-pwquality` + `nano /etc/pam.d/common-password`

Después de "retry 3" añadir:
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


### 3. Debes instalar y configurar sudo siguiendo reglas estrictas

>Guardar historial del comando sudo

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

### 4. Además del usuario root, un usuario con tu login como nombre debe existir. Además debe pertenecer a los grupos user42 y sudo

> Crear grupo, usuario, añadir usuario a grupos y cambiar contraseña

	addgroup user42
	adduser csubires
	adduser csubires sudo
	adduser csubires user42
	passwd csubires

`visudo`
>Añadir

	csubires  	ALL=(ALL:ALL) ALL

>Comprobar con:

	cat /etc/group
	getent group sudo
	getent group user42

## Requisítos de contraseña fuerte:
>`nano /etc/login.defs`
- Tu contraseña debe expirar cada 30 días.
`PASS_MAX_DAYS 30`
- El número mínimo de días permitido antes de modificar una contraseña deberá ser 2. `PASS_MIN_DAYS 2`
- El usuario debe recibir un mensaje de aviso 7 días antes de que su contraseña expire.
`PASS_WARN_AGE 7`

>`nano /etc/pam.d/common-password`
- Tu contraseña debe tener como mínimo 10 caracteres de longitud. `minlen=10`
- Debe contener una mayúscula `ucredit=-1` y un número `dcredit=-1`.
- Por cierto, no puede tener más de 3 veces consecutivas el mismo carácter. `maxrepeat=3`
- La contraseña no puede contener el nombre del usuario. `reject_username`
- La siguiente regla no se aplica a la contraseña para root: La contraseña debe tener al menos 7 caracteres que no sean parte de la antigua contraseña. `difok=7`
- Evidentemente, tu contraseña para root debe seguir esta política. `enforce_for_root`

_Extra:_ Contener al menos una minúscula. `lcredit=-1`

## La contraseña fuerte para tu grupo sudo, debes cumplir con los siguientes requisitos:
>`nano /etc/sudoers.d/sudo42`
- Autenticarte con sudo debe estar limitado a tres intentos en el caso de introducir una contraseña incorrecta. `Defaults  passwd_tries=3`
- Un mensaje personalizado de tu elección debe mostrarse en caso de que la contraseña introducida sea incorrecta cuando se utilice sudo. `Defaults  badpass_message="PASSWORD IS NOT VALID"`
- Para cada comando ejecutado con sudo, tanto el input como el output deben quedar archivados en el directorio /var/log/sudo/. `Defaults  iolog_dir="/var/log/sudo"`,
`Defaults  logfile="/var/log/sudo/sudo42.log"`, `Defaults  log_input, log_output`
- El modo TTY debe estar activado por razones de seguridad. `Defaults  requiretty`
- Por seguridad, los directorios utilizables por sudo deben estar restringidos. Por
ejemplo: /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin `Defaults  secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"`

## Servicio SSH
1. Instalar ssh y comprobar que el servicio está ejecutándose.

```
sudo su
apt install openssh-server
service ssh status
systemctl status ssh
```

2. Configurar

>Modificar los archivos:

`nano /etc/ssh/sshd_config` y `nano /etc/ssh/ssh_config`
- Puerto 4242 `#Port 22 -> Port 4242`
- No debe ser posible conectarte a través de `SSH` como root. `#PermitRootLogin prohibit-password -> PermitRootLogin no`
- [&#11093;] creando un nuevo usuario???.


### Debes configurar el firewall UFW, dejando solamente el puerto 4242 abierto.

	apt install ufw
	ufw enable
	ufw allow 4242
	ufw status numbered

3. Reiniciar servicios
```
service ssh restart
systemctl restart ssh
service ssh status
```

## monitoring.sh
- Debe estar desarrollado en bash. `#!/bin/bash`
- El script mostrará cierta información (listada debajo) en todos los terminales cada 10 minutos (Échale un vistazo a wall). El banner de wall es opcional. Ningún error debe ser visible.
```
/usr/local/sbin/monitoring.sh
crontab -u root -e
*/10 * * * * sh /usr/local/sbin/monitoring.sh

systemctl status cron
grep -a "monitoring.sh" /var/log/syslog
```

### Tu script debe siempre mostrar la siguiente información (Ver PDF):
- La arquitectura de tu sistema operativo y su versión de kernel. `$(uname -a)`
- El número de núcleos físicos.
`$(grep "physical id" /proc/cpuinfo | sort | uniq | wc -l)`
- El número de núcleos virtuales.
`$(grep "processor" /proc/cpuinfo | wc -l)`
- La memoria RAM disponible actualmente en tu servidor y su porcentaje de uso.
- La memoria disponible actualmente en tu servidor y su utilización como un porcentaje.
``` sh
mem_total=$(free --mega | grep Mem: | awk '{print $2}')
mem_used=$(free --mega | grep Mem: | awk '{print $3}')
mem_perce=$(free --mega | grep Mem: | awk '{printf("%.2f"), $3/$2*100}')
Memory Usage: ${mem_used}/${mem_total}MB (${mem_perce}%)
```
- El porcentaje actual de uso de tus núcleos.
`cpu_load=$(expr 100 - $(vmstat 1 2 | tail -1 | awk '{printf $15}') | xargs | awk '{printf("%.1f%%"), $1 + $3}')`
- La fecha y hora del último reinicio.
`$(who -b | awk '$1 == "system" {print $3 " " $4}')`
- Si LVM está activo o no.
`$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)`
- El número de conexiones activas.
`$(ss -ta | grep ESTAB | wc -l)`
- El número de usuarios del servidor.
`$(users | wc -w)`
- La dirección IPv4 de tu servidor y su MAC (Media Access Control)
`"IP $(hostname -I) ($(ip link show | awk '$1 == "link/ether" {print $2}'))"`
- El número de comandos ejecutados con sudo.
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

## Obtener la firma Signature.txt
_Linux:_ `sha1sum born2beroot.vdi`

>Para las correcciones recuerda clonar la máquina ya que asi podras encenderla sin miedo a que cambie la firma.
<br>

## Al ser evaluado
- Durante la defensa, deberás crear un usuario y asignárselo a un grupo.

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

- El uso de SSH será comprobado durante la defensa creando un nuevo usuario.

```
ssh csubires@localhost -p 4242
	...
```

- Durante la defensa, te preguntarán cómo funciona este script. Deberás interrumpirlo sin modificarlo. Échale un vistazo a cron.
```
service cron stop
sudo /etc/init.d/cron stop
sudo /etc/init.d/cron start
```

- Durante la defensa, el contenido del archivo signature.txt se comparará con la firma de tu máquina virtual. Si las dos no son idénticas, tu nota será 0.

## PREGUNTAS ¿?
> ¿Diferencias aptitude y apt?

**APT**, el Advanced Package Tool, una herramienta global de alto nivel que incluye a dpkg como backend, y que le agrega las funcionalidades de gestión de repositorios externos para dependencias y actualizaciones.
distros basadas en DEB, el gestor de paquetes estándar es dpkg, y permite instalar, desinstalar,
apt consolida las características de apt-get, apt-cache

**Aptitude** es otra herramienta de gestión de paquetes en sistemas Debian. A diferencia de apt y apt-get, aptitude es una interfaz de texto basada en curses que proporciona un enfoque interactivo y poderoso para la administración de paquetes.

	La principal diferencia es que apt es un administrador de paquetes de bajo nivel, que puede ser usado por otros administradores de alto nivel como aptitude
		Aptitude al ser de alto nivel tiene mas funcionalidades, pues integra las de apt y sus otras variantes como apt-mark y apt-cache.

> ¿Qué SELinux?

**SELinux** define los controles de acceso para las aplicaciones, los procesos y los archivos dentro de un sistema. Utiliza políticas de seguridad, que consisten en un conjunto de reglas para indicar a SELinux a qué elementos se puede acceder.
Cuando una aplicación o un proceso (conocidos como sujetos) solicitan acceso a algún objeto, como un archivo, SELinux consulta la caché de vector de acceso (AVC), donde se almacenan los permisos de los objetos y los sujetos.

>¿Qué es AppArmor?

**AppArmor** ("Application Armor") es un módulo de seguridad del kernel Linux que permite al administrador del sistema restringir las capacidades de un programa. Para definir las restricciones asocia a cada programa un perfil de seguridad. Este perfil puede ser creado manual o automáticamente. Complementa el modelo tradicional de control de acceso discrecional de Unix (DAC) proporcionando el control de acceso obligatorio (MAC).

> Qué es una máquina virtual?

	Es un software que permite emular un ordenador dentro de otro físico.

> ¿Por qué has escogido Debian?

	Porque es uno de los más usados y del cual parten muchas distribuciones, habiendo gran cantidad de información sobre su utilización.

> ¿Cuál es el propósito de las máquinas virtuales?

	Emular el funcionamiento de un ordenador para poder instalar en ella un sistema operativo, aislandolo de la máquina física. Esto puede ser útil por razones de seguridad, evitar virus, tener backups de sus estados, tener varios servicios corriendo al mismo tiempo y balancearlos, etc

> ¿Qué es LVM?

	Gestor de volúmenes lógicos. Una forma de particionar creando un grupo de volumenes que dentro contendrás los volumenes lógicos.

> ¿Qué es un script?

	Para no tener que ejecutar uno a uno los comandos, se pueden crear script que no es más que un listado de comandos que al ser llamado se ejecutarán uno a uno. Automatización.

> ¿Qué es crontab?

	Programación de tareas que se ejecutaran con una cierta frecuencia.

> ¿Qué es tty?

	En el contexto de UNIX y Linux, 'tty' hace referencia a los terminales estándar del sistema operativo, numerados y usados para la interacción textual con el computador.

## Algunos comandos a la hora de evaluar

```
lscpu
ssh -vvvvA 127.0.0.1 -p 4242

apparmor_status
ls /usr/bin/*session
sudo ufw status
sudo service ufw status
sudo service ssh status
uname -v o uname --kernel-version

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

# Comandos para ver particiones
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

# Revisar
nano /mnt/root/etc/fstab
nano /mnt/root/etc/crypttab

crontab -l
hostname -I
ip a
```


### OTROS
>Quitar sonido teclado

	sudo nano /etc/inputrc
	set bell-style none

>Hacer que funciones las vmware-tools para compartir carpetas:

	apt install open-vm-tools
	sudo vmhgfs-fuse .host:/ /mnt/hgfs/ -o allow_other -o uid=1000

>Cambiar fecha del sistema

	date --set 1998-11-02
	date --set 21:08:00


### TO-DO
- Conectarse al ssh no root.
- Solo 4242 puerto.
- Confirmar que el script inicia cada 10 min.

## Glosario:

**pvs**: muestra una línea por volumen físico. La información aparece de manera configurable y ofrece un alto nivel de control en el formato.

**pvdisplay**: ofrece un mensaje de salida de varias líneas por cada uno de los volúmenes físicos. Además, muestra propiedades físicas como el tamaño, la extensión o los grupos de volúmenes, entre otros.

**pvscan**: se encarga de explorar los equipos del bloque LVM disk que el sistema soporte.

---

**lvs**: este comando muestra información acerca del volumen lógico de una forma ajustable. Permite una gran gestión de formato y es ideal para scripts.

**lvdisplay**: ofrece información del LV como su tamaño, distribución y asignación, a través de un formato fijo.

**lvscan**: se encarga de buscar y enlistar los volúmenes lógicos en el sistema.


[$${\color{red}VOLVER}$$](../../README.md)
