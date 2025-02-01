#include "./printf/libftprintf.h"

/*int main()
{
    const char *flag = "%7.2X";
    unsigned int x = 1515;

    ft_printf(flag, x);
    printf("\n");
    printf(flag, x);
    printf("\n");
    return 0;
}*/


int main() {
    const char *flags[] = {
        "%#20.15X", // Original flag in your example
        "%#-20.15X", // Left-justified flag '-'
        "%#+20.15X", // '+' flag (no effect on unsigned)
        "%#020.15X", // '0' flag (leading zeros)
        "%# 20.15X", // Space flag (no effect on unsigned)
        "%#20.5X",   // Precision smaller than width
        "%#8.12X",   // Precision larger than width
        "%#08.12X",  // '0' flag, precision larger than width
        "%#-8.12X",  // Left-justified, precision larger than width
        "%#10.6X",   // Width 10, precision 6
        "%#-10.6X",  // Left-justified, width 10, precision 6
        "%#010.6X",  // '0' flag, width 10, precision 6
        "%#-010.6X", // Left-justified with '0' flag (note: '-' takes precedence)
        "%#7X",      // Width 7, no precision
        "%#-7X",     // Left-justified, width 7
        "%#07X",     // '0' flag, width 7
        "%#-07X",    // Left-justified with '0' flag
        "%#12.0X",   // Width 12, precision 0
        "%#-12.0X",  // Left-justified, width 12, precision 0
        "%#012.0X",  // '0' flag, width 12, precision 0
        "%#-012.0X", // Left-justified with '0' flag
        "%#5.3X",    // Width 5, precision 3, less than the length of some numbers
        "%#7.2X",    // Width 7, precision 2, less than the length of some numbers
        "%#*.X",     // Variable width and no precision
        "%#*.*X",     // Variable width and precision
        "%20.15X",  // No flags
        "%-20.15X", // Left-justified flag '-'
        "%+20.15X", // '+' flag (no effect on unsigned)
        "%020.15X", // '0' flag (leading zeros)
        "% 20.15X", // Space flag (no effect on unsigned)
        "%20.5X",   // Precision smaller than width
        "%8.12X",   // Precision larger than width
        "%08.12X",  // '0' flag, precision larger than width
        "%-8.12X",  // Left-justified, precision larger than width
        "%10.6X",   // Width 10, precision 6
        "%-10.6X",  // Left-justified, width 10, precision 6
        "%010.6X",  // '0' flag, width 10, precision 6
        "%-010.6X", // Left-justified with '0' flag (note: '-' takes precedence)
        "%7X",      // Width 7, no precision
        "%-7X",     // Left-justified, width 7
        "%07X",     // '0' flag, width 7
        "%-07X",    // Left-justified with '0' flag
        "%12.0X",   // Width 12, precision 0
        "%-12.0X",  // Left-justified, width 12, precision 0
        "%012.0X",  // '0' flag, width 12, precision 0
        "%-012.0X", // Left-justified with '0' flag
        "%5.3X",    // Width 5, precision 3, less than the length of some numbers
        "%7.2X",    // Width 7, precision 2, less than the length of some numbers
    };

    unsigned int values[] = {0, 1, 9, 1515, 255, 4096, 65535, 1048576}; // Test with multiple values, including 0 and single-digit numbers
    int widths[] = {10, 15, 20, 5, 7}; // Include smaller widths
    int precisions[] = {3, 5, 8, 2}; // Include smaller precisions
    bool check = true;

    for (int i = 0; i < sizeof(flags)/sizeof(flags[0]); i++) {
        for (int j = 0; j < sizeof(values)/sizeof(values[0]); j++) {
            if (strstr(flags[i], "*")) {
                for (int k = 0; k < sizeof(widths)/sizeof(widths[0]); k++) {
                    for (int l = 0; l < sizeof(precisions)/sizeof(precisions[0]); l++) {
                        if (widths[k] != precisions[l]) {
                            printf("Testing flag: %s with width: %d, precision: %d and value: %u\n", flags[i], widths[k], precisions[l], values[j]);
                            ft_printf(flags[i], widths[k], precisions[l], values[j]);
                            printf("\n");
                            printf(flags[i], widths[k], precisions[l], values[j]);
                            printf("\n\n");
                        }
                    }
                }
            } else {
                printf("Testing flag: %s with value: %u\n", flags[i], values[j]);
                ft_printf(flags[i], values[j]);
                printf("\n");
                printf(flags[i], values[j]);
                printf("\n\n");
            }
        }
    }

    return 0;
}
