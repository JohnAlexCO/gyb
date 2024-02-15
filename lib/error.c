#define error(...) do { \
    printf(__VA_ARGS__); \
    exit(1); \
    } while(0)
