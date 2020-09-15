make
# passes each single binary in build/ to run.sh
ls -1 build/ | xargs sh run.sh
