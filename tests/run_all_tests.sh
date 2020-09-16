make
# passes each single binary in build/ to run.sh
ls -1 build/ | xargs sh run.sh

# run other tests
# make sure our shell doesn't stuck on the 64kb pipe problem
echo "cat testfile_65kb.txt | cat | wc -l" | ../phipsshell
