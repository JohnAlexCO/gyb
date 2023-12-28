#include "argv.c"
#include "loadf.c"

void init(int argc, char *argv[]){
    init_loadf(argc, argv);
    init_argv(argc, argv);

}