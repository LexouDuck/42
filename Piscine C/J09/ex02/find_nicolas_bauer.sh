grep -i "^n" $1 | cut -f2- | grep -i "^bauer" | rev | cut -f2 | rev | grep "-"
