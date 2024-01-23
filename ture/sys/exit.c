void syscall_exit(ture_t *ture) {
    uint64_t status = ture->br;
    exit(status);
}