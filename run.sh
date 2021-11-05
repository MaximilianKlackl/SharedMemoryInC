gcc -lrt sender.c -o sender
gcc -lrt receiver.c -o receiver

./sender &
./receiver