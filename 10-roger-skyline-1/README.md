# 42: roger-skyline-1

---

### Debian VM Setup

- _OS Image_: Download a [Debian netinst iso](https://www.debian.org/distrib/)
- _RAM_: 1.0 GB (1024 MB) of access memory
- _ROM_: 8.0 GB Hard Disk, fixed size

**Localisation**

- _Language_: English
- _Area_: France
- _Locale_: American English (en-US)
- _Keyboard_: [you decide]

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
root@roger:> apt-get install crontab
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

We need to know the name of the 2nd network interface, you can see its name by doing:
```sh
user@roger:> ip a
```
Usually, it should be something like `enp0s8`

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

# Primary network interfaces

allow-hotplug enp0s3
iface enp0s3 inet dhcp

allow-hotplug [2nd_interface]
iface [2nd_interface] inet static address 192.168.56.3 netmask 255.255.255.252
```

---

### Setting up SSH

To set up SSH connections, we need to modify the `/etc/ssh/sshd_config` file:
```sh
user@roger:> sudo vim /etc/ssh/sshd_config
```
The following 4 lines must be present in the file, by either uncommenting these lines in the file, or by manually adding these lines yourself:
```sh
Port [anything except 22]
PasswordAuthentification yes
PermitRootLogin no
PubkeyAuthentication yes
```

After this, you must generate a **public key** from your host machine by doing this command:
```sh
$> ssh-keygen
```
After which, you can copy the generated **key** from the file `~/.ssh/id_rsa.pub` on the host machine, and write that same **key** into the file `~/.ssh/authorized_keys` inside the VM, so as to allow SSH connections.
```sh
user@roger:> mkdir ~/.ssh
user@roger:> echo '[RSA public key file contents]' > ~/.ssh/authorized_keys
```

With this done, your VM should have internet access and SSH set up.
All you need to do for these to work is reboot the VM.

To access the VM from the host with SSH, do the following command in a host terminal:
```sh
$> ssh [user]@[IP] -p [VM_SSH_PORTNUMBER]
# example:
$> ssh user@192.168.56.3 -p 23
```

---

### Setting up Firewall

**Configuring iptables**


