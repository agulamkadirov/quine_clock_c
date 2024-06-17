#include <stdio.h>
#include  <time.h>
#include <unistd.h>

#define ANSI_RED "\033[1;31m"
#define ANSI_DEFAULT "\033[0m"
#define FONT_WIDTH 3*2
#define FONT_HEIGHT 5
// we left 2 columns empty between 2 fonts
// that's why we're adding extra 2*7+1
#define SOURCE_WIDTH FONT_WIDTH*(6+2) + 15

// these 2 variables are defined in linking
// start of section .source_code
extern const char _s[];
// end of section .source_code
extern const char _e[];

const unsigned int fonts[] = {31599,19812,14479,31207,23524,29411,29679,30866,31727,31719,1040};

int font_set(int fi, int r, int c)
{
    int font = fonts[fi];
    return font & (1 << (r*3 + c));
}

void display_source() {
    while(1) {
        time_t now = time(NULL);
        struct tm *stm = localtime(&now);
        int r = 0;

        char* ptr = _s;
        while(ptr != _e) {
            if(r >= FONT_HEIGHT) {
                for(int c = 0; c < SOURCE_WIDTH && ptr != _e; ++c, ++ptr) {
                    printf("%c", *ptr);
                }
                ++r;
                printf("\n");
                continue;
            }

            int clock_fonts[8] = {
                (int)stm->tm_hour / 10, stm->tm_hour % 10,
                10,
                (int)stm->tm_min / 10, stm->tm_min % 10,
                10,
                (int)stm->tm_sec / 10, stm->tm_sec % 10,
            };
            for(int c = 0; c < SOURCE_WIDTH && ptr != _e; ++c) {
                if(c % 8 == 6) {
                    printf(ANSI_DEFAULT);
                    printf("%c", *ptr);
                    ++ptr;
                    printf("%c", *ptr);
                    ++ptr;
                    ++c;
                    continue;
                }
                if( font_set(clock_fonts[c/8], 4-r, ((c%8)/2)) ) {
                    printf(ANSI_RED);
                    printf("%c", *ptr);
                } else {
                    printf(ANSI_DEFAULT);
                    printf("%c", *ptr);
                }
                ++ptr;
            }
            printf(ANSI_DEFAULT);
            ++r;
            printf("\n");
        }

        sleep(1);
        printf("\n\033[%dA\033[%dD",r+2,0);
    }
}

int main() {
    display_source();
    return 0;
}
