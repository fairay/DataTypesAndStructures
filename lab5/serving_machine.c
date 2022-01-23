#include "head.h"

options_t default_options(void)
{
    options_t opt =
    {
        .t1 = T1,
        .t2 = T2,
        .t3 = T3,
        .t4 = T4,
        .step = SHOW_STEP,
        .max_1 = MAX_REQUEST
    };
    return opt;
}

options_t test_options(void)
{
    options_t opt =
    {
        .t1 = TEST1,
        .t2 = TEST2,
        .t3 = TEST3,
        .t4 = TEST4,
        .step = TEST_SIZE + 1,
        .max_1 = TEST_SIZE
    };
    return opt;
}


void print_options(options_t opt)
{
    printf(">>> Serving machine options:\n");
    printf("________________________________________\n");
    printf("Input time\n");
    printf("Queue 1) T1:\t[ %3f, %3f ]\n", opt.t1[0], opt.t1[1]);
    printf("Queue 2) T2:\t[ %3f, %3f ]\n", opt.t2[0], opt.t2[1]);
    printf("\nProcessing time\n");
    printf("Queue 1) T3:\t[ %3f, %3f ]\n", opt.t3[0], opt.t3[1]);
    printf("Queue 2) T4:\t[ %3f, %3f ]\n", opt.t4[0], opt.t4[1]);
    printf("\nPrint step: %d\n", opt.step);
    printf("Max processing requests: %d\n", opt.max_1);
    printf("________________________________________\n\n");
}

options_t change_options(options_t opt)
{
    int sc, mode = 1;
    float time_min, time_max;
    float* change_t;

    while (mode >= 1 && mode <= 4)
    {
        printf(">>> Select changing T option (1, 2, 3, 4) or 0 for exit: ");
        sc = scanf("%d", &mode);
        if (sc != 1)
            mode = -1;
        else if (mode != 0)
        {
            printf("Input time range T%d [t_min, t_max]: ", mode);
            sc = scanf("%f%f", &time_min, &time_max);
            if (sc != 2)
                mode = -1;
            else if (time_min > time_max || time_min < 0 || time_max <= 0)
                mode = -2;
        }

        switch (mode)
        {
            case 1:
                change_t = &opt.t1[0];
                break;
            case 2:
                change_t = &opt.t2[0];
                break;
            case 3:
                change_t = &opt.t3[0];
                break;
            case 4:
                change_t = &opt.t4[0];
                break;
            case 0:
                printf("Exit\n");
                return opt;
            case -1:
                show_error_message(WRONG_FORMAT);
                printf("Exit\n");
                return opt;
            case -2:
                show_error_message(WRONG_TIME);
                printf("Exit\n");
                return opt;
        }
        (*change_t) = time_min;
        (*(change_t + 1)) = time_max;
    }
    return opt;
}

float rnd_time(float t[2])
{
    return t[0] + (t[1] - t[0]) * ((float)rand() / RAND_MAX);
}

float min(float a1, float a2)
{
    if (a1 < a2)
        return a1;
    else
        return a2;
}


stats_t sv_work_list(options_t opt, free_mem_t *free_adr)
{
    stats_t stat = {
        .time = 0,
        .memory = 0
    };

    int is_print = 0;

    float pre_time, time = 0;
    float downtime = 0;

    float proc_time = 0;
    int proc_mode = 0;
    int proc_n1 = 0, proc_n2 = 0;

    double len_time1 = 0, len_time2 = 0;
    double stay_time1 = 0, stay_time2 = 0;

    float add_t1 = rnd_time(opt.t1);
    float add_t2 = rnd_time(opt.t2);

    stat.time = clock();

    lqueue_t queue1, queue2;
    queue1 = create_lque(free_adr);
    queue2 = create_lque(free_adr);

    while (proc_n1 < opt.max_1)
    {
        // printf("Current time:\t %.3f \n", time);
        // Adding new requests
        if (time >= add_t1)
        {
            push_lque(&queue1, add_t1);
            add_t1 = rnd_time(opt.t1) + time;
        }

        if (time >= add_t2)
        {
            push_lque(&queue2, add_t2);
            add_t2 = rnd_time(opt.t2) + time;
        }

        //  Update SM status and process
        if (time >= proc_time)
        {
            switch (proc_mode)
            {
                case 1:
                    proc_n1++;
                    is_print = proc_n1 % opt.step == 0;

                    if (lque_empty(queue1))
                    {
                        if (lque_empty(queue2))
                            proc_mode = 0;
                        else
                            proc_mode = 2;
                    }
                    break;

                case 2:
                    proc_n2++;
                    if (lque_empty(queue2))
                    {
                        if (lque_empty(queue1))
                            proc_mode = 0;
                        else
                            proc_mode = 1;
                    }
                    break;

                case 0:
                    if (!lque_empty(queue1))
                        proc_mode = 1;
                    if (!lque_empty(queue2))
                        if (lque_empty(queue1) || peak_lque(queue2) < peak_lque(queue1))
                            proc_mode = 2;
                    break;
            }

            if  (proc_mode == 1)
            {
                stay_time1 += time - pop_lque(&queue1);
                proc_time = rnd_time(opt.t3) + time;
            }
            else if (proc_mode == 2)
            {
                stay_time2 += time - pop_lque(&queue2);
                proc_time = rnd_time(opt.t4) + time;
            }
        }


        // Print current info
        if (is_print)
        {
            is_print = 0;
            printf("\n___________________________________ Done: %5d\n", proc_n1);
            printf("Current time:\t %.3f \n\n", time);

            printf("\nQueue 1:\n");
            printf("Length:\t %d\n", lque_len(queue1));
            printf("Average length:\t %.2lf\n", len_time1 / time);
            printf("Average request stay time: %.2lf\n", stay_time1 / proc_n1);

            printf("\nQueue 2:\n");
            printf("Length:\t %d\n", lque_len(queue2));
            printf("Average length:\t %.2lf\n", len_time2 / time);
            printf("Average request stay time: %.2lf\n", stay_time2 / proc_n2);
        }

        pre_time = time;
        time = min(add_t1, add_t2);
        if (proc_mode == 0)
            downtime += time - pre_time;
        else
            time = min(time, proc_time);

        len_time1 += lque_len(queue1) * (time - pre_time);
        len_time2 += lque_len(queue2) * (time - pre_time);
    }
    time = pre_time;
    pre_time = (proc_n1 * (opt.t3[1] + opt.t3[0]) + proc_n2 * (opt.t4[1] + opt.t4[0])) / 2.0 + downtime;

    if (opt.step < opt.max_1)
    {
        printf("\n\n------------------------------------------------------------------------\n");
        printf("Modeling completed!\n\n");

        printf("Time:\t\t %.3f\n", time);
        printf("Downtime:\t%.3f\n", downtime);
        printf("Queue 1: In - %d \t Out - %d\n", lque_len(queue1) + proc_n1, proc_n1);
        printf("Queue 2: In - %d \t Out - %d\n", lque_len(queue2) + proc_n2, proc_n2);

        printf("\nComparing time and predicted time (Queue 1 and 2 processing time + downtime)\n");
        printf("Time: %.3f \t Predicted time: %.3f \t Error: %.3f %%\n",
               time,  pre_time, fabs(pre_time - time) / pre_time * 100);
        printf("------------------------------------------------------------------------\n");
    }

    delete_lque(&queue1);
    delete_lque(&queue2);

    stat.memory = sizeof(cell_t) * list_len(*free_adr);
    stat.time = (clock() - stat.time) * 1000 / CLK_TCK;
    return stat;
}

stats_t sv_work_arr(options_t opt)
{
    stats_t stat = {
        .time = 0,
        .memory = 0
    };
    int is_print = 0;

    float pre_time, time = 0;
    float downtime = 0;

    float proc_time = 0;
    int proc_mode = 0;
    int proc_n1 = 0, proc_n2 = 0;

    double len_time1 = 0, len_time2 = 0;
    double stay_time1 = 0, stay_time2 = 0;

    float add_t1 = rnd_time(opt.t1);
    float add_t2 = rnd_time(opt.t2);

    stat.time = clock();

    aqueue_t queue1, queue2;
    queue1 = create_aque();
    queue2 = create_aque();

    while (proc_n1 < opt.max_1)
    {
        // Adding new requests
        if (time >= add_t1)
        {
            push_aque(&queue1, add_t1);
            add_t1 = rnd_time(opt.t1) + time;
        }

        if (time >= add_t2)
        {
            push_aque(&queue2, add_t2);
            add_t2 = rnd_time(opt.t2) + time;
        }

        //  Update SM status and process
        if (time >= proc_time)
        {
            switch (proc_mode)
            {
                case 1:
                    proc_n1++;
                    is_print = proc_n1 % opt.step == 0;

                    if (aque_empty(queue1))
                    {
                        if (aque_empty(queue2))
                            proc_mode = 0;
                        else
                            proc_mode = 2;
                    }
                    break;

                case 2:
                    proc_n2++;
                    if (aque_empty(queue2))
                    {
                        if (aque_empty(queue1))
                            proc_mode = 0;
                        else
                            proc_mode = 1;
                    }
                    break;

                case 0:
                    if (!aque_empty(queue1))
                        proc_mode = 1;
                    if (!aque_empty(queue2))
                        if (aque_empty(queue1) || peak_aque(queue2) < peak_aque(queue1))
                            proc_mode = 2;
                    break;
            }

            if  (proc_mode == 1)
            {
                stay_time1 += time - pop_aque(&queue1);
                proc_time = rnd_time(opt.t3) + time;
            }
            else if (proc_mode == 2)
            {
                stay_time2 += time - pop_aque(&queue2);
                proc_time = rnd_time(opt.t4) + time;
            }
        }


        // Print current info
        if (is_print)
        {
            is_print = 0;
            printf("\n___________________________________ Done: %5d\n", proc_n1);
            printf("Current time:\t %.3f \n\n", time);

            printf("\nQueue 1:\n");
            printf("Length:\t %d\n", aque_len(queue1));
            printf("Average length:\t %.2lf\n", len_time1 / time);
            printf("Average request stay time: %.2lf\n", stay_time1 / proc_n1);

            printf("\nQueue 2:\n");
            printf("Length:\t %d\n", aque_len(queue2));
            printf("Average length:\t %.2lf\n", len_time2 / time);
            printf("Average request stay time: %.2lf\n", stay_time2 / proc_n2);
        }

        pre_time = time;
        time = min(add_t1, add_t2);
        if (proc_mode == 0)
            downtime += time - pre_time;
        else
            time = min(time, proc_time);

        len_time1 += aque_len(queue1) * (time - pre_time);
        len_time2 += aque_len(queue2) * (time - pre_time);
    }
    time = pre_time;
    pre_time = (proc_n1 * (opt.t3[1] + opt.t3[0]) + proc_n2 * (opt.t4[1] + opt.t4[0])) / 2.0 + downtime;
    if (opt.step < opt.max_1)
    {
        printf("\n\n------------------------------------------------------------------------\n");
        printf("Modeling completed!\n\n");

        printf("Time:\t\t %.3f\n", time);
        printf("Downtime:\t%.3f\n", downtime);
        printf("Queue 1: In - %d \t Out - %d\n", aque_len(queue1) + proc_n1, proc_n1);
        printf("Queue 2: In - %d \t Out - %d\n", aque_len(queue2) + proc_n2, proc_n2);

        printf("\nComparing time and predicted time (Queue 1 and 2 processing time + downtime)\n");
        printf("Time: %.3f \t Predicted time: %.3f \t Error: %.3f %%\n",
               time,  pre_time, fabs(pre_time - time) / pre_time * 100);
        printf("------------------------------------------------------------------------\n\n");
    }

    stat.memory = sizeof(float) * (queue1.size + queue2.size);
    delete_aque(&queue1);
    delete_aque(&queue2);

    stat.time = (clock() - stat.time) * 1000 / CLK_TCK;
    return stat;
}
