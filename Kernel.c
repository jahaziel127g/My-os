void kernel_main() {
    char *video_memory = (char *)0xB8000;
    *video_memory = 'K';  // Display 'K' on screen
}
