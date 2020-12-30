

sed -e 's%$DATE%'"$(date +%m-%d-%y)"'%' \
    -e 's%$USERNAME%'"$username"'%' \
    -e 's%$FILEDIR%'"$FILE"'%' \
    -e 's%$PROBLEMURL%'"$URL"'%' \
    "$SRC" > "$proj_root/$file"