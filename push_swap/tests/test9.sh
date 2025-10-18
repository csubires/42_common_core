clear
echo "Memory leaks"
echo
echo "In this section, we'll test memory leaks using leaks command."
echo
echo
echo
echo "Press enter to start testing."
read
# Memory leaks 1
clear
echo "Memory leaks"
echo
echo "First test: Test memory leaks of push_swap with invalid input."
echo
echo "Test input: leaks -atExit -- ./push_swap 1 4 42 8 7 one"
echo
echo "Right output is 'Error' without memoryleaks."
echo
echo "User output:"
leaks -atExit -- ./push_swap 1 4 42 8 7 one
echo
echo
echo
echo "Press enter to move forward."
read
# Memory leaks 2
clear
echo "Memory leaks"
echo
echo "Second test: Test memory leaks of push_swap with valid input."
echo
echo "Test input: leaks -atExit -- ./push_swap 3 2 1"
echo
echo "Check that there is no memoryleaks."
echo
echo "User output:"
leaks -atExit -- ./push_swap 3 2 1
echo
echo
echo
echo "Press enter to move forward."
read
# Memory leaks 3
clear
echo "Memory leaks"
echo
echo "Third test: Test memory leaks of push_swap with valid input of 505 integers."
echo
echo "Test input: leaks -atExit -- ./push_swap <505 random values>"
echo
echo "Check that there is no memoryleaks."
echo
echo "User output:"
leaks -atExit -- ./push_swap 6304 1892 7047 4184 -5020 3937 3745 9094 5334 770 -7976 3722 -9732 1287 -8591 -3297 -2336 -4809 6888 -8999 -4099 -1550 2585 -2577 2796 4414 6450 4185 7844 -1161 -1580 -5337 -558 -2579 -335 -3505 8296 -6143 -3047 2334 4039 -5304 -8337 -3413 5079 -7621 5622 182 6919 7188 -98 2085 8275 5749 1529 5560 2024 -4494 3808 -3543 -1691 -6174 -1881 8154 -6997 -6173 -6414 4680 -948 8870 -282 9678 623 700 -7151 -1750 6050 2991 4830 -3849 -1395 9241 -2192 -9736 8403 -5872 -4890 -5549 8638 -3361 7289 -391 9728 -8350 2116 -4278 -3018 4808 3821 8866 4487 -5023 5259 6856 -5296 -3607 661 108 -5196 -288 -7064 -491 -5790 4901 -6670 -6494 5452 -9132 -1660 149 -6728 8649 8373 -6193 7547 -7786 5458 4526 -5652 1925 -6397 -7923 -3310 -6426 -4567 7695 7977 -1700 9552 3154 -8361 4701 -8704 -7293 3268 -2898 9852 2289 6100 6985 8167 6155 5821 6722 7765 -8556 7126 -2508 -4663 -371 -1181 -4862 -326 -5249 5576 5793 -3398 -1281 7 -5125 -7830 6318 -8799 3160 18 -4314 -7115 -5316 -8384 -3349 -447 -8492 5132 6056 1489 2449 2752 7694 6383 -6833 -8177 966 9824 320 -9438 7914 6548 -4511 3913 1710 -2106 -7640 -7063 6806 -7498 7810 -7975 -7408 -1168 1609 140 -6147 -5653 -4254 5873 7586 3950 1469 7397 6487 6838 -4428 2594 191 -9288 -8889 -8955 7984 -9281 -3702 9973 2259 -740 6815 -2666 -2888 8165 7090 8594 4665 -9014 741 -3514 9040 3947 -8412 -6564 -7158 -4540 7252 8538 4116 -7018 5045 -8804 -8178 -611 5416 -6102 -7462 -6619 -5219 -4163 -5566 -8159 8287 4968 9140 1555 2103 -9457 6158 -3676 -965 6456 -5754 -3235 3694 9065 -1503 1540 -6521 -3118 -971 7483 3014 -5159 -8986 -1392 -9384 4388 4415 5044 -6469 484 3316 -8611 871 -6425 7546 -2815 5021 7581 7815 -9889 1807 -9376 -9880 3650 -8667 -4808 -8064 -3265 -1302 -3213 4358 9400 5460 5182 -6428 9408 7752 -2023 -7889 -7138 -3437 -6022 5040 5693 -4195 -1327 856 -6317 7108 -7233 9690 7337 -9278 8659 -8206 2838 3043 4422 6007 -4247 -121 247 -9290 -6274 -5591 -1962 -8147 -8648 1197 7936 -5973 -585 -6104 -496 2760 -1220 -5132 7283 8971 2670 -1412 -2289 1657 1405 -8498 9500 5358 -7853 9609 -1900 2710 -939 8388 3855 1195 -3342 4143 8552 -6115 -2277 -8189 -3634 -1605 6720 3432 5172 7056 2450 -2513 -4126 4803 -3081 7084 -818 -6188 2929 9707 -7491 -2083 -9475 1731 -5262 4658 -6929 3466 -9312 7478 -5036 -5884 -3254 -557 1527 -5478 -8917 5183 -2300 1771 -7130 -3494 -2536 5229 6560 2559 4197 9805 5055 -36 -6876 830 4223 -8859 2472 22 1092 -2809 -374 7359 8426 481 4017 -739 -5729 -4393 4122 3451 1331 8288 -4578 -6948 -4655 -3070 4821 -7932 -2503 -4391 -1258 7092 9151 -1444 -5822 5794 6788 454 5861 2939 -7712 -5792 619 -8956 -2623 879 3070 -3785 2230 -9843 -8423 8806 -3745 -2889 -8879 6346 -6239 -404 5118 4529 5985 8536 -6573 4133 -2008 -1334 -7898 7045 -565 7494 -8896 3964 -1354 7849 8478
echo
echo
echo "Third test: Test memory leaks of push_swap with valid input of 505 integers."
echo
echo
echo
echo "Press enter to move forward."
read
# Memory leaks 4a
clear
echo "Memory leaks"
echo
echo "4th test (1/2): Test memory leaks of checker with invalid input."
echo
echo "Test input: ./push_swap 1 42 one | leaks -atExit --  ./checker 1 42 one"
echo
echo "Right output is 'Error' without memoryleaks."
echo
echo "User output:"
./push_swap 1 42 one | leaks -atExit --  ./checker 1 42 one
echo
echo
echo
echo "Press enter to move forward."
read
# Memory leaks 4b
clear
echo "Memory leaks"
echo
echo "4th test (2/2): Test memory leaks of checker with invalid input."
echo
echo "Test input: ./push_swap 1 42 3 | leaks -atExit --  ./checker 1 42 one"
echo
echo "Right output is 'Error' without memoryleaks."
echo
echo "User output:"
./push_swap 1 42 3 | leaks -atExit --  ./checker 1 42 one
echo
echo
echo
echo "Press enter to move forward."
read
# Memory leaks 5
clear
echo "Memory leaks"
echo
echo "5th test: Test memory leaks of checker with valid input."
echo
echo "Test input: ./push_swap 3 2 1 | leaks -atExit --  ./checker 3 2 1"
echo
echo "Right output is 'OK' without memoryleaks."
echo
echo "User output:"
./push_swap 3 2 1 | leaks -atExit --  ./checker 3 2 1
echo
echo
echo
echo "Press enter to move forward."
read
# CHECKER
clear
echo "Checker program - Error management"
echo
echo "In this section, we'll evaluate the checker's error management.
If at least one fails, no points will be awarded for this
section. Move to the next one."
echo
echo
echo
echo "Press enter to start testing."
read
# Error management 1
clear
echo "Checker program - Error management"
echo
echo "First test: Run checker with non numeric parameters."
echo
echo "Test input: ./checker a b c"
echo
echo "Right output is 'Error'."
echo
echo "User output:"
./checker a b c
echo
echo
echo
echo "Press enter to move forward."
read
# Error management 2
clear
echo "Checker program - Error management"
echo
echo "Second test: Run checker with a duplicate numeric parameter."
echo
echo "Test input: ./checker 1 2 4 42 1"
echo
echo "Right output is 'Error'."
echo
echo "User output:"
./checker 1 2 4 42 1
echo
echo
echo
echo "Press enter to move forward."
read
# Error management 3
clear
echo "Checker program - Error management"
echo
echo "Third test: Run checker with only numeric parameters including one
greater than MAX_INT."
echo
echo "Test input: ./checker 1 2 3 4 2147483648"
echo
echo "Right output is 'Error'."
echo
echo "User output:"
./checker 1 2 3 4 2147483648
echo
echo
echo
echo "Press enter to move forward."
read
# Error management 4
clear
echo "Checker program - Error management"
echo
echo "4th test: Run checker without any parameters. The program must
not display anything and give the prompt back."
echo
echo "Test input: ./checker"
echo
echo "Right output is display nothing and give the prompt back."
echo
echo "User output:"
./checker
echo "This is the next line."
echo
echo
echo
echo "Press enter to move forward."
read
# Error management 5
clear
echo "Checker program - Error management"
echo
echo "5th test: Run checker with valid parameters, and write an action that
doesn't exist during the instruction phase."
echo
echo "Test input: ./checker 1 2 3 42 420 666"
echo
echo "Right output is 'Error'."
echo
echo "Write an action that doesn't exist: (for example: pc)"
./checker 1 2 3 42 420 666
echo
echo
echo
echo "Press enter to move forward."
read
# Error management 6
clear
echo "Checker program - Error management"
echo
echo "6th test: Run checker with valid parameters, and write an action with
one or several spaces before and/or after the action during
the instruction phase."
echo
echo "Test input: ./checker 1 2 3 42 420 666"
echo
echo "Right output is 'Error'."
echo
echo "Write an action with one or several spaces before the action: (for example: ' pb')"
./checker 1 2 3 42 420 666
echo
echo "Write an action with one or several spaces after the action: (for example: 'pb ')"
./checker 1 2 3 42 420 666
echo
echo
echo
echo "Press enter to move forward."
read
# Error management 7
clear
echo "Checker program - Error management"
echo
echo "7th test: Run checker with only numeric parameters including one
smaller than MIN_INT."
echo
echo "Test input: ./checker 1 2 3 4 -2147483649"
echo
echo "Right output is 'Error'."
echo
echo "User output:"
./checker 1 2 3 4 -2147483649
echo
echo
echo
echo "Press enter to move forward."
read
# FALSE TESTS
clear
echo "Checker program - False tests"
echo
echo "In this section, we'll evaluate the checker's ability to manage
a list of instructions that doesn't sort the list. Execute the
following 2 tests. If at least one fails, no points will be awarded
for this section. Move to the next one."
echo
echo "Don't forget to press CTRL+D to stop reading during the
intruction phase."
echo
echo
echo
echo "Press enter to move forward."
read
# False tests 1
clear
echo "Checker program - False tests"
echo
echo "First test: Run checker with the following command '$>./checker 0 9 1 8 2
7 3 6 4 5' then write the following valid action list [sa, pb, rrr]."
echo
echo "Test input: ./checker 0 9 1 8 2 7 3 6 4 5"
echo
echo "Right output is 'KO'."
echo
echo "Write the following valid action list [sa, pb, rrr]:"
./checker 0 9 1 8 2 7 3 6 4 5
echo
echo
echo
echo "Press enter to move forward."
read
# False tests 2a
clear
echo "Checker program - False tests"
echo
echo "Second test (1/3): Run checker with a valid list as parameter of your choice then
write a valid instruction list that doesn't order the integers.
Checker should display 'KO'. You'll have to specifically check
that the program wasn't developed to only answer correctly
on the test included in this scale. You should repeat this
test couple of times with several permutations before you
validate it.."
echo
echo "Test input: ./checker 666 0 -42 200 -420 420 500"
echo
echo "Right output is 'KO'."
echo
echo "Write the following action list [ra]:"
./checker 666 0 -42 200 -420 420 500
echo
echo
echo
echo "Press enter to try again."
read
# False tests 2b
clear
echo "Checker program - False tests"
echo
echo "Second test (2/3): Run checker with a valid list as parameter of your choice then
write a valid instruction list that doesn't order the integers.
Checker should display 'KO'. You'll have to specifically check
that the program wasn't developed to only answer correctly
on the test included in this scale. You should repeat this
test couple of times with several permutations before you
validate it.."
echo
echo "Test input: ./checker 666 0 -42 200 -420 420 500"
echo
echo "Right output is 'KO'."
echo
echo "Write the action list of your choice (that doesn't order the integers):"
./checker 666 0 -42 200 -420 420 500
echo
echo
echo
echo "Press enter to try again."
read
# False tests 2c
clear
echo "Checker program - False tests"
echo
echo "Second test (3/3): Run checker with a valid list as parameter of your choice then
write a valid instruction list that doesn't order the integers.
Checker should display 'KO'. You'll have to specifically check
that the program wasn't developed to only answer correctly
on the test included in this scale. You should repeat this
test couple of times with several permutations before you
validate it.."
echo
echo "Test input: ./checker 1 2 3 4"
echo
echo "Right output is 'KO'."
echo
echo "Write the action list of your choice (that doesn't order the integers):"
./checker 1 2 3 4
echo
echo
echo
echo "Press enter to move forward."
read
# RIGHT TESTS
clear
echo "Checker program - Right tests"
echo
echo "In this section, we'll evaluate the checker's ability to manage
a lists of instructions that sort the list. Execute the
following 2 tests. If at least one fails, no points will
be awarded for this section. Move to the next one."
echo
echo "Don't forget to press CTRL+D to stop reading during the
intruction phase."
echo
echo
echo
echo "Press enter to move forward."
read
# Right tests 1
clear
echo "Checker program - Right tests"
echo
echo "First test: Run checker with the following command '$>./checker 0 1 2'
then press CTRL+D without writing any instruction."
echo
echo "Test input: ./checker 0 1 2"
echo
echo "Right output is 'OK'."
echo
echo "Press CTRL+D without writing any instructions:"
./checker 0 1 2
echo
echo
echo
echo "Press enter to move forward."
read
# Right tests 2
clear
echo "Checker program - Right tests"
echo
echo "Second test: Run checker with the following command '$>./checker 0 9 1 8 2'
then write the following valid action list [pb, ra, pb, ra, sa, ra, pa, pa]."
echo
echo "Test input: ./checker 0 9 1 8 2"
echo
echo "Right output is 'OK'."
echo
echo "Write the following action list [pb, ra, pb, ra, sa, ra, pa, pa]:"
./checker 0 9 1 8 2
echo
echo
echo
echo "Press enter to move forward."
read
# Right tests 3a
clear
echo "Checker program - Right tests"
echo
echo "Third test (1/3): Run checker with a valid list as parameter of your choice then
write a valid instruction list that order the integers. Repeat 3 times."
echo
echo "Test input: ./checker 0 1 2 3"
echo
echo "Right output is 'OK'."
echo
echo "Write the action list of your choice (that order the integers):"
./checker 0 1 2 3
echo
echo
echo
echo "Press enter to try again."
read
# Right tests 3b
clear
echo "Checker program - Right tests"
echo
echo "Third test (2/3): Run checker with a valid list as parameter of your choice then
write a valid instruction list that order the integers. Repeat 3 times."
echo
echo "Test input: ./checker 0 1 2 3"
echo
echo "Right output is 'OK'."
echo
echo "Write the action list of your choice (that order the integers):"
./checker 0 1 2 3
echo
echo
echo
echo "Press enter to try again."
read
# Right tests 3c
clear
echo "Checker program - Right tests"
echo
echo "Third test (3/3): Run checker with a valid list as parameter of your choice then
write a valid instruction list that order the integers. Repeat 3 times."
echo
echo "Test input: ./checker 0 1 2 3"
echo
echo "Right output is 'OK'."
echo
echo "Write the action list of your choice (that order the integers):"
./checker 0 1 2 3
echo
echo
echo
echo "Press enter to move forward."
read
PUSH_SWAP TESTS

PUSH_SWAP - IDENTITY TESTS
clear
echo "Push_swap - Identity tests"
echo
echo "In this section, we'll evaluate push_swap's behavior when
given a list, which has already been sorted. Execute the
following 3 tests. If at least one fails, no points will be
awarded for this section. Move to the next one."
echo
echo
echo
echo "Press enter to start testing."
read
# IDENTITY TEST 1
clear
echo "Push_swap - Identity tests"
echo
echo "First test: Run the following command '$>./push_swap 42'. The program
should display nothing (0 instruction)."
echo
echo "Test input: ./push_swap 42"
echo
echo "Right output is display nothing and give the prompt back."
echo
echo "User output:"
./push_swap 42
echo "This is the next line."
echo
echo
echo
echo "Press enter to move forward."
read
# IDENTITY TEST 2
clear
echo "Push_swap - Identity tests"
echo
echo "Second test: Run the following command '$>./push_swap 0 1 2 3'. The
program should display nothing (0 instruction)."
echo
echo "Test input: ./push_swap 0 1 2 3"
echo
echo "Right output is display nothing and give the prompt back."
echo
echo "User output:"
./push_swap 0 1 2 3
echo "This is the next line."
echo
echo
echo
echo "Press enter to move forward."
read
# IDENTITY TEST 3
clear
echo "Push_swap - Identity tests"
echo
echo "Third test: Run the following command '$>./push_swap 0 1 2 3 4 5 6 7 8 9'.
The program should display nothing (0 instruction)."
echo
echo "Test input: ./push_swap 0 1 2 3 4 5 6 7 8 9"
echo
echo "Right output is display nothing and give the prompt back."
echo
echo "User output:"
./push_swap 0 1 2 3 4 5 6 7 8 9
echo "This is the next line."
echo
echo
echo
echo "Press enter to move forward."
read
# PUSH_SWAP - SIMPLE VERSION
clear
echo "Push_swap - Simple version"
echo
echo "If the following test fails, no points will be awarded
for this section. Move to the next one."
echo
echo
echo
echo "Press enter to start testing."
read
# SIMPLE VERSION 1
clear
echo "Push_swap - Simple version"
echo
echo "First test: Run '$>ARG='2 1 0'; ./push_swap $ ARG | ./checker $ ARG'.
Check that the checker program displays 'OK' and that
the size of the list of instructions from push_swap is
2 OR 3. Otherwise the test fails."
echo
echo "Right output: Checker program should display 'OK' and size of list
instructions from push_swap is 2 OR 3."
echo
echo "User instructions from push_swap:"
./push_swap 2 1 0
echo "User output from checker:"
arg="2 1 0"; ./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to move forward."
read
# ANOTHER SIMPLE VERSION
clear
echo "Push_swap - Another simple version"
echo
echo "Test the program with 5 random integers."
echo
echo "Execute the following 2 tests. If at least one fails,
no points will be awarded for this section. Move to
the next one."
echo
echo
echo
echo "Press enter to start testing."
read
# ANOTHER SIMPLE VERSION 1
clear
echo "Push_swap - Another simple version"
echo
echo "First test: Run '$>ARG='1 5 2 4 3'; ./push_swap $ ARG | ./checker $ ARG'.
Check that the checker program displays 'OK' and that
the size of the list of instructions from push_swap isn't more than 12.
Kudos if the size of the list of instructions is 8."
echo
echo "Right output: Checker program should display 'OK' and size of list
instructions from push_swap isn't more than 12."
echo
echo "User instructions from push_swap:"
./push_swap 1 5 2 4 3
echo "User output from checker:"
arg="1 5 2 4 3"; ./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to move forward."
read
# ANOTHER SIMPLE VERSION 2a
clear
echo "Push_swap - Another simple version"
echo
echo "Second test (1/3): Run '$>ARG=''<5 random values>''; ./push_swap $ ARG |
./checker $ ARG' and replace the placeholder by 5 random
valid values. Check that the checker program displays 'OK'
and that the size of the list of instructions
from push_swap isn't more than 12. Otherwise this test fails.
You'll have to specifically check that the program
wasn't developed to only answer correctly on the test
included in this scale. You should repeat this test
couple of times with several permutations before you validate it."
echo
echo
echo "Give five random values and press enter:"
read arg
echo
echo "Right output: Checker program should display 'OK' and size of list
instructions from push_swap isn't more than 12."
echo
echo "User instructions from push_swap:"
./push_swap $arg
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# ANOTHER SIMPLE VERSION 2b
clear
echo "Push_swap - Another simple version"
echo
echo "Second test (2/3): Run '$>ARG=''<5 random values>''; ./push_swap $ ARG |
./checker $ ARG' and replace the placeholder by 5 random
valid values. Check that the checker program displays 'OK'
and that the size of the list of instructions
from push_swap isn't more than 12. Otherwise this test fails.
You'll have to specifically check that the program
wasn't developed to only answer correctly on the test
included in this scale. You should repeat this test
couple of times with several permutations before you validate it."
echo
echo
echo "Give five random values and press enter:"
read arg
echo
echo "Right output: Checker program should display 'OK' and size of list
instructions from push_swap isn't more than 12."
echo
echo "User instructions from push_swap:"
./push_swap $arg
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# ANOTHER SIMPLE VERSION 2c
clear
echo "Push_swap - Another simple version"
echo
echo "Second test (3/3): Run '$>ARG=''<5 random values>''; ./push_swap $ ARG |
./checker $ ARG' and replace the placeholder by 5 random
valid values. Check that the checker program displays 'OK'
and that the size of the list of instructions
from push_swap isn't more than 12. Otherwise this test fails.
You'll have to specifically check that the program
wasn't developed to only answer correctly on the test
included in this scale. You should repeat this test
couple of times with several permutations before you validate it."
echo
echo
echo "Give five random values and press enter:"
read arg
echo
echo "Right output: Checker program should display 'OK' and size of list
instructions from push_swap isn't more than 12."
echo
echo "User instructions from push_swap:"
./push_swap $arg
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to move forward."
read
# PUSH_SWAP - MIDDLE VERSION
clear
echo "Push_swap - Middle version"
echo
echo "Test the program with 100 random integers."
echo
echo "If the following test fails, no points will be awarded
for this section. Move to the next one."
echo
echo
echo
echo "Press enter to start testing."
read
# PUSH_SWAP - MIDDLE VERSION 1
clear
echo "Push_swap - Middle version"
echo
echo "First test (1/5): Run ''$>ARG=''<100 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 700:	5
- Less than 900:	4
- Less than 1100:	3
- Less than 1300:	2
- Less than 1500:	1"
echo
echo
echo "Give 100 random values and press enter:"
read arg
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# PUSH_SWAP - MIDDLE VERSION 2
clear
echo "Push_swap - Middle version"
echo
echo "First test (2/5): Run ''$>ARG=''<100 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 700:	5
- Less than 900:	4
- Less than 1100:	3
- Less than 1300:	2
- Less than 1500:	1"
echo
echo
echo "Give 100 random values and press enter:"
read arg
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# PUSH_SWAP - MIDDLE VERSION 3
clear
echo "Push_swap - Middle version"
echo
echo "First test (3/5): Run ''$>ARG=''<100 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 700:	5
- Less than 900:	4
- Less than 1100:	3
- Less than 1300:	2
- Less than 1500:	1"
echo
echo
echo "Give 100 random values and press enter:"
read arg
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# PUSH_SWAP - MIDDLE VERSION 4
clear
echo "Push_swap - Middle version"
echo
echo "First test (4/5): Run ''$>ARG=''<100 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 700:	5
- Less than 900:	4
- Less than 1100:	3
- Less than 1300:	2
- Less than 1500:	1"
echo
echo
echo "Give 100 random values and press enter:"
read arg
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# PUSH_SWAP - MIDDLE VERSION 5
clear
echo "Push_swap - Middle version"
echo
echo "First test (5/5): Run ''$>ARG=''<100 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 700:	5
- Less than 900:	4
- Less than 1100:	3
- Less than 1300:	2
- Less than 1500:	1"
echo
echo
echo "Give 100 random values and press enter:"
read arg
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to move forward."
read
# PUSH_SWAP - ADVANCED VERSION
clear
echo "Push_swap - Advanced version"
echo
echo "Test the program with 500 random integers."
echo
echo "If the following test fails, no points will be awarded
for this section. Move to the next one."
echo
echo "In this section we'll use hard coded sets of random integers (by random.org).
If you like to use your own sets, you need to do this yourself."
echo
echo
echo
echo "Press enter to move forward."
read
clear
# PUSH_SWAP - ADVANCED VERSION 1
clear
echo "Push_swap - Middle version"
echo
echo "First test (1/5): Run ''$>ARG=''<500 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 5500:	5
- Less than 7000:	4
- Less than 8500:	3
- Less than 10000:	2
- Less than 11500:	1"
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
arg="181629719 -261077236 -327075565 392980651 -892046755 -476661260 -268476237 -472785279 -693083564 406414796 835993532 801841125 705600130 -757511235 586378458 -129398561 221028014 -843964011 969265629 666883018 19527925 -948110487 632828887 339805998 219893713 -430319415 -657103028 -543077705 814913306 396354810 -797116081 492797252 146726982 -567486738 -747320181 94672320 653900178 553323046 -340877866 -936015801 -679775925 -426475051 -219483894 -654670817 592938988 -740064006 -350177168 783528465 905928397 934856317 350984396 996220293 976324395 -219800371 -700542595 75358783 767608052 -760311455 230035613 604923768 -754753259 -985621029 385145056 -664544407 689628102 -837679429 359542164 -306882620 -819083564 287491323 -103898481 967545499 423938500 -127089437 153468017 -460606199 -533868842 869650635 -958863909 -179300191 -159925835 -223756860 152937027 964384258 56855073 803813014 806585603 894908158 -76163331 42461363 87193574 258098673 -175236379 169999309 -265143508 234392239 629271097 -416737372 832137216 -548643307 525025664 748015961 254850936 262238960 -602397811 335481181 -148500883 436570964 138337257 -468598586 146084882 -254025130 -797491852 -518938316 -902992039 998655954 -48836029 57403015 515531487 -373337657 -65258921 510753987 557973146 265674603 -345952219 43835300 -464720106 -147309344 752946367 145734574 -18163185 631716812 -444355529 810966762 -421931248 -576359827 -342709418 523095345 327888808 -444217913 -183313837 419171332 117394627 -631880657 -794594061 723478814 -11497749 669977992 -334942801 786644223 72714628 825501540 308973572 431311387 185497910 250940982 123285286 -290789152 311228699 421317257 -314581848 249325156 641672473 -408464023 594671977 40569478 473341701 -536637667 -298874760 559181933 970545118 -595370599 -72993880 397506171 465645136 -944442337 81872411 443197151 284446617 137019210 -860292176 784248966 -970445740 -243341856 -847916507 480521753 -285956251 733761615 661019000 -182181313 -514130917 -80614980 724320561 73001389 92437276 -609940879 482321818 741002654 806673276 894333299 -767096841 70503367 220843229 333318938 820202437 -198970233 -6080429 506435080 4251735 527204139 619961150 597855628 620421340 922396031 -615723011 -901914940 619369774 683969940 -694296703 937207440 -110254038 -487541789 -979453255 -194792420 719040567 139880993 -564695012 241568595 455890995 314049802 -752742744 670798132 -370320832 945881414 372970386 5148442 196588513 996199486 75705613 685089203 929239260 -220152244 374309101 837158850 48023962 592464180 -739443984 823960581 -424968648 927304442 -718144386 -499023076 269555081 -449671904 86233162 -280719826 -967417161 -389908218 -314435827 -548210339 935754703 304170807 -181153019 -420202957 781383954 120132344 -944887551 -101661057 -98332637 959777946 -63745793 862594658 -90094880 282814475 568445697 893355558 -181892396 -459883386 -401172697 -139118072 573583799 672631637 639118962 -547218805 27041065 546963086 -253242865 -240791430 -236326720 731659715 966910458 215565463 -444025092 -458913454 -727786098 590165081 -249437205 -165878643 586165913 -647369574 429762168 592868239 176653326 -976834416 777712738 137829721 -576381346 356936024 366881186 -710299397 -527705209 -203600684 388136145 213648959 -913684066 -333432948 353615179 -683172315 -952543473 368404469 -887540812 783971329 -851000590 497777263 604940177 370942845 -641861312 -962850393 -126785948 -775012105 924624234 -652004813 861427653 201923079 -177748385 -730592909 -58653257 -695281312 -796414057 -175885617 495852047 -195142739 -78335021 -411316222 263939806 428063695 -668365002 961010079 -513054458 -447365234 494362976 -140556262 95372892 -936470696 722875573 -320707251 -737633395 -51563870 -524173460 -482240094 -769710618 -421725035 106377282 -200254385 -984857197 266042871 837470306 -344622153 656326655 -966536853 208327801 257681794 777608222 -480870878 -810451299 -941349618 -221966974 327817937 465044675 -695764634 723405906 957127871 519234531 -968020140 72773837 -199670592 -465790010 -392895918 637876316 2195801 -820424062 -872859695 -753147374 -167795071 405610390 154710992 358784976 -441477635 250218380 596413976 -721542518 -376943614 356962054 934105434 -166408635 958565230 746638069 715052538 76249289 -986956065 -612661815 385156516 -513571245 -156962110 469777782 445430400 479889340 818621210 -845803085 -989547084 -889830061 957625405 931057338 183825159 10953013 -627066666 910380547 -709042508 980264244 513746245 -624706014 544481425 36603466 601364743 943750829 872701354 -948668956 962056915 152431918 -705839561 -563272374 -503686411 -474606216 -806336510 -772285694 -588611506 -3273539 -129743198 361843287 152566064 68933756 792779259 -554014506 506580572 -183197617 -948834387 -671951633 -672754676 -575917769 -11985340 554736654 624814800 -654105395 -90700993 -100314732 833452744 324817576 -535233587 -572027059 -343477974 -370624518 930711427 626745596 361217446 849950813 -635987311 -409427076 702114300 -782125745 -760382008 -802104770 -379060115 -349874428 614570568 685276244 -265443080 244155169 -629661043 703483669 871899071 707926908 -590744717 787729160 -18497657 -189114350 128387439 55097219 348010161 558723972 -12633297"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# PUSH_SWAP - ADVANCED VERSION 2
clear
echo "Push_swap - Middle version"
echo
echo "First test (2/5): Run ''$>ARG=''<500 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 5500:	5
- Less than 7000:	4
- Less than 8500:	3
- Less than 10000:	2
- Less than 11500:	1"
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
arg="241219036 37454006 882005967 306726182 623218773 187821964 536505791 -980018333 249387816 -79006159 -433669648 364253322 -239337312 -20710578 -18703460 -936723177 -701040325 -951268538 -949708820 438649674 606378643 -579382456 -139760240 -722894193 127371830 -485177988 69333693 -757819352 -216649065 620784352 49217263 -370908160 545319528 11674650 -456656251 -232766849 172298273 -511993964 517444447 -992712793 611614355 804226037 358770402 -823001126 224373738 141633999 787580753 -174111232 -897651371 -908381803 76593383 773603740 -523744984 83324065 927681405 423529066 -106189220 676038319 -832417886 888353959 395442164 -260823769 -371966269 -809999133 -393759214 306464183 303325276 -962392619 -199693363 -113383558 993739697 501065538 397542258 -954228674 -208908447 475609504 -704990890 -255758663 -515280907 30860208 121898189 -425054259 -327378365 -62599187 -310983656 -518406429 565734570 -571713287 648916793 -897629692 774872831 465787812 -53137491 448309617 -369698897 911495674 -738439654 950459367 54859733 148192 -803350849 -941933315 -138225923 768660766 848980505 76042093 757402073 -47615184 580418881 84528553 686768857 836936433 -766002970 -853287052 -529225828 -579668072 -178054775 520760383 606754397 216397999 -703619563 -931763162 738879969 313404211 -559990767 -310716486 443257614 747672884 899264358 -66140458 771833438 321963790 80756335 -469352799 -68676033 -789280039 -887166876 -181245771 -799361981 -734990506 -346266585 987419993 -980563705 -304062706 402297398 883539961 -301313817 845147547 423677222 -293822075 318547724 471381997 -144251227 243023137 -49616696 -210139005 929476205 491632357 10602328 352165335 187809890 -414970003 -836561228 -249149428 -803158063 -259643636 683487767 272807803 591169622 311136364 -535391286 354350516 38279704 -694621517 -56560314 -60517108 232267270 97152023 -974538203 -123181696 393612479 48085988 910362131 -297065529 726979603 222166677 -61532067 786642198 -256653438 -665278625 -300694930 -915368554 -442144941 981832425 -678299563 554614608 -97598763 -572397036 -301951368 95463872 870696282 -30184805 -112368335 -897768616 -717448594 -722187491 -526553247 -362393909 324210383 50295608 265381103 65698949 -585158888 -607374789 -426803192 911058709 -977175720 241876926 691989891 363024876 -193016352 243380465 -660794384 110790271 -903645658 -460546795 -843844713 934799461 -921943092 312959046 -976858961 -248870718 -18460689 -35945522 574974156 73659414 -896394886 -743491223 629121526 798107469 -856340774 -135643135 478934077 36627727 156625006 10067769 421223228 432796083 -205653431 -877461493 350423818 539497018 385996804 873664373 -569545222 410393548 806950098 -614187612 -613153088 -226216032 -658149215 685343556 866059348 -539663545 -336034511 200697828 -587648013 504254981 -963553055 -565731464 -886866377 239556972 -407329498 272638954 983680083 310392595 -49247521 890111137 -110686800 -992728257 -122559021 717129452 -73883547 637678269 496636984 234632009 -217707858 341562387 440599364 -646710851 93959568 974052514 -953979897 652930920 -101709444 -183468288 -970404434 23099332 -266204463 880144215 -463867416 675529294 895466319 228741163 156532071 665198560 -761851016 -952860280 -373632889 -258300445 -120295113 -893809723 735737831 804065818 694494940 714937906 -962291228 -792514348 860989824 -655072974 -528944926 501030329 -847091537 115126345 55271896 -182226963 -811364067 202024369 -875207512 -981884572 455692490 -753662674 138511598 540808881 -471225015 -616884115 64399399 903608093 186640967 -826594748 -797757608 654370935 -559431160 100440213 972073030 -367343666 841333367 -190753940 734802070 879879819 302687120 -764378257 -594045078 116451417 233162561 479477016 -393394358 197994190 998907391 569324813 -490136572 -83778939 550925272 -830072274 789538162 -512539760 634315091 -385418919 -683972483 -896846442 -831938996 -94429421 69381166 467833712 935626363 653868326 -933714374 677864661 -314109237 -508156947 -832063745 -479596762 -832730795 -633218219 -916343095 -274306419 524184037 -385705816 489410390 365034972 803857095 -741525400 -977091874 952501183 797335203 -720327820 -881371413 938539334 -813229640 178392721 -454137076 -232851314 56487698 -842357882 96320240 231165686 658527175 342963011 160871586 -904429996 234660534 -928940803 176111797 -13660019 -800743792 648521586 453940084 -430078904 -393239274 619760211 -882490717 -264186784 989639754 -43296126 31559714 997895159 -50063223 598003586 534759275 628418032 242264472 380799727 -107416453 -373743426 59499338 967871519 -552634818 347830608 -608577084 781728284 -324282963 -927412734 -14627044 -754978975 -48427542 382608486 531741653 -339520289 -690693496 941939256 989879837 -748793199 -770711808 -10819350 145249475 -658252158 -482823432 69409803 -241890170 879437338 299781867 404919995 -941779281 -468766848 -887919355 949714938 138039957 49844849 -780560442 461222276 410255603 942467898 133188440 384159537 -537667671 707324271 -768046277 -941089571 -458627575 -353420935 901024961 906273677 -704036119 -814656304 -224501818 996142236 232613658 158329951 -902374265 426728506 321766807 -814977407 649229048 577007719 350444749 -933012949 -300368982 -926236974 916668387 388758323"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# PUSH_SWAP - ADVANCED VERSION 3
clear
echo "Push_swap - Middle version"
echo
echo "First test (3/5): Run ''$>ARG=''<500 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 5500:	5
- Less than 7000:	4
- Less than 8500:	3
- Less than 10000:	2
- Less than 11500:	1"
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
arg="-308682455 -899284287 68042684 -775056788 -929363055 83257823 -872423787 -991183664 -457238344 661187299 242663989 -974323782 463566421 811027990 673669676 564646659 -563468635 201523653 -89202399 542508907 -420044598 -891781477 905702384 -805298659 -908947743 850069582 228975231 809808190 285067259 -588970230 620595705 -589956813 988784037 -393518497 921709141 644687386 912853709 997266877 477263767 300849607 919041383 529566384 -634425918 -971632649 283795757 -887572265 659837635 643478521 29696029 -846137985 -807077862 -796472126 304863713 911997971 477640173 -408513656 -755789810 114055656 749725360 997367202 933433690 852676780 -202144272 -593671855 332255360 -904220480 -286535222 496768167 -188815857 -379630096 -935079918 705884189 -942753791 -156129555 777166415 -613138814 -377826131 -15913571 -925880974 167687140 867754261 -427084166 274245292 -365136262 -20093001 264488732 -174373690 -703020029 757576615 -446546439 -798504270 -642659963 -745762261 597603755 532769229 391381653 343539655 -259431519 -827560673 275398380 907735762 -937428472 -123356225 216397506 -419645952 951894525 -579155524 -35904610 -695265141 645314231 451125733 -89818286 859387014 -848639536 -407307926 -124610914 975303225 -200538509 871389601 -437404749 507631453 703509000 642682002 589982535 -791721811 -914258717 -293680014 -652033376 -251707070 50928811 -609318122 885346763 -824310056 977472493 975507988 -277489374 371357723 -886655045 -298173532 468471452 88307465 -106996072 -342659703 -498604881 569760076 292817149 -402778678 -498596654 261373861 419622932 835788216 -476432808 208681939 927536369 -525857122 745345946 617844312 219040376 239200760 -558679693 -92909415 -896886773 -318695426 759591287 -998507058 632015496 -577214170 -596802664 -799607133 875626031 811756074 642015113 -729101388 158448386 243763112 232296628 -282031635 -798781013 -371592326 2712535 -122301182 719572794 -204293455 -59649617 862663090 -40803206 -663477014 -577658658 -557952532 639988600 -194051283 -894309215 -852718791 -448529268 598626148 -757333129 -491905179 998625501 308118977 -287769835 700039047 -49297803 -916455360 211312649 -376506396 951617665 47058920 626099134 -855734404 -347005840 -833240194 -440315097 -348985663 -712299203 -258079930 936237590 -120499092 383191605 67802975 504788142 -94711097 790452717 921479462 -384863247 165828087 709847121 679650414 -124660632 -832969490 -123371839 808372129 165827385 464945503 -972243347 516780874 -244033050 -544160376 681493959 -413985664 -897092289 -984391882 -625323131 53000678 -788498293 -96538522 -403140991 308713747 386699365 678775402 -129021005 -106552091 753119013 655367659 -353266013 -975500057 -249391073 -24165110 -588505939 -87938704 -216948122 -337818020 442849201 120307591 448667763 637192984 653786893 450085481 221765161 82013490 417157821 936515483 -253581141 -266812212 -598838473 -922339501 206873747 508509670 -878842718 -848511380 881900430 352727621 481883432 -99612432 134612592 -550065532 -293091081 622198825 84740796 -818461920 -323950327 888469725 804539981 523711583 807445050 -799763557 -212312331 -557735168 -927463073 835341118 489684839 -892897769 993913004 -487205482 -598547745 801852096 -321806245 -849516749 210155041 -85345859 -627859915 -471237292 684722207 -882629586 325720138 748589297 -439847952 -179614770 -227789515 -199371475 786596701 745018635 394813321 -123895806 263243093 -173844449 853530430 107035871 -769867454 -176105476 -816719146 954703520 798063250 530660323 -448943828 417535008 -316951734 832727338 -646223380 -692931100 -260802178 -700454057 -699900254 251605744 709592487 909844435 -449895449 872725018 344449556 -154587898 -311856577 227871621 -323978887 578297359 -617645384 -892207223 -990548549 -734395993 451631736 -551088126 -510933967 -772086878 -114213545 -374823432 -69693907 87225241 -280319991 363374274 -147803650 -57843943 -897044125 -904012173 -987622083 -140211064 915429447 504920879 713341040 970270749 657756185 975164111 -49812562 -237171263 121173278 -378401503 357849118 253715826 -238439605 333622619 666295421 894280989 -886380280 -352623728 -898894509 84012335 17051598 451097800 212662204 984978212 -619062524 793278427 200314153 -936503271 -591595187 -598519142 -101015714 -149917740 -865389650 -283744595 -923605980 928758407 681254767 753085355 31487928 -787243334 -503803200 654046897 388237807 531843132 -324894557 89037264 -55937619 819388022 -693135211 -418440729 678215417 322012734 -984294512 -290836050 -767578858 -671321665 -23864003 -855251289 -987753776 -870752406 780932372 778563208 -107228447 -299778459 505657107 -752701809 -793561396 -444314888 -681980248 -475286429 -896294718 891374797 -187242137 732980415 529701620 506926146 65930049 -489780747 283911722 926545926 594289192 620084504 -945885120 -710419872 -829381547 347737092 64599234 337702686 -933136823 -121215288 836364481 775839016 -878557609 39480095 391487407 109095962 62472165 -969642486 85381945 -589532565 262681892 718341726 -930265552 -677416100 863134621 -129595321 -225142686 438202843 -756348274 766967803 407613156 -783622456 634476681 515055320 365369575 -252629257 -70037886 803973149 -779468997 180895511 -717656675 -261695241 141894985 -425157796 -197650736 -333509653 530176545"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# PUSH_SWAP - ADVANCED VERSION 4
clear
echo "Push_swap - Middle version"
echo
echo "First test (4/5): Run ''$>ARG=''<500 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 5500:	5
- Less than 7000:	4
- Less than 8500:	3
- Less than 10000:	2
- Less than 11500:	1"
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
arg="-791073529 594251200 499617387 960078351 426446824 -64519907 321997423 -80899827 945408963 -110033750 683273147 403194734 438672287 822161687 576526273 -342917445 -354594973 550608041 452756308 -223629385 563245709 280723271 -76820541 331947365 -957733373 125213409 -635109389 -232574906 332933881 711509047 986252053 478335806 -442805284 -64959822 655419494 204551151 -711633939 -568379649 738820817 838769762 449956541 407207052 -64966725 465358800 -902799382 386111115 662033558 68992333 -388134561 -130512167 -160930780 782030879 35330248 -149945014 -283393646 437194724 -763364109 -452388285 -17941262 -656360879 975579209 -28534112 -666943280 -235713326 942067685 514705594 -239326579 971533611 951709462 -410093894 -938933934 -842003083 -133049525 53442830 307306971 -894501664 924571747 -911158887 648969098 -84317559 -312177235 -240678223 970822336 348710181 499800472 882574073 -281647419 -2930282 -104718433 166698199 37021240 465390033 -607572631 -462444478 -528920311 -8778211 -323660260 -989038532 62388069 -323534116 -381257995 102335632 424542885 -131597461 517252763 -319825224 206771828 -142928523 296480173 737589892 117697091 648459829 72340852 -86164891 889167091 -55588605 -289477467 -487867967 -537291227 -852951565 -630806898 -657162202 146941376 -213619351 -557748658 706516390 -373111609 -978648609 25683948 531183167 -243606494 -553850353 811984657 -307626628 568802206 -266409972 -130203496 670659576 -427385319 -116109034 361432538 580569987 536316418 742542671 -43981192 -167702285 455853270 -935952343 747983854 -788439523 -690799972 480388681 836197062 -279292426 531334102 602282048 -788052349 413105537 868769176 198198162 382813334 218999674 -234799425 870508268 -703017959 82898427 -650227091 155830014 -437653998 898086590 -928739763 -699584092 93844188 914598883 931700364 322912821 -82342350 418085237 -119085073 570711690 125133798 -77707538 246068892 363977198 814371799 893137419 -438397060 -223347869 -586155586 911222362 -38043938 14076305 128454121 -984916375 -820895473 -339671165 621773949 735107060 22576430 668453431 -523817594 -830799033 759954015 -148774194 -701307990 726164624 -865282633 -83372749 -679584146 417305511 -994153485 -932433385 536978648 -474689562 650520400 211831100 -691425106 184272698 -53486273 -159969475 464124239 -759471504 -833210610 769752702 -511281503 -648825595 -816687654 51622383 -94941009 298765564 507269535 -345956264 -990328024 195610299 -535200540 -820284207 7534742 -563748903 953389918 -989081334 -397929060 818896512 770732137 -983710502 378102618 388798699 796159000 -455073087 526689886 -372016420 -297986130 -199187961 -921309969 47068392 117801711 -872091618 457766235 626399493 -11268571 178721469 803292466 330158022 977403139 722338303 641768067 -994296325 -99724949 -296035910 -147521455 810821817 841213534 -295660825 -158526669 84615457 910429219 976644096 204008647 866436488 976451038 428249980 895486554 337552416 -994583717 786390969 -868121726 -278332315 -478143764 -812840559 -932469695 -602729277 -794061396 344324475 -343564306 -829858378 -534988278 -653302681 212230265 -815129516 -889204322 638207509 -438972714 95439233 -408770885 341863571 -615441166 -361317835 -545934468 -869274639 752037742 910350944 -169553615 -747154536 -248651071 -381117312 -172029302 226395989 -72262717 367356515 -146658738 746484585 223187913 167917720 420645651 -133081620 16281046 -148897373 414203711 310170487 200313720 -798307609 736269560 985217124 374853508 -626554479 -366359958 -764379099 341285904 464113446 397016936 -104013160 -289701898 939557726 128111811 -52405493 -563102870 875354287 -364685343 -834018247 862987649 307515336 631146684 -497781585 -125069234 889644586 -897305463 263768136 -46192411 -263794811 -911888017 783253980 767316201 665759915 -600224818 -946944061 577131800 574079912 188894187 -851677935 -85140872 520455253 156778755 715303652 -625389476 -85688780 876979078 328796533 -931318123 -59588699 732642289 257442420 -594786831 -681001942 -549766051 79366984 -713826715 475375247 -763798829 -849176315 971503298 -869900059 645929574 269067428 -403149657 557109579 880373044 -996456935 946129806 -391752857 -603402998 123727453 -77863919 -106645432 -848293319 -352451269 -621264433 848156228 -532485044 948546581 930428072 413165352 -925021622 -409828456 -275706187 567213961 -788292131 -514555108 -165597873 520307922 -131135524 750890579 862950655 422960675 817509706 199919374 82071972 -527839035 50653617 891109464 -317440522 -805830365 -570546557 752778140 -797878478 -452119790 -101603104 -988212098 410261499 490406287 -270609463 -493399958 26218690 644461990 793746368 -554905347 743639321 214159264 737752968 365684352 901249489 833679700 -687650092 -769658291 813455415 -272790084 212148808 -400872407 -914990293 700299595 -919542438 -19027470 -936170894 80524459 972799366 -693299931 -667060766 62639832 8466993 666060201 -524550126 486766118 363543374 279408457 -317150638 -914281535 543442750 -561594638 537604583 777634205 -609810002 -129813805 -220286952 -324571751 -197451560 -611279422 -455420452 535695286 646684981 169531887 -595539034 -617350386 -866017623 -927853106 589403259 -235283833 311112458 629407251 -270207526 755366326 -400286861 -859655862"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to try again."
read
# PUSH_SWAP - ADVANCED VERSION 5
clear
echo "Push_swap - Middle version"
echo
echo "First test (5/5): Run ''$>ARG=''<500 random values>''; ./push_swap $ ARG |
./checker $ ARG'' and replace the placeholder by 100 random valid values.
Check that the checker program displays 'OK' and then give a grade based on
the size of the list of instructions:
- Less than 5500:	5
- Less than 7000:	4
- Less than 8500:	3
- Less than 10000:	2
- Less than 11500:	1"
echo
echo "Right output: Checker program should display 'OK' and points
will be awarded based on size of the list of instuctions."
echo
echo "User instructions count from push_swap:"
arg="-657339020 856038820 -490238715 683128433 -129532451 -451441457 -870338693 -897507249 -134510288 895947345 176210446 -363994327 -85329892 593015747 -192926062 592963355 872799644 103286185 -734987115 -14871117 1522335 -215159846 -975930998 994013095 278298358 257523953 -345518996 806101698 774525339 -255672958 -393469836 826808656 174171092 -246411301 -989709907 -434650784 678321609 653366761 654735881 -49294530 213735363 734099934 684594880 -225461664 -872549071 -114446798 -760577285 -397934680 -244370081 -455606816 652124046 -305369661 -798548578 -621316824 -497132684 -740362115 -971290116 -637930062 -374380949 -989270807 20602224 -238939426 685608043 82211244 -248481439 -753021617 -927123964 920470980 493744770 -540718830 -589993960 529080906 -895392740 -252150160 122649082 826455104 107987380 597503266 234433692 -492468858 958187507 -447255522 104501685 -8052204 -471535420 278784300 -488952125 934600175 764423896 -572839909 -623371446 882681440 -627794872 -801630052 670454632 736779613 -798250557 -443301732 531456954 700495920 732668369 -44619792 -884116464 -730319624 950262833 -399119094 279139981 -967469146 -938230670 -264571776 653874383 -688402732 -688029906 -646472655 330449043 -103024407 172761214 259084663 -419621874 -239479036 915204853 -446224940 -655243236 783112331 -826381689 634393859 654541168 977068567 -126140461 -176603750 -713760816 229354451 943498279 -198009314 -634628800 293174487 -909654549 -214124131 228751667 325518344 689472798 -658121088 -167813351 -859654671 100405974 241022925 987749492 -369234996 -80892287 193153011 380569047 -933106282 -56952439 360418238 284630826 779041305 -139835721 941848625 449217650 74622184 650780778 -898610636 -84929527 -138185247 -425108295 152720518 97873424 -209258482 -356788636 292340291 -50078451 -265128559 -868758572 -331365002 36708695 -720078972 -546064444 -417427952 -712642621 535691112 -508175141 36747109 346543979 -941408020 897790525 -830085037 454327004 604399404 120304828 399743750 -226405220 248407818 628372583 -236481694 797580476 -435788408 -224996253 194522686 538237099 -657620948 852020867 -272997449 242924509 761351887 -505398067 -751837046 797009715 97796831 434523771 752546222 917178877 -637858290 -150772116 999888922 604105135 -206582775 -759777359 843341904 815460721 -794248869 913964274 27519473 -680233198 100823328 643081558 -755155873 -210049412 -661953314 324569403 -777085527 568506032 263390846 909325193 -691147586 754229963 -661812150 -712120319 -701469699 630972570 680048367 -493223023 -698072266 744170295 -200768906 505720298 502808840 52395761 -309138707 236038257 596351655 585297745 -386175152 78404683 -857225129 -117912765 -202669305 280707477 -141710478 782401313 -456073235 -345961627 -773527500 57559065 200801495 -128900713 805407290 729785391 -224716842 756642689 86991689 705360222 301056145 683891983 -699398541 -296594147 -22001346 794416337 -947770498 -22005071 902334811 -847432537 590103211 -127678507 -65511464 -337236377 207771117 -858715378 -724402190 425421397 818838211 -413839202 -372715049 131805639 860508899 -247532289 612297759 -969940910 -926961241 -641345674 -564973254 364151661 567722582 277459013 807205812 646650084 303082868 -662686761 163345334 -632397687 -286371239 -460897958 -625783274 -255824627 -946072810 523420399 -164936702 -475095429 -784646834 -651094360 16606335 512193475 9808370 -122897337 544808697 -93586516 974571936 -93992240 92973556 -787793494 274962238 780310353 498578688 207390594 658055087 905255665 392671860 888105122 402582740 -223275599 47465377 -772168365 -395519295 550787489 -864176020 168686253 -374212922 758179482 63939838 300293717 825786185 153400791 -122309752 196944828 348569081 881827225 99488332 -162538646 -382393897 -640673006 394881964 696817281 452797778 120764872 378584613 -670114515 410509087 -341937005 -181903561 786869177 -487289496 552843555 -957659912 -814726246 -111326568 -640174016 370473422 873653003 133254229 -584533470 -420600522 748488628 373819852 -60293617 162236824 -557726820 -420555705 976229042 -313715045 738705801 -845213997 868039495 257689523 358446312 89987458 -342916619 12740629 137111630 588204887 -718702456 -347822436 -756323925 979736262 -933285808 -992159309 -158128124 -602536160 374636579 544918561 52852041 201792341 -948376552 -512799516 973109250 -949705302 -899490907 191076034 699922021 -183703525 -496002108 -248078277 678930640 -459310002 460224890 -594251932 276228671 927724962 506928208 -244894290 -560199468 473721543 5680128 -183703938 -662613106 -146141014 -547795451 -915285690 351731027 4572431 123735431 -18872113 -12191864 144468695 236841720 -307104748 -831733764 -431617331 -610087009 509636096 330782371 -551859505 400252693 283355687 805987503 -149621216 508375639 878145593 111602522 188815400 558814440 -588561016 -995423119 -524667007 432092120 -585057662 -715015828 171094995 -61423809 -386432307 -667067079 57255700 -396528068 -137856111 338202574 -253374917 294195945 863300471 290355490 552436465 -867880925 590447327 204120669 -945788313 -513438148 964457173 187029696 863705419 437393084 -944982059 700019016 -759977835 905826508 -789613097 -80322964 669668293 315363059 101497748 -154091565 227073227 748376316 -209029917"
./push_swap $arg | wc -l
echo "User output from checker:"
./push_swap $arg | ./checker $arg
echo
echo
echo
echo "Press enter to move forward."
read
# END
clear
echo "The end"
echo
echo "All tests are done."
echo
echo "Do not forget to check author file and run norminette!"
echo
echo
echo
echo "Press enter to quit."
read
clear
