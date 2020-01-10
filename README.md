# PolicyManager
A simple root privilege policy manager for Linux and macOS
### Installation
``` bash
sudo sh << END
cp -r etc/* /etc
mkdir -p /usr/local/bin
g++ usr/local/bin/policyman.cpp -o /usr/local/bin/policyman
chown root:root /usr/local/bin/policyman 2>/dev/null    # for Linux
chown root:wheel /usr/local/bin/policyman 2>/dev/null   # for macOS
chmod +s /usr/local/bin/policyman
END
```
### Usage
The policy scripts are in /etc/policyman.d/policies, and all policy scripts are Bash scripts.
#### How to write policies
Here are two examples.

The first example (/etc/policyman.d/policies/example_policy):
``` bash
# Avaliable variables
# $calleruid  [variable]  - UID of the caller of PolicyManager
# $username   [variable]  - The username of the caller
# $program    [variable]  - The program which the caller would like to execute.
# $args       [array]     - The arguments of the program
echo "n"         # y - yes   n - no   Here gives the answer to whether the caller's request is allowed. If two scripts gives different answer, the result will be "yes".
echo HOME USER   # These environment variables will be kept, if the result is "yes".
############################## WARNING: NEVER keep the environment variable PATH ! ##############################
# This policy script does nothing but make it keep the environment variable HOME and USER if other policy scripts answer "yes".
```
The second example (/etc/policyman.d/policies/authorized_actions):
``` bash
if [ "$(dirname "$program")" == "/etc/authorized_actions" ]; then
	echo "y"
fi
# This policy script allows all programs under /etc/authorized_actions run with root privilege.
```
