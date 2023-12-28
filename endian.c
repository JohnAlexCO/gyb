int endianness = 0;

void ifEndian(){
    integer check = 0xffddeeccbbaa9988;
    char *cherk = (char*) &check;
    if (*cherk == 0x88){
        endianness = true;
    } else { endianness = false; }
}

integer flipEndian(integer value){
    return  ((value & 0x00000000000000FF) << 56) |
            ((value & 0x000000000000FF00) << 40) |
            ((value & 0x0000000000FF0000) << 24) |
            ((value & 0x00000000FF000000) << 8)  |
            ((value & 0x000000FF00000000) >> 8)  |
            ((value & 0x0000FF0000000000) >> 24) |
            ((value & 0x00FF000000000000) >> 40) |
            ((value & 0xFF00000000000000) >> 56);
}

integer littleEndian(integer value) {
    if (!endianness) { return flipEndian(value);
    } else { return value; } }

integer bigEndian(integer value) {
    if (endianness) { return flipEndian(value);
    } else { return value; } }
