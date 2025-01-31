#define MEM_SIZE 1024 * 1024  // 1MB for testing

static unsigned char memory[MEM_SIZE];
static int next_free = 0;

void* malloc(int size) {
    if (next_free + size > MEM_SIZE) return 0;
    void* ptr = &memory[next_free];
    next_free += size;
    return ptr;
}
