#!/bin/bash
read -p "Write BitOS to /dev/sda? (Will Delete All Data) [y/N] " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
	echo "Writing BitOS to /dev/sda ..."
	sudo dd if=output/bitos.iso of=/dev/sda
	echo "Done!"
fi
