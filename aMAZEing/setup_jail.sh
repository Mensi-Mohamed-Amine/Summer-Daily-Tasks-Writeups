#!/bin/bash


mkdir -p /home/user/jail/aMAZEing
cd /home/user

cp flag.txt /home/user/jail/aMAZEing 

cp maze /usr/bin

# copy_to_jail
# Define the jail directory
JAIL_DIR="/home/user/jail"

# List of commands to copy
COMMANDS=("cat" "socat" "ls" "clear" "sh" "bash" "maze")

# Copy each command and its dependencies
for cmd in "${COMMANDS[@]}"; do
    # Get the full path of the command
    cmd_path=$(which "$cmd")
    if [ -z "$cmd_path" ]; then
        echo "Command '$cmd' not found. Skipping."
        continue
    fi

    # Copy the command
    mkdir -p "$JAIL_DIR$(dirname "$cmd_path")"
    cp "$cmd_path" "$JAIL_DIR$cmd_path"

    # Copy dependencies
    for lib in $(ldd "$cmd_path" | grep -o '/[^ ]*'); do
        mkdir -p "$JAIL_DIR$(dirname "$lib")"
        cp "$lib" "$JAIL_DIR$lib"
    done
done

echo "Commands and dependencies copied to jail."

cp -a /home/user/jail/usr/bin /home/user/jail/bin



socat TCP-LISTEN:1337,reuseaddr,fork EXEC:'nsjail -q -Mo --chroot /home/user/jail --disable_clone_newnet --log nsjail.log -- /usr/bin/maze',pty,stderr 




