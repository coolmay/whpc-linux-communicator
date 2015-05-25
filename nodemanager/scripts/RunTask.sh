#!/bin/bash

. common.sh

[ -z "$1" ] && echo "task execution id not specified" && exit 202
[ -z "$2" ] && echo "run.sh not specified" && exit 202
[ -z "$3" ] && echo "user name not specified" && exit 202

rootLogFolder=/opt/hpcnodemanager/logs
trustLogFile=${rootLogFolder}${1}_trust.txt
failedTrustLogFile=${rootLogFolder}/failed_${1}_trust.txt
trustKeysDir=${rootLogFolder}/${1}_${3}/
sshFolder=/home/${3}/.ssh/
if [ "$3" = "root" ]; then
	sshFolder=/root/.ssh/
fi

/bin/bash WaitForTrust.sh "$3" "$1" > $trustLogFile 2>&1 || (mv $trustLogFile $failedTrustLogFile; mkdir $trustFileDir && cp -rf ${sshFolder}* $trustKeysDir; exit 203) && /bin/bash $2

