#ifndef EXECUTOR_TESTS_H
# define EXECUTOR_TESTS_H

# include "defines.h"
# include "structs.h"

char *build_full_path(const char *relative_path);
    //1. cat < input1.txt > out1.txt > out2.txt | wc | sed 's/t/c/g'                                                                                                                        
    //2. echo Hello World > output.txt | wc -w < output.txt                                                                                 PASSED* (if your in bash it sometimes says the output file is not found sometimes just returns the value of wc: 2)
    //3. ls | grep "txt" >> results.txt | sort                                                                                              PASSED                                                                                      
    //4. cat << EOF | wc -l                                                                                                                 PASSED                                                                                                     
    //5. cat input.txt input1.txt > combined.txt                                                                                            PASSED                                                                  
    //6. cat << EOF | grep "hello" > greetings.txt                                                                                          PASSED* (this works but, unlike bash, while the heredoc is running the output file is generated. This works as intended even if someone deletes this file because it gets remade just before execution)                                 
    //7. grep "error" log1.txt log2.txt | sort | tee errors_sorted.txt | wc -l > count.txt                                                  PASSED
    //8. ls > non_existent_dir/output.txt                                                                                                   PASSED                                                                                                 
    //9. ll > output.txt  | wc -l                                                                                                           PASSED (at home my pc has a ll command ?! so i did this changing the command - it is working)                                                                  
    //10. cat | cat | ls                                                                                                                    FAIL  (will have to be handled with signals to interrupt child)
    //11. cat << "" < input.txt                                                                                                             PASSED
    //12. cat << "" >> output.txt < input.txt (input doesnt exist)                                                                          PASSED (PASSED)                     
    //13. cat <missing <inf <<EOF <<ll                                                                                                      FAIL (bash runs the HEREDOC and then complains about the input file. this solution imediatly complais about the input file missing and exits)
    //14. grep hi <./test_files/infile                                                                                                      PASS
    //15. grep hi "<infile" <         ./test_files/infile                                                                                   PASS
    //16. echo hi < ./test_files/infile bye bye                                                                                             BUILTIN
    //17. grep hi <./test_files/infile_big <./test_files/infile                                                                             PASS
    //18. echo <"./test_files/infile" "bonjour       42"                                                                                    BUILTIN
    //19. cat <"./test_files/file name with spaces"                                                                                         PASS
    //20. cat <./test_files/infile_big ./test_files/infile                                                                                  PASS
    //21. cat <"1""2""3""4""5"                                                                                                              PASS
    //22. echo <"./test_files/infile" <missing <"./test_files/infile"                                                                       BUILTIN
    //23. echo <missing <"./test_files/infile" <missing                                                                                     BUILTIN
    //24. cat <"./test_files/infile"                                                                                                        PASS   
    //25. echo <"./test_files/infile_big" | cat <"./test_files/infile"                                                                      BUILTIN
    //26. echo <"./test_files/infile_big" | cat "./test_files/infile"                                                                       BUILTIN
    //27. echo <"./test_files/infile_big" | echo <"./test_files/infile"                                                                     BUILTIN
    //28. echo hi | cat <"./test_files/infile"                                                                                              BUILTIN
    //29. echo hi | cat "./test_files/infile"                                                                                               BUILTIN
    //30. cat <"./test_files/infile" | echo hi                                                                                              BUILTIN
    //31. cat <"./test_files/infile" | grep hello                                                                                           PASSED
    //32. cat <"./test_files/infile_big" | echo hi                                                                                          BUILTIN
    //33. cat <missing                                                                                                                      PASSED
    //34. cat <missing | cat                                                                                                                PASSED
    //35. cat <missing | echo oi                                                                                                            BUILTIN
    //36. cat <missing | cat <"./test_files/infile"                                                                                         PASSED
    //37. echo <123 <456 hi | echo 42                                                                                                       BUILTIN
    //38. ls >./outfiles/outfile01                                                                                                          PASSED
    //39. echo hi >         ./outfiles/outfile01 bye                                                                                        BUILTIN                           
    //40. ls >./outfiles/outfile01 >./outfiles/outfile02                                                                                    PASSED
    //41. ls >./outfiles/outfile01 >./test_files/invalid_permission                                                                         PASSED
    //42. ls >"./outfiles/outfile with spaces"                                                                                              PASSED
    //43. ls >"./outfiles/outfile""1""2""3""4""5"                                                                                           PASSED
    //44. ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"                                               PASSED
    //45. ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission                                      PASSED
    //46. cat <"./test_files/infile" >"./outfiles/outfile01"                                                                                PASSED
    //47. echo hi >./outfiles/outfile01 | echo bye
    //48. echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye
    //49. echo hi | echo >./outfiles/outfile01 bye
    //50. echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02
    //51. echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02
    //52. echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye
    //53. echo hi >./test_files/invalid_permission | echo bye
    //54. echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye
    //55. echo hi | echo bye >./test_files/invalid_permission
    //56. echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission
    //57. echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01
    //58. cat <"./test_files/infile" >./test_files/invalid_permission                                                                       PASSED
    //59. cat >./test_files/invalid_permission <"./test_files/infile"                                                                       PASSED
    //60. cat <missing >./outfiles/outfile01                                                                                                PASSED
    //61. cat >./outfiles/outfile01 <missing                                                                                                PASSED
    //62. cat <missing >./test_files/invalid_permission                                                                                     PASSED
    //63. cat >./test_files/invalid_permission <missing                                                                                     FIXED (trap first redir error with char *redir_error) atually not fixed because no other command will execute
    //64. cat >./outfiles/outfile01 <missing >./test_files/invalid_permission                                                               PASSED
    //65. ls >>./outfiles/outfile01                                                                                                         PASSED
    //66. ls >>      ./outfiles/outfile01                                                                                                   PASSED
    //67. ls >>./outfiles/outfile01 >./outfiles/outfile01                                                                                   PASSED
    //68. ls >./outfiles/outfile01 >>./outfiles/outfile01                                                                                   PASSED
    //69. ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02                                                             PASSED
    //70. ls >>./outfiles/outfile01 >>./outfiles/outfile02                                                                                  PASSED
    //71. ls >>./test_files/invalid_permission                                                                                              PASSED
    //72. ls >>./test_files/invalid_permission >>./outfiles/outfile01                                                                       PASSED
    //73. ls >>./outfiles/outfile01 >>./test_files/invalid_permission                                                                       PASSED
    //74. ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02                                                 PASSED
    //75. ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02                                                              PASSED
    //76. ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing                                                              PASSED
    //77. ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02 | cat < ./input1.txt > /outfiles/outfile03      FAIL
    //78. cat <main.c>./outfiles/outfile                                                                                                    PASSED
    //79. cat <main.c|ls                                                                                                                    PASSED
    //80. echo hi >>./outfiles/outfile01 | echo bye
    //81. echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye
    //82. echo hi | echo >>./outfiles/outfile01 bye
    //83. echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02
    //84. echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02
    //85. echo hi >>./test_files/invalid_permission | echo bye
    //86. echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye
    //87. echo hi | echo bye >>./test_files/invalid_permission
    //88. echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission

t_exec_data *test_90();
t_exec_data *test_89();
t_exec_data *test_88();
t_exec_data *test_87();
t_exec_data *test_86();
t_exec_data *test_85();
t_exec_data *test_84();
t_exec_data *test_83();
t_exec_data *test_82();
t_exec_data *test_81();
t_exec_data *test_80();
t_exec_data *test_79();
t_exec_data *test_78();
t_exec_data *test_77();
t_exec_data *test_76();
t_exec_data *test_75();
t_exec_data *test_74();
t_exec_data *test_73();
t_exec_data *test_72();
t_exec_data *test_71();
t_exec_data *test_70();
t_exec_data *test_69();
t_exec_data *test_68();
t_exec_data *test_67();
t_exec_data *test_66();
t_exec_data *test_65();
t_exec_data *test_64();
t_exec_data *test_63();
t_exec_data *test_62();
t_exec_data *test_61();
t_exec_data *test_60();
t_exec_data *test_59();
t_exec_data *test_58();
t_exec_data *test_57();
t_exec_data *test_56();
t_exec_data *test_55();
t_exec_data *test_54();
t_exec_data *test_53();
t_exec_data *test_52();
t_exec_data *test_51();
t_exec_data *test_50();
t_exec_data *test_49();
t_exec_data *test_48();
t_exec_data *test_47();
t_exec_data *test_46();
t_exec_data *test_45();
t_exec_data *test_44();
t_exec_data *test_43();
t_exec_data *test_42();
t_exec_data *test_41();
t_exec_data *test_40();
t_exec_data *test_39();
t_exec_data *test_38();
t_exec_data *test_37();
t_exec_data *test_36();
t_exec_data *test_35();
t_exec_data *test_34();
t_exec_data *test_33();
t_exec_data *test_32();
t_exec_data *test_31();
t_exec_data *test_30();
t_exec_data *test_29();
t_exec_data *test_28();
t_exec_data *test_27();
t_exec_data *test_26();
t_exec_data *test_25();
t_exec_data *test_24();
t_exec_data *test_23();
t_exec_data *test_22();
t_exec_data *test_21();
t_exec_data *test_20();
t_exec_data *test_19();
t_exec_data *test_18();
t_exec_data *test_17();
t_exec_data *test_16();
t_exec_data *test_15();
t_exec_data *test_14();
t_exec_data *test_13();
t_exec_data *test_12();
t_exec_data *test_11();
t_exec_data *test_10();
t_exec_data *test_9();
t_exec_data *test_8();
t_exec_data *test_7();
t_exec_data *test_6();
t_exec_data *test_5();
t_exec_data *test_4();
t_exec_data *test_3();
t_exec_data *test_2();
t_exec_data *test_1();
t_exec_data *test_0();


#endif