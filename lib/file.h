#define fd_stdin        0
#define fd_stdout       1
#define fd_stderr       2
#define fd_stdbuffsize  1024*1024*4

typedef struct {
    char name[255];
    char *content;
    uint64_t index;
    uint64_t size;
} file_t;

void file_read  (ture_t *ture, file_t *file, uint64_t buffer, uint64_t size);
void file_write (ture_t *ture, file_t *file, uint64_t buffer, uint64_t size);