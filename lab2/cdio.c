#include "head.h"

static int month_len[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int is_leap(int year)
{
    if (year % 4 != 0)
        return 0;
    else if ((year % 100 == 0) && (year % 400 != 0))
        return 0;
    return 1;
}

int check_dob_validity(dob_t dob)
{
    if ((dob.month == 0) || (dob.month > 12) || (dob.day == 0))
        return WRONG_DOB;

    if ((dob.month == 2) && (dob.day == 29))
    {
        if (is_leap(dob.year))
            return OK;
        else
            return WRONG_DOB;
    }

    if (dob.day > month_len[dob.month - 1])
        return WRONG_DOB;
    return OK;
}

int convert_days(dob_t date, int is_leap)
{
    int i = 0;
    int days = date.day;
    while (i + 1 < date.month)
        days += month_len[i++];
    if (is_leap && (date.month > 2))
        days += 1;
    return days;
}

int check_phone_validity(char phone[])
{
    if (strlen(phone) > MAX_LEN_PHONE)
        return WRONG_FORMAT;
    else if (strspn(phone, PHONE_SYMBLOS) != strlen(phone))
        return WRONG_PHONE;
    return OK;
}

int check_str_validity(char str[], int max_len)
{
    if (strlen(str) == 0)
        return WRONG_FORMAT;
    if (strlen(str) > max_len)
        return WRONG_FORMAT;
    return OK;
}

void print_sub(sub_t sub)
{
    printf("%20s |", sub.surname);
    printf("%20s |", sub.name);
    printf("%16s |", sub.phone);
    printf("%20s |", sub.address);
    printf("%9s |", sub.status);

    if (strcmp(sub.status, PERSONAL))
    {
        printf("%20s", sub.info.off.post);
        printf("%20s", sub.info.off.org);
    }
    else
    {
        printf("%02hu.", sub.info.pers.day);
        printf("%02hu.", sub.info.pers.month);
        printf("%04hu", sub.info.pers.year);
    }

    printf("\n");
}

int scan_sub(sub_t* sub)
{
    int sc = 0;
    int code;

    printf("Surname (<=%d simbols):\t\t", MAX_LEN_NAME);
    sc += scanf("%s", sub->surname);
    code = check_str_validity(sub->surname, MAX_LEN_NAME);
    if (code != OK)
        return code;

    printf("Name (<=%d simbols):\t\t", MAX_LEN_NAME);
    sc += scanf("%s", sub->name);
    code = check_str_validity(sub->name, MAX_LEN_NAME);
    if (code != OK)
        return code;

    printf("Phone (<=%d simbols):\t\t", MAX_LEN_PHONE);
    sc += scanf("%s", sub->phone);
    code = check_phone_validity(sub->phone);
    if (code != OK)
        return code;
    code = check_str_validity(sub->phone, MAX_LEN_PHONE);
    if (code != OK)
        return code;

    printf("Addres (<=%d simbols, no spases): ", MAX_LEN_ADR);
    sc += scanf("%s", sub->address);
    code = check_str_validity(sub->address, MAX_LEN_ADR);
    if (code != OK)
        return code;

    printf("Status (%s or %s):\t", PERSONAL, OFFICIAL);
    sc += scanf("%s", sub->status);

    if (strcmp(sub->status, OFFICIAL) && strcmp(sub->status, PERSONAL))
        return WRONG_STATUS;
    else if (sc != 5)
        return WRONG_FORMAT;

    sc = 0;
    if (strcmp(sub->status, PERSONAL) == 0)
    {
        printf("Date of birth (DD MM YY):\t\t");
        sc += scanf("%husd", &sub->info.pers.day);
        sc += scanf("%husd", &sub->info.pers.month);
        sc += scanf("%husd", &sub->info.pers.year);
        if (sc != 3)
            return WRONG_FORMAT;
        else if (check_dob_validity(sub->info.pers) != OK)
            return WRONG_DOB;
    }
    else
    {
        printf("Post (<=%d simbols):\t\t", MAX_LEN_NAME);
        sc += scanf("%s", sub->info.off.post);
        code = check_str_validity(sub->info.off.post, MAX_LEN_NAME);
        if (code != OK)
            return code;

        printf("Organisation (<=%d simbols):\t", MAX_LEN_NAME);
        sc += scanf("%s", sub->info.off.org);
        code = check_str_validity(sub->info.off.org, MAX_LEN_NAME);
        if (code != OK)
            return code;
        if (sc != 2)
            return WRONG_FORMAT;
    }
    return OK;
}

void shift_table_l(sub_t table[], int pos, int n)
{
    for (int i = pos; i < n - 1; i++)
        table[i] = table[i + 1];
}


// Deletion check functions
int is_del_surname(sub_t sub, char key[])
{
    return (!strcmp(key, sub.surname));
}

int is_del_name(sub_t sub, char key[])
{
    return (!strcmp(key, sub.name));
}

int is_del_phone(sub_t sub, char key[])
{
    return (!strcmp(key, sub.phone));
}

int is_del_address(sub_t sub, char key[])
{
    return (!strcmp(key, sub.address));
}

int is_del_status(sub_t sub, char key[])
{
    return (!strcmp(key, sub.status));
}

int is_del_post(sub_t sub, char key[])
{
    return (!strcmp(key, sub.info.off.post));
}

int is_del_org(sub_t sub, char key[])
{
    return (!strcmp(key, sub.info.off.org));
}

int is_del_year(sub_t sub, int key)
{
    return (key == sub.info.pers.year);
}

int is_del_month(sub_t sub, int key)
{
    return (key == sub.info.pers.month);
}

int is_del_day(sub_t sub, int key)
{
    return (key == sub.info.pers.day);
}
