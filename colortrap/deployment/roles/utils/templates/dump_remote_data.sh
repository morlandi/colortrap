#!/bin/bash
# Script to dump db and media from remote host
# Mario Orlandi, 2016

REMOTE_HOST="{{ inventory_hostname }}"
REMOTE_DBNAME="{{ database.db_name }}"
REMOTE_DBOWNER="{{ database.db_user }}"
REMOTE_MEDIA_FOLDER='{{ django.media_root }}'
LOCAL_DBNAME="{{ database.db_name }}"
LOCAL_DBOWNER="{{ database.db_user }}"
LOCAL_MEDIA_FOLDER="./../public/media"

PREFIX=$(date +%Y-%m-%d_%H.%M.%S)_

#
# Helpers
#

# Show script usage
help() {
    echo ''
    echo 'Retrieve db and or media from remote host.'
    echo 'Mario Orlandi, 2016'
    echo ''
    echo 'Usage:'
    echo '    $ ./dump_remote_data [options] action source'
    echo 'where:'
    echo '    action = sync|dump'
    echo '    source = media|db|all'
    echo 'options:'
    echo '    -f, --force = never prompt (use default values for all parameters)'
    echo ''
}

# Ask user to confirm or edit the value of specified variable
ask_user() {
    varname=$1
    default_value=${!varname}
    read -e -p "$varname ($default_value) ? " answer
    if [ -z "$answer" ]; then
        answer=$default_value
    fi
    eval $varname=$answer
}

do_dump_media() {
    echo '***'
    echo '*** dump media ...'
    echo '***'

    SYNC_FOLDER='./'$REMOTE_HOST
    COMMAND="rsync -avz -e 'ssh' --delete --progress --partial --exclude=CACHE/ $REMOTE_HOST:$REMOTE_MEDIA_FOLDER/ $SYNC_FOLDER/media/"
    echo $COMMAND
    $COMMAND

    echo ''
    MEDIA_DUMP_FILENAME="${PREFIX}${LOCAL_DBNAME}.media.tar.gz"
    echo "cd $SYNC_FOLDER && tar czf $MEDIA_DUMP_FILENAME media && cd ./.."
    cd $SYNC_FOLDER && tar czf $MEDIA_DUMP_FILENAME media && cd ./..

    echo ''
    echo '=========================================================================='
    COMMAND="ls -lh $SYNC_FOLDER/$MEDIA_DUMP_FILENAME"
    echo $COMMAND
    $COMMAND
    echo '=========================================================================='
}

do_dump_db() {
    echo '***'
    echo '*** dump db ...'
    echo '***'

    DB_DUMP_FILENAME="${PREFIX}${REMOTE_DBNAME}.sql.gz"
    DB_DUMP_FILEPATH="./${REMOTE_HOST}/${DB_DUMP_FILENAME}"
    ssh $REMOTE_HOST "sudo -u postgres pg_dump $REMOTE_DBNAME | sed -e 's/OWNER TO.*;$/OWNER TO ${LOCAL_DBOWNER};/' | gzip" > $DB_DUMP_FILEPATH

    echo ''
    echo '=========================================================================='
    COMMAND="ls -lh $DB_DUMP_FILEPATH"
    echo $COMMAND
    $COMMAND
    echo '=========================================================================='
}

do_sync_media() {
    echo '***'
    echo '*** sync media ...'
    echo '***'

    SYNC_FOLDER='./'$REMOTE_HOST
    COMMAND="rsync -avz -e 'ssh' --delete --progress --partial --exclude=CACHE/ $REMOTE_HOST:$REMOTE_MEDIA_FOLDER/ $SYNC_FOLDER/media/"
    echo $COMMAND
    $COMMAND

    COMMAND="rsync -avz -e 'ssh' --delete --progress --partial --exclude=CACHE/ $SYNC_FOLDER/media/ $LOCAL_MEDIA_FOLDER/"
    echo $COMMAND
    $COMMAND

    echo ''
    echo '=========================================================================='
    COMMAND="ls -lh $LOCAL_MEDIA_FOLDER"
    echo $COMMAND
    $COMMAND
    echo '=========================================================================='
}

do_sync_db() {
    echo '***'
    echo '*** sync db ...'
    echo '***'

    psql --dbname="template1" --command="drop database if exists $LOCAL_DBNAME"
    psql --dbname="template1" --command="create database $LOCAL_DBNAME owner $LOCAL_DBOWNER"
    ssh $REMOTE_HOST "sudo -u postgres pg_dump $REMOTE_DBNAME | sed -e 's/OWNER TO.*;$/OWNER TO ${LOCAL_DBOWNER};/' | gzip" | gunzip | psql $LOCAL_DBNAME

    # SQL="update django_site set domain='`hostname`.`hostname -d`' where id=1"
    # echo $SQL
    # psql -d $LOCAL_DBNAME -c "$SQL"
    # psql $LOCAL_DBNAME --command="select * from django_site"

    echo ''
    echo '=========================================================================='
    echo "psql --dbname=\"template1\" --command=\"\l $LOCAL_DBNAME;\""
    psql --dbname="template1" --command="\l $LOCAL_DBNAME;"
    echo '=========================================================================='
}

################################################################################

#
# Parse command line
#

action=''
source=''
skip_params=0
for var in "$@"
do
    # action ?
    if [ "$var" == "sync" ] || [ "$var" == "dump" ] ; then
        eval action=$var
    fi
    # source ?
    if [ "$var" == "db" ] || [ "$var" == "media" ] || [ "$var" == "all" ] ; then
        eval source=$var
    fi
    # skip_params ?
    if [ "$var" == "-f" ] || [ "$var" == "--force" ] ; then
        eval skip_params=1
    fi
done

#
# Sanity check
#

if [ "$action" != "sync" ] && [ "$action" != "dump" ]; then
    help
    exit
fi
if [ "$source" != "db" ] && [ "$source" != "media" ] && [ "$source" != "all" ]; then
    help
    exit
fi

#
# Ask user to confirm or edit relevant parameters (unless 'force' option has been specified)
#

if [ $skip_params == 0 ] ; then
    echo ''
    echo 'Please confirm and/or edit parameters:'
    echo '--------------------------------------'
    ask_user 'REMOTE_HOST'
    if [ "$source" == "db" ] || [ "$source" == "all" ] ; then
        ask_user 'REMOTE_DBNAME'
        ask_user 'REMOTE_DBOWNER'
    fi
    if [ "$source" == "media" ] || [ "$source" == "all" ] ; then
        ask_user 'REMOTE_MEDIA_FOLDER'
    fi
    if [ "$source" == "db" ] || [ "$source" == "all" ] ; then
        ask_user 'LOCAL_DBNAME'
        ask_user 'LOCAL_DBOWNER'
    fi
    if [ "$source" == "media" ] || [ "$source" == "all" ] ; then
        ask_user 'LOCAL_MEDIA_FOLDER'
    fi
fi

#
# Summarize all relevant parameters
#

echo ''
echo 'Parameters summary:'
echo '-------------------'
echo 'REMOTE_HOST         : '$REMOTE_HOST
if [ "$source" == "db" ] || [ "$source" == "all" ] ; then
    echo 'REMOTE_DBNAME       : '$REMOTE_DBNAME
    echo 'REMOTE_DBOWNER      : '$REMOTE_DBOWNER
fi
if [ "$source" == "media" ] || [ "$source" == "all" ] ; then
    echo 'REMOTE_MEDIA_FOLDER : '$REMOTE_MEDIA_FOLDER
fi
if [ "$source" == "db" ] || [ "$source" == "all" ] ; then
    echo 'LOCAL_DBNAME        : '$LOCAL_DBNAME
    echo 'LOCAL_DBOWNER       : '$LOCAL_DBOWNER
fi
if [ "$source" == "media" ] || [ "$source" == "all" ] ; then
    echo 'LOCAL_MEDIA_FOLDER  : '$LOCAL_MEDIA_FOLDER
fi
echo ''

#
# Ask if user wants to proceed
#

if [ $skip_params == 0 ] ; then
    result=" "
    while [ "$result" != "n" ] && [ "$result" != "N" ] && [ "$result" != "y" ] && [ "$result" != "Y" ] ; do
        read -p "Ready to $action $source. Proceed (y/n) ? " result
    done
    if [ "$result" != "y" ] && [ "$result" != "Y" ] ; then
        echo "aborted"
        exit
    fi
fi

#
# Perform actions
#

if [ "$action" == "dump" ]; then
    if [ "$source" == "db" ] || [ "$source" == "all" ] ; then
        do_dump_db
    fi
    if [ "$source" == "media" ] || [ "$source" == "all" ] ; then
        do_dump_media
    fi
fi

if [ "$action" == "sync" ]; then
    if [ "$source" == "db" ] || [ "$source" == "all" ] ; then
        do_sync_db
    fi
    if [ "$source" == "media" ] || [ "$source" == "all" ] ; then
        do_sync_media
    fi
fi
