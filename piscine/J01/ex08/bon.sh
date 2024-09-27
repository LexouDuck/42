ldapsearch -Q -LLL "(sn=*bon*)" | grep "cn:" | wc -l | tr -d " "
