# PolicyManager
A simple root privilege policy manager for Linux and macOS.
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
The policy scripts are in /etc/policyman.d/policies, and all policy scripts shoule be Bash scripts.
#### How to write policies
Here are two examples.

The first example (/etc/policyman.d/policies/example_policy):
``` bash
# Avaliable variables
# $calleruid  [variable]  - Caller's UID
# $username   [variable]  - Caller's  username
# $program    [variable]  - The program which the caller wants to execute
# $args       [array]     - Arguments
echo "n"         # y - yes   n - no   Give the answer here to whether the caller's request is allowed. If two scripts give different answer, the result will be "yes".
echo HOME USER   # These environment variables will be kept, if the result is "yes".
############################## WARNING: NEVER keep the environment variable PATH! ##############################
# This policy script does nothing but make it keep HOME and USER if other policy scripts answer "yes".
```
The second example (/etc/policyman.d/policies/authorized_actions):
``` bash
if [ "$(dirname "$program")" == "/etc/authorized_actions" ]; then
	echo "y"
fi
# This policy script allows all programs under /etc/authorized_actions run with root privilege.
```
