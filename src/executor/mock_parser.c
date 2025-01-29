#include "../../inc/minishell.h"

t_exec_data *get_test(int test_number)
{
    if (test_number == 0) return test_0();
    if (test_number == 1) return test_1();
    if (test_number == 2) return test_2();
    if (test_number == 3) return test_3();
    if (test_number == 4) return test_4();
    if (test_number == 5) return test_5();
    if (test_number == 6) return test_6();
    if (test_number == 7) return test_7();
    if (test_number == 8) return test_8();
    if (test_number == 9) return test_9();
    if (test_number == 10) return test_10();
    if (test_number == 11) return test_11();
    if (test_number == 12) return test_12();
    if (test_number == 13) return test_13();
    if (test_number == 14) return test_14();
    if (test_number == 15) return test_15();
    if (test_number == 16) return test_16();
    if (test_number == 17) return test_17();
    if (test_number == 18) return test_18();
    if (test_number == 19) return test_19();
    if (test_number == 20) return test_20();
    if (test_number == 21) return test_21();
    if (test_number == 22) return test_22();
    if (test_number == 23) return test_23();
    if (test_number == 24) return test_24();
    if (test_number == 25) return test_25();
    if (test_number == 26) return test_26();
    if (test_number == 27) return test_27();
    if (test_number == 28) return test_28();
    if (test_number == 29) return test_29();
    if (test_number == 30) return test_30();
    if (test_number == 31) return test_31();
    if (test_number == 32) return test_32();
    if (test_number == 33) return test_33();
    if (test_number == 34) return test_34();
    if (test_number == 35) return test_35();
    if (test_number == 36) return test_36();
    if (test_number == 37) return test_37();
    if (test_number == 38) return test_38();
    if (test_number == 39) return test_39();
    if (test_number == 40) return test_40();
    if (test_number == 41) return test_41();
    if (test_number == 42) return test_42();
    if (test_number == 43) return test_43();
    if (test_number == 44) return test_44();
    if (test_number == 45) return test_45();
    if (test_number == 46) return test_46();
    if (test_number == 47) return test_47();
    if (test_number == 48) return test_48();
    if (test_number == 49) return test_49();
    if (test_number == 50) return test_50();
    if (test_number == 51) return test_51();
    if (test_number == 52) return test_52();
    if (test_number == 53) return test_53();
    if (test_number == 54) return test_54();
    if (test_number == 55) return test_55();
    if (test_number == 56) return test_56();
    if (test_number == 57) return test_57();
    if (test_number == 58) return test_58();
    if (test_number == 59) return test_59();
    if (test_number == 60) return test_60();
    if (test_number == 61) return test_61();
    if (test_number == 62) return test_62();
    if (test_number == 63) return test_63();
    if (test_number == 64) return test_64();
    if (test_number == 65) return test_65();
    if (test_number == 66) return test_66();
    if (test_number == 67) return test_67();
    if (test_number == 68) return test_68();
    if (test_number == 69) return test_69();
    if (test_number == 70) return test_70();
    if (test_number == 71) return test_71();
    if (test_number == 72) return test_72();
    if (test_number == 73) return test_73();
    if (test_number == 74) return test_74();
    if (test_number == 75) return test_75();
    if (test_number == 76) return test_76();
    if (test_number == 77) return test_77();
    if (test_number == 78) return test_78();
    if (test_number == 79) return test_79();
    if (test_number == 80) return test_80();
    if (test_number == 81) return test_81();
    if (test_number == 82) return test_82();
    if (test_number == 83) return test_83();
    if (test_number == 84) return test_84();
    if (test_number == 85) return test_85();
    if (test_number == 86) return test_86();
    if (test_number == 87) return test_87();
    if (test_number == 88) return test_88();
    if (test_number == 89) return test_89();
    if (test_number == 90) return test_90();

    return (NULL);
}

t_redir *create_rdir(t_redir_type type, char *str)
{
    t_redir *new_re_dir = malloc (sizeof(t_redir));

    new_re_dir->next = NULL;
    new_re_dir->str = str;
    new_re_dir->error = NULL;
    new_re_dir->type = type;

    return (new_re_dir);
}

void add_redir_to_list(t_redir **head, t_redir *new_redir)
{
    t_redir *temp;

    
    if (!new_redir || !head)
        return;
    if (!(*head))
    {
        *head = new_redir;
        return ;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_redir;
    new_redir->next = NULL;
}
char **add_string_to_array(char *new_str, char **old_array) {
    int count = 0;
    
    while (old_array && old_array[count] != NULL)
        count++;
    char **new_array = malloc((count + 2) * sizeof(char *));
    if (!new_array)
        return NULL; 
    
    for (int i = 0; i < count; i++) 
    {
        new_array[i] = ft_strdup(old_array[i]);
        if (!new_array[i]) 
        {
            for (int j = 0; j < i; j++)
                free(new_array[j]);
            free(new_array);
            return NULL;
        }
    }
    
    new_array[count] = ft_strdup(new_str);
    if (!new_array[count]) 
    {
        for (int i = 0; i < count; i++)
            free(new_array[i]);
        free(new_array);
        return NULL;
    }
    new_array[count + 1] = NULL;
    

    if (old_array) 
    {
        for (int i = 0; i < count; i++)
            free(old_array[i]);
        free(old_array);
    }
    free(new_str);
    return new_array;
}

