#include <ctype.h>  // Pour isdigit
#include <math.h>   // Pour pow

double ft_atof(const char *str) {
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1;
    int exponent = 0;

    // Ignorer les espaces initiaux
    while (*str == ' ')
        str++;

    // Gérer le signe
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Analyser la partie entière du nombre
    while (isdigit(*str)) {
        result = result * 10.0 + (*str - '0');
        str++;
    }

    // Gérer la partie fractionnaire du nombre
    if (*str == '.') {
        str++;
        double divisor = 10.0;
        while (isdigit(*str)) {
            fraction += (*str - '0') / divisor;
            divisor *= 10.0;
            str++;
        }
    }

    // Combinez la partie entière et la partie fractionnaire
    result += fraction;

    // Gérer l'exposant éventuel
    if (*str == 'e' || *str == 'E') {
        str++;
        int exp_sign = 1;
        if (*str == '-') {
            exp_sign = -1;
            str++;
        } else if (*str == '+') {
            str++;
        }
        while (isdigit(*str)) {
            exponent = exponent * 10 + (*str - '0');
            str++;
        }
        exponent *= exp_sign;
    }

    // Appliquer l'exposant
    if (exponent != 0) {
        result *= pow(10, exponent);
    }

    return result * sign;
}
