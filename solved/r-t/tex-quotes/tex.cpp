#include <cstdio>

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }

    void process() {
        bool open = true;

        while (b != 0) {
            if (b == '"') {
                if (open) {
                    putchar('`');
                    putchar('`');
                }
                else {
                    putchar('\'');
                    putchar('\'');
                }
                open = !open;
            }
            else
                putchar(b);
            read();
        }
    }
};

int main()
{
    Reader rr;

    rr.process();

    return 0;
}
