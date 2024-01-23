// https://man7.org/linux/man-pages/man2/close.2.html
void syscall_close(ture_t *ture) {
    uint64_t fd = ture->br;
    if (fd < 3) { error("syscall_close not allowed to close stdin, stdout, or stderr\n"); }
    if ( fd_table[fd] == NULL ) { error("syscall_close called on invalid file descriptor\n"); }
    free(fd_table[fd]->content);
    fd_table[fd]->index = 0;
    fd_table[fd]->size = 0;
    fd_table[fd] = NULL;
    ture->ar = 0;
}