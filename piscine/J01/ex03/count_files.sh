find . \( -type f -or -type d \) -and \( -name "." -or -name "*" \) -print | wc -l | tr -d " "
