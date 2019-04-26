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

Manual setup - select `SCSI1 (0,0,0) (sda) - etc`, that's the HDD.
Then confirm, and right under that HDD, there will be the `FREE SPACE` partition under it.
- _Partition 1_: 4.2 GB -> Primary -> Beginning -> Use as: ext4 -> Mount Point: `/`
- _Partition 2_: 1.0 GB -> Primary -> Beginning -> Use as: Swap Area
- _Partition 3_: Remaining Space -> Primary -> Use as: ext4 -> Mount Point: `/home`

- _Additionnal CDs to scan_: No

**Package Mangager**
- _Country_: France
- _Mirror_: ftp.fr.debian.org
- _HTTP Proxy_: None

**Config**
- _Particpative user survey_: No
- _Software_: Debian Desktop Environment, with SSH Server and Standard system utilities
- _GRUB Boot Loader_: Yes, /dev/sda

---

### Setting up SSH

**Installing packages**

Connect as the non-root user
```sh
user@roger$> apt-get update -y && apt-get upgrade -y
user@roger$> apt-get install sudo
user@roger$> apt-get install vim
user@roger$> apt-get install iptables-persistent
user@roger$> apt-get install fail2ban
user@roger$> apt-get install sendmail
user@roger$> apt-get install portsentry
adduser
```
