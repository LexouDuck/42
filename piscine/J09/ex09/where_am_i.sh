var=$(ifconfig | grep "inet" | grep "netmask" | tr "b" "\n" | cut -f 2 | tr -d "inet" | tr -d "netmask" | tr -d "broadcast" | cut -d " " -f 2)
if [[ $var ]]
then
	echo $var | tr " " "\n"
else
	echo "Je suis perdu!\n"
fi