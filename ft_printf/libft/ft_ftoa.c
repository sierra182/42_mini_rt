#include <stdlib.h>
#include <math.h>
#include <limits.h>

static int int_length(long n) {
    int length = (n <= 0) ? 1 : 0;
    while (n) {
        length++;
        n /= 10;
    }
    return length;
}

static void reverse_str(char *str, int len) {
    int start = 0;
    int end = len - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

static char *itoa(long n, char *str) {
    int i = 0;
    int is_negative = (n < 0);

    if (is_negative) {
        n = -n;
    }

    if (n == 0) {
        str[i++] = '0';
    }

    while (n != 0) {
        int digit = n % 10;
        str[i++] = digit + '0';
        n /= 10;
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse_str(str, i);

    return str;
}

char *ft_ftoa(double value) {
    long ipart = (long)value;
    int ipart_len = int_length(ipart);
    int total_len = ipart_len + 1;

    char *str = (char *)malloc(total_len + 1);
    if (str == NULL) {
        return NULL;
    }

    char *ipart_str = (char *)malloc(ipart_len + 1);
    if (ipart_str == NULL) {
        free(str);
        return NULL;
    }

    itoa(ipart, ipart_str);

    int i = 0;
    while (ipart_str[i] != '\0') {
        str[i] = ipart_str[i];
        i++;
    }

    free(ipart_str);

    str[i] = '\0';

    return str;
}