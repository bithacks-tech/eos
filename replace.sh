#!/bin/bash
sudo sed -i "s/$1/$2/g"  `grep $1 -rl . --exclude-dir=".git*"`
sudo find . -name "*$1*" | xargs -i echo sudo mv \"{}\" \"{}\" | sudo sed "s/$1/$2/2g" | sh 
