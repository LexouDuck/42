# 42: roger-skyline-1

---

**IMPORTANT FOREWORD**
- Mind the difference in how different programs use the term GB (GigaBytes)
  Sometimes it's (1GB = 10^9 = 1,000,000,000 bytes), sometimes (1GB = 2^30 = 1,073,741,824 bytes)
  This conversion might make your disk partitions be incorrectly sized if you don't pay attention !
  You can use `fdisk` to check the partitions, and `gparted` to resize them if needed.
- Many times, doing `sudo service _ restart` will not have the full effect -> `sudo reboot` to be sure !
- Check your `/etc/hosts.deny` file before each reboot, and remove from the file any IPs that you've been using to test things.

### Debian VM Setup

- _OS Image_: Download a [Debian netinst iso](https://www.debian.org/distrib/) and store it in the 42 goinfre storage space.
- _RAM_: 1.0 GB (1024 MB) of access memory
- _ROM_: 8.0 GB Hard Disk, fixed size

**IMPORTANT**: you need to go into the settings for your VM and change the 'Network' setting 'NAT' to 'Bridged Adapter'

Then, start the newly created VM - the hypervisor program will prompt you to give the location of the VM ISO.

After that, select **Install** (rather than graphical install).

**Localisation**

- _Language_: English
- _Area_: other -> France
- _Locale_: United States (en-US)
- _Keyboard_: [depends: either American English or French]

**Admin**

- _Hostname_: roger
- _Domain_: 42.fr
- _Root Password_: [you decide]

**Non-Admin User**

- _Full Name_: [you decide]
- _Username_: [you decide]
- _Password_: [you decide]

**Disk partitions**

Manual setup - select `SCSI1 (0,0,0) (sda) - etc` (that's the HDD), and confirm.

Now, right under that HDD, there should be the `FREE SPACE` partition under it.

Select that `FREE SPACE` to set up each new partition, as follows:

- _Partition 1_: 4.2 GB -> Primary -> Beginning -> Use as: ext4 -> Mount Point: `/`
- _Partition 2_: 1.0 GB -> Primary -> Beginning -> Use as: Swap Area
- _Partition 3_: Remaining Space -> Primary -> Use as: ext4 -> Mount Point: `/home`

**Package Mangager**

- _Additionnal CDs to scan_: No

- _Country_: France
- _Mirror_: ftp.fr.debian.org
- _HTTP Proxy_: None

**Config**
- _Particpative user survey_: No
- _Software_: Debian Desktop Environment, with SSH Server and Standard system utilities
- _GRUB Boot Loader_: Yes, /dev/sda

---

### Installing packages

Input the previously-set root password, as requested.

Then, install the following packages:
```sh
root@roger:> apt-get update -y
root@roger:> apt-get upgrade -y
root@roger:> apt-get install sudo
root@roger:> apt-get install vim
root@roger:> apt-get install ufw
root@roger:> apt-get install iptables-persistent
root@roger:> apt-get install fail2ban
root@roger:> apt-get install sendmail
root@roger:> apt-get install portsentry
root@roger:> apt-get install apache2
```
Setup the non-root user as sudoer and login:
```sh
root@roger:> adduser [user] sudo
root@roger:> su - [user]
user@roger:> 
```

---

### Configuring network interfaces

To setup a static IP, we need to modify the `/etc/network/interfaces` file:
```sh
user@roger:> sudo vim /etc/network/interfaces
```
You need to modify this file, such that it should look like this:
```sh
source /etc/network/interfaces.d/*

# The loopback network interface
auto lo
iface lo inet loopback

# The primary network interface
allow-hotplug enp0s3
iface enp0s3 inet static
	address 10.12.124.[you decide]
	netmask 255.255.255.252
	broadcast 10.12.255.255
	gateway 10.12.254.254
```

With this done, your VM should have internet access set up.
All you need to do for these to work is **reboot** the VM.

You can test whether or not you have internet access by doing:
```sh
user@roger:> ping 8.8.8.8
```

---

### Setting up SSH

To set up SSH connections, we need to modify the `/etc/ssh/sshd_config` file:
```sh
user@roger:> sudo vim /etc/ssh/sshd_config
```
The following 4 lines must be present in the file, by either uncommenting these lines in the file, or by manually adding these lines yourself:
```sh
...
Port [port_ssh: can be anything from 1000 to 9999]
...
PermitRootLogin no
...
PubkeyAuthentication yes
...
PasswordAuthentification yes
...
```

After this, you must generate a **public key** from your host machine by doing this command:
```sh
$> ssh-keygen
```
After which, you can copy the generated **key** from the file `~/.ssh/id_rsa.pub` on the host machine, and write that same **key** into the file `~/.ssh/authorized_keys` inside the VM, so as to allow SSH connections.

The easiest way to do this is with the `ssh-copy-id` command from the host machine:
```sh
$> ssh-copy-id -i ~/.ssh/id_rsa.pub -p [port_ssh] [user]@[IP_vm]
```

To access the VM from the host with SSH, do the following command in a host terminal:
```sh
$> ssh [user]@[IP_vm] -p [port_ssh]
# example:
$> ssh user@10.12.124.45 -p 6666
```

Finally, we need to modify the `/etc/ssh/sshd_config` file:
```sh
user@roger:> sudo vim /etc/ssh/sshd_config
```
The following line must be changed back to 'no':
```sh
...
PasswordAuthentification no
...
```

---

### Setting up Firewall

**Uncomplicated Firewall**

Instead of using iptables and its annoying syntax, we're gonna be using uncomplicated firewall (ufw)

You can either run these commands by hand (with `sudo`), or you put these in a `.sh` script, and run it with `sudo sh script.sh` (you might need to `chmod 755` the script file beforehand to run it)

```sh
ufw default deny incoming
ufw default allow outgoing

ufw allow 6666
ufw allow 25
ufw allow 80/tcp
ufw allow 443

ufw enable
```
After this, you can check everything is correct by doing `sudo ufw status`, the output should be like so:
```
Status: active

To                         Action      From
--                         ------      ----
[port_ssh]                 ALLOW       Anywhere
25                         ALLOW       Anywhere
80/tcp                     ALLOW       Anywhere
443                        ALLOW       Anywhere
[port_ssh] (v6)            ALLOW       Anywhere (v6)
25 (v6)                    ALLOW       Anywhere (v6)
80/tcp (v6)                ALLOW       Anywhere (v6)
443 (v6)                   ALLOW       Anywhere (v6)
```

---

### Setting up portsentry

First, we need to stop the currently running portsentry daemon by doing:
```sh
user@roger:> sudo /etc/init.d/portsentry stop
```

Then, we must activate advanced TCP and UDP mode - you can do this by modifying the file `/etc/default/portsentry` like such:
```ini
TCP_MODE="atcp"
UDP_MODE="audp"
```

Next, we must have portsentry block TCP and UDP scans, by writing the following settings into `/etc/portsentry/portsentry.conf`:
```ini
##################
# Ignore Options #
##################
# 0 = Do not block UDP/TCP scans.
# 1 = Block UDP/TCP scans.
# 2 = Run external command only (KILL_RUN_CMD)

BLOCK_UDP="1"
BLOCK_TCP="1"
```

In this same configuration file `/etc/portsentry/portsentry.conf`, you must comment/remove the current `KILL_ROUTE` line.
Instead of it, uncomment the corresponding `KILL_ROUTE` line which uses `iptables`, the line should look like this:
```ini
KILL_ROUTE="/sbin/iptables -I INPUT -s $TARGET$ -j DROP"
```

We can now restart the portsentry process, by doing the following command:
```sh
user@roger:> sudo /etc/init.d/portsentry start
```

---

### Setting up fail2ban

First you must create the following file: `/etc/fail2ban/jail.local`:
```sh
user@roger:> cat /etc/fail2ban/jail.local 
[sshd]
enable = true
banaction = iptables-multiport
port = [port_ssh]
filter = sshd
logpath = %(sshd_log)s
backend = %(sshd_backend)s
maxretry = 5
findtime = 30
bantime = 180

[sshd-ddos]
enable = true
port = [port_ssh]
filter = sshd-ddos
logpath = %(sshd_log)s
backend = %(sshd_backend)s
maxretry = 5
findtime = 30
bantime = 180

[http-get-dos]
enabled = true
port = http,https
filter = http-get-dos
logpath = /var/log/http_dos.log
maxretry = 100
findtime = 30
bantime = 6000

[http-post-dos]
enabled = true
port = http,https
filter = http-post-dos
logpath = /var/log/http_dos.log
maxretry = 60
findtime = 30
bantime = 6000
```

You must next create the http DOS attack log file that is referenced from the `jail.local` file:
```sh
user@roger:> sudo touch /var/log/http_dos.log
```

Then, we need to create two files (`http-get-dos.conf` and `http-post-dos.conf`) to configure fail2ban properly:
- `/etc/fail2ban/filter.d/http-get-dos.conf`
```sh
[Definition]
failregex = \[[^]]+\] \[.*\] \[client <HOST>\] "GET .*
ignoreregex =
```
- `/etc/fail2ban/filter.d/http-post-dos.conf`
```sh
[Definition]
failregex = \[[^]]+\] \[.*\] \[client <HOST>\] "POST .*
ignoreregex =
```

After all that, you need to start running the fail2ban service by doing:
```sh
user@roger:> sudo systemctl enable fail2ban
user@roger:> sudo systemctl restart fail2ban
```

After this, you should **reboot** your virtual machine.

---

### Script to update packages

To update packages regularly, you must create the following `.sh` script file:
- `/root/scripts/script_log.sh`
```sh
#!/bin/bash
apt-get update -y >> /var/log/update_script.log
apt-get upgrade -y >> /var/log/update_script.log
```

And we must give this file the proper permissions, and let `root` run it without using `sudo`:
```sh
user@roger:> sudo chmod 755 /root/scripts/script_log.sh
user@roger:> sudo chown root /root/scripts/script_log.sh
```

To have the script be run at the required times, you must modify the crontab file by doing:
```sh
user@roger:> sudo crontab -e
```
The previous command will prompt you to select a text editor, you must write this in the crontab file:
```sh
0 4 * * wed root /root/scripts/script_log.sh
@reboot root /root/scripts/script_log.sh
```

---

### Script to oversee crontab modifications

Let's create the following `.sh` script file:
- `/root/scripts/script_crontab.sh`
```sh
#!/bin/sh

CRON_FILE=/etc/crontab
CHECK_FILE=/root/.crontab-checker

if [ ! -f $CHECK_FILE ] || [ "`md5sum < $CRON_FILE`" != "`cat $CHECK_FILE`" ]
then
    echo "The crontab file has been modified !" | mail -s "root: crontab modified" root
    md5sum < $CRON_FILE > $CHECK_FILE;
    chmod 700 $CHECK_FILE;
fi
```
This script will create a file containing the MD5 checksum of our crontab to check against whenever it's changed.

Do not forget to set the correct permissions for this `.sh` script:
```sh
user@roger:> sudo chmod 755 /root/scripts/script_crontab.sh
user@roger:> sudo chown root /root/scripts/script_crontab.sh
```

To have the script be run at the required times, you must modify the crontab file by doing:
```sh
user@roger:> sudo crontab -e
```
The previous command will prompt you to select a text editor, you must write this in the crontab file:
```sh
0 0 * * * root /root/scripts/script_crontab.sh
```

---

### Web server: apache

We must first create a folder to hold our html website data, with the correct permissions:
```sh
user@roger:> sudo mkdir -p /var/www/init.[login].fr/html
user@roger:> sudo chown -R user:user /var/www/init.[login].fr/html
user@roger:> sudo chmod -R 755 /var/www/init.[login].fr
```

And now we can create a simple HTML index page to test the web server:
- `/var/www/init.[login].fr/html/index.html`
```xml
<html>
    <head>
        <title>Roger-Skyline</title>
    </head>
    <body>
        <h1>The website works!</h1>
        <p>Lorem ipsum</p>
    </body>
</html>
```

We need apache to know how to deliver this HTML content, so we'll create an apache config file:
- `/etc/apache2/sites-available/init.login.fr.conf`
```xml
<VirtualHost *:80>
    ServerAdmin admin@example.com
    ServerName init.[login].fr
    ServerAlias init.[login].fr
    DocumentRoot /var/www/init.[login].fr/html
    ErrorLog ${APACHE_LOG_DIR}/error.log
    CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>
```

We can now activate our server by doing the following commands:
```sh
user@roger:> cd /etc/apache2/sites-enabled
user@roger:> sudo rm 000-default.conf
user@roger:> sudo ln -s ../sites-available/init.login.fr.conf ./
user@roger:> sudo service apache2 restart
```

So as to have a valid SSL certificate, we then need to do the following commands:
```
user@roger:> cd /etc/ssl/certs/
user@roger:> sudo openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout roger.key -out roger.crt
```

And then we must add the port 443 config to our config file, so HTTPS can function:
- `/etc/apache2/sites-available/init.login.fr.conf`
```xml
<VirtualHost *:443>
    DocumentRoot /var/www/init.login.fr/html
    ServerName init.login.fr
    SSLEngine on
    SSLCertificateFile /etc/ssl/crt/roger.crt
    SSLCertificateKeyFile /etc/ssl/crt/roger.key
</VirtualHost>
```
Lancer la commande suivante sudo a2enmod ssl afin d'activer le module SSL d'apache, puis redemarrer le serveruweb
```sh
user@roger:> sudo systemctl restart apache2
```
(Though, you might want to `sudo reboot` just to be sure)

After this, you might wanna do some DoS/SlowLoris and nmap tests.

---

**Author:** aduquesn
