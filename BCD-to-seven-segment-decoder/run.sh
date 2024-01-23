#!/bin/bash
echo ""
echo "This run.sh created by NCHU 7111093024 EE715 C.T Hsu "
echo "Used for the CAD from Berkeley SIS > espresso"
echo "------------------------------------------------------------"
echo "1. BCD-to-seven-segment decoder"

echo -e "| A B C D | e | f |" 
echo -e "|-----------------|" 
echo -e "| 0 0 0 0 | 1 | 1 |" 
echo -e "| 0 0 0 1 | 0 | 0 |"
echo -e "| 0 0 1 0 | 1 | 0 |"
echo -e "| 0 0 1 1 | 0 | 0 |"
echo -e "| 0 1 0 0 | 0 | 1 |"
echo -e "| 0 1 0 1 | 0 | 1 |"
echo -e "| 0 1 1 0 | 1 | 1 |"
echo -e "| 0 1 1 1 | 0 | 0 |"
echo -e "| 1 0 0 0 | 1 | 1 |"
echo -e "| 1 0 0 1 | 0 | 1 |"
echo -e "| 1 0 1 0 | 0 | 0 |"
echo -e "| 1 0 1 1 | 0 | 0 |"
echo -e "| 1 1 0 0 | 0 | 0 |"
echo -e "| 1 1 0 1 | 0 | 0 |"
echo -e "| 1 1 1 0 | 0 | 0 |"
echo -e "| 1 1 1 1 | 0 | 0 |"

echo "e = A'B'C'D' + A'B'CD' + A'BCD' + AB'C'D'"
echo "f = A'B'C'D' + A'BC'D' + A'BC'D' + A'BCD' + AB'C'D' + AB'C'D"
echo "------------------------------------------------------------"
echo "Comparing BCD with normal and Don't care approaches"
printf "%-30s %-10s %-10s\n" "Operation" "Time (ms)" "Size"
echo "------------------------------------------------------------"

run_task () {
    local start_time=$(date +%s%N)
    sis < $1 > /dev/null 2>&1  
    local end_time=$(date +%s%N)
    local elapsed_time=$(( ($end_time - $start_time) / 1000000 ))
    local size=$(stat --printf="%s" $2)  
    printf "%-14s %-15s %-10s %-10s\n" "$3" "$4" "$elapsed_time" "$size"
}

run_task "bcd_base.sis" "bcd_base_out.pla" "BCD" "Base"
run_task "bcd_dc.sis" "bcd_dc_out.pla" "BCD" "Don't Care"

run_task "e.sis" "e_out.pla" "'e'" "Base"
run_task "e_dc.sis" "e_dc_out.pla" "'e'" "Don't Care"

run_task "f.sis" "f_out.pla" "'f'" "Base"
run_task "f_dc.sis" "f_dc_out.pla" "'f'" "Don't Care"

echo "------------------------------------------------------------"
echo "Question (a) - simplify by espresso"
echo "For e segment e = A'CD' + B'C'D'"
echo -e "| A B C D | e |" 
echo -e "|-------------|" 
echo -e "| 0 - 1 0 | 1 |" 
echo -e "| - 0 0 0 | 1 |"
echo "For f segment f = A'BC' + AB'C' + A'BC' + A'C'D'"
echo -e "| A B C D | e |" 
echo -e "|-------------|" 
echo -e "| 0 1 0 - | 1 |" 
echo -e "| 1 0 0 - | 1 |"
echo -e "| 0 1 - 0 | 1 |" 
echo -e "| 0 - 0 0 | 1 |"
echo "------------------------------------------------------------"
echo "Question (b) - Get a simpler logic expression"
echo "e = No; e = A'CD' + B'C'D'"
echo "f = Yes"
echo "f = A'BC' + AB'C' + A'C'D'"
echo "f = A'C'(B + D') + AB'C'"
echo "B + D' will always be true since if B = 0, D' = 1"
echo "f = A'C' + AB'C'"
echo "A'C' is true regardless of the value of B"
echo "AB'C'is redundant and can be removed"
echo "f = A'C'"
echo "Question (c) - draw the layout of the PLA."
echo "show in the BCD.pdf."


run_task2 () {
    local start_time=$(date +%s%N)
    sis < $1 > /dev/null 2>&1  
    local end_time=$(date +%s%N)
    local elapsed_time=$(( ($end_time - $start_time) / 1000000 ))
    local size=$(stat --printf="%s" $2)  
    printf "%-14s %-15s %-10s %-10s\n" "$3" "$4" "$elapsed_time" "$size"
}

echo "------------------------------------------------------------"
echo "2. Compare Espresso and Exact Algorithm (QM)"

printf "%-14s %-15s %-10s %-10s\n" "Operation" "QM" "Time (ms)" "Size"
echo "------------------------------------------------------------"

run_task2 "alu4.sis" "alu4_out.pla" "ALU4" "NO" 
run_task2 "alu4_dex.sis" "alu4_dex_out.pla" "ALU4" "YES" 
run_task2 "apex5.sis" "apex5_out.pla" "APEX5" "NO" 
run_task2 "apex5_dex.sis" "apex5_dex_out.pla" "APEX5" "YES"

echo "------------------------------------------------------------"
