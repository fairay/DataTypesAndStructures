#include <stdio.h>
#include <string.h>

#define MAX_LEN 30
#define MAX_STR 50
#define MNT_SIZE 60

#define DIGITS "0123456789"

#define OK               0
#define WRONG_FORMAT    -1
#define EMPTY_STR       -2
#define ORDER_OVERFLOW  -3

typedef struct
{
    int sign;
    int mnt[MAX_LEN];
    int digits;
    int order;
} real_number;

void show_error_message(int code)
{
    printf("Error: ");
    switch (code)
    {
        case WRONG_FORMAT:
            printf("incorrect number format");
            break;
        case ORDER_OVERFLOW:
            printf("order owerflowded");
            break;
    }
    printf("\n");
}

int is_digit(char a)
{
    return ((a <= '9') && (a >= '0'));
}

void shift_str_l(char *str, int pos)
{
    int i = pos;

    while (str[i] != '\0')
    {
        str[i] = str[i + 1];
        i++;
    }
}

void shift_str_r(char *str, int pos)
{
    for (int i = strlen(str) + 1; i > pos; i--)
        str[i] = str[i - 1];
}

void delete_char_r(char *str, int pos, char del_chr)
{
    while (str[pos] == del_chr)
        shift_str_l(str, pos);
}

void delete_char_l(char *str, int pos, char del_chr)
{
    while (str[pos] == del_chr)
    {
        shift_str_l(str, pos);
        pos--;
    }
}

void format_input(char *str)
{
    int is_e = 0, is_point = 0;
    int e_pos;
    int i = 0;
    int is_mnt = 0;
    int mant_beg = 1, mant_end;

    while ((str[i] != '\0') && (str[i] != 'E'))
    {
        if (is_digit(str[i]))
        {
            is_mnt = 1;
            break;
        }
        i++;
    }

    if (!is_mnt)
        strcpy(str, "ERROR");

    if (strchr(str, 'E') != NULL)
        is_e = 1;
    if (strchr(str, '.') != NULL)
        is_point = 1;

    // Удаление лишних пробелов
    delete_char_r(str, 0, ' ');
    delete_char_l(str, strlen(str) - 1, ' ');

    if (is_e)
    {
        e_pos = strcspn(str, "E");
        delete_char_r(str, e_pos + 1, ' ');
        delete_char_l(str, e_pos - 1, ' ');
        e_pos = strcspn(str, "E");

        if (strchr("+-", str[e_pos + 1]) == NULL)
        {
            shift_str_r(str, e_pos + 1);
            str[e_pos + 1] = '+';
        }

        mant_end = e_pos - 1;
    }
    else
        mant_end = strlen(str) - 1;

    if (strchr("+-", str[0]) == NULL)
    {
        shift_str_r(str, 0);
        str[0] = '+';
        mant_end++;
    }

    //Удаление незначащих нулей
    if (is_point)
        delete_char_l(str, mant_end, '0');
    delete_char_r(str, mant_beg, '0');

    if (!is_e)
        strcat(str, "E+0");
}

int input_number(real_number *num, char *str)
{
    int i;
    int is_point = 0;
    int is_signific = 0;
    int order_sign = 1;
    int order_nums = 0;
    int order = 0;

    /*
    if (!((strncmp(str, "+.E", 3)) && (strncmp(str, "-.E", 3)) &&
          (strncmp(str, "+E", 2)) && (strncmp(str, "-E", 2))))
        return WRONG_FORMAT;
    */

    // Определение знака
    if (str[0] == '+')
        num -> sign = 1;
    else
        num -> sign = -1;

    // Запись мантисы
    i = 1;
    num -> digits = 0;
    num -> order = 0;
    while (str[i] != 'E')
    {
        if (is_digit(str[i]))
        {
            if (num -> digits == 30)
                return WRONG_FORMAT;

            if ((!is_signific) && (str[i] != '0'))
                is_signific = 1;

            if (is_signific)
            {
                num -> mnt[num -> digits] = str[i] - '0';
                num -> digits += 1;
            }
            else
                num -> order -= 1;

            if (!is_point)
                num -> order += 1;
        }
        else if (str[i] == '.')
        {
            if (is_point)
                return WRONG_FORMAT;
            else
                is_point = 1;
        }
        else
            return WRONG_FORMAT;
        i++;
    }

    // Знак порядка
    i += 1;
    if (str[i] == '+')
        order_sign = 1;
    else
        order_sign = -1;
    i++;

    // Значение порядка
    while (str[i] != '\0')
    {
        if (is_digit(str[i]))
        {
            order_nums += 1;
            if (order_nums > 5)
                return WRONG_FORMAT;

            order *= 10;
            order += str[i] - '0';
        }
        else
            return WRONG_FORMAT;
        i++;
    }

    if (order_nums == 0)
        return WRONG_FORMAT;
    order *= order_sign;
    num -> order += order;

    return OK;
}

void output_number(real_number num)
{
    if (num.sign == 1)
        printf("+");
    else
        printf("-");

    printf("0.");
    for (int i = 0; i < num.digits; i++)
        printf("%d", num.mnt[i]);

    printf(" E ");
    if (num.order >= 0)
        printf("+");
    printf("%d\n", num.order);
}

int multiply(real_number a, real_number b, real_number* res)
{
    int res_mnt[MNT_SIZE];
    int i, j, k;
    int buffer = 0;

    for (k = 0; k < MNT_SIZE; k++)
        res_mnt[k] = 0;

    for (i = a.digits - 1; i >= 0; i--)
    {
        if (!a.mnt[i])
            continue;
        for (j = b.digits - 1; j >= 0; j--)
        {
            buffer += a.mnt[i] * b.mnt[j] + res_mnt[i + j + 1];
            res_mnt[i + j + 1] = buffer % 10;
            buffer /= 10;
        }
        res_mnt[i + j + 1] = buffer % 10;
        buffer /= 10;
    }
    res -> order = a.order + b.order - 1;
    if (!res_mnt[0])
    {
        for (i = 0; i < 59; i++)
            res_mnt[i] = res_mnt[i + 1];
        if (!res_mnt[0])
        {
            res -> order = 0;
            a.sign = 1;
            b.sign = 1;
        }
    }

    else
        res -> order += 1;
    if ((res -> order > 99999) || (res -> order < -99999))
        return ORDER_OVERFLOW;

    // Округление
    if (res_mnt[30] >= 5)
    {
        i = 29;
        while (res_mnt[i] == 9)
            res_mnt[i--] = 0;
        res_mnt[i] += 1;
    }

    // Подсчёт значаших цифр мантисы
    i = (a.digits + b.digits > 30) ? 30 : a.digits + b.digits;
    while ((!res_mnt[i - 1]) && (i > 1))
        i--;
    i = (i) ? i : 1;
    res -> digits = i;

    for (i = 0; i < res -> digits; i++)
        res -> mnt[i] = res_mnt[i];

    res -> sign = a.sign * b.sign;
    return OK;
}

int main(void)
{
    real_number a, b, result;
    int code;
    char input_str[MAX_STR];

    printf("Programm for multiplying two real numbers\n\n");
    printf("Format of entry numbers:\n");
    printf("Real number format: < 31 significant numbers, (1.2313) \n  or \n");
    printf("Exponential form: < 31 significant numbers, < 6 degree order, (-131.1321 E +06)\n");
    printf("Exemple of input numbers: .00025, +123001., -123.456, 1234567 E -20, 1234567 E 20, 123.4567 E23\n\n");
    printf("Input two numbers:\n");
    printf("    5    10   15   20   25   30\n");
    printf("Orders --|----|----|----|----|\n");

    gets(input_str);
    format_input(input_str);
    code = input_number(&a, input_str);
    if (code != OK)
    {
        show_error_message(code);
        return code;
    }

    gets(input_str);
    format_input(input_str);
    code = input_number(&b, input_str);
    if (code != OK)
    {
        show_error_message(code);
        return code;
    }

    code = multiply(a, b, &result);
    if (code != OK)
    {
        show_error_message(code);
        return code;
    }

    printf("Result: ");
    output_number(result);
    return OK;
}
