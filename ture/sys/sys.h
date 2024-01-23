#define fd_table_size 64
file_t *fd_table[fd_table_size];

void syscall_read(ture_t *ture);
void syscall_write(ture_t *ture);
void syscall_open(ture_t *ture);
void syscall_close(ture_t *ture);
void syscall_brk(ture_t *ture);
void syscall_exit(ture_t *ture);
void ture_syscall(ture_t *ture);